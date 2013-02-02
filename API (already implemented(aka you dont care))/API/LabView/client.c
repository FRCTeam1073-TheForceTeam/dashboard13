/////////////////////////////////////////
//
// This example client.c file shows how to display
// an image from RoboRealm within a picture panel.
// See the other API routines in commented out
// code below as to how to use them in LabView
//
// Be sure RoboRealm is running with its API
// (Options->API tab) turned on and set to
// port 6060.
//
/////////////////////////////////////////

#include <tcpsupp.h>
#include <rs232.h>
#include <ansi_c.h>
#include <userint.h>
#include <client.h>
#include <formatio.h>
#include <utility.h>
#include "RR_API.h"

/* Defines */
#define TRUE 1
#define FALSE 0

int nPanelHandle;
int nStatus;

/* Function Prototypes */
void vUIErrorMessage(char *, char *, long);

void main(void)
{
	int iPortNum;
	char szServerName[256];
	char buffer[64];
	char *values[2];
	char valueBuffer[128];
	char *names[2];
	char *results[2];
	char resultBuffer[128];
	char xml[8192];
	int width, height;
	unsigned char image[320*240*3];
	FILE *fp;

	strcpy(szServerName, "localhost");
	iPortNum = 6060;

	/* load user interface panel */
	nPanelHandle = LoadPanel (0, "client.uir", PANEL);
	if (nPanelHandle < 0)
	{
		MessagePopup("Error Message", "LoadPanel() error!");
		return;
	}

	nStatus = DisplayPanel (nPanelHandle);
	if (nStatus < 0)
	{
		MessagePopup("Error Message", "DisplayPanel() error!");
		return;
	}

	if (!rr_connect(szServerName, iPortNum))
	{
		MessagePopup("TCP Client", "Connection to server failed !");
		QuitUserInterface(0);
	}
	else
	{
		SetCtrlVal(nPanelHandle, PANEL_CONNECTED, 1);
	}

	////////////////////////////////////////////////////
	//
	// Begin RR API testing
	//
	////////////////////////////////////////////////////
/*
	// set a custom variable to test
	rr_setVariable("custom_var", "test");

	// read back our custom variable ... should be equal to 'test'
	rr_getVariable("custom_var", buffer, 64);
	if (stricmp(buffer, "test")!=0)
	{
		printf("Error in custom_var");
		getchar();
		exit(-1);
	}

	// delete our custom variable
	if (!rr_deleteVariable("custom_var"))
	{
		printf("Error in delete variable");
		getchar();
		exit(-1);
	}

	// try to get it back again ... should be empty
	rr_getVariable("custom_var", buffer, 64);
	if (buffer[0]!=0)
	{
		printf("Error in delete custom_var");
		getchar();
		exit(-1);
	}

	values[0]=valueBuffer;
	values[1]=&valueBuffer[64];
	names[0]="custom_var_1";
	names[1]="custom_var_2";

	strcpy(values[0], "test1");
	strcpy(values[1], "test2");
	rr_setVariables(names, values, 2);

	// get the both cogx and cogy variable
	memset(resultBuffer, 0 ,sizeof(resultBuffer));
	results[0]=resultBuffer;
	results[1]=&resultBuffer[64];
	if (rr_getVariables("custom_var_1, custom_var_2", results, 128, 2)!=2)
	{
		printf("Error in GetVariables, did not return 2 results");
		getchar();
		exit(-1);
	}
	else
	{
		if (stricmp(results[0], "test1")!=0)
		{
			printf("Error in get/set multiple variables");
			getchar();
			exit(-1);
		}
		if (stricmp(results[1], "test2")!=0)
		{
			printf("Error in get/set multiple variables");
			getchar();
			exit(-1);
		}
	}

	// ensure that the camera is on and processing images
	rr_setCamera("on");
	rr_run("on");

	// get the current image dimention
	rr_getDimension(&width, &height);

	// get the current processed image from RoboRealm and save as a PPM
	if (rr_getImage("processed", image, &width, &height, 320*240*3))
	{
		if (width*height*3>1280*1024*3)
		{
			printf("Processed image width/height error!");
			exit(0);
		}
		rr_savePPM("c:\\temp\\test.ppm", image, width, height);
	}

	// get the current "source" image from RoboRealm and save as a PPM
	if (rr_getImage("source", image, &width, &height, 320*240*3))
	{
		if (width*height*3>1280*1024*3)
		{
			printf("Source image width/height error!");
			exit(0);
		}
		rr_savePPM("c:\\temp\\test2.ppm", image, width, height);
	}

	// we can also grab other variables such as the image_count
	rr_getVariable("image_count", buffer, 64);
	if (atoi(buffer)<=0)
	{
		printf("Error in getting image_count");
		getchar();
		exit(-1);
	}

	// turn off live camera
	rr_setCamera("off");

	// load an image for experimentation
	rr_loadPPM("c:\\www\\RoboRealm\\bin\\remo.ppm", image, &width, &height, 320*240*3);

	// change the current image
	rr_setImage("source", image, width, height, false);

	// add a marker image called mt_new_image
	rr_setImage("my_new_image", image, width, height, false);

	// execute a RGB filter on the loaded image
	rr_execute("<head><version>1.50</version></head><RGB_Filter><min_value>40</min_value><channel>3</channel></RGB_Filter>");

	// get the current RGB_Filter parameter
	rr_getParameter("RGB_Filter", 1, "min_value", buffer, 64);

	// change it to 60
	rr_setParameter("RGB_Filter", 1, "min_value", "60");

	// run a .robo program
	rr_loadProgram("c:\\www\\RoboRealm\\scripts\\red.robo");

	// grab the current running .robo program
	rr_getProgram(xml, 8192);

	// load an image from disk
	rr_loadImage(NULL, "c:\\www\\RoboRealm\\bin\\remo.gif");

	// save that image back to disk .. note that we can switch extensions
	rr_saveImage(NULL, "c:\\temp\\remo.jpg");

	rr_setCamera("on");
	// change the camera to another one
	rr_setCamera("CompUSA PC Camera");
	Delay(2);
	// now set it back
	rr_setCamera("Logitech");

	// turn off processing
	rr_run("off");
	Delay(2);
	// run once
	rr_run("once");
	Delay(2);
	// run for 100 frames (~3.3 seconds)
	rr_run("100");
	Delay(2);
	// turn processing back on
	rr_run("on");

	// wait for the image count to exceed 1000 (assuming a 30 fps here)
	rr_waitVariable("image_count", "500", 100000);

	// wait for a new image
	rr_waitImage();

	// save a processed version of an image on disk
	rr_loadImage(NULL, "c:\\www\\RoboRealm\\bin\\remo.gif");
	rr_waitImage();
	rr_saveImage("processed", "c:\\temp\\test.jpg");

	// load an image based on compressed bytes
	fp = fopen("c:\\www\\RoboRealm\\bin\\remo.gif", "rb");
	if (fp!=NULL)
	{
		int len = fread((char *)image, 1, 320*240*3, fp);
		fclose(fp);
		rr_setCompressedImage("source", image, len, false);
	}

	// close the RoboRealm application .. if you want too ... otherwise leave it running
	rr_close();

	// disconnect from API Server
	rr_disconnect();
*/

	// example to show how to display the processed image from RoboRealm
	// see examples above on how to access other API routines
	if (rr_getImage("processed", image, &width, &height, 320*240*3))
	{
		int bid;
		NewBitmapEx(320*3, 24, 320, 240, NULL, image, NULL, NULL, &bid);
		SetCtrlBitmap(nPanelHandle, PANEL_PICTURE, 0, bid);
	}

	////////////////////////////////////////////////////
	//
	// End RR API testing
	//
	////////////////////////////////////////////////////

	nStatus = RunUserInterface ();
	if (nStatus < 0)
	{
		MessagePopup("Error Message", "RunUserInterface()");
		return;
	}
}



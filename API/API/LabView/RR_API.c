#include <utility.h>
#include <userint.h>
#include <tcpsupp.h>
#include <ansi_c.h>
#include "RR_API.h"

int handle=0;

// indicates that the application is connected to RoboRealm Server
int connected=false;
// holds the previously read data size
int lastDataTop=0;
// holds the previously read data buffer
int lastDataSize=0;
// contains the read/write socket timeouts
int timeout=DEFAULT_TIMEOUT;
// general buffer for data manipulation and socket reading
char buffer[MAX_BUFFER_SIZE];

char errorMsg[64];


int CVICALLBACK rr_dispatch(unsigned handle, int event, int error, void *callbackData);

/******************************************************************************/
/* Text string manipulation routines */
/******************************************************************************/


/*
Escapes strings to be included in XML message. This can be accomplished by a
sequence of replace statements.
	& -> &amp;
	" -> &quote;
	< -> &lt;
	> -> &gt;
*/
void rr_escape(char *txt, char *dest, int max)
{
	int i, j;

	for (j=i=0;txt[i]&&(j<max);i++)
	{
		if (txt[i]=='&')
		{
			if (j+5<max)
			{
				strcpy(&dest[j], "&amp;");
				j+=5;
			}
		}
		else
		if (txt[i]=='"')
		{
			if (j+5<max)
			{
				strcpy(&dest[j], "&quote;");
				j+=5;
			}
		}
		else
		if (txt[i]=='<')
		{
			if (j+4<max)
			{
				strcpy(&dest[j], "&lt;");
				j+=4;
			}
		}
		else
		if (txt[i]=='>')
		{
			if (j+4<max)
			{
				strcpy(&dest[j], "&gt;");
				j+=4;
			}
		}
		else
		{
			dest[j++]=txt[i];
		}
	}

	dest[j]=0;
}

/*
Unrr_escapes strings that have been included in an XML message. This can be
accomplished by a sequence of replace statements.
	&amp; -> &
	&quote; -> "
	&lt; -> <
	&gt; -> >
*/
void rr_unescape(char *txt)
{
	int i, j;

	for (j=i=0;txt[i];i++)
	{
		if (txt[i]=='&')
		{
			if (strnicmp(&txt[i], "&amp;", 5)==0)
			{
				txt[j++]='&';
				i+=4;
			}
			else
			if (strnicmp(&txt[i], "&quote;", 7)==0)
			{
				txt[j++]='"';
				i+=6;
			}
			else
			if (strnicmp(&txt[i], "&lt;", 4)==0)
			{
				txt[j++]='<';
				i+=3;
			}
			else
			if (strnicmp(&txt[i], "&gt;", 4)==0)
			{
				txt[j++]='>';
				i+=3;
			}
		}
		else
		{
			txt[j++]=txt[i];
		}
	}

	txt[j]=0;
}

/******************************************************************************/
/* Socket Routines */
/******************************************************************************/

/* Initiates a socket connection to the RoboRealm server */
int rr_connect(char *hostname, int port)
{
	connected=false;

	/* Connect to Server */
	if (ConnectToTCPServer(&handle, port, hostname, rr_dispatch, NULL, 2000)<0)
	{
		return false;
	}

	connected=true;

	return true;
}

/* close the socket handle */
void rr_disconnect()
{
	if (connected) DisconnectFromTCPServer(handle);
}

/* Timed read from a socket */
int rr_read(int hSocket, unsigned char *buffer, int len)
{
	int bytesToRead = len;
	int bytesRead;

	/*
     * Disable library error checking as we are going to read until
     * there is no more data left (read call times out).
     */
    DisableBreakOnLibraryErrors ();

	while (bytesToRead>0)
	{
		if ((bytesRead = ClientTCPRead(hSocket, &buffer[len - bytesToRead], bytesToRead, 2000))<0)
		{
			//MessagePopup("TCP Client", "TCP read error!");
			if (bytesToRead!=len)
				return len - bytesToRead;
			else
				return -1;
		}
		bytesToRead -= bytesRead;
	}

    /* Enable library error checking. */
    EnableBreakOnLibraryErrors ();

  	return len;
}

int rr_send(int hSocket, unsigned char *buffer, int len)
{
	int bytesToWrite = len;

	while (bytesToWrite > 0)
	{
		int bytesWritten = ClientTCPWrite(hSocket, &buffer[len - bytesToWrite], bytesToWrite, 0);
		bytesToWrite -= bytesWritten;
	}

	return 1;
}

/*
Buffered socket image read. Since we don't know how much data was read from a
previous socket operation we have to add in any previously read information
that may still be in our buffer. We detect the end of XML messages by the
</response> tag but this may require reading in part of the image data that
follows a message. Thus when reading the image data we have to move previously
read data to the front of the buffer and continuing reading in the
complete image size from that point.
*/
int rr_readImageData(int hSocket, unsigned char *pixels, int len)
{
  int num;

	// check if we have any information left from the previous read
	num = lastDataSize-lastDataTop;
	if (num>len)
	{
		memcpy(pixels, &buffer[lastDataTop], len);
		lastDataTop+=num;
		return num;
	}
	memcpy(pixels, &buffer[lastDataTop], num);
	len-=num;
	lastDataSize=lastDataTop=0;

	// then keep reading until we're read in the entire image length
  do
  {
    int res = rr_read(hSocket, (unsigned char *)&pixels[num], len);
	if (res<0)
	{
		lastDataSize=lastDataTop=0;
		return -1;
	}
    num+=res;
    len-=res;
  }
  while (len>0);

  return num;
}

/*
Skips the specified length of data in case the incoming image is too big for the current
buffer. If we don't read in the image entirely then the next API statements will
not work since a large binary buffer will be before any response can be read
*/
void rr_skipData(int hSocket, int len)
{
	int num = lastDataSize-lastDataTop;
	char skipBuffer[1024];
	lastDataSize=lastDataTop=0;
	len-=num;
	do
	{
		int res = rr_read(hSocket, (unsigned char *)skipBuffer, len>1024?1024:len);
		len-=res;
	}
	while (len>0);
}

/* Read's in an XML message from the RoboRealm Server. The message is always
delimited by a </response> tag. We need to keep reading in information until
this tag is seen. Sometimes this will accidentally read more than needed
into the buffer such as when the message is followed by image data. We
need to keep this information for the next readImage call.*/

int rr_readMessage(int hSocket, unsigned char *buffer, int len)
{
	int num=0;
	char *delimiter = "</response>";
	int top=0;
	int i;
	int nextReadLen = 11;

	// read in blocks of data looking for the </response> delimiter
	do
	{
		int res = rr_read(hSocket, (unsigned char *)&buffer[num], nextReadLen);
		if (res<0)
		{
			lastDataSize=lastDataTop=0;
			return -1;
		}
		lastDataSize=num+res;
		for (i=num;i<num+res;i++)
		{
			if (buffer[i]==delimiter[top])
			{
				top++;
				if (delimiter[top]==0)
				{
					num=i+1;
					buffer[num]=0;
			    	lastDataTop=num;
					return num;
				}
			}
			else
			    top=0;
		}
		nextReadLen = 11-top;
		num+=res;
		len-=res;
	}
  	while (len>0);

	lastDataTop=num;
	buffer[num]=0;
  return num;
}

/******************************************************************************/
/* API Routines */
/******************************************************************************/

/* Returns the current image dimension */
int rr_getDimension(int *width, int *height)
{
	char *cmd = "<request><get_dimension/></request>";

	if (!connected) return false;

  	rr_send(handle, cmd, strlen(cmd));

  // read in variable length
  	if (rr_readMessage(handle, (unsigned char *)buffer, MAX_BUFFER_SIZE)>0)
	{
		sscanf(buffer, "<response><width>%d</width><height>%d</height></response>", width, height);
		return true;
	}

	return false;
}

/*
Returns the named image.
	name - input - name of image to grab. Can be source, processed, or marker name.
	pixels  - output - contains RGB 8 bit byte.
	width - output - contains grabbed image width
	height - output - contains image height
	len - input - maximum size of pixels to read
*/
int rr_getImage(char *name, unsigned char *pixels, int *width, int *height, unsigned int max)
{
	char ename[64];
	unsigned int len;
	if (!connected) return false;
	if (name==NULL) name="";

	// rr_escape the name for use in an XML stream
	rr_escape(name, ename, 64);

	// create the message request
	sprintf(buffer, "<request><get_image>%s</get_image></request>", ename);
  	rr_send(handle, buffer, strlen(buffer));

  // read in response which contains image information
  	if (rr_readMessage(handle, (unsigned char *)buffer, MAX_BUFFER_SIZE)>0)
	{
		// parse image width and height
		sscanf(buffer, "<response><length>%d</length><width>%d</width><height>%d</height></response>", &len, width, height);
		if (len>max)
		{
	    	rr_skipData(handle, len);
			return false;
		}
		// actual image data follows the message
		if ((unsigned int)rr_readImageData(handle, (unsigned char *)pixels, len)!=len)
			return false;
		else
		{
			return true;
		}
	}

	return false;
}

/*
Sets the current source image.
	name - input - the name of the image to set. Can be source or marker name
	pixels  - input - contains RGB 8 bit byte.
	width - input - contains grabbed image width
	height - input - contains image height
*/
int rr_setImage(char *name, unsigned char *pixels, int width, int height, int wait)
{
	char ename[64];
	if (!connected) return false;
	if (name==NULL) name="";

	// rr_escape the name for use in an XML string
	rr_escape(name, ename, 64);

	// setup the message request
	sprintf(buffer, "<request><set_image><source>%s</source><width>%d</width><height>%d</height><wait>%s</wait></set_image></request>", ename, width, height, wait?"1":"");
  	rr_send(handle, buffer, strlen(buffer));

    // send the RGB triplet pixels after message
	rr_send(handle, (char *)pixels, width*height*3);

  // read message response
	if (rr_readMessage(handle, (unsigned char *)buffer, MAX_BUFFER_SIZE)>0)
	{
		if (stricmp(buffer, "<response>ok</response>")!=0)
			return false;
		else
			return true;
	}

	return false;
}

/*
Sets the current source image from compressed bytes.
	name - input - the name of the image to set. Can be source or marker name
	pixels  - input - contains compress image bytes.
	size - input - specifies len of bytes contained in pixels
*/
int rr_setCompressedImage(char *name, unsigned char *pixels, int size, int wait)
{
	char ename[64];
	if (!connected) return false;
	if (name==NULL) name="";

	// rr_escape the name for use in an XML string
	rr_escape(name, ename, 64);

	// setup the message request
	sprintf(buffer, "<request><set_image><compressed>1</compressed><source>%s</source><size>%d</size><wait>%s</wait></set_image></request>", ename, size, wait?"1":"");
  	rr_send(handle, buffer, strlen(buffer));

  	// send the RGB triplet pixels after message
	rr_send(handle, (char *)pixels, size);

  	// read message response
	if (rr_readMessage(handle, (unsigned char *)buffer, MAX_BUFFER_SIZE)>0)
	{
		if (stricmp(buffer, "<response>ok</response>")!=0)
			return false;
		else
			return true;
	}

	return false;
}

/*
Returns the value of the specified variable.
	name - input - the name of the variable to query
	result - output - contains the current value of the variable
	max - input - the maximum size of what the result can hold
*/
int rr_getVariable(char *name, char *result, int max)
{
	char ename[64];
	if (!connected) return false;
	if ((name==NULL)||(name[0]==0)) return false;

	// rr_escape the name for use in an XML string
	rr_escape(name, ename, 64);

	result[0]=0;

	sprintf(buffer, "<request><get_variable>%s</get_variable></request>", ename);
  	rr_send(handle, buffer, strlen(buffer));

  	// read in variable length
  	if (rr_readMessage(handle, (unsigned char *)buffer, max>MAX_BUFFER_SIZE?MAX_BUFFER_SIZE:max)>0)
	{
		sscanf(buffer, "<response><%*[^>]>%[^<]</%*[^>]></response>", result);
		rr_unescape(result);
		return true;
	}

	return false;
}

/*
Returns the value of the specified variables.
	name - input - the names of the variable to query
	result - output - contains the current values of the variables
	max - input - the maximum size of what the result can hold
*/
int rr_getVariables(char *names, char *results[], int len, int rows)
{
	char ename[100];
	int i = 10;
	int j=0;
	int p=0;

	if (!connected) return 0;
	if ((names==NULL)||(names[0]==0)) return 0;

	// rr_escape the name for use in an XML string
	rr_escape(names, ename, 100);

	results[0][0]=0;

	sprintf(buffer, "<request><get_variables>%s</get_variables></request>", ename);
  	rr_send(handle, buffer, strlen(buffer));

	if (rr_readMessage(handle, (unsigned char *)buffer, len)>0)
	{
		if (strnicmp(buffer, "<response>", 10)!=0) return 0;

		while (j<rows)
		{
			// read in start tag
			if (buffer[i]!='<') return 0;
			while (buffer[i]&&(buffer[i]!='>')) i++;
			if (buffer[i]!='>') return 0;
			// read in variable value
			i++;
			while (buffer[i]&&(buffer[i]!='<'))
				results[j][p++]=buffer[i++];
			// read in end tag
			if (buffer[i]!='<') return 0;
			while (buffer[i]&&(buffer[i]!='>')) i++;
			if (buffer[i]!='>') return 0;
			i++;
			// rr_unescape the resulting value
			results[j][p]=0;
			rr_unescape(results[j]);
			// continue to next variable
			j++;

			// last part of text should be the end response tag
			if (strnicmp(&buffer[i], "</response>", 11)==0) break;
		}

		return j;
	}

	return 0;
}

/*
Sets the value of the specified variable.
	name - input - the name of the variable to set
	value - input - contains the current value of the variable to be set
*/
int rr_setVariable(char *name, char *value)
{
	if (!connected) return false;
	if ((name==NULL)||(name[0]==0)) return false;

	// create request message
	strcpy(buffer, "<request><set_variable><name>");
	rr_escape(name, &buffer[strlen(buffer)], 4096-strlen(buffer));
	strcat(buffer, "</name><value>");
	rr_escape(value, &buffer[strlen(buffer)], 4096-strlen(buffer));
	strcat(buffer, "</value></set_variable></request>");

	// send that message to RR Server
	rr_send(handle, buffer, strlen(buffer));

  	// read in confirmation
  	if (rr_readMessage(handle, (unsigned char *)buffer, MAX_BUFFER_SIZE)>0)
	{
		if (stricmp(buffer, "<response>ok</response>")!=0)
			return false;
		else
			return true;
	}

	return false;
}

/*
Sets the value of the specified variables.
	names - input - the name of the variable to set
	values - input - contains the current value of the variable to be set
*/
int rr_setVariables(char *names[], char *values[], int num)
{
	int j=0;
	int i;

	if (!connected) return false;
	if ((names==NULL)||(values==NULL)||(names[0][0]==0)) return false;

	// create request message
	strcpy(buffer, "<request><set_variables>");
	j=strlen(buffer);
	for (i=0;(i<num);i++)
	{
		if ((j+17)>=4096) return false;
		strcpy(&buffer[j], "<variable><name>");
		j+=strlen(&buffer[j]);
		rr_escape(names[i], &buffer[j], 4096-j);
		j+=strlen(&buffer[j]);
		if ((j+16)>=4096) return false;
		strcpy(&buffer[j], "</name><value>");
		j+=strlen(&buffer[j]);
		rr_escape(values[i], &buffer[j], 4096-j);
		j+=strlen(&buffer[j]);
		if ((j+20)>=4096) return false;
		strcpy(&buffer[j], "</value></variable>");
		j+=strlen(&buffer[j]);
  	}
	if ((j+25)>=4096) return false;
	strcpy(&buffer[j], "</set_variables></request>");
	j+=strlen(&buffer[j]);

	// send that message to RR Server
	rr_send(handle, buffer, j);

  	// read in confirmation
  	if (rr_readMessage(handle, (unsigned char *)buffer, MAX_BUFFER_SIZE)>0)
	{
		if (stricmp(buffer, "<response>ok</response>")!=0)
			return false;
		else
			return true;
	}

	return false;
}

/*
Deletes the specified variable
	name - input - the name of the variable to delete
*/
int rr_deleteVariable(char *name)
{
	char ename[64];
	if (!connected) return false;
	if ((name==NULL)||(name[0]==0)) return false;

	// rr_escape the name for use in an XML string
	rr_escape(name, ename, 64);

	sprintf(buffer, "<request><delete_variable>%s</delete_variable></request>", ename);

  	rr_send(handle, buffer, strlen(buffer));

  	// read in variable length
  	if (rr_readMessage(handle, (unsigned char *)buffer, MAX_BUFFER_SIZE)>0)
	{
		if (stricmp(buffer, "<response>ok</response>")!=0)
			return false;
		else
			return true;
	}

	return false;
}

/*
Executes the provided image processing pipeline
	source - the XML .robo file string
*/
int rr_execute(char *source)
{
	if (!connected) return false;
	if ((source==NULL)||(source[0]==0)) return false;

	// create the request message
	strcpy(buffer, "<request><execute>");
	rr_escape(source, &buffer[strlen(buffer)], 4096-strlen(buffer));
	strcat(buffer, "</execute></request>");

	//send the string
  	rr_send(handle, buffer, strlen(buffer));

  	// read in result
  	if (rr_readMessage(handle, (unsigned char *)buffer, MAX_BUFFER_SIZE)>0)
	{
		if (stricmp(buffer, "<response>ok</response>")!=0)
			return false;
		else
			return true;
	}

	return false;
}

/*
Executes the provided .robo file. Note that the file needs to be on the machine
running RoboRealm. This is similar to pressing the 'open program' button in the
main RoboRealm dialog.
	filename - the XML .robo file to run
*/
int rr_loadProgram(char *filename)
{
	if (!connected) return false;
	if ((filename==NULL)||(filename[0]==0)) return false;

	strcpy(buffer, "<request><load_program>");
	rr_escape(filename, &buffer[strlen(buffer)], 4096-strlen(buffer));
	strcat(buffer, "</load_program></request>");

  	rr_send(handle, buffer, strlen(buffer));

  	if (rr_readMessage(handle, (unsigned char *)buffer, MAX_BUFFER_SIZE)>0)
	{
		if (stricmp(buffer, "<response>ok</response>")!=0)
			return false;
		else
			return true;
	}

	return false;
}

/*
Returns the currently load .robo file
*/
int rr_getProgram(char *xml, int len)
{
	char *cmd = "<request><get_program></get_program></request>";

	if (!connected) return false;

  	rr_send(handle, cmd, strlen(cmd));

  	if (rr_readMessage(handle, (unsigned char *)xml, len)>0)
	{
		if (strnicmp(buffer, "<response><", 11)!=0)
			return false;
		else
			return true;
	}

	return false;
}


/*
Loads an image into RoboRealm. Note that the image needs to exist
on the machine running RoboRealm. The image format must be one that
RoboRealm using the freeimage.dll component supports. This includes
gif, pgm, ppm, jpg, png, bmp, and tiff. This is
similar to pressing the 'load image' button in the main RoboRealm
dialog.
	name - name of the image. Can be "source" or a marker name,
	filename - the filename of the image to load
*/
int rr_loadImage(char *name, char *filename)
{
	if (!connected) return false;

	if ((filename==NULL)||(filename[0]==0)) return false;
	if ((name==NULL)||(name[0]==0)) name="source";

	strcpy(buffer, "<request><load_image><filename>");
	rr_escape(filename, &buffer[strlen(buffer)], 4096-strlen(buffer));
	strcat(buffer, "</filename><name>");
	rr_escape(name, &buffer[strlen(buffer)], 4096-strlen(buffer));
	strcat(buffer, "</name></load_image></request>");

  	rr_send(handle, buffer, strlen(buffer));

  	// read in variable length
  	if (rr_readMessage(handle, (unsigned char *)buffer, MAX_BUFFER_SIZE)>0)
	{
		if (stricmp(buffer, "<response>ok</response>")!=0)
			return false;
		else
			return true;
	}

	return false;
}

/*
Saves the specified image in RoboRealm to disk. Note that the filename is relative
to the machine that is running RoboRealm. The image format must be one that
RoboRealm using the freeimage.dll component supports. This includes
gif, pgm, ppm, jpg, png, bmp, and tiff. This is
similar to pressing the 'save image' button in the main RoboRealm
dialog.
	name - name of the image. Can be "source","processed", or a marker name,
	filename - the filename of the image to save
*/
int rr_saveImage(char *source, char *filename)
{
	if (!connected) return false;

	if ((filename==NULL)||(filename[0]==0)) return false;
	if ((source==NULL)||(source[0]==0)) source="processed";

	// create the save image message
	strcpy(buffer, "<request><save_image><filename>");
	rr_escape(filename, &buffer[strlen(buffer)], 4096-strlen(buffer));
	strcat(buffer, "</filename><source>");
	rr_escape(source, &buffer[strlen(buffer)], 4096-strlen(buffer));
	strcat(buffer, "</source></save_image></request>");

  	// send it on its way
	rr_send(handle, buffer, strlen(buffer));

  	// read in any result
  	if (rr_readMessage(handle, (unsigned char *)buffer, MAX_BUFFER_SIZE)>0)
	{
		if (stricmp(buffer, "<response>ok</response>")!=0)
			return false;
		else
			return true;
	}

	return false;
}

/*
Sets the current camera driver. This can be used to change the current viewing camera
to another camera installed on the same machine. Note that this is a small delay
when switching between cameras. The specified name needs only to partially match
the camera driver name seen in the dropdown picklist in the RoboRealm options dialog.
For example, specifying "Logitech" will select any installed Logitech camera including
"Logitech QuickCam PTZ".
*/
int rr_setCamera(char *name)
{
	int res;
	if (!connected) return false;
	if ((name==NULL)||(name[0]==0)) return false;

	strcpy(buffer, "<request><set_camera>");
	rr_escape(name, &buffer[strlen(buffer)], 4096-strlen(buffer));
	strcat(buffer, "</set_camera></request>");

  	res = rr_send(handle, buffer, strlen(buffer));

  	// read in variable length
  	if (rr_readMessage(handle, (unsigned char *)buffer, MAX_BUFFER_SIZE)>0)
	{
		if (stricmp(buffer, "<response>ok</response>")!=0)
			return false;
		else
			return true;
	}

	return false;
}

/*
This routine provides a way to stop processing incoming video. Some image processing
tasks can be very CPU intensive and you may only want to enable processing when
required but otherwise not process any incoming images to release the CPU for other
tasks. The run mode can also be used to processing individual frames or only run
the image processing pipeline for a short period. This is similar to pressing the
"run" button in the main RoboRealm dialog.
	mode - can be toggle, on, off, once, or a number of frames to process
	*/
int rr_run(char *mode)
{
	if (!connected) return false;
	if ((mode==NULL)||(mode[0]==0)) return false;

	strcpy(buffer, "<request><run>");
	rr_escape(mode, &buffer[strlen(buffer)], 4096-strlen(buffer));
	strcat(buffer, "</run></request>");

  	rr_send(handle, buffer, strlen(buffer));

  	if (rr_readMessage(handle, (unsigned char *)buffer, MAX_BUFFER_SIZE)>0)
	{
		if (stricmp(buffer, "<response>ok</response>")!=0)
			return false;
		else
			return true;
	}

	return false;
}

/*
There is often a need to pause your own Robot Controller program to wait for
RoboRealm to complete its task. The eaisest way to accomplish this is to wait
on a specific variable that is set to a specific value by RoboRealm. Using the
waitVariable routine you can pause processing and then continue when a variable
changes within RoboRealm.
	name - name of the variable to wait for
	value - the value of that variable which will cancel the wait
	timeout - the maximum time to wait for the variable value to be set
*/
int rr_waitVariable(char *name, char *value, int ti)
{
	if (!connected) return false;
	if ((name==NULL)||(name[0]==0)) return false;

	strcpy(buffer, "<request><wait_variable><name>");
	rr_escape(name, &buffer[strlen(buffer)], 4096-strlen(buffer));
	strcat(buffer, "</name><value>");
	rr_escape(value, &buffer[strlen(buffer)], 4096-strlen(buffer));
	strcat(buffer, "</value><timeout>");
	sprintf(&buffer[strlen(buffer)], "%d", timeout);
	strcat(buffer, "</timeout></wait_variable></request>");

	timeout=ti;
	if (timeout==0) timeout=100000000;

  	rr_send(handle, buffer, strlen(buffer));

	if (rr_readMessage(handle, (unsigned char *)buffer, MAX_BUFFER_SIZE)>0)
	{
		timeout=DEFAULT_TIMEOUT;
		if (stricmp(buffer, "<response>ok</response>")!=0)
			return false;
		else
			return true;
	}

	timeout=DEFAULT_TIMEOUT;
	return false;
}

/*
If you are rapdily grabbing images you will need to wait inbetween each
get_image for a new image to be grabbed from the video camera. The wait_image
request ensures that a new image is available to grab. Without this routine
you may be grabbing the same image more than once.
*/
int rr_waitImage()
{
	if (!connected) return false;

	strcpy(buffer, "<request><wait_image></wait_image></request>");

  	rr_send(handle, buffer, strlen(buffer));

  	// read in variable length
  	if (rr_readMessage(handle, (unsigned char *)buffer, MAX_BUFFER_SIZE)>0)
	{
		if (stricmp(buffer, "<response>ok</response>")!=0)
			return false;
		else
			return true;
	}

	return false;
}

/* If you are running RoboRealm on the same machine as your API program you can use
this routine to start RoboRealm if it is not already running.
	filename - the path to RoboRealm on your machine
*/
int rr_open(char *filename, int port)
{
	return 1;
}


/* Closes the roborealm application nicely. */
int rr_close()
{
	if (!connected) return false;

	strcpy(buffer, "<request><close></close></request>");

  	rr_send(handle, buffer, strlen(buffer));

  	// read in variable length
  	if (rr_readMessage(handle, (unsigned char *)buffer, MAX_BUFFER_SIZE)>0)
	{
		if (stricmp(buffer, "<response>ok</response>")!=0)
			return false;
		else
			return true;
	}

	return false;
}

//////////////////////////////////// Basic Image Load/Save routines ////////////////////////

// Utility routine to save a basic PPM
int rr_savePPM(char *filename, unsigned char *buffer, int width, int height)
{
  FILE *fp;
  int num;
  int len;
  int length=width*height*3;

  if ((fp=fopen(filename,"wb"))!=NULL)
  {
    fprintf(fp, "P6\n%d %d\n255\n", width, height);

    for (len=0;len<length;len+=num)
    {
      if ((num=(length-len))>4096)
        num=4096;
      num=fwrite(&buffer[len], 1, num, fp);
    }

		fclose(fp);
  }
  return len;
}

unsigned char *rr_readLine(FILE *fp, unsigned char *buffer)
{
  while (!feof(fp))
  {
    fscanf(fp, "%[^\n]\n", buffer);
    if (buffer[0]!='#')
      return buffer;
  }
  return NULL;
}

// Utility routine to load a basic PPM. Note that this routine does NOT handle
// comments and is only included as a quick example.
int rr_loadPPM(char *filename, unsigned char *buffer, int *width, int *height, int max)
{
  	FILE *fp;
  	int len, num, w,h;

  	if ((fp=fopen(filename,"rb"))!=NULL)
	{
    	rr_readLine(fp, buffer);
		if (strcmp((char *)buffer, "P6")!=0)
		{
			printf("Illegal format!\n");
			fclose(fp);
			return -1;
		}

    	rr_readLine(fp, buffer);
		sscanf((char *)buffer, "%d %d", &w, &h);

		*width=w;
		*height=h;

    	rr_readLine(fp, buffer);
		if (strcmp((char *)buffer, "255")!=0)
		{
			printf("Illegal format!\n");
			fclose(fp);
			return -1;
		}

		for (len=0;(len<w*h*3)&&(len<max);len+=num)
		{
			if (len+65535>max) num=max-len; else num=65535;
			num=fread(&buffer[len], 1, num, fp);
			if (num==0) break;
		}

		fclose(fp);

		return 1;
	}

	return -1;
}

/*
Sets the value of the specified parameter.
	module - input - the name of the module which contains the parameter
	module_number - input - module count in case you have more than one of the same module
	name - input - the name of the variable to set
	value - input - contains the current value of the variable to be set
*/
int rr_setParameter(char *module, int count, char *name, char *value)
{
	if (!connected) return false;
	if ((module==NULL)||(module[0]==0)) return false;
	if ((name==NULL)||(name[0]==0)) return false;

	// create request message
	strcpy(buffer, "<request><set_parameter><module>");
	rr_escape(module, &buffer[strlen(buffer)], 4096-strlen(buffer));
	strcat(buffer, "</module><module_number>");
	sprintf(&buffer[strlen(buffer)], "%d", count);
	strcat(buffer, "</module_number><name>");
	rr_escape(name, &buffer[strlen(buffer)], 4096-strlen(buffer));
	strcat(buffer, "</name><value>");
	rr_escape(value, &buffer[strlen(buffer)], 4096-strlen(buffer));
	strcat(buffer, "</value></set_parameter></request>");

	// send that message to RR Server
	rr_send(handle, buffer, strlen(buffer));

  // read in confirmation
  if (rr_readMessage(handle, (unsigned char *)buffer, MAX_BUFFER_SIZE)>0)
	{
		if (stricmp(buffer, "<response>ok</response>")!=0)
			return false;
		else
			return true;
	}

	return false;
}

/*
Returns the value of the specified parameter.
	module - input - the name of the module which contains the parameter
	module_number - input - module count in case you have more than one of the same module
	name - input - the name of the parameter to query
	result - output - contains the current value of the parameter
	max - input - the maximum size of what the result can hold
*/
int rr_getParameter(char *module, int count, char *name, char *result, int max)
{
	if (!connected) return false;
	if ((name==NULL)||(name[0]==0)) return false;

	strcpy(buffer, "<request><get_parameter><module>");
	rr_escape(module, &buffer[strlen(buffer)], 4096-strlen(buffer));
	strcat(buffer, "</module><module_number>");
	sprintf(&buffer[strlen(buffer)], "%d", count);
	strcat(buffer, "</module_number><name>");
	rr_escape(name, &buffer[strlen(buffer)], 4096-strlen(buffer));
	strcat(buffer, "</name></get_parameter></request>");

	result[0]=0;

  rr_send(handle, buffer, strlen(buffer));

  // read in variable length
  if (rr_readMessage(handle, (unsigned char *)buffer, max)>0)
	{
		sscanf(buffer, "<response><%*[^>]>%[^<]</%*[^>]></response>", result);
		rr_unescape(result);
		return true;
	}

	return false;
}

int CVICALLBACK rr_dispatch(unsigned handle, int event, int error, void *callbackData)
{
	switch (event)
	{
		case TCP_DATAREADY:
		break;
		case TCP_DISCONNECT:
		break;
	}
	return 0;
}


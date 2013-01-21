/* MexFunction.c
 *
 * Author: RoboRealm
 *				 Feburary 2, 2009
 *
 * The program 'MexFunction.c' is intended as an example of how
 * you can integrate Matlab with RoboRealm using the mex functional
 * capabilities of Matlab and the RoboRealm socket based API.
 *
 * Please see
 * http://www.roborealm.com/help/API.php
 * for more information about the RoboRealm API and what the
 * functions below are used for.
 *
 *----------------------------------------------------
 *
 * This script was tested on a Windows XP system and compiled
 * using Visual Studio 2006.
 *
 * To unload a loaded dll use
 *   clear mex
 *----------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mex.h"
#include "RR_API.cpp"

#define MAX_IMAGE_WIDTH 1024
#define MAX_IMAGE_HEIGHT 960

RR_API rr;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  char    *inString;
  double  *ptr;
  double  numDouble;
  int     mrows, ncols, *array_magic, i, j, nelem;
  int     *temp;

  if (nrhs <= 0)
	{
    mexPrintf("Format for calling 'RoboRealm' executable:\n");
    mexPrintf("\tRoboRealm( <function_string>, <arg1>, <arg2> )\n");
		return;
  }

  /* Read in first argument: either a string or NULL '[]' */
  if (((mxIsChar(prhs[0]) != 1) & (!mxIsEmpty(prhs[0]))) == 1)
	{
    mexErrMsgTxt("First argument should be a string.");
		return;
	}

	inString = mxArrayToString(prhs[0]);

	if (stricmp(inString, "open")==0)
	{
	  if ((nrhs<2)||(!mxIsChar(prhs[1]))||(mxIsEmpty(prhs[1])))
		{
	    mexErrMsgTxt("Second argument should be the path to the RoboRealm executable of type string.");
			return;
		}

		if ((nrhs<3)||(!mxIsNumeric(prhs[2]))||(mxIsEmpty(prhs[2])))
		{
	    mexErrMsgTxt("Fourth argument should be the API port numberto use.");
			return;
		}

		char *name = mxArrayToString(prhs[1]);
		int port = (int)mxGetScalar(prhs[2]);

		if (!rr.open(name, port))
		{
			mexErrMsgTxt("API call failed. Perhaps due to a timeout?");
			return;
		}
		return;
	}
	else
	if (stricmp(inString, "connect")==0)
	{
	  if (((mxIsChar(prhs[1]) != 1) & (!mxIsEmpty(prhs[1]))) == 1)
		{
	    mexErrMsgTxt("Second argument should be a network hostname/ip address string.");
		}
		int port = 6060;
		if (!mxIsEmpty(prhs[2]))
		{
			if (mxGetClassID(prhs[2]) != mxINT32_CLASS)
			{
				mexErrMsgTxt("Third argument should be an integer port number.");
				return;
			}
			port = (int)mxGetScalar(prhs[2]);
		}

		if (!rr.connect(mxArrayToString(prhs[1]), port))
		{
			mexErrMsgTxt("RoboRealm API does not appear to be activated on localhost:6060!");
			return;
		}
		return;
	}
	else
	{
		if (!rr.connected)
		{
      mexPrintf("Connecting to RoboRealm using default values!\n");
			if (!rr.connect("localhost", 6060))
			{
				mexErrMsgTxt("RoboRealm API does not appear to be activated on localhost:6060!");
				return;
			}
		}
	}

	// Get_Dimension
	if (stricmp(inString, "get_dimension")==0)
	{
		mwSize Dims[2]={1};
		plhs[0] = mxCreateNumericArray(1, Dims, mxUINT32_CLASS, mxREAL);
		plhs[1] = mxCreateNumericArray(1, Dims, mxUINT32_CLASS, mxREAL);
		int *wid = (int *)mxGetData(plhs[0]);
		int *hei = (int *)mxGetData(plhs[1]);

		if (!rr.getDimension(wid, hei))
		{
			mexErrMsgTxt("API call failed. Perhaps due to a timeout?");
			return;
		}
	}
	else
	if (stricmp(inString, "get_image")==0)
	{
		char *name = NULL;

		if (nrhs>=2)
		{
			if (!mxIsEmpty(prhs[1]))
			{
				if (mxIsChar(prhs[1]) != 1)
				{
					mexErrMsgTxt("Second argument should be a image name of type string.");
					return;
				}
				name = mxArrayToString(prhs[1]);
			}
		}

		unsigned char *pixels = (unsigned char *)mxCalloc(MAX_IMAGE_WIDTH*MAX_IMAGE_HEIGHT*3, sizeof(char));
		int width=MAX_IMAGE_WIDTH, height=MAX_IMAGE_HEIGHT;

		if (!rr.getImage(name, pixels, &width, &height, MAX_IMAGE_WIDTH*MAX_IMAGE_HEIGHT*3, "RGB"))
		{
			mexErrMsgTxt("API call failed. Perhaps due to a timeout?");
			return;
		}

		mwSize Dims[3]={height, width, 3};
		plhs[0] = mxCreateNumericArray(3, Dims, mxUINT8_CLASS, mxREAL);
		unsigned char *res = (unsigned char *)mxGetData(plhs[0]);

		int len = width*height*3;
		int l = width*height;
		int ll = width*height*2;
		int x,y, a,b;
		int w = width*3;
		int v = height;

		for (y=0, b=0;y<len-w;b++, y+=w)
		{
			for (x=y, a=b;x<y+w;a+=v)
			{
				res[a]=pixels[x++];
				res[a+l]=pixels[x++];
				res[a+ll]=pixels[x++];
			}
		}
		mxFree(pixels);
	}
	else
	if (stricmp(inString, "set_image")==0)
	{
		if ((nrhs!=2)||(mxIsEmpty(prhs[1])))
		{
			mexErrMsgTxt("Second argument should be an image of unsigned int 8 bits.");
			return;
		}

    const mxArray *ptr = prhs[1];

		if (mxGetClassID(ptr)!=mxUINT8_CLASS)
		{
      mxArray *cast_prhs[1]={ NULL };
      mexCallMATLAB(1, cast_prhs, 1, (mxArray **)&prhs[0],"uint8");
      ptr=cast_prhs[0];
    }

    if (mxGetClassID(ptr)!=mxUINT8_CLASS)
		{
			mexErrMsgTxt("Could not convert image type to unsigned int 8 bits.");
			return;
		}

		int width = mxGetN(ptr)/3;
		int height = mxGetM(ptr);

		int len = width*height*3;
		int l = width*height;
		int ll = width*height*2;
		int x,y, a,b;
		int w = width*3;
		int v = height;

		unsigned char *pixels = (unsigned char *)mxCalloc(len, sizeof(char));
		unsigned char *data = (unsigned char *)mxGetData(ptr);
		for (y=0, b=0;y<len-w;b++, y+=w)
		{
			for (x=y, a=b;x<y+w;a+=v)
			{
				pixels[x++] = data[a];
				pixels[x++] = data[a+l];
				pixels[x++] = data[a+ll];
			}
		}

		rr.setImage((unsigned char *)pixels, width, height, false);
		mxFree(pixels);
	}
	else
	if (stricmp(inString, "get_variable")==0)
	{
	  if ((nrhs<2)||(mxIsChar(prhs[1]) != 1)||(mxIsEmpty(prhs[1])))
		{
	    mexErrMsgTxt("Second argument should be a variable name of type string.");
			return;
		}
		else
		{
			char buffer[256];
			buffer[0]=0;
			if (!rr.getVariable(mxArrayToString(prhs[1]), buffer, 256))
			{
				mexErrMsgTxt("API call failed. Perhaps due to a timeout?");
				return;
			}
		  plhs[0] = mxCreateString(buffer);
		}
	}
	else
	if (stricmp(inString, "get_variables")==0)
	{
		char *results[16];
		char store[256*16];

		if (nrhs<=1)
		{
			mexErrMsgTxt("Missing variable name list (comma delimited) as a second parameter!");
			return;
		}

		int idx=0;
		for (i=0;i<16;i++)
		{
			results[i]=&store[idx];
			idx+=256;
		}

		char *names = mxArrayToString(prhs[1]);
		int num=1;
		for (i=0;names[i];i++)
			if (names[i]==',')
				num++;

		int l = rr.getVariables(names, results, 256, num);

		for (i=0;i<num;i++)
		  plhs[i] = mxCreateString(results[i]);
	}
	else
	if (stricmp(inString, "set_variable")==0)
	{
	  if ((nrhs<2)||(!mxIsChar(prhs[1]))||(mxIsEmpty(prhs[1])))
		{
	    mexErrMsgTxt("Second argument should be a variable name of type string.");
			return;
		}

		if ((nrhs<3)||(mxIsEmpty(prhs[2])))
		{
	    mexErrMsgTxt("Third argument should be the value for the variable.");
			return;
		}

		char *name = mxArrayToString(prhs[1]);

    const mxArray *ptr = prhs[2];

		if (mxGetClassID(ptr)!=mxCHAR_CLASS)
		{
      mxArray *cast_prhs[1]={ NULL };
      mexCallMATLAB(1, cast_prhs, 1, (mxArray **)&prhs[2],"num2str");
      ptr=cast_prhs[0];
    }
		char *value = mxArrayToString(ptr);

		if (!rr.setVariable(name, value))
		{
			mexErrMsgTxt("API call failed. Perhaps due to a timeout?");
			return;
		}
	}
	else
	if (stricmp(inString, "set_variables")==0)
	{
		char *names[16];
		char *values[16];
		int num=0;

		for (i=1;((i+1)<nrhs);i+=2)
		{
			names[num] = mxArrayToString(prhs[i]);

	    const mxArray *ptr = prhs[i+1];

			if (mxGetClassID(ptr)!=mxCHAR_CLASS)
			{
				mxArray *cast_prhs[1]={ NULL };
				mexCallMATLAB(1, cast_prhs, 1, (mxArray **)&prhs[2],"num2str");
				ptr=cast_prhs[0];
			}
			values[num] = mxArrayToString(ptr);

			num++;
		}

		if (!rr.setVariables(names, values, num))
		{
			mexErrMsgTxt("API call failed. Perhaps due to a timeout?");
			return;
		}
	}
	else
	if (stricmp(inString, "delete_variable")==0)
	{
	  if ((nrhs<2)||(!mxIsChar(prhs[1]))||(mxIsEmpty(prhs[1])))
		{
	    mexErrMsgTxt("Second argument should be a variable name of type string.");
			return;
		}

		char *name = mxArrayToString(prhs[1]);

		if (!rr.deleteVariable(name))
		{
			mexErrMsgTxt("API call failed. Perhaps due to a timeout?");
			return;
		}
	}
	else
	if (stricmp(inString, "execute")==0)
	{
	  if ((nrhs<2)||(!mxIsChar(prhs[1]))||(mxIsEmpty(prhs[1])))
		{
	    mexErrMsgTxt("Second argument should be an XML formatted string.");
			return;
		}

		char *prg = mxArrayToString(prhs[1]);

		if (!rr.execute(prg))
		{
			mexErrMsgTxt("API call failed. Perhaps due to a timeout?");
			return;
		}
	}
	else
	if (stricmp(inString, "load_program")==0)
	{
	  if ((nrhs<2)||(!mxIsChar(prhs[1]))||(mxIsEmpty(prhs[1])))
		{
	    mexErrMsgTxt("Second argument should be a robofile filename.");
			return;
		}

		char *path = mxArrayToString(prhs[1]);

		if (!rr.loadProgram(path))
		{
			mexErrMsgTxt("API call failed. Perhaps due to a timeout?");
			return;
		}
	}
	else
	if (stricmp(inString, "get_program")==0)
	{
		char buffer[256];

		if (!rr.getProgram(buffer, 256))
		{
			mexErrMsgTxt("API call failed. Perhaps due to a timeout?");
			return;
		}

		 plhs[0] = mxCreateString(buffer);
	}
	else
	if (stricmp(inString, "load_image")==0)
	{
	  if ((nrhs<2)||(!mxIsChar(prhs[1]))||(mxIsEmpty(prhs[1])))
		{
	    mexErrMsgTxt("Second argument should be an image filename of type string.");
			return;
		}

		char *path = mxArrayToString(prhs[1]);

		if (!rr.loadImage("source", path))
		{
			mexErrMsgTxt("API call failed. Perhaps due to a timeout?");
			return;
		}
	}
	else
	if (stricmp(inString, "save_image")==0)
	{
	  if ((nrhs<2)||(!mxIsChar(prhs[1]))||(mxIsEmpty(prhs[1])))
		{
	    mexErrMsgTxt("Second argument should be an image filename of type string.");
			return;
		}

		char *path = mxArrayToString(prhs[1]);

		if (!rr.saveImage("processed", path))
		{
			mexErrMsgTxt("API call failed. Perhaps due to a timeout?");
			return;
		}
	}
	else
	if (stricmp(inString, "set_camera")==0)
	{
	  if ((nrhs<2)||(!mxIsChar(prhs[1]))||(mxIsEmpty(prhs[1])))
		{
	    mexErrMsgTxt("Second argument should be a camera name of type string.");
			return;
		}

		char *name = mxArrayToString(prhs[1]);

		if (!rr.setCamera(name))
		{
			mexErrMsgTxt("API call failed. Perhaps due to a timeout?");
			return;
		}
	}
	else
	if (stricmp(inString, "get_camera")==0)
	{
		char buffer[256];

		if (!rr.getCamera(buffer, 256))
		{
			mexErrMsgTxt("API call failed. Perhaps due to a timeout?");
			return;
		}

		 plhs[0] = mxCreateString(buffer);
	}
	else
	if (stricmp(inString, "run")==0)
	{
	  if ((nrhs<2)||(!mxIsChar(prhs[1]))||(mxIsEmpty(prhs[1])))
		{
	    mexErrMsgTxt("Second argument should be a off, on, or toggle of type string.");
			return;
		}

		char *name = mxArrayToString(prhs[1]);

		if (!rr.run(name))
		{
			mexErrMsgTxt("API call failed. Perhaps due to a timeout?");
			return;
		}
	}
	else
	if (stricmp(inString, "wait_variable")==0)
	{
	  if ((nrhs<2)||(!mxIsChar(prhs[1]))||(mxIsEmpty(prhs[1])))
		{
	    mexErrMsgTxt("Second argument should be a variable name of type string.");
			return;
		}

		if ((nrhs<3)||(!mxIsChar(prhs[2]))||(mxIsEmpty(prhs[2])))
		{
	    mexErrMsgTxt("Third argument should be a variable value of type string.");
			return;
		}

		if ((nrhs<4)||(!mxIsNumeric(prhs[3]))||(mxIsEmpty(prhs[3])))
		{
	    mexErrMsgTxt("Fourth argument should be a timeout in milliseconds number.");
			return;
		}

		char *name = mxArrayToString(prhs[1]);
		char *value = mxArrayToString(prhs[2]);
		int timeout = (int)mxGetScalar(prhs[3]);

		if (!rr.waitVariable(name, value, timeout))
		{
			mexErrMsgTxt("API call failed. Perhaps due to a timeout?");
			return;
		}
	}
	else
	if (stricmp(inString, "wait_image")==0)
	{
		if (!rr.waitImage())
		{
			mexErrMsgTxt("API call failed. Perhaps due to a timeout?");
			return;
		}
	}
	else
	if (stricmp(inString, "minimize_window")==0)
	{
		rr.minimizeWindow();
	}
	else
	if (stricmp(inString, "maximize_window")==0)
	{
		rr.maximizeWindow();
	}
	else
	if (stricmp(inString, "move_window")==0)
	{
		if ((nrhs<2)||(!mxIsNumeric(prhs[1]))||(mxIsEmpty(prhs[1])))
		{
	    mexErrMsgTxt("Second argument should be a X position.");
			return;
		}

		if ((nrhs<3)||(!mxIsNumeric(prhs[2]))||(mxIsEmpty(prhs[2])))
		{
	    mexErrMsgTxt("Third argument should be a Y position.");
			return;
		}

		int X = (int)mxGetScalar(prhs[1]);
		int Y = (int)mxGetScalar(prhs[2]);

		if (!rr.moveWindow(X, Y))
		{
			mexErrMsgTxt("API call failed. Perhaps due to a timeout?");
			return;
		}
	}
	else
	if (stricmp(inString, "resize_window")==0)
	{
		if ((nrhs<2)||(!mxIsNumeric(prhs[1]))||(mxIsEmpty(prhs[1])))
		{
	    mexErrMsgTxt("Second argument should be the window width.");
			return;
		}

		if ((nrhs<3)||(!mxIsNumeric(prhs[2]))||(mxIsEmpty(prhs[2])))
		{
	    mexErrMsgTxt("Third argument should be the window height.");
			return;
		}

		int width = (int)mxGetScalar(prhs[1]);
		int height = (int)mxGetScalar(prhs[2]);

		if (!rr.resizeWindow(width, height))
		{
			mexErrMsgTxt("API call failed. Perhaps due to a timeout?");
			return;
		}
	}
	else
	if (stricmp(inString, "position_window")==0)
	{
		if ((nrhs<2)||(!mxIsNumeric(prhs[1]))||(mxIsEmpty(prhs[1])))
		{
	    mexErrMsgTxt("Second argument should be a X size.");
			return;
		}

		if ((nrhs<3)||(!mxIsNumeric(prhs[2]))||(mxIsEmpty(prhs[2])))
		{
	    mexErrMsgTxt("Third argument should be a Y size.");
			return;
		}

		if ((nrhs<4)||(!mxIsNumeric(prhs[3]))||(mxIsEmpty(prhs[3])))
		{
	    mexErrMsgTxt("Forth argument should be the window width.");
			return;
		}

		if ((nrhs<5)||(!mxIsNumeric(prhs[4]))||(mxIsEmpty(prhs[4])))
		{
	    mexErrMsgTxt("Third argument should be the window height.");
			return;
		}

		int X = (int)mxGetScalar(prhs[1]);
		int Y = (int)mxGetScalar(prhs[2]);
		int width = (int)mxGetScalar(prhs[3]);
		int height = (int)mxGetScalar(prhs[4]);

		if (!rr.positionWindow(X, Y, width, height))
		{
			mexErrMsgTxt("API call failed. Perhaps due to a timeout?");
			return;
		}
	}
	else
	if (stricmp(inString, "get_camera_format")==0)
	{
		int width, height, frameRate;
		char compression[5];
		if (!rr.getCameraFormat(&width, &height, &frameRate, compression))
		{
			mexErrMsgTxt("API call failed. Perhaps due to a timeout?");
			return;
		}
		mwSize Dims[2]={1};
		plhs[0] = mxCreateNumericArray(1, Dims, mxUINT32_CLASS, mxREAL);
		plhs[1] = mxCreateNumericArray(1, Dims, mxUINT32_CLASS, mxREAL);
		plhs[2] = mxCreateNumericArray(1, Dims, mxUINT32_CLASS, mxREAL);
		*(int *)mxGetData(plhs[0]) = width;
		*(int *)mxGetData(plhs[1]) = height;
		*(int *)mxGetData(plhs[2]) = frameRate;
		compression[4]=0;
		plhs[3] = mxCreateString(compression);
	}
	else
	if (stricmp(inString, "set_camera_format")==0)
	{
		if ((nrhs<2)||(!mxIsNumeric(prhs[1]))||(mxIsEmpty(prhs[1])))
		{
	    mexErrMsgTxt("Second argument should be a width size.");
			return;
		}

		if ((nrhs<3)||(!mxIsNumeric(prhs[2]))||(mxIsEmpty(prhs[2])))
		{
	    mexErrMsgTxt("Third argument should be a height size.");
			return;
		}

		if ((nrhs<4)||(!mxIsNumeric(prhs[3]))||(mxIsEmpty(prhs[3])))
		{
	    mexErrMsgTxt("Forth argument should be the framerate number.");
			return;
		}

	  if ((nrhs<5)||(!mxIsChar(prhs[4]))||(mxIsEmpty(prhs[4])))
		{
	    mexErrMsgTxt("Fifth argument should be a compression format string (RGB, YUV, etc. supported by your camera).");
			return;
		}

		int width = (int)mxGetScalar(prhs[1]);
		int height = (int)mxGetScalar(prhs[2]);
		int frameRate = (int)mxGetScalar(prhs[3]);
		char *compression = mxArrayToString(prhs[4]);

		if (!rr.setCameraFormat(width, height, frameRate, compression))
		{
			mexErrMsgTxt("API call failed. Perhaps due to a timeout?");
			return;
		}
	}
	else
	if (stricmp(inString, "get_camera_properties")==0)
	{
		char *names[64];
		int values[64];
		int min[64];
		int max[64];
		int automatic[64];
		int num=0;
		int idx=0;
		char store[64*64];

		for (i=0;i<64;i++)
		{
			names[i]=&store[idx];
			names[i][0]=0;
			idx+=64;
		}

		if (nrhs==1)
		{
			if (!rr.getCameraProperties(names, values, min, max, automatic, 64))
			{
				mexErrMsgTxt("API call failed. Perhaps due to a timeout?");
				return;
			}

			char buffer[1024];
			buffer[0]=0;
			for (i=0;(i<64)&&(names[i][0]);i++)
			{
				if (i>0) strcat(buffer, ",");
				strcat(buffer, names[i]);
			}
			plhs[0] = mxCreateString(buffer);
		}
		else
		{
			for (i=1;(i<nrhs)&&(i<64);i++)
				names[i-1] = mxArrayToString(prhs[i]);

			if (!rr.getCameraProperties(names, values, min, max, automatic, nrhs-1))
			{
				mexErrMsgTxt("API call failed. Perhaps due to a timeout?");
				return;
			}

			mwSize Dims[2]={4};
			for (i=0;i<(nrhs-1)&&(i<63);i++)
			{
				plhs[i] = mxCreateNumericArray(1, Dims, mxINT32_CLASS, mxREAL);
				int *vals = (int *)mxGetData(plhs[i]);
				vals[0]= values[i];
				vals[1]= min[i];
				vals[2]= max[i];
				vals[3]= automatic[i];
			}
		}
	}
	else
	if (stricmp(inString, "set_camera_properties")==0)
	{
		char *names[64];
		int values[64];
		int automatic[64];
		int num=0;

		for (i=1;((i+2)<nrhs);i+=3)
		{
			names[num] = mxArrayToString(prhs[i]);

			values[num] = (int)mxGetScalar(prhs[i+1]);

			automatic[num] = (int)mxGetScalar(prhs[i+2]);

			num++;
		}

		if (!rr.setCameraProperties(names, values, automatic, num))
		{
			mexErrMsgTxt("API call failed. Perhaps due to a timeout?");
			return;
		}
	}
	else
	if (stricmp(inString, "disconnect")==0)
	{
		rr.disconnect();
	}
	else
	if (stricmp(inString, "close")==0)
	{
		rr.close();
	}
	else
	{
		mexErrMsgTxt("Unknown command string!");
		return;
	}
}

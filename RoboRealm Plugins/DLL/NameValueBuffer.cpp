////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2007, RoboRealm, all rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are NOT permitted.
//
// Refer to http://www.roborealm.com/registration/Source_Code_Agreement.html
// for license information.
////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// NameValueBuffer
//
// Function:
// Provides data packing routines for transfering data (mainly configuration information)
// from your dll module to RoboRealm. You should not modify this file.
/////////////////////////////////////////////////////////////////////////////

#include "NameValueBuffer.h"

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include "Types.h"

NameValueBuffer::~NameValueBuffer()
{
  free(buffer);
}

NameValueBuffer::NameValueBuffer(int len)
{
  buffer=(char *)malloc(len);
  bufferTop=0;
  bufferSize=len;
}

NameValueBuffer::NameValueBuffer()
{
  buffer=(char *)malloc(64);
  bufferTop=0;
  bufferSize=64;
}

void NameValueBuffer::clear()
{
  bufferTop=0;
  if (bufferSize>8192)
  {
    free(buffer);
    buffer=(char *)malloc(1024);
    bufferSize=1024;
  }
}

void NameValueBuffer::checkspace(int len)
{
  char *tmp;

  if ((bufferTop+len)>=bufferSize)
  {
    tmp=buffer;
    bufferSize=(bufferSize<<1)+len+2;
    buffer=(char *)malloc(bufferSize);
    memcpy(buffer, tmp, bufferTop);
    free(tmp);
  }
}

void NameValueBuffer::append(char *name, char *value)
{
	int ln = strlen(name)+1;
	int lv = strlen(value)+1;
  checkspace(ln+lv+5);

	buffer[bufferTop++]=CHAR_VALUE;
	buffer[bufferTop++]=ln>>8;
	buffer[bufferTop++]=ln&255;
	memcpy(&buffer[bufferTop], name, ln);
	bufferTop+=ln;
	buffer[bufferTop++]=lv>>8;
	buffer[bufferTop++]=lv&255;
	memcpy(&buffer[bufferTop], value, lv);
	bufferTop+=lv;
}

void NameValueBuffer::append(char *name, char *value, int len, int type)
{
	int ln = strlen(name)+1;
  checkspace(ln+len+5);

	buffer[bufferTop++]=type;
	buffer[bufferTop++]=ln>>8;
	buffer[bufferTop++]=ln&255;
	memcpy(&buffer[bufferTop], name, ln);
	bufferTop+=ln;
	buffer[bufferTop++]=len>>8;
	buffer[bufferTop++]=len&255;
	memcpy(&buffer[bufferTop], value, len);
	bufferTop+=len;
}

void NameValueBuffer::append(char *name, char *value, int len, int type, int size)
{
	int ln = strlen(name)+1;
  checkspace(ln+len+5);

	buffer[bufferTop++]=type;
	buffer[bufferTop++]=ln>>8;
	buffer[bufferTop++]=ln&255;
	memcpy(&buffer[bufferTop], name, ln);
	bufferTop+=ln;
	buffer[bufferTop++]=len>>8;
	buffer[bufferTop++]=len&255;
	buffer[bufferTop++]=size&255;
	buffer[bufferTop++]=(size>>8)&255;
	buffer[bufferTop++]=(size>>16)&255;
	buffer[bufferTop++]=(size>>24)&255;
	// - sizeof(int) since we prepended array length
	memcpy(&buffer[bufferTop], value, len-sizeof(int));
	bufferTop+=len-sizeof(int);
}

void NameValueBuffer::append(char *name, int i)
{
  char buffer[32];
  sprintf(buffer, "%d", i);
	append(name, buffer);
}

void NameValueBuffer::append(char *name, float f)
{
  char buffer[32];
  sprintf(buffer, "%f", f);
	append(name, buffer);
}

void NameValueBuffer::append(char *name, char **values, int count)
{
	int ln = strlen(name)+1;
	int len = 2;
	int i;

	// determine total length of all string values
	for (i=0;i<count;i++)
		if (values[i])
			len+=strlen(values[i])+1;

  checkspace(ln+len+5);

	buffer[bufferTop++]=CHAR_ARRAY_VALUE;
	buffer[bufferTop++]=ln>>8;
	buffer[bufferTop++]=ln&255;
	memcpy(&buffer[bufferTop], name, ln);
	bufferTop+=ln;
	buffer[bufferTop++]=len>>8;
	buffer[bufferTop++]=len&255;

	buffer[bufferTop++]=count>>8;
	buffer[bufferTop++]=count&255;

	for (i=0;i<count;i++)
	{
		if (values[i])
		{
			int l = strlen(values[i])+1;

			memcpy(&buffer[bufferTop], values[i], l);

			bufferTop+=l;
		}
		else
		{
			buffer[bufferTop++]=0;
		}
	}
}


char *NameValueBuffer::getBuffer()
{
  return buffer;
}

unsigned int NameValueBuffer::size()
{
  return bufferTop;
}

void NameValueBuffer::alloc(int len)
{
  checkspace(len+1);
}

char *NameValueBuffer::seek(char *name)
{
	unsigned int lnn = strlen(name)+1;
	int i=0;
	while (i<bufferTop)
	{
		unsigned char type = buffer[i++];
		if ((type==CHAR_VALUE) || (type==INT_VALUE))
		{
			unsigned int ln = (buffer[i]<<8)|(buffer[i+1]);
			if (lnn==ln)
			{
				if (memicmp(name, &buffer[i+2], ln)==0)
				{
					return &buffer[i+ln+4];
				}
			}
		}
	}
	return (char *)NULL;
}


void NameValueBuffer::set(unsigned char *data, int len)
{
	checkspace(len);

	memcpy(buffer, data, len);
	bufferTop=len;
}

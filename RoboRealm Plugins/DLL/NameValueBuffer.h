////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2007, RoboRealm, all rights reserved.
//
// Redistribution and use in source and binary forms, with or without 
// modification, are NOT permitted.
//
// Refer to http://www.roborealm.com/registration/Source_Code_Agreement.html
// for license information.
////////////////////////////////////////////////////////////////////////////

#ifndef _NAMEVALUESTORE
#define _NAMEVALUESTORE 1

#include <ctype.h>

class NameValueBuffer
{
	char *buffer;
	long bufferTop;
	long bufferSize;

public:

	~NameValueBuffer();
	NameValueBuffer(int len);
	NameValueBuffer();
	void clear();
	void checkspace(int len);
	void append(char *name, char *value);
	void append(char *name, char *value, int len, int type);
	void append(char *name, int i);
	void append(char *name, float f);
	void append(char *name, char **values, int count);
	void append(char *name, char *value, int len, int type, int size);
	char *getBuffer();
	unsigned int size();
	void alloc(int len);
	char *seek(char *name);
	int read(int *type, char **name, int *nlen, char **value, int *vlen);
	void set(unsigned char *data, int len);
};

#endif
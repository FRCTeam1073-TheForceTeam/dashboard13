#ifndef _RR_API
#define _RR_API 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// default read and write socket timeout
#define DEFAULT_TIMEOUT 60000

// maximum size of a message that can be read from RoboRealm
#define MAX_BUFFER_SIZE 4096

#define false 0
#define true 1

// the port number to listen on ... needs to match that used in RR interface
#define SERVER_PORTNUM 6060

extern int handle;
extern int connected;
extern int lastDataTop;
extern int lastDataSize;
extern int timeout;
extern char buffer[4096];

extern char errorMsg[64];

int rr_readMessage(int hSocket, unsigned char *buffer, int len);
int rr_readImageData(int hSocket, unsigned char *buffer, int len);
void rr_unescape(char *txt);
void rr_escape(char *txt, char *dest, int max);

int rr_connect(char *hostname, int port);
int rr_getDimension(int *width, int *height);
int rr_getImage(char *name, unsigned char *pixels, int *width, int *height, unsigned int len);
void rr_disconnect(void);
int rr_getVariable(char *name, char *buffer, int max);
int rr_setVariable(char *name, char *value);
int rr_deleteVariable(char *name);
int rr_setImage(char *name, unsigned char *image, int width, int height, int wait);
int rr_setCompressedImage(char *name, unsigned char *image, int size, int wait);
int rr_execute(char *source);
int rr_loadProgram(char *filename);
int rr_loadImage(char *name, char *filename);
int rr_saveImage(char *source, char *filename);
int rr_setCamera(char *mode);
int rr_read(int hSocket, unsigned char *buffer, int len);
int rr_run(char *mode);
int rr_waitVariable(char *name, char *value, int timeout);
int rr_waitImage(void);
int rr_close(void);
int rr_open(char *filename, int port);
unsigned char *rr_readLine(FILE *fp, unsigned char *buffer);
int rr_savePPM(char *filename, unsigned char *buffer, int width, int height);
int rr_loadPPM(char *filename, unsigned char *buffer, int *width, int *height, int max);
int rr_getVariables(char *names, char *results[], int len, int rows);
int rr_setVariables(char *names[], char *values[], int num);
void rr_skipData(int hSocket, int len);
int rr_getParameter(char *module, int count, char *name, char *result, int max);
int rr_setParameter(char *module, int count, char *name, char *value);
int rr_getProgram(char *xml, int len);

#endif

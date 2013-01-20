#pragma once


class PipeControl
{
public:
	PipeControl(void);
	~PipeControl(void);
	unsigned int Write(float angle, float distance);
	DWORD WINAPI PipeControlInstanceThread();
private:
	HANDLE hPipe;
	

};


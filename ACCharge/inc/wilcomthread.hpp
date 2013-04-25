#ifndef WILCOM_THREADBASECALSS_20080912__HPP
#define WILCOM_THREADBASECLASS_20080912__HPP




#pragma once



#include <string>
#include <windows.h>
#include  <process.h>

using namespace std;


/************************************************************************
 *																		*
 *							CLASS OF Thread								*
 *																		*
 ************************************************************************/


class Thread
{
public:
	Thread(std::string p_name = "", int p_sleep = 10);
	void start();
	void stop();
	virtual void beforeExecute() = 0;
	virtual void doExecute() = 0;
	virtual void beforeExit() = 0;
	static UINT WINAPI Execute(LPVOID s);


private:
	HANDLE								m_handle;
	HANDLE								m_exitEvent;
	std::string							m_exitEventName;
	int									m_sleep;
};




#endif
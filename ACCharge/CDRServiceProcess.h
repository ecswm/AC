/***********************************************
CDRServiceProcess.h
CDR Windows Service Base on ACE_NT_SERVICE
added by carterliu at 2013/3/31
************************************************/

#ifndef CDR_SERVICE_PROCESS_H
#define CDR_SERVICE_PROCESS_H

#include "ace/Mutex.h"
#include "ace/Singleton.h"
#include "ace/NT_Service.h"
#include <string>

class CDRServicerProcess:public ACE_NT_Service
{
public:
	CDRServicerProcess():m_open(false),m_stop(true),ACE_NT_Service("CDRServicer","AudioCode CDR Service")
	{
		/*
		std::string evtname = name();
		evtname += "CDRServerEventEM";
		_exitMainEvent = CreateEvent(NULL, TRUE, FALSE, evtname.c_str());
		*/
	}
	~CDRServicerProcess();

	//override function
	virtual int svc(void);
	virtual int open(void *args /* = 0 */);
	virtual int fini();
	virtual void handle_control(DWORD control_code);
private:
	//服务打开及停止标志
	bool m_open;
	bool m_stop;
	HANDLE _exitMainEvent;
};

typedef ACE_Singleton<CDRServicerProcess,ACE_Mutex> SCDRServiceProcess;

#endif
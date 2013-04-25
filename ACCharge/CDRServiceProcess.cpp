/*************************************************
CDRServiceProcess.cpp
服务类实现
added by carterliu at 2013/3/31
*************************************************/


#include "CDRServiceProcess.h"
#include "Reactive_CDRServer.h"
#include "WilcomLogger.h"

CDRServicerProcess::~CDRServicerProcess()
{

}

int CDRServicerProcess::open(void *args)
{
	int result;
	m_stop = false;
	m_open = true;
	return result = ACE_NT_Service::open(args);
}

void CDRServicerProcess::handle_control(DWORD control_code)
{
	if (control_code==SERVICE_CONTROL_SHUTDOWN
		||control_code==SERVICE_CONTROL_STOP)
	{
		this->report_status(SERVICE_STOP_PENDING);
		m_stop = true;
	}
	else
		ACE_NT_Service::handle_control(control_code);
}


int CDRServicerProcess::svc()
{	
	m_stop = false;
	this->report_status(SERVICE_RUNNING);
	ACE::init();

	Reactive_CDRServer server;
	if (server.open(514) == -1)
		return	-1;

	while(!m_stop)
	{	
		server.run();
	}
	return 0;
}

int CDRServicerProcess::fini()
{	
	if (m_open)
		ACE_NT_Service::fini();

	this->m_stop = TRUE;
	m_open = FALSE;
	return 0;
}
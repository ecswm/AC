/************************************************
CDRServer.cpp

created by carter.liu at 2013/3/12
*************************************************/

#include "CDRServer.h"

#define CDR_LISTEN_PORT	514

int CDRServer::open(u_short port /* = 0 */)
{
	ACE_INET_Addr server_addr;
	int result;

	if(port != 0)
		result = server_addr.set(port,(ACE_UINT32) INADDR_ANY);
	else
		result = server_addr.set(CDR_LISTEN_PORT,(ACE_UINT32) INADDR_ANY);
	if (result == -1) return -1;

	// Start listening, enable reuse of listen address for quick restarts.
	return m_acceptor.open(server_addr, 1);
}


int CDRServer::run(/*int args,char *argv[]*/)
{
		if (wait_for_multiple_events() == -1)
			return -1;
		if (handle_connections() == -1)
			return	-1;
		if(handle_data() ==	-1)
			return	-1;
	return 0;
}





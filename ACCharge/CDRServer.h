/************************************************************
CDRServer.h
循环处理服务器端基类
created by carter.liu at 2013/3/12
************************************************************/


#ifndef _CDRSERVER_H
#define _CDRSERVER_H

#include "ace/FILE_IO.h"
#include "ace/SOCK_Acceptor.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL
class ACE_SOCK_Stream;
ACE_END_VERSIONED_NAMESPACE_DECL

class CDRServer
{
public:
	virtual int run(/*int args,char *argv[]*/);
	virtual int open(u_short port = 0);
protected:
	virtual int handle_data(ACE_SOCK_Stream * = 0) = 0;
	virtual int handle_connections() = 0;
	virtual int wait_for_multiple_events() {return 0;};

	virtual ~CDRServer(){m_acceptor.close();}
	ACE_SOCK_ACCEPTOR &acceptor() {return m_acceptor;};
	
private:
	ACE_SOCK_ACCEPTOR m_acceptor;	
};

#endif
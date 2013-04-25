/*****************************************************
Reactive_CDRServer.h
基于select循环处理服务端
created by carter.liu at 2013/3/12
*****************************************************/

#ifndef REACTIVE_CDRSERVER_H
#define REACTIVE_CDRSERVER_H

#include "ace/ACE.h"
#include "ace/FILE_IO.h"
#include "ace/Handle_Set.h"
#include "ace/INET_Addr.h"
#include "ace/SOCK_Stream.h"
#include "ace/SOCK_Acceptor.h"
#include "CDRServer.h"
#include "CDRHandle.h"


class Reactive_CDRServer:public CDRServer
{
protected:
	ACE_SOCK_Dgram peer;
	ACE_INET_Addr  port_to_listen;
	ACE_Handle_Set master_handle_set;
	ACE_Handle_Set active_read_set;
public:
	virtual int open(u_short port /* = 0 */)
	{
	    port_to_listen.set_port_number(514); 
		ACE_SOCK_Dgram peer(port_to_listen); 
		master_handle_set.set_bit(peer.get_handle());

		peer.enable(ACE_NONBLOCK);
		return 0;
	}
protected:
	virtual int wait_for_multiple_events()
	{
		active_read_set = master_handle_set;
		int width = (int)master_handle_set.max_set()+1;
		return ACE::select(width,active_read_set);
	}

	virtual int handle_connections()
	{
		return 0;
	}

	virtual int handle_data(ACE_SOCK_Stream * )
	{
		ACE_Handle_Set_Iterator peer_iterator(active_read_set);
		for(ACE_HANDLE handle;
			(handle = peer_iterator())!=ACE_INVALID_HANDLE;
			)
		{
			//设置CDR_Handle进行CDR信息处理
			p_CDRHandle->recv_cdr_record(handle);
		}
		return 0;
	}
};

#endif 



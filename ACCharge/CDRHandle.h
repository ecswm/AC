/*******************************************
CDRHandle.h
CDR信息处理
added by carter liu at 2013/3/15
*******************************************/


#ifndef _CDRHANDLE_H
#define _CDRHANDLE_H

#include "ace/FILE_IO.h"
#include "ace/SOCK_Stream.h"
#include "ace/SOCK_Dgram.h"
#include "ACProtocol.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL
class ACE_Message_Block;
ACE_END_VERSIONED_NAMESPACE_DECL

class CDRHandle
{
protected:
	ACE_SOCK_Dgram cdr_peer_;
	ACProtocol m_protocol;
	
public:
	CDRHandle();
	CDRHandle(ACE_HANDLE handle)
	{
		cdr_peer_.set_handle(handle);
	}
	CDRHandle(const ACE_SOCK_Dgram &cdr_peer):cdr_peer_(cdr_peer){}
	int close() {return cdr_peer_.close();}
	int recv_cdr_record(ACE_HANDLE handle);
	ACE_SOCK_Dgram &peer () { return cdr_peer_; }
};

extern  CDRHandle	*p_CDRHandle;
#endif
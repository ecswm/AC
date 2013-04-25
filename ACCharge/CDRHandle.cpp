
#include "ace/ACE.h"
#include "ace/Functor.h"
#include "ace/CDR_Stream.h"
#include "ace/INET_Addr.h"
#include "ace/Message_Block.h"
#include "CDRHandle.h"
#include "WilcomLogger.h"

#define MAXHOSTNAMELEN 100

CDRHandle *p_CDRHandle = NULL;

CDRHandle::CDRHandle()
{

}

int CDRHandle::recv_cdr_record (ACE_HANDLE handle)
{
	ACE_INET_Addr peer_addr;
	ACE_CDR::ULong length;
	cdr_peer_.set_handle(handle);
	char revbuf[1500];
	memset(revbuf,0,1500);
    if ((length =cdr_peer_.recv(revbuf,1500,peer_addr)) > 0) {
	  WriteLog(revbuf,I);
	  m_protocol.ExtractPackage(revbuf,1500);
	  return length;
    }
	return -1;
}




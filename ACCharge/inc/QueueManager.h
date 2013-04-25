

#ifndef   QUEUE_MANAGER_HPP
#define	  QUEUE_MANAGER_HPP

#pragma once

#include "Queue.hpp"
#include "Thread_Guard.hpp"
#include "Thread_cs.hpp"
#include "ccrdbsDefs.h"

class    QueueManager
{
	public:
		  QueueManager();
		  ~QueueManager();
		  Queue<RevRouteBuf *>  m_Queue;
			
		  void		  PushElemRevList(RevRouteBuf *&);
	   	  bool		  PopElemRevList(RevRouteBuf *&);
		  bool		  CheckRevList();
	private:
		  ThreadCriticalSection			m_ListLock;
};

extern	  QueueManager					*p_QueueManager;
extern    QueueManager					*p_TmpQueueManager;
#endif



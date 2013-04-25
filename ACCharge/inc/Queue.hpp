/*************************************************************************
*		 
*		 Queue.hpp
*		 safer and more convenient queue class
*
*		 Created by CarterLiu on 13-February 2009	
**************************************************************************/

#ifndef	QUEUE_HPP
#define QUEUE_HPP

#pragma once

#include <queue>
#include <exception>

using namespace std;

template<class T>

class Queue
{
	protected:
		std::deque<T> m_PreDataList;

	public:
		typename std::deque<T>::size_type size() const
		{
			return m_PreDataList.size();
		}

		bool empty() const
		{
			return m_PreDataList.empty();
		}

		void push(const T elem)
		{
			m_PreDataList.push_back(elem);
		}
		
		void pop(T &elem)
		{
			elem = m_PreDataList.front();
			m_PreDataList.pop_front();
			//elem = *m_PreDataList.begin();
			//m_PreDataList.erase(m_PreDataList.begin());
		}

		bool Find(T &elem,const char *CallID)
		{
			std::deque<T>::iterator pos;
			for (pos = m_PreDataList.begin();pos < m_PreDataList.end();)
			{
				if (strcmp(CallID,(*pos).CallID) == 0)
				{
					strcpy(elem.CallID,CallID);
					strcpy(elem.ANI,(*pos).ANI);
					strcpy(elem.StationID,(*pos).StationID);
					m_PreDataList.erase(pos++);
					return true;
				}
				pos++;
			}
			return false;
		}

		class ReadEmptyQueue: public std::exception
		{
		public:
			virtual const char* what() const throw()
			{
				return "read empty queue";		
			}
			
		};

};

#endif
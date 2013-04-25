/*********************************************
DB基类实现
*********************************************/
#include "ACDB.h"

ACDB::ACDB()
{
	::CoInitialize(NULL); 
}

ACDB::~ACDB()
{
	::CoUninitialize();
}

bool ACDB::IsOpen()
{
	if(m_pConnection )
		return m_pConnection->GetState() != adStateClosed;
	return FALSE;
}

void ACDB::Close()
{
	if(IsOpen())
		m_pConnection->Close();
}





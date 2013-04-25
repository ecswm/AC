/****************************************************
DB基类
用于支持CDR多数据库
****************************************************/
#ifndef ACDB_H
#define ACDB_H


#include "CDRUtil.h"
#include <string>
#include <Windows.h>

#import "C:Program Files\Common Files\System\ado\msadox.dll"
#import "c:\program files\common files\system\ado\msado15.dll" no_namespace rename ("EOF","adoEOF")

class ACDB
{

public:
	ACDB();
	~ACDB();
	bool IsOpen();
	//重载函数
	virtual bool Open(){return true;};
	virtual void ProcessCDR(CDRINFO &cdrinfo) = 0 ;
	virtual void Close();
protected:
	string m_ConnectString;
	bool   m_IsOpen;
	char   ErrorMsg[512];
	_ConnectionPtr m_pConnection;
	_CommandPtr   m_pCommand;
};


#endif
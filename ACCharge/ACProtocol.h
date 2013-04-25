#include <string>
#include <vector>
#include "ACDB.h"
#include "MDB_ACDB.h"
#include "MSSQL_ACDB.h"
#include "ORACLE_ACDB.h"

using namespace std;

#ifndef _ACPROTOCOL_H
#define _ACPROTOCOL_H

class ACProtocol
{
	public:
	ACProtocol();
	~ACProtocol();
	
	void ExtractPackage(char *revbuf,int length);
	void DecodePackageData(char *revbuf,int length);
	void DecodePackageData(string::iterator begin,string::iterator end);

	private:
	string m_CDRBuf;
	ACDB   *m_pACDB;
};
#endif
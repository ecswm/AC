/******************************************
MDB_ACDB.h
����mdb���ݿ�
******************************************/
#include "ACDB.h"

class MDB_ACDB:public ACDB
{
	public:
		MDB_ACDB();
		bool Open();
	    void ProcessCDR(CDRINFO &cdrinfo);	
};

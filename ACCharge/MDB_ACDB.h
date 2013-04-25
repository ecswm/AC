/******************************************
MDB_ACDB.h
∑√Œ mdb ˝æ›ø‚
******************************************/
#include "ACDB.h"

class MDB_ACDB:public ACDB
{
	public:
		MDB_ACDB();
		bool Open();
	    void ProcessCDR(CDRINFO &cdrinfo);	
};

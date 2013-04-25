/**************************************
ORACLE_ACDB.h
∑√Œ oracle ˝æ›ø‚
**************************************/
#include "ACDB.h"

class ORACLE_ACDB:public ACDB
{
	public:
		ORACLE_ACDB(string _ip,string _dbname,string _user,string _pwd):m_ip(_ip),m_dbname(_dbname),m_user(_user),m_pwd(_pwd)
		{
			m_ConnectString = "Provider=OraOLEDB.Oracle.1; Persist Security Info=false;Data Source=" + m_dbname;
		}
		bool Open();
		void ProcessCDR(CDRINFO &cdrinfo);
	private:
		const string m_ip;
		const string m_dbname;
		const string m_user;
		const string m_pwd;
		
};
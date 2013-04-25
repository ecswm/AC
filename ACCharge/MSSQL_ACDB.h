/*******************************************
MSSQL_ACDB.h
·ÃÎÊMSSQLÊý¾Ý¿â
*******************************************/
#include "ACDB.h"

class MSSQL_ACDB:public ACDB
{
	public:
		MSSQL_ACDB(string _ip,string _dbname,string _user,string _pwd):m_ip(_ip),m_dbname(_dbname),m_user(_user),m_pwd(_pwd)
		{
			m_ConnectString = "Provider=SQLOLEDB.1;Persist Security Info=False;Initial Catalog=";
			m_ConnectString.append(m_dbname);
			m_ConnectString.append("; Data Source =");
			m_ConnectString.append(m_ip);
		}
		~MSSQL_ACDB();
	    bool Open();
	    void ProcessCDR(CDRINFO &cdrinfo);	
	private:
		const string m_ip;
		const string m_dbname;
		const string m_user;
		const string m_pwd;
		
};
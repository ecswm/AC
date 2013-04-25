#include "ACProtocol.h"

ACProtocol::ACProtocol()
{
	//根据DB TYPE,生成不同访问数据库
	string dbtype = SysParam.m_sqltype;
	if (dbtype=="MSSQL")
	{
		m_pACDB = new MSSQL_ACDB(SysParam.m_dbip,SysParam.m_dbname,SysParam.m_dbuser,SysParam.m_dbpwd);
	}
	else
	{
		if (dbtype=="ORACLE")
		{
			m_pACDB = new ORACLE_ACDB(SysParam.m_dbip,SysParam.m_dbname,SysParam.m_dbuser,SysParam.m_dbpwd);
		}
		else
		{
			m_pACDB = new MDB_ACDB();
		}
	}
	m_pACDB->Open();
}

ACProtocol::~ACProtocol()
{

}
/************************************
	Method    :ExtractPackage
	Summary   :解析包
	Parameters:char *revbuf[in],int length[in]
	return    :void
	2013-03-16 added by carter liu

************************************/
void ACProtocol::ExtractPackage(char *revbuf,int length)
{
	string::size_type first_pos;
	string::size_type index_pos;

	m_CDRBuf.append(revbuf);
	first_pos = m_CDRBuf.find(CDRHeader);
	index_pos = 9; 
	if (first_pos != string::npos)
	{
		m_CDRBuf.erase(0,first_pos);
		while((first_pos=m_CDRBuf.find(CDRHeader,index_pos))!=string::npos)
		{
			//解析CDR
			DecodePackageData(m_CDRBuf.begin(),m_CDRBuf.begin()+first_pos);
		}
	DecodePackageData(m_CDRBuf.begin(),m_CDRBuf.end());
	}
}


/****************************************
	Method:	DecodePackageData
	Summary:解析CDR信息
	Parameters:string::iterator begin[in],string::iterator end[in]
	return:void
	2013-03-16 added by carter liu
****************************************/
void ACProtocol::DecodePackageData(string::iterator begin,string::iterator end)
{
	std::vector<string> cdrvec(100);
	CDRINFO cdrinfo;
	std::string::iterator pos = begin;
	int	 cdrindex;
	for(pos,cdrindex=0;pos!=end;pos++)
	{
		if (*pos!='|')
		{
			(cdrvec.at(cdrindex)).push_back(*pos);
		}
		else
		{
			cdrindex++;
		}
	}
	
	cdrinfo.m_CallId = cdrvec.at(CallId);
	cdrinfo.m_ConnectTime = CDRUtil::FormatTimeString(cdrvec.at(ConnectTime).c_str());
	cdrinfo.m_DstNumBeforeMap = cdrvec.at(DstNumBeforeMap);
	cdrinfo.m_DstPhoneNum = cdrvec.at(DstPhoneNum);
	cdrinfo.m_Durat = atoi(cdrvec.at(Durat).c_str());
	cdrinfo.m_ReleaseTime = CDRUtil::FormatTimeString(cdrvec.at(ReleaseTime).c_str());
	cdrinfo.m_SetupTime = CDRUtil::FormatTimeString(cdrvec.at(SetupTime).c_str());
	cdrinfo.m_SrcNumBeforeMap = cdrvec.at(SrcNumBeforeMap);
	cdrinfo.m_SrcPhoneNum = cdrvec.at(SrcPhoneNum);
	cdrinfo.m_TrmReason = cdrvec.at(TrmReason);
	
	m_pACDB->ProcessCDR(cdrinfo);
	m_CDRBuf.erase(begin,end);
}
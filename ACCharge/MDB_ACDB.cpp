/******************************************
MDB_ACDB.cpp
访问MDB数据库
******************************************/
#include "MDB_ACDB.h"
#include "WilcomLogger.h"

//创建CDR库cdr表语句
const char *sqlstr = "CREATE TABLE CDR(CallId Text(50),SetupTime Text(50),ConnectTime Text(50),ReleaseTime Text(50),SrcPhoneNum Text(50),SrcNumberBeforeMap Text(50), DstPhoneNum Text(50),DstNumbeforeMap Text(50), Duart Integer,TrmReason Text(50))";

MDB_ACDB::MDB_ACDB()
{
	string cdrdbpath =CDRUtil::GetSelfDirectory() + "cdr.mdb";
	WIN32_FIND_DATA fd; 
	HRESULT hr = S_OK;
	HANDLE hFind = FindFirstFile(cdrdbpath.c_str(), &fd); 
	
	m_ConnectString = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + cdrdbpath;
	
	m_pConnection.CreateInstance(__uuidof(Connection));
	if(hFind != INVALID_HANDLE_VALUE) 
	{
		m_pConnection->Open(m_ConnectString.c_str(),"","",adModeUnknown);
		return; 
	}
	try 
	{ 
		ADOX::_CatalogPtr pCatalog = NULL; 
		variant_t RecordsAffected;
		
		hr = pCatalog.CreateInstance(__uuidof (ADOX::Catalog)); 
		if(FAILED(hr)) 
			_com_issue_error(hr); 
		else 
			pCatalog->Create(_bstr_t(m_ConnectString.c_str())); //Create mdb
			m_pConnection->Open(m_ConnectString.c_str(),"","",adModeUnknown);
			m_pConnection->Execute(sqlstr, &RecordsAffected, adCmdText);
			m_pConnection->Close();
	}
	catch(_com_error &e)
	{
		//打印日志至文件
		sprintf(ErrorMsg,ERROR_MSG_MDB_CONNECT,m_ConnectString.c_str(),e.ErrorMessage(),e.Description());
		WriteLog(ErrorMsg,E);
		return;
	}
}

bool MDB_ACDB::Open()
{
	if (!IsOpen())
	{
		HRESULT hr = S_OK;
		try
		{
			hr = m_pConnection.CreateInstance(__uuidof(Connection));

			if (SUCCEEDED(hr))
			{
				hr = m_pConnection->Open(_bstr_t(m_ConnectString.c_str()),
					"",
					"",
					adModeUnknown);
			}
			return hr == S_OK;
		} 
		catch(_com_error &e)
		{
			sprintf(ErrorMsg,ERROR_MSG_MDB_CONNECT,m_ConnectString.c_str(),e.ErrorMessage(),e.Description());
			WriteLog(ErrorMsg,E);
			return false;
		}
	}
	return true;
}

void MDB_ACDB::ProcessCDR(CDRINFO &cdrinfo)
{
	char insertsql[1024];
	memset(insertsql,0,1024);
	sprintf(insertsql, "INSERT INTO CDR\
           (CallId\
           ,SetupTime\
           ,ConnectTime\
           ,ReleaseTime\
           ,SrcPhoneNum\
           ,SrcNumberBeforeMap\
           ,DstPhoneNum\
           ,DstNumbeforeMap\
           ,Duart\
           ,TrmReason)\
			VALUES\
		   ('%s',\
		    '%s',\
			'%s',\
		    '%s',\
			'%s',\
		    '%s',\
			'%s',\
		    '%s',\
			 %d,\
		    '%s'\
			)",cdrinfo.m_CallId.c_str(),
			cdrinfo.m_SetupTime.c_str(),
			cdrinfo.m_ConnectTime.c_str(),
			cdrinfo.m_ReleaseTime.c_str(),
			cdrinfo.m_SrcPhoneNum.c_str(),
			cdrinfo.m_SrcNumBeforeMap.c_str(),
			cdrinfo.m_DstPhoneNum.c_str(),
			cdrinfo.m_DstNumBeforeMap.c_str(),
			cdrinfo.m_Durat,
			cdrinfo.m_TrmReason.c_str());
	try 
	{ 
		m_pConnection->Execute(insertsql,NULL,adCmdText);
	}
	catch(_com_error &e)
	{
		//打印日志
		sprintf(ErrorMsg,ERROR_EXEC_MDB_INSERTCDR,insertsql,e.ErrorMessage(),e.Description());
		WriteLog(ErrorMsg,E);
		return;
	}
}
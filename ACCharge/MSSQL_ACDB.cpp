/******************************************
MSSQL_ACDB.cpp
访问MSSQL数据库
******************************************/
#include "MSSQL_ACDB.h"
#include "WilcomLogger.h"

bool MSSQL_ACDB::Open()
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
					_bstr_t(m_user.c_str()),
					_bstr_t(m_pwd.c_str()),
					adModeUnknown);
			}
			return hr == S_OK;
		} 
		catch(_com_error &e)
		{
			sprintf(ErrorMsg,ERROR_MSG_MSSQL_CONNECT,m_ConnectString.c_str(),e.ErrorMessage(),e.Description());
			WriteLog(ErrorMsg,E);
			return false;
		}
	}	
	return true;
}

void MSSQL_ACDB::ProcessCDR(CDRINFO &cdrinfo)
{
	_ParameterPtr CallId	  = NULL;
	_ParameterPtr SetupTime   = NULL;
	_ParameterPtr ConnectTime = NULL;
	_ParameterPtr ReleaseTime = NULL;
	_ParameterPtr SrcPhoneNum = NULL;
	_ParameterPtr SrcNumBeforeMap = NULL;
	_ParameterPtr DstPhoneNum = NULL;
	_ParameterPtr DstNumBeforeMap = NULL;
	_ParameterPtr Durat = NULL;
	_ParameterPtr TrmReason = NULL;

	CallId.CreateInstance(__uuidof(Parameter));
	SetupTime.CreateInstance(__uuidof(Parameter));
	ConnectTime.CreateInstance(__uuidof(Parameter));
	ReleaseTime.CreateInstance(__uuidof(Parameter));
	SrcPhoneNum.CreateInstance(__uuidof(Parameter));
	SrcNumBeforeMap.CreateInstance(__uuidof(Parameter));
	DstPhoneNum.CreateInstance(__uuidof(Parameter));
	DstNumBeforeMap.CreateInstance(__uuidof(Parameter));
	Durat.CreateInstance(__uuidof(Parameter));
	TrmReason.CreateInstance(__uuidof(Parameter));

	m_pCommand.CreateInstance(__uuidof(Command));
	m_pCommand->ActiveConnection = m_pConnection;
	m_pCommand->CommandType = adCmdStoredProc;
	m_pCommand->CommandText = _bstr_t("InsertCDR");//存储过程名

	/*
	@CallId varchar(50),
		@SetupTime varchar(50),
		@ConnectTime varchar(50),
		@ReleaseTime varchar(50),
		@SrcPhoneNum varchar(50),
		@SrcNumberBeforeMap varchar(50),
		@DstPhoneNum varchar(50),
		@DstNumBeforeMap varchar(50),
		@Duart integer,
		@TrmReason varchar(50)

		@CallId char(50),
		@SetupTime char(50),
		@ConnectTime char(50),
		@ReleaseTime char(50),
		@SrcPhoneNum char(50),
		@SrcNumberBeforeMap char(50),
		@DstPhoneNum char(50),
		@DstNumBeforeMap char(50),
		@Duart integer,
		@TrmReason char(50)
	*/
	CallId = m_pCommand->CreateParameter(_bstr_t("@CallId"),adVarChar,adParamInput,50);
	CallId->Value = _variant_t(cdrinfo.m_CallId.c_str());


	SetupTime=m_pCommand->CreateParameter(_bstr_t("@SetupTime"),adVarChar,adParamInput,50);  
	SetupTime->Value = _variant_t(cdrinfo.m_SetupTime.c_str());

	ConnectTime=m_pCommand->CreateParameter(_bstr_t("@ConnectTime"),adVarChar,adParamInput,50);
	ConnectTime->Value = _variant_t(cdrinfo.m_ConnectTime.c_str());

	ReleaseTime=m_pCommand->CreateParameter(_bstr_t("@ReleaseTime"),adVarChar,adParamInput,50);
	ReleaseTime->Value = _variant_t(cdrinfo.m_ReleaseTime.c_str());

	SrcPhoneNum = m_pCommand->CreateParameter(_bstr_t("@SrcPhoneNum"),adChar,adParamInput,50);
	SrcPhoneNum->Value = _variant_t(cdrinfo.m_SrcPhoneNum.c_str());

	SrcNumBeforeMap=m_pCommand->CreateParameter(_bstr_t("@SrcNumberBeforeMap"),adChar,adParamInput,50);  
	SrcNumBeforeMap->Value = _variant_t(cdrinfo.m_SrcNumBeforeMap.c_str());

	DstPhoneNum=m_pCommand->CreateParameter(_bstr_t("@DstPhoneNum"),adChar,adParamInput,50);
	DstPhoneNum->Value = _variant_t(cdrinfo.m_DstPhoneNum.c_str());

	DstNumBeforeMap=m_pCommand->CreateParameter(_bstr_t("@DstNumBeforeMap"),adChar,adParamInput,50);
	DstNumBeforeMap->Value = _variant_t(cdrinfo.m_DstNumBeforeMap.c_str());

	Durat = m_pCommand->CreateParameter(_bstr_t("@Duart"),adInteger,adParamInput,sizeof(int));
	Durat->Value = _variant_t(cdrinfo.m_Durat);

	TrmReason=m_pCommand->CreateParameter(_bstr_t("@TrmReason"),adChar,adParamInput,50);  
	TrmReason->Value = _variant_t(cdrinfo.m_TrmReason.c_str());

	m_pCommand->Parameters->Append(CallId);
	m_pCommand->Parameters->Append(SetupTime);
	m_pCommand->Parameters->Append(ConnectTime);
	m_pCommand->Parameters->Append(ReleaseTime);
	m_pCommand->Parameters->Append(SrcPhoneNum);
	m_pCommand->Parameters->Append(SrcNumBeforeMap);
	m_pCommand->Parameters->Append(DstPhoneNum);
	m_pCommand->Parameters->Append(DstNumBeforeMap);
	m_pCommand->Parameters->Append(Durat);
	m_pCommand->Parameters->Append(TrmReason);
	
	//执行
	try
	{
		m_pCommand->Execute(NULL,NULL,adCmdStoredProc);
	}
	catch(_com_error &e)//捕捉异常
	{
		//记录失败日志
		sprintf(ErrorMsg,ERROR_EXEC_MSSQL_INSERTCDR,e.ErrorMessage(),e.Description());
		WriteLog(ErrorMsg,E);
	}
}







#include "CDRUtil.h"
#include "WilcomLogger.h"

SYSPARM	SysParam;

/*********************************************************************************************
Method    :InitLooger
Summary   :初始化日志功能
Parameters:None
return    :void
2008-07-05 added by doug han
*********************************************************************************************/
void CDRUtil::InitLogger()
{
	string path = GetSelfDirectory()+ "Config\\log4Cxx.properties";
	SvrInitLogger(path.c_str());

}
/*********************************************************************************************
	Method    :GetConfigParams
	Summary   :从文件中获得配置信息
	Parameters:None
	return    :void
	2008-07-05 added by doug han
********************************************************************************************/
void CDRUtil::GetConfigParams(void)
{
	char								buf[MAX_PATH], localPort[128];
	char								* pright;
	char								sectionname[1024];
	string								section;
	strcpy(SysParam.m_sqltype,"MDB");

	GetModuleFileName(NULL, buf, MAX_PATH);

	pright = strrchr(buf, '\\');

	if ( pright )
		*pright = '\0';

	strcat(buf, "\\cdrcfg");

	GetPrivateProfileSectionNames(sectionname,1024,buf);
	section = sectionname;
	while(section.length()!=0)
	{
		//默认数据库类型为MSSQL
		if (section == "dbserver")
		{
			GetPrivateProfileString("dbserver", "Type", "MSSQL", SysParam.m_sqltype, 1024, buf);
			GetPrivateProfileString("dbserver", "IP", "127.0.0.1", SysParam.m_dbip, 1024, buf);
			GetPrivateProfileString("dbserver", "Name", "CDR", SysParam.m_dbname, 1024, buf);
			GetPrivateProfileString("dbserver", "LoginID", "sa", SysParam.m_dbuser, 1024, buf);
			GetPrivateProfileString("dbserver", "Password", "sa", SysParam.m_dbpwd, 1024, buf);
		} 
		section = sectionname + section.length();
	}
	GetPrivateProfileString("NET", "Port", "514", localPort, 128, buf);
	SysParam.m_localport = atoi(localPort);
}




/*********************************************************************************************
	Method    :SaveConfigParams
	Summary   :保存配置信息
	Parameters:None
	return    :void
	2008-07-05 added by doug han
********************************************************************************************/
void CDRUtil::SaveConfigParams(void)
{
	char								buf[MAX_PATH], localPort[64];
	char								* pright;


	GetModuleFileName(NULL, buf, MAX_PATH);

	pright = strrchr(buf, '\\');

	if ( pright )
		*pright = '\0';

	strcat(buf, "\\cdrcfg");

/*
	WritePrivateProfileString("CTI", "TServerName", SysParam.serverID, buf);
	WritePrivateProfileString("CTI", "LoginID", SysParam.loginID, buf);
	WritePrivateProfileString("CTI", "Password", SysParam.passwd, buf);
	sprintf(localPort, "%d", SysParam.remotePort);
	WritePrivateProfileString("NET", "Port", localPort, buf);
	WritePrivateProfileString("NET", "IP", SysParam.IP, buf);
	*/
}


/*********************************************************************************************
	Method    :GetSelfDirectory
	Summary   :获取当前运行目录
	Parameters:None
	return    :void
	2008-07-05 added by doug han
********************************************************************************************/
std::string CDRUtil::GetSelfDirectory()
{
	char								buf[MAX_PATH];
	char								* pright;


	GetModuleFileName(NULL, buf, MAX_PATH);

	pright = strrchr(buf, '\\');
	if ( pright )
		*(pright + 1) = '\0';

	return buf;
}

/************************************************************************************************
Method    :FormatTimeString
Summary   :格式化UTC时间字符串
Parameters:char *p_timestring[in]
return    :void
2008-07-05 added by doug han
************************************************************************************************/
std::string CDRUtil::FormatTimeString(const char *p_timestring)
{
	//时间字段为空,返回空
	if (*p_timestring == 32)
	{
		return "";
	}
	unsigned int year,month,day,hour,minute,second,missecond;
	char szWeekday[8]={0};
	char szMonth[8]={0};
	char szDate[50]={0};
	string time;
	sscanf(p_timestring,UTC_TIME_FORMAT,&hour,&minute,&second,&missecond,szWeekday,szMonth,&day,&year);
	
	month = ParseMonth(szMonth);
	sprintf(szDate,STD_TIME_FORMAT,year,month,day,hour,minute,second);
	return time.assign(szDate);
}

unsigned int CDRUtil::ParseMonth(const char *p_month)
{
	static const char *abmon[12] = {
		"Jan", "Feb", "Mar", "Apr", "May", "Jun",
		"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
	};

	char last = *(p_month+2);
	switch(last)
	{
	case 'n':
			if(*(p_month+1) == 'a')
			{
				return 1;
			}
			if(*(p_month+1) == 'u')
			{
				return 6;
			}
			break;
	case 'b':
			return 2;
			break;
	case  'r':
			if(*(p_month+1) == 'a')
			{
				return 3;
			}
			if(*(p_month+1) == 'p')
			{
				return 4;
			}
			break;
	case 'y':
				return 5;
			break;
	case 'l':
				return 7;
			break;
	case 'g':
				return 8;
			break;
	case 'p':
				return 9;
			break;
	case 't':
				return 10;
			break;
	case 'v':
				return 11;
			break;
	case 'c':
				return 12;
			break;
	}
}
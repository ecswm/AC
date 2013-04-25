/****************************************************
ACDef.h
CDR字段常量定义
added by carterliu at 2013/3/20
*****************************************************/

#ifndef _ACDEF_H
#define _ACDEF_H
#include <string>
using namespace std;

/*********************************************
CDR字段索引常量定义
*********************************************/
const string   CDRHeader = "CALL_END";
const unsigned int  ReportType = 0;
const unsigned int  Cid		   = 1;
const unsigned int  CallId     = 2;
const unsigned int  Trunk      = 3;
const unsigned int  BChan      = 4;
const unsigned int  ConId      = 5;
const unsigned int  TG         = 6;
const unsigned int  EPTyp      = 7;
const unsigned int  Orig       = 8;
const unsigned int  SourceIp   = 9;
const unsigned int  DestIp     = 10;
const unsigned int  STON       = 11;
const unsigned int  SNPI       = 12;
const unsigned int  SrcPhoneNum= 13;
const unsigned int  SrcNumBeforeMap= 14;
const unsigned int  DTON	   = 15;
const unsigned int  DNPI       = 16;
const unsigned int  DstPhoneNum= 17;
const unsigned int  DstNumBeforeMap=18;
const unsigned int  Durat      = 19;
const unsigned int  Coder      = 20;
const unsigned int  Intrv      = 21;
const unsigned int  RptIp      = 22;
const unsigned int  Port       = 23;
const unsigned int  TrmSd      = 24;
const unsigned int  TrmReason  = 25;
const unsigned int  Fax        = 26;
const unsigned int  InPackets  = 27;
const unsigned int  OutPackets = 28;
const unsigned int  PackLoss   = 29;
const unsigned int  RemotePackLoss=30;
const unsigned int  UniqueId   = 31;
const unsigned int  SetupTime  = 32;
const unsigned int  ConnectTime= 33;
const unsigned int  ReleaseTime= 34;
const unsigned int  RTPdelay   = 35;
const unsigned int  RTPjitter  = 36;
const unsigned int  RTPssrc    = 37;
const unsigned int  RemoteRTPssrc=38;
const unsigned int  RedirectReason=39;
const unsigned int  RTON       = 40;
const unsigned int  MeteringPulses=41;
const unsigned int  RNPI	   = 42;
const unsigned int  RedirectPhonNum=43;

/*************************************
CDR信息结构体定义
**************************************/
typedef 
struct
{
	string m_CallId;
	string m_SetupTime;
	string m_ConnectTime;
	string m_ReleaseTime;
	string m_SrcPhoneNum;
	string m_SrcNumBeforeMap;
	string m_DstPhoneNum;
	string m_DstNumBeforeMap;
	unsigned long m_Durat;
	string m_TrmReason;
} CDRINFO;

/************************************
配置参数结构体定义
************************************/
typedef
struct 
{
	unsigned short m_localport;
	char     m_sqltype[64];
	unsigned short m_dbport;
	char 	 m_dbip[64];
	char	 m_dbname[64];
	char 	 m_dbuser[64];
	char 	 m_dbpwd[64];
} SYSPARM;

/***********************************
错误消息格式字符串常量定义
************************************/
const char ERROR_MSG_MDB_CONNECT[] =   {"connect mdb (%s) error,message:%s,desc: %s"};
const char ERROR_MSG_MSSQL_CONNECT[] = {"connect sqldb (%s) error,message:%s,desc:%s"};
const char ERROR_MSG_ORACLE_CONNECT[] ={"connect oradb (%s) error,message:%s,desc:%s"};
const char ERROR_EXEC_MDB_INSERTCDR[] = {"insert cdr mdb error,sql:%s,message:%s,desc:%s"};
const char ERROR_EXEC_MSSQL_INSERTCDR[] = {"insert cdr mssql error,message:%s,desc:%s"};
const char ERROR_EXEC_ORACLE_INSERTCDR[] = {"insert cdr oracle error,message:%s,desc:%s"};

/************************************
时间格式字符串定义
UTC时间字符串
STD时间字符串
************************************/
const char UTC_TIME_FORMAT[] = {"%02d:%02d:%02d.%04d  UTC %03s %03s %02d %04d"};
const char STD_TIME_FORMAT[] = {"%04d-%02d-%02d %02d:%02d:%02d"};
#endif
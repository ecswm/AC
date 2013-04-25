/************************************************************************
*																		*
* WilcomLogger.h													    *
*																		*
* Copyright (c) 2003-2013 Shanghai Wilcom Information					*
* Technology Co., Ltd.													*
*																		*
* Created by CarterLiu on 19-06 2009								    *
************************************************************************/




#ifndef WILCOM_LOGGER_H
#define   WILCOM_LOGGER_H


#ifdef  WilcomLoggerDLL_EXPORTS
#define Wilcom_Logger_DLL_API  __declspec(dllexport)
#else

#define Wilcom_Logger_DLL_API  __declspec(dllimport)
#endif





enum LogLev{D,T,I,W,E,F};


#ifdef __cplusplus
extern "C" 
{
#endif

Wilcom_Logger_DLL_API void  __stdcall InitLogger();
Wilcom_Logger_DLL_API void  __stdcall SvrInitLogger(const char *path);
Wilcom_Logger_DLL_API void  __stdcall WriteLog(const char *p_EventStr,LogLev p_LogLevel);
Wilcom_Logger_DLL_API void  __stdcall SetLogLev();


#ifdef __cplusplus
}
#endif


#endif
/************************************************************************
 *																		*
 * CDRUtil.hpp															*
 *																		*							
 *																		*
 ************************************************************************/




#ifndef _CDR_UTIL_H
#define _CDR_UTIL_H

#pragma once

#include "ACCDRInfo.h"
#include <time.h>
#include <windows.h>

class CDRUtil
{
public:
	static void InitLogger();
	static void GetConfigParams(void);
	static void SaveConfigParams(void);
	static string GetSelfDirectory();
	static string FormatTimeString(const char *p_timestring);
	static unsigned int  ParseMonth(const char *p_month);
};

extern SYSPARM	SysParam;

#endif
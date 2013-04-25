// ACCharge.cpp : 定义控制台应用程序的入口点。
//

#include <string>  
#include <iostream>  
using namespace std; 
#include "ace/Functor.h"
#include "ace/SOCK_Dgram.h"
#include "ace/Log_Msg.h"
#include "Reactive_CDRServer.h"
#include "WilcomLogger.h"
#include "CDRServiceProcess.h"
#include "CDRUtil.h"
#include "ace/Get_Opt.h"

ACE_NT_SERVICE_DEFINE (CDRServicer,
					   CDRServicerProcess,
					   ACE_TEXT ("CDR Service"));

#define DEFAULT_SERVICE_INIT_STARTUP     SERVICE_AUTO_START




/************************************
	Method    :parse_args
	Summary   :命令行参数解析
	Parameters:int argc [in],char *argv[] [in]
	return    :void
	2013-03-16 added by carter liu

************************************/
int opt_install=0;
int opt_remove=0;
int opt_start=0;
int opt_kill=0;
int opt_type=0;
int opt_debug=0;
int opt_port =0;
int opt_startup;

void print_usage_and_die()
{
	printf("Usage: %s"
			" -in -r -s -k -tn -d -p\n"
			"  -i: Install this program as an NT service, with specified startup\n"
			"  -r: Remove this program from the Service Manager\n"
			"  -s: Start the service\n"
			"  -k: Kill the service\n"
			"  -t: Set startup for an existing service\n"
			"  -d: Debug; run as a regular application\n"
			"  -p: port:Set Port for Server Listen");
	return;
}

void parse_args(int argc,char *argv[])
{
	const char options[] = ACE_TEXT("i:rskt:d::p:");
	ACE_Get_Opt get_opt(argc,argv,options,1,0,ACE_Get_Opt::PERMUTE_ARGS,1);
	int b = get_opt.long_option(ACE_TEXT("port"),'p',ACE_Get_Opt::ARG_REQUIRED);
	int c;

	while((c=get_opt())!=-1)
		switch(c)
	{
		case 'i':
			opt_install = 1;
			opt_startup = ACE_OS::atoi (get_opt.opt_arg ());
			if (opt_startup <= 0)
				print_usage_and_die ();
				break;
		case 'r':
			opt_remove = 1;
			break;
		case 's':
			opt_start = 1;
			break;
		case 'k':
			opt_kill = 1;
			break;
		case 't':
			opt_type = 1;
			opt_startup = ACE_OS::atoi (get_opt.opt_arg ());
			if (opt_startup <= 0)
				print_usage_and_die ();
				break;
		case 'd':
			opt_debug = 1;
			break;
		case 'p':
			opt_port = ACE_OS::atoi(get_opt.opt_arg());
			if(opt_port <= 0)
				opt_port = 514;
				print_usage_and_die();
				break;
		default:
			// -i can also be given without a value - if so, it defaults
			// to defined value.
			if (ACE_OS::strcmp (get_opt.argv ()[get_opt.opt_ind () - 1], ACE_TEXT ("-i")) == 0)
			{
				opt_install = 1;
				opt_startup = DEFAULT_SERVICE_INIT_STARTUP;
			}
			else
			{
				print_usage_and_die ();
			}
			break;

	}
}

int main(int argc, char *argv[])
{
	CDRUtil::InitLogger();
	CDRUtil::GetConfigParams();

	p_CDRHandle = new CDRHandle();

	SCDRServiceProcess::instance ()->name (ACE_TEXT ("CDRServicer"),
		ACE_TEXT ("AudioCode CDR Service"));
	
	parse_args(argc,argv);

	if (opt_install && !opt_remove)
	{
		if (-1 == SCDRServiceProcess::instance ()->insert (opt_startup))
		{
			ACE_ERROR ((LM_ERROR, ACE_TEXT ("%p\n"), ACE_TEXT ("insert")));
			return -1;
		}
		return 0;
	}

	if (opt_remove && !opt_install)
	{
		if (-1 == SCDRServiceProcess::instance ()->remove ())
		{
			ACE_ERROR ((LM_ERROR, ACE_TEXT ("%p\n"), ACE_TEXT ("remove")));
			return -1;
		}
		return 0;
	}

	if (opt_start && opt_kill)
		print_usage_and_die ();

	if (opt_start)
	{
		if (-1 == SCDRServiceProcess::instance ()->start_svc ())
		{
			ACE_ERROR ((LM_ERROR, ACE_TEXT ("%p\n"), ACE_TEXT ("start")));
			return -1;
		}
		return 0;
	}

	if (opt_kill)
	{
		if (-1 == SCDRServiceProcess::instance ()->stop_svc ())
		{
			ACE_ERROR ((LM_ERROR, ACE_TEXT ("%p\n"), ACE_TEXT ("stop")));
			return -1;
		}
		return 0;
	}

	if (opt_type)
	{
		if (-1 == SCDRServiceProcess::instance ()->startup (opt_startup))
		{
			ACE_ERROR ((LM_ERROR, ACE_TEXT ("%p\n"), ACE_TEXT ("set startup")));
			return -1;
		}
		return 0;
	}
	
	if (opt_debug)
	{
		SCDRServiceProcess::instance ()->svc ();
	}
	else
	{
		ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("%T (%t): Starting service.\n")));

	ACE_NT_SERVICE_RUN (CDRServicer,
		SCDRServiceProcess::instance (),
		ret);
	if (ret == 0)
		ACE_ERROR ((LM_ERROR,
		ACE_TEXT ("%p\n"),
		ACE_TEXT ("Couldn't start service")));
	else
		ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("%T (%t): Service stopped.\n")));

	}
	return 0;
}



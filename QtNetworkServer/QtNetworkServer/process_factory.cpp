#include "process_factory.h"
#include "process_register.h"
#include "process_login.h"


CmdProcessFactory::CmdProcessFactory()
{
}


CmdProcessFactory::~CmdProcessFactory()
{
}

CmdProcessFactory & CmdProcessFactory::instance()
{
	static CmdProcessFactory obj;
	return obj;
}

ProcessInterface *CmdProcessFactory::getProcess(CommandType type)
{
	ProcessInterface* cmd = 0;
	switch (type)
	{
	case CT_REGISTER:
	{
		cmd = new ProcessRegister;
	}
	break;
	case CT_LOGIN:
	{
		cmd = new ProcessLogin;
	}
	break;
	default:
		break;
	}
	return cmd;
}

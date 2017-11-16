#include "command_factory.h"

#include "command_def.h"

CommandFactory::CommandFactory()
{
}


CommandFactory::~CommandFactory()
{
}

CommandFactory & CommandFactory::Instance()
{
	static CommandFactory obj;
	return obj;
}

Command * CommandFactory::getCommand(CommandType type)
{
	Command *command = 0;
	switch (type)
	{
	case CT_REGISTER:
	{
		command = new CommandRegister;
	}
	break;
	case CT_REGISTER_RESPONSE:
	{
		command = new CommandRegisterResponse;
	}
	break;
	case CT_LOGIN:
	{
		command = new CommandLogin;
	}
	break;
	case CT_LOGIN_RESPONSE:
	{
		command = new CommandLoginResponse;
	}
	break;
	case CT_MESSAGE:
	{
		command = new CommandMessage;
	}
	break;
	case CT_GENERAL_RESPONSE:
	{
		command = new GeneralResponse;
	}
	break;
	default:
		break;
	}

	return command;
}

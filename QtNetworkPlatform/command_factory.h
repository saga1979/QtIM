#pragma once
#include "command_interface.h"

class CommandFactory
{
protected:
	CommandFactory();
public:
	
	~CommandFactory();
	static CommandFactory& Instance();
	Command* getCommand(CommandType);
};


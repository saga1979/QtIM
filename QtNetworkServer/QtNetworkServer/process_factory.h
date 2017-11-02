#pragma once
#include "process_interface.h"
#include "command_def.h"
class CmdProcessFactory
{
protected:
	CmdProcessFactory();
public:	
	~CmdProcessFactory();
	static CmdProcessFactory& instance();
	ProcessInterface* getProcess(CommandType);
};


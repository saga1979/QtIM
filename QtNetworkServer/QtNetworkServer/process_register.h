#pragma once
#include "process_interface.h"

class ProcessRegister : public ProcessInterface
{
public:
	ProcessRegister();
	~ProcessRegister();

	// Inherited via CommandProcess
	virtual bool ProcessCommand(const Command *, QAbstractSocket *, ClientInfoManager* = 0) override;
};


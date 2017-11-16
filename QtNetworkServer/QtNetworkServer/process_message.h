#pragma once
#include "process_interface.h"
class ProcessMessage :	public ProcessInterface
{
public:

	ProcessMessage() ;
	~ProcessMessage();
	// Inherited via ProcessInterface
	virtual bool ProcessCommand(const Command *, QAbstractSocket *, ClientInfoManager * = 0) override;

};


#pragma once
#include "process_interface.h"
class ProcessLogin: public ProcessInterface
{
public:
	ProcessLogin();
	~ProcessLogin();

	// Inherited via ProcessInterface
	virtual bool ProcessCommand(const Command *, QIODevice *) override;
};


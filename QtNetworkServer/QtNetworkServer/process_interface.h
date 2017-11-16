#pragma once

#include <QAbstractSocket>
#include "client_info_manager.h"
class Command;

class ProcessInterface
{
public:
	virtual bool ProcessCommand(const Command*, QAbstractSocket*, ClientInfoManager* = 0) = 0;
	virtual ~ProcessInterface() {};
};

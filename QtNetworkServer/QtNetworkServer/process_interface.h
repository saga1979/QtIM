#pragma once

#include <QIODevice>
class Command;

class ProcessInterface
{
public:
	virtual bool ProcessCommand(const Command*, QIODevice*) = 0;
	virtual ~ProcessInterface() {};
};

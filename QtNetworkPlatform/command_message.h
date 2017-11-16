#pragma once
#include "command_interface.h"

#include <string>
using std::string;

class QTNETWORKPLATFORM_EXPORT CommandMessage :	public Command
{
public:
	string from;
	string to;
	string msg;

	// Inherited via Command
	virtual const string to_data() const override;
	virtual int from_data(const string &) override;
	virtual CommandType type() const override;
	virtual int length() const override;
};


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

	virtual int from_data(const string &) override;
	virtual CommandType type() const override;	
protected:
	// Inherited via Command
	virtual const string internal_to_data() const override;
	virtual int internal_length() const override;
};


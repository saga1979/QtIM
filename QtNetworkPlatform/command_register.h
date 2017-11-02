#pragma once

#include "command_interface.h"
struct QTNETWORKPLATFORM_EXPORT CommandRegister : public Command
{
	string name;
	string pwd;
	string info;
	string img;
	// Inherited via CommandMessage
	virtual const string  to_data() const override;
	virtual int from_data(const string &) override;
	virtual  CommandType type() const;
	// Inherited via CommandMessage
	virtual int  length() const override;
};


#pragma once

#include "command_interface.h"
struct QTNETWORKPLATFORM_EXPORT CommandRegister : public Command
{
	string name;
	string pwd;
	string info;
	string img;

	virtual int from_data(const string &) override;
	virtual  CommandType type() const;
protected:
	// Inherited via CommandMessage
	virtual int  internal_length() const override;
	// Inherited via CommandMessage
	virtual const string  to_internal_data() const override;
};


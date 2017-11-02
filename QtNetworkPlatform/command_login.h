#pragma once

#include "command_interface.h"

struct QTNETWORKPLATFORM_EXPORT CommandLogin : public Command
{
	string name;
	string pwd;


	// Inherited via Command
	virtual const string to_data() const override;

	virtual int from_data(const string &) override;

	virtual CommandType type() const override;

	virtual int length() const override;

};



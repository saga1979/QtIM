#pragma once

#include "command_interface.h"

struct QTNETWORKPLATFORM_EXPORT CommandLogin : public Command
{
	string id;
	string pwd;	

	virtual int from_data(const string &) override;
	virtual CommandType type() const override;
protected:
	// Inherited via Command
	virtual const string to_internal_data() const override;
	virtual int internal_length() const override;
};



#pragma once

#include "command_interface.h"
//<request>0</request><success>1<success><msg>xxx</msg>
struct QTNETWORKPLATFORM_EXPORT GeneralResponse : public Command
{
	GeneralResponse();
	CommandType request;
	bool success;
	string msg;
	// Inherited via Command
	virtual const string to_data() const override;
	virtual int from_data(const string &) override;
	virtual CommandType type() const override;
	virtual int length() const override;
};


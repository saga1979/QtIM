#pragma once
#include "command_interface.h"
class QTNETWORKPLATFORM_EXPORT CommandLoginResponse :	public Command
{
public:

	bool success;
	std::string msg;
	
	virtual int from_data(const string &) override;
	virtual CommandType type() const override;
protected:
	// Inherited via Command
	virtual const string to_internal_data() const override;
	virtual int internal_length() const override;
};


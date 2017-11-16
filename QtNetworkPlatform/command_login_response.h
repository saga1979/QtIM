#pragma once
#include "command_interface.h"
class QTNETWORKPLATFORM_EXPORT CommandLoginResponse :	public Command
{
public:
	CommandLoginResponse();
	~CommandLoginResponse();

	bool success;
	std::string msg;
	// Inherited via Command
	virtual const string to_data() const override;
	virtual int from_data(const string &) override;
	virtual CommandType type() const override;
	virtual int length() const override;
};


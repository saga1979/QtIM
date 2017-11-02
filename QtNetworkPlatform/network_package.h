#pragma once

#include "command_interface.h"


struct QTNETWORKPLATFORM_EXPORT Package : public ISerializable
{
	Package();
	Package(Command* cmd);
	~Package();

	const Command* getCmd()const;

	int data_len() const;

	// Inherited via ISerializable
	virtual const string to_data() const override;

	virtual int  from_data(const string &) override;

	static const string to_data(const Command&);

private:
	Command *command;
};

#pragma once

#include <string>
#include <cstdint>

using std::string;


#include "command_type.h"


struct ISerializable
{
	virtual const string to_data() const = 0;
	virtual int from_data(const string&) = 0;
};

struct Command : public ISerializable
{
	virtual  CommandType type() const = 0;

	virtual  int  length() const = 0;

	virtual ~Command() {}

};

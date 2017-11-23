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

struct QTNETWORKPLATFORM_EXPORT Command : public ISerializable
{
	virtual  CommandType type() const = 0;

	virtual  int  length() const;

	virtual ~Command() {}


	// Inherited via ISerializable
	virtual const string to_data() const override;

protected:
	virtual const string internal_to_data() const = 0;
	virtual  int  internal_length() const = 0;

};

#include "command_general_response.h"


GeneralResponse::GeneralResponse() :success(false)
{
}

const string GeneralResponse::to_data() const
{
	return string();
}

int GeneralResponse::from_data(const string &)
{
	return 0;
}

CommandType GeneralResponse::type() const
{
	return CommandType();
}

int GeneralResponse::length() const
{
	return 0;
}

#include "command_interface.h"

int Command::length() const
{
	int len = strlen("<type>") * 2 + 1;
	len += sizeof(EnumType) ;
	len += internal_length();
	return len;
}

const string Command::to_data() const
{
	string data;

	data += "<type>";
	uint32_t tmp = type();
	data.append((const char*)&tmp, sizeof(EnumType));
	data += "</type>";

	data += internal_to_data();

	return data;
}





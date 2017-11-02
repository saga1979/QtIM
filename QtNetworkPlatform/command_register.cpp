#include "command_register.h"

#include "command_utilies.h"

CommandType CommandRegister::type() const
{
	return CT_REGISTER;
}
const string  CommandRegister::to_data() const
{
	string data;

	data += "<type>";
	uint32_t tmp = type();
	data.append((const char*)&tmp, sizeof(EnumType));
	data += "</type>";

	data += "<name>";
	data += this->name;
	data += "</name>";

	data += "<pwd>";
	data += pwd;
	data += "</pwd>";

	data += "<info>";
	data += info;
	data += "</info>";

	data += "<img>";
	data += img;
	data.append("</img>");

	return data;
}

int CommandRegister::from_data(const string &data)
{
	name = get_value(data, "name");
	pwd = get_value(data, "pwd");
	info = get_value(data, "info");
	img = get_value(data, "img");
	return 0;
}

int  CommandRegister::length() const
{
	int len = strlen("<type>") * 2 + 1;
	len += strlen("<pwd>") * 2 + 1;
	len += strlen("<info>") * 2 + 1;
	len += strlen("<img>") * 2 + 1;
	len += sizeof(EnumType);

	len += name.length();
	len += pwd.length();
	len += info.length();
	len += img.length();
	return len;//todo...
}


#include "command_login.h"
#include "command_utilies.h"

const string CommandLogin::to_data() const
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

	return data;
}

int CommandLogin::from_data(const string &data)
{
	name = get_value(data, "name");
	pwd = get_value(data, "pwd");

	return 0;
}

CommandType CommandLogin::type() const
{
	return CT_LOGIN;
}

int CommandLogin::length() const
{
	//¸½¼Ó×Ö·û<type></type>
	int len = strlen("<type>") * 2 + 1;
	len += strlen("<pwd>") * 2 + 1;
	len += strlen("<name>") * 2 + 1;
	//ÄÚÈÝ
	len += sizeof(EnumType);
	len += name.length();
	len += pwd.length();
	return len;
}

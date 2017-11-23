#include "command_login.h"
#include "command_utilies.h"

const string CommandLogin::internal_to_data() const
{
	string data;

	data += "<name>";
	data += this->id;
	data += "</name>";

	data += "<pwd>";
	data += pwd;
	data += "</pwd>";	

	return data;
}

int CommandLogin::from_data(const string &data)
{
	id = get_value(data, "name");
	pwd = get_value(data, "pwd");

	return 0;
}

CommandType CommandLogin::type() const
{
	return CT_LOGIN;
}

int CommandLogin::internal_length() const
{
	//¸½¼Ó×Ö·û<type></type>
	int len = strlen("<pwd>") * 2 + 1;
	len += strlen("<name>") * 2 + 1;
	//ÄÚÈÝ
	len += id.length();
	len += pwd.length();
	return len;
}

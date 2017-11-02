#include "command_register_response.h"

#include "command_utilies.h"



CommandRegisterResponse::CommandRegisterResponse() :success(false)
{

}
//<type>xxx</type><success>1</success>
const string CommandRegisterResponse::to_data() const
{
	string data;

	data += "<type>";
	uint32_t tmp = type();
	data.append((const char*)&tmp, sizeof(EnumType));
	data += "</type>";

	data += "<success>";
	data += success ? "1" : "0";
	data += "</success>";

	return data;

}

int  CommandRegisterResponse::from_data(const string &data)
{
	string str = get_value(data, "success");

	success = (str == "0" ? false : true);

	return 0;
}

CommandType CommandRegisterResponse::type() const
{
	return CT_REGISTER_RESPONSE;
}

int CommandRegisterResponse::length() const
{
	int len = strlen("<type>") * 2 + 1;
	len += strlen("<success>") * 2 + 1;
	len += sizeof(EnumType);
	len += 1;
	return len;//<success>1</success>
}
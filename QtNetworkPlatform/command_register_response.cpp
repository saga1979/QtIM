#include "command_register_response.h"

#include "command_utilies.h"



CommandRegisterResponse::CommandRegisterResponse() :success(false)
{

}
//<type>xxx</type><success>1</success>
const string CommandRegisterResponse::to_data() const
{
	string format_data;

	format_data += "<type>";
	uint32_t tmp = type();
	format_data.append((const char*)&tmp, sizeof(EnumType));
	format_data += "</type>";

	format_data += "<success>";
	format_data += success ? "1" : "0";
	format_data += "</success>";

	format_data += "<data>";
	format_data += data;
	format_data += "</data>";

	return format_data;

}

int  CommandRegisterResponse::from_data(const string &buff)
{
	string str = get_value(buff, "success");

	success = (str == "0" ? false : true);

	data = get_value(buff, "data");

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
	len += strlen("<data>") * 2 + 1;
	len += sizeof(EnumType);
	len += 1;
	len += data.length();
	return len;//<success>1</success>
}
#include "command_general_response.h"
#include "command_utilies.h"


GeneralResponse::GeneralResponse() :success(false)
{
}

const string GeneralResponse::internal_to_data() const
{
	string data;	

	data += "<cmd>";
	data.append((const char*)&request, sizeof(EnumType));;
	data += "</cmd>";

	data += "<success>";
	data += success?"1":"0";
	data += "</success>";

	data += "<msg>";
	data += msg;
	data += "</msg>";

	return data;
}

int GeneralResponse::from_data(const string &buff)
{
	string str = get_value(buff, "success");

	success = (str == "0" ? false : true);

	str = get_value(buff, "cmd");

	request = (CommandType) (*(EnumType*)(str.data()));

	msg = get_value(buff, "msg");
	return 0;
}

CommandType GeneralResponse::type() const
{
	return CT_GENERAL_RESPONSE;
}

int GeneralResponse::internal_length() const
{
	int len = strlen("<msg>") * 2 + 1;
	len += strlen("<success>") * 2 + 1;
	len += strlen("<cmd>") * 2 + 1;
	//ÄÚÈÝ
	len += sizeof(EnumType);
	len += msg.length();
	len += 1;//bool "0" or "1"
	return len;
}

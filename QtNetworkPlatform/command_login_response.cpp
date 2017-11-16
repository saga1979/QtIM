#include "command_login_response.h"
#include "command_utilies.h"


CommandLoginResponse::CommandLoginResponse()
{
}


CommandLoginResponse::~CommandLoginResponse()
{
}

const string CommandLoginResponse::to_data() const
{
	string data;

	data += "<type>";
	uint32_t tmp = type();
	data.append((const char*)&tmp, sizeof(EnumType));
	data += "</type>";

	data += "<success>";
	data += success ? "1" : "0";
	data += "</success>";

	data += "<msg>";
	data += msg;
	data += "</msg>";


	return data;
}

int CommandLoginResponse::from_data(const string &buff)
{
	string str = get_value(buff, "success");

	success = (str == "0" ? false : true);

	msg = get_value(buff, "msg");
	return 0;
}

CommandType CommandLoginResponse::type() const
{
	return CT_LOGIN_RESPONSE;
}

int CommandLoginResponse::length() const
{
	int len = strlen("<type>") * 2 + 1;
	len += strlen("<msg>") * 2 + 1;
	len += strlen("<success>") * 2 + 1;
	//ÄÚÈÝ
	len += sizeof(EnumType);
	len += msg.length();
	len += 1;//bool "0" or "1"
	return len;
}

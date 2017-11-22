#include "command_login_response.h"
#include "command_utilies.h"


const string CommandLoginResponse::to_internal_data() const
{
	string data;

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

int CommandLoginResponse::internal_length() const
{
	int len = strlen("<msg>") * 2 + 1;
	len += strlen("<success>") * 2 + 1;
	//ÄÚÈÝ
	len += msg.length();
	len += 1;//bool "0" or "1"
	return len;
}

#include "command_message.h"
#include "command_utilies.h"

/*

<type>xxx</type><from>xxx</from><to>xxx</to><msg>xxxx</msg>
					[*]表示所有人       
*/



const string CommandMessage::internal_to_data() const
{
	string data;

	data += "<from>";
	data += from;
	data += "</from>";

	data += "<to>";
	data += to;
	data += "</to>";

	data += "<msg>";
	data += msg;
	data += "</msg>";

	return data;
}

int CommandMessage::from_data(const string &data)
{
	from = get_value(data, "from");
	to = get_value(data, "to");
	msg = get_value(data, "msg");
	return 0;
}

CommandType CommandMessage::type() const
{
	return CT_MESSAGE;
}

int CommandMessage::internal_length() const
{
	int len = strlen("<from>") * 2 + 1;
	len += strlen("<to>") * 2 + 1;
	len += strlen("<msg>") * 2 + 1;

	len += from.length();
	len += to.length();
	len += msg.length();
	return len;
	
}

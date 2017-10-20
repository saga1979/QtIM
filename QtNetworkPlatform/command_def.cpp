#include "command_def.h"
#include <cassert>

static string get_value(const string& data, const string& start_name, const string& end_name)
{
	size_t start = data.find(start_name) + start_name.length();

	size_t end = data.find(end_name);

	string ret = data.substr(start, end - start);

	return ret;
}

static string get_value(const string& data, const string& name)
{

	string field_start = '<' + name + '>';
	string field_end = "</" + name + '>';

	return get_value(data, field_start, field_end);
}

const string  CommandRegister::to_data() const
{
	string data;

	data += "<type>";
	uint32_t tmp = type;
	data.append((const char*)&tmp, sizeof(uint32_t));	
	data += "</type>";
		
	data+= "<name>";
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

void CommandRegister::from_data(const string &data)
{
	type = (CommandType) *(uint32_t*)(get_value(data, "type").data());
	name = get_value(data, "name");
	pwd = get_value(data, "pwd");
	info = get_value(data, "info");
	img = get_value(data, "img");
}

uint16_t CommandRegister::len()
{
	assert(0);
	return 0;//todo...
}


static const char* package_start = "start";
static const char* package_end = "end";

Package::Package():message(0)
{
}

Package::~Package()
{
	if (message != 0)
	{
		delete message;
	}
}

const string Package::to_data() const
{
	string data;

	data += package_start;

	string tData = message->to_data();

	uint16_t len = tData.length();
	data.append((const char*)&len, sizeof(uint16_t));

	data.append(tData);

	data.append(package_end);


	return data;
}

void Package::from_data(const string &data)
{
	size_t start = data.find(package_start);

	if (start == string::npos)
	{
		return;
	}

	start += strlen(package_start);
	//取命令数据长度
	string slen = data.substr(start, 2);
	uint16_t len = *(uint16_t*)slen.data();

	string cmd_data = data.substr(start + sizeof(uint16_t), len);
	//取命令类型
	string stype = get_value(cmd_data, "type");
	uint32_t type = *(uint32_t*)stype.data();

	switch (type)
	{
	case CT_REGISTER:
	{
		message = new CommandRegister;		
	}
	break;
	case CT_MESSAGE:
	{
		message = new CommandMessage;
	}
	break;
	default:
		break;
	}

	if (message != 0)
	{
		message->from_data(cmd_data);
	}


}

const string CommandMessage::to_data() const
{
	return string();
}

void CommandMessage::from_data(const string &)
{
}

uint16_t CommandMessage::len()
{
	return uint16_t();
}

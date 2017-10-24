#include "command_def.h"
#include <cassert>

typedef uint32_t LenType;
typedef uint32_t EnumType;

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
	name = get_value(data, "name");
	pwd = get_value(data, "pwd");
	info = get_value(data, "info");
	img = get_value(data, "img");
}

int  CommandRegister::length () const
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
	return len ;//todo...
}


static const char* package_start = "start";
static const char* package_end = "end";

Package::Package():command(0)
{
}

Package::Package(Command * cmd):command(cmd)
{
}

Package::~Package()
{
	if (command != 0)
	{
		delete command;
	}
}

const string Package::to_data() const
{
	return Package::to_data(*this->command);
}

const string Package::to_data(const Command& cmd)
{
	string data;

	data += package_start;//开头

	string tData = cmd.to_data();

	LenType len = tData.length();
	data.append((const char*)&len, sizeof(LenType));//两个字节标识命令数据长度

	data.append(tData);//命令数据

	data.append(package_end);//结束

	return data;

}

int Package::data_len() const
{
	assert(command != 0);
	if (command == 0)
	{
		return -1;
	}
	return strlen(package_start) + sizeof(LenType) + command->length() + strlen(package_end);
}
void Package::from_data(const string &data)
{
	size_t start = data.find(package_start);
	size_t end_index = data.find(package_end);

	if (start == string::npos || end_index == string::npos)
	{
		return;//初步校验包是否完整
		//还需要根据数据长度确认在符合协议规范的位置出现结尾标识
	}

	start += strlen(package_start);
	//取命令数据长度
	string slen = data.substr(start, sizeof(LenType));
	LenType len = *(LenType*)slen.data();

	string cmd_data = data.substr(start + sizeof(LenType), len);
	//取命令类型
	string stype = get_value(cmd_data, "type");
	EnumType type = *(EnumType*)stype.data();

	switch (type)
	{
	case CT_REGISTER:
	{
		command = new CommandRegister;		
	}
	break;
	case CT_MESSAGE:
	default:
		break;
	}
	if (command != 0)
	{
		command->from_data(cmd_data);
	}
}

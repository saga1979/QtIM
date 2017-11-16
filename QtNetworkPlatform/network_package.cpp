#include <cassert>
#include "network_package.h"
#include "command_utilies.h"
#include "command_factory.h"


static const char* package_start = "start";
static const char* package_end = "end";

Package::Package() :command(0)
{
}

Package::Package(Command * cmd) : command(cmd)
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
	data.append((const char*)&len, sizeof(LenType));//标识命令数据长度

	data.append(tData);//命令数据

	data.append(package_end);//结束

	return data;

}

const string Package::to_data(const Command *cmd)
{
	return to_data(*cmd);
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

const Command* Package::getCmd() const
{
	return command;
}
int  Package::from_data(const string &data)
{
	size_t start = data.find(package_start);
	size_t end_index = data.find(package_end);

	if (start == string::npos || end_index == string::npos)
	{
		return -1;//初步校验包是否完整
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

	command = CommandFactory::Instance().getCommand((CommandType)type);
	if (command == 0)
	{
		return -1;
	}
	command->from_data(cmd_data);
	return end_index + strlen(package_end);
}
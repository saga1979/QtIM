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

	data += package_start;//��ͷ

	string tData = cmd.to_data();

	LenType len = tData.length();
	data.append((const char*)&len, sizeof(LenType));//��ʶ�������ݳ���

	data.append(tData);//��������

	data.append(package_end);//����

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
		return -1;//����У����Ƿ�����
				  //����Ҫ�������ݳ���ȷ���ڷ���Э��淶��λ�ó��ֽ�β��ʶ
	}

	start += strlen(package_start);
	//ȡ�������ݳ���
	string slen = data.substr(start, sizeof(LenType));
	LenType len = *(LenType*)slen.data();

	string cmd_data = data.substr(start + sizeof(LenType), len);
	//ȡ��������
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
#include "process_register.h"
#include "command_def.h"
#include "datasource.h"


ProcessRegister::ProcessRegister()
{
}


ProcessRegister::~ProcessRegister()
{
}

bool ProcessRegister::ProcessCommand(const Command *command, QAbstractSocket *io, ClientInfoManager*)
{
	CommandRegister* cmd = (CommandRegister*)command;

	if (cmd == 0)
	{
		return false;
	}

	UserInfo info;
	info.name = QString::fromStdString(cmd->name);
	info.pwd = QString::fromStdString(cmd->pwd);
	info.img = QByteArray::fromRawData(cmd->img.data(), cmd->img.length());

	CommandRegisterResponse response;

	if (DataSource::Instance().RegisterUser(info))
	{
		response.success = true;
		response.data =  info.id.toStdString();//注册成功,返回产生的ID
	}

	string data = Package::to_data(response);

	io->write(data.data(), data.length());

	return true;

}

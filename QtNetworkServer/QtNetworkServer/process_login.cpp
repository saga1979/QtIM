#include "process_login.h"
#include "command_def.h"
#include "datasource.h"


ProcessLogin::ProcessLogin()
{
}


ProcessLogin::~ProcessLogin()
{
}

bool ProcessLogin::ProcessCommand(const Command *command, QIODevice *io)
{
	CommandLogin* cmd = (CommandLogin*)command;
	//校验用户登陆是否合法

	UserInfo* info = DataSource::Instance().getUserInfo(cmd->name);

	GeneralResponse response;

	response.command_request = CT_LOGIN_RESPONSE;
	if (info == 0)//没有此用户
	{
		response.msg = "user not exist";
	}
	else if (cmd->pwd != info->pwd.toStdString())//密码是否正确
	{
		response.msg = "password not correct";
	}
	else
	{
		response.success = true;
	}

	string data = Package::to_data(response);

	io->write(data.data(), data.length());

	return response.success;

}

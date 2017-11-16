#include <cassert>
#include "process_login.h"
#include "command_def.h"
#include "datasource.h"


ProcessLogin::ProcessLogin()
{
}


ProcessLogin::~ProcessLogin()
{
}

bool ProcessLogin::ProcessCommand(const Command *command, QAbstractSocket *io, ClientInfoManager* manager)
{
	CommandLogin* cmd = (CommandLogin*)command;
	//校验用户登陆是否合法

	UserInfo* info = DataSource::Instance().getUserInfo(cmd->id);

	//GeneralResponse response;

	//response.request = CT_LOGIN_RESPONSE;

	CommandLoginResponse response;
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
		//将认证成功的客户端加入客户端管理
		ClientInfo* info = new ClientInfo;

		info->setId(QString::fromStdString(cmd->id));
		info->setSocket(io);
		assert(manager);
		manager->add(info);
	}

	string data = Package::to_data(response);

	io->write(data.data(), data.length());

	return response.success;

}

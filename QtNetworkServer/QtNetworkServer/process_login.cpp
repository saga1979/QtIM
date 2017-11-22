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
	}

	string data = Package::to_data(response);

	io->write(data.data(), data.length());

	//如果认证成功

	if (response.success)
	{		
		//将认证成功的客户端加入客户端管理
		ClientInfo* info = new ClientInfo;

		info->setId(QString::fromStdString(cmd->id));
		info->setSocket(io);
		assert(manager);
		manager->add(info);

		//发送在线用户信息

		QList<ClientInfo*> *clients =  manager->getOnlineClients();
		CommandUserStatus userStatus;
		UserStatus status;
		for (QList<ClientInfo*>::ConstIterator it = clients->cbegin(); it != clients->cend(); it++)
		{
			status.id = (*it)->id().toStdString();
			status.online = true;
			userStatus.add(status);
		}

		string str = Package::to_data(userStatus);

		io->write(str.data(), str.length());		
	}

	return response.success;

}

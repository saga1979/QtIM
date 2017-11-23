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


	QList<ClientInfo*> *clients = manager->getOnlineClients();

	ClientInfo* clientInfo = 0;

	foreach(clientInfo, *clients)
	{
		if (clientInfo->id().toStdString() == cmd->id)
		{
			response.success = false;
			response.msg = "user already logined!";
			break;
		}
	}

	string data = Package::to_data(response);

	io->write(data.data(), data.length());

	//如果认证成功

	if (!response.success)
		return false;


	//在线用户信息	

	CommandUserStatus userStatus;
	UserStatus status;
	status.online = true;
	for (QList<ClientInfo*>::ConstIterator it = clients->cbegin(); it != clients->cend(); it++)
	{
		status.id = (*it)->id().toStdString();

		userStatus.add(status);
	}

	//获取所有用户id,统计离线用户
	QStringList allUsers = DataSource::Instance().getAllUserID();
	status.online = false;
	for (QStringList::ConstIterator it = allUsers.cbegin(); it != allUsers.end(); it++)
	{
		if (!userStatus.userExist(it->toStdString()))
		{
			status.id = it->toStdString();
			userStatus.add(status);
		}
	}

	string str = Package::to_data(userStatus);

	io->write(str.data(), str.length());

	//将认证成功的客户端加入客户端管理
	ClientInfo* pinfo = new ClientInfo;

	pinfo->setId(QString::fromStdString(cmd->id));
	pinfo->setSocket(io);
	assert(manager);
	manager->add(pinfo);

	return response.success;

}

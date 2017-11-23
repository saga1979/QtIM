#include "qtnetworkclient.h"
#include "userregister.h"
#include "userlogin.h"
#include "command_def.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <cassert>


#include <string>
using namespace std;

QtNetworkClient::QtNetworkClient(QWidget *parent)
	: QMainWindow(parent)
	,m_socket(0)
	, m_userLogin(0)
	, m_userRegister(0)
	,m_lastCommand(CT_END)
	,m_commSocket(0)
{
	ui.setupUi(this);
	//界面初始化
	ui.m_pbSend->setDisabled(true);

	//用户注册
	m_userRegister = new UserRegister(this);
	connect(ui.m_acRegisterUser, &QAction::triggered, m_userRegister, &UserRegister::exec);
	ui.m_acRegisterUser->setIcon(QIcon(":/menu/resources/user_register.png"));
	//响应用户注册事件
	QObject::connect(m_userRegister, SIGNAL(userRegister()), this, SLOT(OnUserRegister()));
	//用户登录
	m_userLogin = new UserLogin(this);

	QAction *action = ui.m_menuUser->addAction("Login");
	action->setIcon(QIcon(":/menu/resources/user_login.png"));
	connect(action, &QAction::triggered, m_userLogin, &UserLogin::exec);
	//响应用户登陆请求

	QObject::connect(m_userLogin, SIGNAL(LoginRequest(const LoginInfo&)), this, SLOT(OnLoginRequest(const LoginInfo&)));
	//响应发送消息事件

	QObject::connect(ui.m_pbSend, SIGNAL(clicked()), this, SLOT(OnSendMessage()));
	

}



void QtNetworkClient::OnSocketError(QAbstractSocket::SocketError error)
{

}

void QtNetworkClient::OnRegisterDataReadyRead()
{
	QByteArray data =  m_socket->readAll();

	m_socketBuff.append(data.toStdString());

	Package package;

	int index = package.from_data(m_socketBuff);

	if (index <= 0)
	{
		return;
	}

	m_socketBuff.erase(0, index);//把已经解析的数据从缓冲区清除


	switch (package.getCmd()->type())
	{
	case CT_REGISTER_RESPONSE:
	{
		CommandRegisterResponse* cmd = (CommandRegisterResponse*)(package.getCmd());

		if (cmd == 0)
		{
			break;
		}

		if (cmd->success)//注册成功
		{
			QMessageBox::information(m_userRegister, "success", QString::fromStdString(cmd->data));
			m_userRegister->close();
		}
		else
		{
			QMessageBox::critical(m_userRegister, "error", "failed to register!");
		}

	}
	break;	
	
	default:
		break;
	}
}

void QtNetworkClient::OnUserRegister()
{
	CommandRegister* cmd = m_userRegister->message();

	if (cmd == 0)
	{
		return;
	}	
	string data = Package::to_data(*cmd);

	if (m_socket == 0)
	{
		m_socket = new QTcpSocket;
		QObject::connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(OnSocketError(QAbstractSocket::SocketError)));
		QObject::connect(m_socket, SIGNAL(readyRead()), this, SLOT(OnRegisterDataReadyRead()));
		m_socket->connectToHost("127.0.0.1", 8002);//这个是系统默认的配置,以后应该写在程序的配置文件中
	}

	m_socket->write(data.data(), data.length());
	m_lastCommand = CT_REGISTER;

}

void QtNetworkClient::OnLoginRequest(const LoginInfo& info)
{
	if (m_commSocket != 0)
	{
		delete m_commSocket;
	}
	m_loginInfo = info;
	m_commBuff.clear();
	
	m_commSocket = new QTcpSocket;
	QObject::connect(m_commSocket, SIGNAL(connected()), this, SLOT(OnCommConnected()));
	QObject::connect(m_commSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(OnCommSocketError(QAbstractSocket::SocketError)));
	QObject::connect(m_commSocket, SIGNAL(readyRead()), this, SLOT(OnCommDataReadyRead()));	
	
	m_commSocket->connectToHost(info.server, info.port);
	
}

void QtNetworkClient::OnSendMessage()
{
	CommandMessage msg;
	msg.from = m_loginInfo.id.toStdString();//todo...
	msg.to = "*";
	msg.msg = ui.m_teMsg->toPlainText().toStdString();

	string data = Package::to_data(msg);

	m_commSocket->write(data.data(), data.length());
}

void QtNetworkClient::OnCommSocketError(QAbstractSocket::SocketError)
{
}

void QtNetworkClient::OnCommDataReadyRead()
{
	QByteArray data = m_commSocket->readAll();

	m_commBuff.append(data.toStdString());	

	while (1)
	{
		Package package;
		//循环解析
		int index = package.from_data(m_commBuff);
		if (index <= 0)
		{
			return;
		}

		m_commBuff.erase(0, index);//把已经解析的数据从缓冲区清除

		switch (package.getCmd()->type())
		{

		case CT_MESSAGE:
		{
			CommandMessage* cmd = (CommandMessage*)(package.getCmd());

			if (cmd == 0)
			{
				break;
			}

			ui.m_lwMessages->addItem(QString("From:%1 %2").arg(cmd->from.c_str()).arg(cmd->msg.c_str()));

		}
		break;
		case CT_LOGIN_RESPONSE:
		{
			CommandLoginResponse* cmd = (CommandLoginResponse*)(package.getCmd());
			if (cmd == 0)
			{
				break;
			}

			if (cmd->success)
			{
				m_userLogin->close();
				ui.m_pbSend->setEnabled(true);
			}
			else
			{
				QMessageBox::critical(this, "failed", QString::fromStdString(cmd->msg));
			}
		}
		break;
		case CT_USER_STATUS:
		{
			CommandUserStatus *cmd = (CommandUserStatus*)(package.getCmd());
			assert(cmd != 0);
			if (cmd == 0)
			{
				break;
			}

			list<UserStatus> users;
			cmd->data(users);

			ui.m_lwUsers->clear();

			for (list<UserStatus>::const_iterator it = users.cbegin(); it != users.end(); it++)
			{
				QListWidgetItem* item = new QListWidgetItem(ui.m_lwUsers);
				item->setText(QString::fromStdString(it->id));

				QString resource = it->online ? ":/menu/resources/user_online.png" :
					":/menu/resources/user_offline.png";
				item->setIcon(QIcon(resource));

			}
		}
		break;
		default:
			break;
		}
	}

	
	
}

void QtNetworkClient::OnCommConnected()
{
	//发送登陆请求信息
	CommandLogin login;
	login.id = m_loginInfo.id.toStdString();
	login.pwd = m_loginInfo.pwd.toStdString();

	string data = Package::to_data(login);

	m_commSocket->write(data.data(), data.length());

	
}


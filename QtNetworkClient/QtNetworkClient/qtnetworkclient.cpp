#include "qtnetworkclient.h"
#include "userregister.h"
#include "userlogin.h"
#include "command_def.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>


#include <string>
using namespace std;

QtNetworkClient::QtNetworkClient(QWidget *parent)
	: QMainWindow(parent),m_socket(0), m_userLogin(0), m_userRegister(0),m_lastCommand(CT_END)
{
	ui.setupUi(this);
	QObject::connect(ui.m_btConnect, SIGNAL(clicked()), this, SLOT(OnConnectClick()));

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


}

void QtNetworkClient::OnConnectClick()
{
	if (m_socket == 0) 
	{
		m_socket = new QTcpSocket;
		QObject::connect(m_socket, SIGNAL(connected()), this, SLOT(OnConnected()));
		QObject::connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(OnSocketError(QAbstractSocket::SocketError)));
		QObject::connect(m_socket, SIGNAL(readyRead()), this, SLOT(OnDataReadyRead()));
	}

	//QHostAddress ha("127.0.0.1");

	m_socket->connectToHost("127.0.0.1", 8001);

	ui.m_btConnect->setDisabled(true);
	ui.m_btConnect->setText("connectiong...");
	
}

void QtNetworkClient::OnConnected()
{
	ui.m_btConnect->setText("connected");
}

void QtNetworkClient::OnSocketError(QAbstractSocket::SocketError error)
{
	ui.m_btConnect->setEnabled(true);
	ui.m_btConnect->setText("connect");
}

void QtNetworkClient::OnDataReadyRead()
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

	m_socket->write(data.data(), data.length());
	m_lastCommand = CT_REGISTER;

}


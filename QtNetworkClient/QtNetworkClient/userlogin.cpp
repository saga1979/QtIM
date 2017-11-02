#include "userlogin.h"
#include "command_def.h"

UserLogin::UserLogin(QWidget *parent)
	: QDialog(parent), m_socket(0)
{
	ui.setupUi(this);
	QObject::connect(ui.m_pbLogin, SIGNAL(clicked()), this, SLOT(OnLogin()));
}

UserLogin::~UserLogin()
{
}

void UserLogin::OnConnected()
{
	//发送登陆请求信息
	CommandLogin login;
	login.name = ui.m_leUser->text().toStdString();
	login.pwd = ui.m_lePwd->text().toStdString();

	string data = Package::to_data(login);

	m_socket->write(data.data(), data.length());
	//应该判断是否发送成功了todo
}

void UserLogin::OnDataReadyRead()
{
	emit LoginResponse(m_socket);
}

void UserLogin::OnSocketError()
{
	ui.m_pbLogin->setEnabled(true);
	ui.m_pbLogin->setText("Login");
}

void UserLogin::OnLogin()
{
	
	if (m_socket == 0)
	{
		m_socket = new QTcpSocket;
		QObject::connect(m_socket, SIGNAL(connected()), this, SLOT(OnConnected()));
		QObject::connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(OnSocketError(QAbstractSocket::SocketError)));
		QObject::connect(m_socket, SIGNAL(readyRead()), this, SLOT(OnDataReadyRead()));
	}

	//QHostAddress ha("127.0.0.1");
	QString server = ui.m_leServer->text();
	int port = ui.m_lePort->text().toInt();
	m_socket->connectToHost(server, port);

	//ui.m_pbLogin->setDisabled(true);
	ui.m_pbLogin->setText("connectiong...");	
}

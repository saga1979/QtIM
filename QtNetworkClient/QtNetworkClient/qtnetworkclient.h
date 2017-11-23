#pragma once

#include <string>
#include <QtWidgets/QMainWindow>

#include "ui_qtnetworkclient.h"
#include "command_def.h"

#include "userlogin.h"


class UserRegister;
class QtNetworkClient : public QMainWindow
{
	Q_OBJECT

public:
	QtNetworkClient(QWidget *parent = Q_NULLPTR);

private slots:
	//注册处理
	void OnSocketError(QAbstractSocket::SocketError);
	void OnRegisterDataReadyRead();
	void OnUserRegister();
	
	//发送消息
	void OnSendMessage();
	//通信连接处理
	void OnLoginRequest(const LoginInfo&);
	void OnCommSocketError(QAbstractSocket::SocketError);
	void OnCommDataReadyRead();
	void OnCommConnected();

private:
	Ui::QtNetworkClientClass ui;
	QTcpSocket* m_socket;
	UserRegister *m_userRegister;
	UserLogin *m_userLogin;
	std::string m_socketBuff;
	CommandType m_lastCommand;
	QAbstractSocket* m_commSocket;
	std::string m_commBuff;
	LoginInfo m_loginInfo;
};

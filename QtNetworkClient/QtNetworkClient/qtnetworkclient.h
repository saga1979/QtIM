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
	//ע�ᴦ��
	void OnSocketError(QAbstractSocket::SocketError);
	void OnRegisterDataReadyRead();
	void OnUserRegister();
	
	//������Ϣ
	void OnSendMessage();
	//ͨ�����Ӵ���
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

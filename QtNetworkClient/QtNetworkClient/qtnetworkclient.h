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

	void OnSocketError(QAbstractSocket::SocketError);
	void OnDataReadyRead();
	void OnUserRegister();
	void OnLoginResponse(QTcpSocket*);

private:
	Ui::QtNetworkClientClass ui;
	QTcpSocket* m_socket;
	UserRegister *m_userRegister;
	UserLogin *m_userLogin;
	std::string m_socketBuff;
	CommandType m_lastCommand;
};

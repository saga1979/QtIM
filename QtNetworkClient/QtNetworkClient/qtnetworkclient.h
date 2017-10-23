#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qtnetworkclient.h"

#include <QTcpSocket>


class UserRegister;
class UserLogin;
class QtNetworkClient : public QMainWindow
{
	Q_OBJECT

public:
	QtNetworkClient(QWidget *parent = Q_NULLPTR);

private slots:
    void OnConnectClick();
	void OnConnected();
	void OnSocketError(QAbstractSocket::SocketError);
	void OnDataReadyRead();
	void OnUserRegister();

private:
	Ui::QtNetworkClientClass ui;
	QTcpSocket* m_socket;
	UserRegister *m_userRegister;
	UserLogin *m_userLogin;
};

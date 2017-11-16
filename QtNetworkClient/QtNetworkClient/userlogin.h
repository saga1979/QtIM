#pragma once

#include <QDialog>
#include <QTcpSocket>
#include <string>
#include "ui_userlogin.h"

using std::string;

struct LoginInfo 
{
	QString id;
	QString pwd;
	QString server;
	int port;
};

class UserLogin : public QDialog
{
	Q_OBJECT

public:
	UserLogin(QWidget *parent = Q_NULLPTR);
	~UserLogin();
Q_SIGNALS:
	void LoginRequest(const LoginInfo&);
private slots:
	void OnLogin();
private:
	Ui::UserLogin ui;
	QTcpSocket* m_socket;
	string m_buff;
};

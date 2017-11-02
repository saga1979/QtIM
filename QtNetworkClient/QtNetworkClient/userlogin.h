#pragma once

#include <QDialog>
#include <QTcpSocket>
#include "ui_userlogin.h"

class UserLogin : public QDialog
{
	Q_OBJECT

public:
	UserLogin(QWidget *parent = Q_NULLPTR);
	~UserLogin();
Q_SIGNALS:
	void LoginResponse(QTcpSocket*);
private slots:
	void OnLogin();
	void OnConnected();
	void OnDataReadyRead();
	void OnSocketError();
private:
	Ui::UserLogin ui;
	QTcpSocket* m_socket;
};

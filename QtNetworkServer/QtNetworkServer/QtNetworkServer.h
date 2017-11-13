#pragma once

#include <QtWidgets/QMainWindow>
#include <QtSql>
#include "ui_QtNetworkServer.h"
#include "register_server.h"

#include <list>
#include <map>
#include <string>

class QTcpServer;
class QTcpSocket;


#include <QDateTime>
struct OnlineUserInfo
{
	QString name;
	QDateTime loginTime;
};

class QtNetworkServer : public QMainWindow
{
	Q_OBJECT

public:
	QtNetworkServer(QWidget *parent = Q_NULLPTR);
	~QtNetworkServer();

private slots:
	void OnStartClick();
	void OnNewConnection();
	void OnSendClick();
	void OnClientReadyRead();
	void OnUserSelected(QListWidgetItem*);
	void OnUserManagerClick();
	void OnCloseUserShowTab(int);

private:
	Ui::QtNetworkServerClass ui;
	QTcpServer* m_comServer;
	RegisterServer* m_registerServer;
	std::list<QTcpSocket*> m_clients;
	std::list<OnlineUserInfo*> m_onlineUsers;
	std::map<QTcpSocket*, std::string*> m_clientBuffs;
	QTabWidget* m_twUserInfoShower;
};

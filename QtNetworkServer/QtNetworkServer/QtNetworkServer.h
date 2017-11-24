#pragma once

#include <QtWidgets/QMainWindow>
#include <QtSql>
#include "ui_QtNetworkServer.h"
#include "register_server.h"
#include "client_info_manager.h"
#include "socket_process.h"

#include <list>
#include <map>
#include <string>

class QTcpServer;
class QTcpSocket;

using std::string;
struct MySocketClient
{
	string *buff;
	QMutex *mutex;
	SocketProcess *process;
	QAbstractSocket * socket;
	QWaitCondition *con;
	MySocketClient(QAbstractSocket* s):socket(s)
	{
		buff = new string;
		mutex = new QMutex;
		con = new QWaitCondition;
		process = new SocketProcess(socket,buff, mutex, con);
		process->start();
	}
	~MySocketClient()
	{
		process->requestInterruption();
	}
};

using std::map;
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
	void OnClientDisconnected();

private:
	Ui::QtNetworkServerClass ui;
	QTcpServer* m_comServer;
	RegisterServer* m_registerServer;
	map<QAbstractSocket*, MySocketClient*> m_clients;
	QTabWidget* m_twUserInfoShower;
};

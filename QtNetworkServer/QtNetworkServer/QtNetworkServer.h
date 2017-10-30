#pragma once

#include <QtWidgets/QMainWindow>
#include <QtSql>
#include "ui_QtNetworkServer.h"

#include <list>
#include <map>
#include <string>

class QTcpServer;
class QTcpSocket;


class QtNetworkServer : public QMainWindow
{
	Q_OBJECT

public:
	QtNetworkServer(QWidget *parent = Q_NULLPTR);

private slots:
	void OnStartClick();
	void OnNewConnection();
	void OnSendClick();
	void OnClientReadyRead();
	void OnUserSelected(QListWidgetItem*);
	void OnUserManagerClick();

private:
	Ui::QtNetworkServerClass ui;
	QTcpServer* m_tcpServer;
	std::list<QTcpSocket*> m_clients;
	std::map<QTcpSocket*, std::string*> m_clientBuffs;
	QTabWidget* m_twUserInfoShower;
};

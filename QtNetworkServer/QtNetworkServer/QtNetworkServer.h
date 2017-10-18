#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtNetworkServer.h"

#include <list>

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

private:
	Ui::QtNetworkServerClass ui;
	QTcpServer* m_tcpServer;
	std::list<QTcpSocket*> m_clients;
};

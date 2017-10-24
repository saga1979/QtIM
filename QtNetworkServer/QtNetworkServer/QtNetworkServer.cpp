#include <QTcpServer>
#include <QTcpSocket>

#include "QtNetworkServer.h"
#include "command_def.h"

using namespace std;

QtNetworkServer::QtNetworkServer(QWidget *parent)
	: QMainWindow(parent), m_tcpServer(0)
{
	ui.setupUi(this);
	ui.m_btSend->setDisabled(true);
	QObject::connect(ui.m_btStart, SIGNAL(clicked()), this, SLOT(OnStartClick()));
	QObject::connect(ui.m_btSend, SIGNAL(clicked()), this, SLOT(OnSendClick()));
}

void QtNetworkServer::OnStartClick()
{
	if (m_tcpServer == 0)
	{
		m_tcpServer = new QTcpServer(this);
		QObject::connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(OnNewConnection()));
		
	}	

	if (!m_tcpServer->listen(QHostAddress::Any, 8001))
	{
		return;
	}

	//m_tcpServer->setMaxPendingConnections(5);

	ui.m_btStart->setText("started");
	ui.m_btStart->setDisabled(true);
}

void QtNetworkServer::OnNewConnection()
{
	QTcpSocket* client = m_tcpServer->nextPendingConnection();

	if (client == 0)
	{
		return;
	}

	QObject::connect(client, SIGNAL(readyRead()), this, SLOT(OnClientReadyRead()));

	ui.m_btSend->setEnabled(true);

	m_clients.push_back(client);

	m_clientBuffs.insert(std::pair<QTcpSocket*, std::string*>(client, new string));

}

void QtNetworkServer::OnSendClick()
{
	for (std::list<QTcpSocket*>::iterator it = m_clients.begin(); it != m_clients.end(); it++)
	{
		QTcpSocket* socket = *it;
		//清理断开的连接及其占用的资源
		if (socket->state() == QAbstractSocket::UnconnectedState)
		{
			it = m_clients.erase(it);
			string* val = m_clientBuffs[*it];
			m_clientBuffs.erase(*it);
			delete val;
			delete socket;
			continue;
		}
		
		socket->write(QByteArray::fromStdString(ui.lineEdit->text().toStdString()));
	}
}

void QtNetworkServer::OnClientReadyRead()
{
	for (std::list<QTcpSocket*>::iterator it = m_clients.begin(); it != m_clients.end(); it++)
	{
		QTcpSocket* socket = *it;

		if (!socket->isReadable())
		{			
			continue;
		}	

		
		QByteArray bytes =  socket->readAll();

		string* buf = m_clientBuffs[socket];

		buf->append(bytes.toStdString());

		Package package;

		package.from_data(*buf);

		QString fff= QString::fromStdString(*buf);
		

		CommandRegister* cmd = (CommandRegister*)package.command;

		if (cmd != 0)
		{
			int i = 0;
		}
				
	}

}

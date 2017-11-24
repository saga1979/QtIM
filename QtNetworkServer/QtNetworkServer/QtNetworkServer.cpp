#include <QTcpServer>
#include <QTcpSocket>
#include <QUuid>
#include <QTabWidget>
#include <QGridLayout>
#include <cassert>

#include "QtNetworkServer.h"
#include "command_def.h"

#include "userinfoshower.h"
#include "datasource.h"
#include "process_factory.h"

using namespace std;

QtNetworkServer::QtNetworkServer(QWidget *parent)
	: QMainWindow(parent)
	, m_comServer(0)
	, m_twUserInfoShower(0)
	, m_registerServer(0)
{
	ui.setupUi(this);
	//布局
	QWidget *center = this->centralWidget();

	QGridLayout * grid = new QGridLayout;
	grid->setColumnStretch(1, 2);
	
	center->setLayout(grid);

	grid->addWidget(ui.m_lwUsers, 0, 0, 1, 1);
	grid->addWidget(ui.lineEdit, 1, 0, 1, 2);
	grid->addWidget(ui.m_btSend, 1, 2,1,1);
	grid->addWidget(ui.m_btStart, 1, 3, 1,1);
	m_twUserInfoShower = new QTabWidget;
	m_twUserInfoShower->setTabsClosable(true);
	grid->addWidget(m_twUserInfoShower, 0, 1, 1, 3);

	ui.m_btSend->setDisabled(true);
	//设置事件
	QObject::connect(ui.m_btStart, SIGNAL(clicked()), this, SLOT(OnStartClick()));
	QObject::connect(ui.m_btSend, SIGNAL(clicked()), this, SLOT(OnSendClick()));
	QObject::connect(ui.m_lwUsers, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(OnUserSelected(QListWidgetItem*)));
	QObject::connect(ui.actionUsers, SIGNAL(triggered()), this, SLOT(OnUserManagerClick()));
	QObject::connect(m_twUserInfoShower, SIGNAL(tabCloseRequested(int)), this, SLOT(OnCloseUserShowTab(int)));
}

void QtNetworkServer::OnStartClick()
{
	if (m_comServer == 0)
	{
		m_comServer = new QTcpServer(this);
		QObject::connect(m_comServer, SIGNAL(newConnection()), this, SLOT(OnNewConnection()));
		
	}	

	if (!m_comServer->listen(QHostAddress::Any, 8001))
	{
		return;
	}

	//m_tcpServer->setMaxPendingConnections(5);

	ui.m_btStart->setText("started");
	ui.m_btStart->setDisabled(true);



	if (m_registerServer == 0)
	{
		m_registerServer = new RegisterServer;
	}

	m_registerServer->start();
}

QtNetworkServer::~QtNetworkServer()
{

	for (map<QAbstractSocket*, MySocketClient*>::iterator it = m_clients.begin();
		it != m_clients.end(); it++)
	{
		it->first->close();
		delete  it->second;
	}	

	if (m_registerServer != 0)
	{
		delete m_registerServer;
	}
}

void QtNetworkServer::OnNewConnection()
{
	QAbstractSocket* client = m_comServer->nextPendingConnection();

	if (client == 0)
	{
		return;
	}

	QObject::connect(client, SIGNAL(readyRead()), this, SLOT(OnClientReadyRead()));
	QObject::connect(client, SIGNAL(disconnected()), this, SLOT(OnClientDisconnected()));
	

	ui.m_btSend->setEnabled(true);

	MySocketClient* sc = new MySocketClient(client);	

	m_clients.insert(pair<QAbstractSocket*, MySocketClient*>(client, sc));

}

void QtNetworkServer::OnSendClick()
{

	//for (std::list<QAbstractSocket*>::iterator it = m_clients.begin(); it != m_clients.end(); it++)
	//{
	//	QAbstractSocket* socket = *it;
	//	//清理断开的连接及其占用的资源
	//	if (socket->state() == QAbstractSocket::UnconnectedState)
	//	{
	//		it = m_clients.erase(it);
	//		string* val = m_clientBuffs[*it];
	//		m_clientBuffs.erase(*it);
	//		delete val;
	//		delete socket;
	//		continue;
	//	}
	//	
	//	socket->write(QByteArray::fromStdString(ui.lineEdit->text().toStdString()));
	//}
}

void QtNetworkServer::OnClientReadyRead()
{
	for (map<QAbstractSocket*, MySocketClient*>::iterator it = m_clients.begin(); it != m_clients.end(); it++)
	{
		QAbstractSocket* socket = it->first;

		if (!socket->isReadable())
		{
			continue;
		}
		
		QByteArray bytes =  socket->readAll();
		//给缓冲区加锁

		m_clients[socket]->mutex->lock();
		string* buf = m_clients[socket]->buff;

		m_clients[socket]->buff->append(bytes.toStdString());

		m_clients[socket]->mutex->unlock();
		//给缓冲区解锁	

		m_clients[socket]->con->notify_one();

	}
}

void QtNetworkServer::OnUserSelected(QListWidgetItem *item)
{
	QString id = item->text();

	UserInfo* info = DataSource::Instance().getUserInfo(id);

	
	int index = -1;

	for (; index < m_twUserInfoShower->count(); index++)
	{
		QString label = m_twUserInfoShower->tabText(index);
		if (label == info->name)
		{			
			break;
		}
	}
	if (index == m_twUserInfoShower->count())
	{
		index = m_twUserInfoShower->addTab(new UserInfoShower(info), info->name);
	}

	m_twUserInfoShower->setCurrentIndex(index);
	
}

void QtNetworkServer::OnUserManagerClick()
{
	ui.m_lwUsers->clear();
	QStringList sl = DataSource::Instance().getAllUserID();
	

	for (QStringList::iterator it = sl.begin(); it != sl.end(); it++)
	{
		QListWidgetItem* item = new QListWidgetItem(ui.m_lwUsers);
		item->setText(*it);
	}
}

void QtNetworkServer::OnCloseUserShowTab(int index)
{
	m_twUserInfoShower->removeTab(index);
}

void QtNetworkServer::OnClientDisconnected()
{
	QAbstractSocket* socket = 0;

	pair<QAbstractSocket*, MySocketClient*> p;

	foreach(p, m_clients)
	{
		socket = p.first;
		if (socket->state() == QAbstractSocket::UnconnectedState)
		{			
			m_clients.erase(socket);
			//该连接还没有加入在线客户端管理模块
			ClientInfoManager::instance().remove(socket);
			delete p.second;
			break;
		}
	}
}

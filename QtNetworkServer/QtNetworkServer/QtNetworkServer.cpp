#include <QTcpServer>
#include <QTcpSocket>
#include <QUuid>
#include <QTabWidget>
#include <QGridLayout>

#include "QtNetworkServer.h"
#include "command_def.h"

#include "userinfoshower.h"
#include "datasource.h"

using namespace std;

QtNetworkServer::QtNetworkServer(QWidget *parent)
	: QMainWindow(parent), m_tcpServer(0), m_twUserInfoShower(0)
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

		int index = package.from_data(*buf);

		if (index <= 0)
		{
			continue;
		}

		buf->erase(0, index);//清理已经读取的数据

		switch (package.getCmd()->type())
		{
		case CT_REGISTER:
		{
			CommandRegister* cmd = (CommandRegister*)(package.getCmd());

			if (cmd == 0)
			{
				continue;
			}

			UserInfo info;
			info.name = QString::fromStdString(cmd->name);
			info.pwd = QString::fromStdString(cmd->pwd);
			info.img = QByteArray::fromRawData(cmd->img.data(), cmd->img.length());

			CommandRegisterResponse response;
			
			string data = Package::to_data(response);

			if (DataSource::Instance().RegisterUser(info))
			{
				response.success = true;
			}

			socket->write(data.data(), data.length());

		}
		break;
		default:
			break;
		}

					
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

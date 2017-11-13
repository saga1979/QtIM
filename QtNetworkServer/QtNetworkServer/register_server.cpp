#include <QTcpServer>
#include <QTcpSocket>

#include <cassert>
#include "register_server.h"
#include "command_def.h"
#include "process_factory.h"


RegisterTask::RegisterTask(QTcpSocket* socket):QThread(0), m_conn(socket)
{
	QObject::connect(m_conn, SIGNAL(readyRead()), this, SLOT(OnClientReadyRead()));
}

void RegisterTask::run()
{
	QThread::run();
}

void RegisterTask::OnClientReadyRead()
{
	QByteArray bytes = m_conn->readAll();	

	m_buff.append(bytes.toStdString());

	Package package;

	int index = package.from_data(m_buff);

	if (index <= 0)
	{
		return;//没有发现完整的数据包
	}

	
	ProcessInterface* pi = CmdProcessFactory::instance().getProcess(package.getCmd()->type());

	assert(pi);

	bool success = pi->ProcessCommand(package.getCmd(), m_conn);

	delete pi;	
	delete m_conn;
	m_conn = 0;

	QThread::exit();

}

void RegisterServer::OnNewConnection()
{
	//生成独立的线程处理用户注册事件
	QTcpSocket* client = m_server->nextPendingConnection();
	assert(client);
	if (client == 0)
	{
		return;
	}

	RegisterTask * task = new RegisterTask(client);

	task->start();
	
	//线程运行完毕后实现自删除
	QObject::connect(task, SIGNAL(finished()), task, SLOT(deleteLater()));

}


RegisterServer::RegisterServer():m_server(0)
{
}


RegisterServer::~RegisterServer()
{
	if (m_server != 0)
	{
		delete m_server;
	}
}

bool RegisterServer::start()
{
	if (m_server == 0)
	{
		m_server = new QTcpServer;
		QObject::connect(m_server, SIGNAL(newConnection()), this, SLOT(OnNewConnection()));
	}	

	if (!m_server->listen(QHostAddress::Any, 8002))
	{
		return false;
	}

	return false;
}

void RegisterServer::stop()
{
	m_server->close();
}

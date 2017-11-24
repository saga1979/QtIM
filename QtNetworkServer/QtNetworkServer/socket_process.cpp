#include <cassert>
#include "socket_process.h"
#include "command_def.h"
#include "process_factory.h"
using namespace std;

SocketProcess::SocketProcess(QObject *parent)
	: QThread(parent)
{
}

SocketProcess::SocketProcess(QAbstractSocket* socket, string* buff, QMutex* mutex, QWaitCondition* con)
	:QThread(0), m_socket(socket), m_buff(buff), m_lock(mutex), m_con(con)
{
	QObject::connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
	QObject::connect(m_socket, SIGNAL(disconnected()), m_socket, SLOT(deleteLater()));
	m_conLock = new QMutex;
}

SocketProcess::~SocketProcess()
{
	delete m_buff;
	delete m_lock;
	delete m_con;
	delete m_conLock;
}

void SocketProcess::run()
{
	while (1)
	{		
		if (isInterruptionRequested())
		{
			break;
		}

		m_conLock->lock();

		if (!m_con->wait(m_conLock, 200))
		{
			m_conLock->unlock();
			continue;
		}


		m_conLock->unlock();


		Package package;

		m_lock->lock();

		int index = package.from_data(*m_buff);

		if (index <= 0)
		{
			m_lock->unlock();
			continue;
		}

		m_buff->erase(0, index);//清理已经读取的数据

		m_lock->unlock();

		ProcessInterface* pi = CmdProcessFactory::instance().getProcess(package.getCmd()->type());

		assert(pi);

		bool success = pi->ProcessCommand(package.getCmd(), m_socket, &ClientInfoManager::instance());

		delete pi;

		if (package.getCmd()->type() == CT_LOGIN && !success)
		{
			m_socket->close();

			break;
		}
	}

}

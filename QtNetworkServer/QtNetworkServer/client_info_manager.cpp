#include "client_info_manager.h"



ClientInfoManager::ClientInfoManager()
{
}


ClientInfoManager::~ClientInfoManager()
{
	for (QList<ClientInfo*>::iterator it = m_clients.begin(); it != m_clients.end(); it++)
	{
		delete *it;
	}
}

QList<ClientInfo*>* ClientInfoManager::getOnlineClients()
{
	return &m_clients;
}

void ClientInfoManager::add(ClientInfo *client)
{
	QObject::connect(client->socket(), SIGNAL(disconnected()), this, SLOT(onSocketDisconnected()));
	m_clients.append(client);
}

void ClientInfoManager::remove(ClientInfo *client)
{
	m_clients.removeOne(client);
	delete client;
}

bool ClientInfoManager::remove(const QAbstractSocket *socket)
{
	for (QList<ClientInfo*>::iterator it = m_clients.begin(); it != m_clients.end(); it++)
	{
		if ((*it)->socket() == socket)
		{
			delete *it;
			m_clients.erase(it);			
			return true;
		}
	}

	return false;
}


void ClientInfoManager::onSocketDisconnected()
{
	//todo...
	for (QList<ClientInfo*>::iterator it = m_clients.begin(); it != m_clients.end(); it++)
	{
		//ClientInfo* info = *it;
		//if (info->socket()->state() == QAbstractSocket::UnconnectedState)
		//{
		//	it = m_clients.erase(it);
		//	delete info;
		//	continue;
		//}
	}

}


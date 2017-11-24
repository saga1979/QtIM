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

ClientInfoManager & ClientInfoManager::instance()
{
	static ClientInfoManager obj;

	return obj;
	// TODO: insert return statement here
}



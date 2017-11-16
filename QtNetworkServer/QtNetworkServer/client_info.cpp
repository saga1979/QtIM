#include "client_info.h"



ClientInfo::ClientInfo():m_socket(0)
{
}


ClientInfo::~ClientInfo()
{
}

QString ClientInfo::id() const
{
	return m_id;
}

void ClientInfo::setId(QString &id)
{
	m_id = id;
}

QAbstractSocket * ClientInfo::socket()
{
	return m_socket;
}

void ClientInfo::setSocket(QAbstractSocket *socket)
{
	m_socket = socket;
}

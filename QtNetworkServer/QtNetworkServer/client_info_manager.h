#pragma once

#include "client_info.h"

#include <QList>

class ClientInfoManager 
{
protected:
	QList<ClientInfo*> m_clients;
	protected slots:
	void onSocketDisconnected();
	ClientInfoManager();
public:	
	~ClientInfoManager();
	QList<ClientInfo*>* getOnlineClients();
	void add(ClientInfo*);
	void remove(ClientInfo*);
	bool remove(const QAbstractSocket*);
	static ClientInfoManager& instance();
};


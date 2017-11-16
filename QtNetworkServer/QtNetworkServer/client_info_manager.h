#pragma once

#pragma once

#include "client_info.h"

#include <QList>

class ClientInfoManager : public QObject
{
	Q_OBJECT
protected:
	QList<ClientInfo*> m_clients;
	protected slots:
	void onSocketDisconnected();
public:
	ClientInfoManager();
	~ClientInfoManager();

	QList<ClientInfo*>* getOnlineClients();
	void add(ClientInfo*);
	void remove(ClientInfo*);
};


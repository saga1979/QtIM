#include "process_message.h"
#include "command_def.h"
#include <string>
using std::string;

ProcessMessage::ProcessMessage()
{
}

ProcessMessage::~ProcessMessage()
{
}

bool ProcessMessage::ProcessCommand(const Command *cmd, QAbstractSocket *io, ClientInfoManager * manager)
{
	if (manager == 0)
	{
		manager = &ClientInfoManager::instance();
	}
	QList<ClientInfo*>* clients = manager->getOnlineClients();
	string data = Package::to_data(cmd);

	for (QList<ClientInfo*>::iterator it = clients->begin(); it != clients->end(); it++)
	{
		(*it)->socket()->write(data.data(), data.length());
		(*it)->socket()->flush();		
	}

	return true;
}

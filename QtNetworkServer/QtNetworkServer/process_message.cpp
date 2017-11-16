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

	QList<ClientInfo*>* clients = manager->getOnlineClients();
	string data = Package::to_data(cmd);

	for (QList<ClientInfo*>::iterator it = clients->begin(); it != clients->end(); it++)
	{
		io->write(data.data(), data.length());
	}

	return true;
}

#pragma once

#include <QString>
#include <QTcpSocket>

class ClientInfo
{
	QString m_id;
	QAbstractSocket* m_socket;
public:
	ClientInfo();
	~ClientInfo();
	QString id() const;
	void setId(QString&);
	QAbstractSocket* socket();
	void setSocket(QAbstractSocket*);
};


#pragma once

#include <QString>
#include <QTcpSocket>

class ClientInfo
{
	QString m_id;
	//所有的socket连接,都将其disconnected信号连接deleteLater槽
	QAbstractSocket* m_socket;
public:
	ClientInfo();
	~ClientInfo();
	QString id() const;
	void setId(QString&);
	QAbstractSocket* socket();
	void setSocket(QAbstractSocket*);
};


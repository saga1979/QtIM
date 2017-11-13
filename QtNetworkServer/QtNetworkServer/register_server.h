#ifndef __REGISTERSERVER_H__
#define __REGISTERSERVER_H__

#include <QThread>
#include <string>

class QTcpServer;
class QTcpSocket;


class RegisterTask : public QThread
{
	Q_OBJECT
public:
	RegisterTask(QTcpSocket* socket);
private:
	QTcpSocket* m_conn;
	std::string m_buff;
protected:
	void run();
protected slots:
	void OnClientReadyRead();

};


class RegisterServer : public QObject
{
	Q_OBJECT

private slots :
	void OnNewConnection();

protected:
	QTcpServer* m_server;
public:
	RegisterServer();
	~RegisterServer();
	bool start();
	void stop();
	//bool restart();
	//bool pause();
	//bool resume();
};

#endif


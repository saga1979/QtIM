#pragma once

#include <QThread>
#include <string>
#include <QMutex>
#include <QAbstractSocket>
#include <QWaitCondition>
using std::string;
class SocketProcess : public QThread
{
	Q_OBJECT

public:
	SocketProcess(QObject *parent);
	SocketProcess(QAbstractSocket*, string* , QMutex*, QWaitCondition*);
	~SocketProcess();
protected:
	void run();
private:
	string* m_buff;
	QMutex* m_lock;
	QWaitCondition* m_con;
	QMutex* m_conLock;
	QAbstractSocket* m_socket;
};

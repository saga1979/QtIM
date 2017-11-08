#include "datasource.h"

#include <QTimer>
#define MAX_USER 999999

DataSource::DataSource()
{
	m_sqlDatabase = QSqlDatabase::addDatabase("QMYSQL");
	m_sqlDatabase.setHostName("127.0.0.1");
	m_sqlDatabase.setDatabaseName("im");
	m_sqlDatabase.setUserName("root");
	m_sqlDatabase.setPassword("root");
}

int DataSource::generateUserID() 
{
	qsrand(QTime::currentTime().msec());

	if (!m_sqlDatabase.isOpen() && !m_sqlDatabase.open())
	{
		return -1;
	}

	QSqlQuery query;

	while (1)
	{
		query.prepare("select count(*) from users where id = :id");

		int id = qrand() % 999999 + 1;

		query.bindValue(":id", QString::number(id));
		if (!query.exec() || !query.next())
		{
			return -1;
		}

		if (query.value(0).toInt() == 0)
		{
			return id;
		}
	}


	return -1;
}


DataSource::~DataSource()
{
}



DataSource & DataSource::Instance()
{
	static DataSource ds;

	return ds;
}

UserInfo * DataSource::getUserInfo(const QString &id)
{
	if (!m_sqlDatabase.isOpen() && !m_sqlDatabase.open())
	{
		return 0;
	}

	QSqlQuery query;
	query.prepare("select * from users where id = :id;");
	query.bindValue(":id", id);

	if (!query.exec())
	{
		return 0;		
	}

	if (!query.next())
	{
		return 0;
	}

	UserInfo* info = new UserInfo;

	info->name = query.value("name").toString();
	info->pwd = query.value("pwd").toString();
	info->img = query.value("img").toByteArray();
	info->info = query.value("info").toString();

	return info;
}

UserInfo * DataSource::getUserInfo(const string &name)
{
	return getUserInfo(QString::fromStdString(name));
}

QStringList DataSource::getAllUserID()
{
	QStringList sl;
	if (!m_sqlDatabase.isOpen() && !m_sqlDatabase.open())
	{
		return sl;
	}

	QSqlQuery query;

	if (!query.exec("select id from users;"))
	{
		return sl;
	}

	while (query.next())
	{
		sl.append(query.value("id").toString());
	}
	return sl;
}

bool DataSource::RegisterUser(UserInfo &info)
{
#ifdef _DEBUG
	QFile file("d:\\tmp\\1.png");
	file.open(QFile::WriteOnly);
	file.write(info.img);
	file.close();
#endif		

	if (!m_sqlDatabase.isOpen() && !m_sqlDatabase.open())
	{
		return false;
	}



	QSqlQuery query;
	query.prepare("insert into users (id, name, pwd, img) values(:id, :name, :pwd, :img);");

	int id = generateUserID();

	query.bindValue(":id", QString::number(id));
	query.bindValue(":name", info.name);
	query.bindValue(":pwd", info.pwd);

	query.bindValue(":img", info.img);

	if (!query.exec())
	{
		qDebug() << query.lastError();
		return false;
	}
	info.id = QString::number(id);
	return true;
}

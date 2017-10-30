#ifndef __DATASOURCE_H__
#define __DATASOURCE_H__

#include <QtCore>
#include <QtSql>

struct UserInfo
{
	QString name;
	QString pwd;
	QByteArray img;
	QString info;
};



class DataSource
{
protected:
	DataSource();
	QSqlDatabase m_sqlDatabase;
public:	
	virtual ~DataSource();
	static DataSource& Instance();
	UserInfo* getUserInfo(const QString&);
	
	//QList<QVariant> getUserInfoField(const QString& id, QStringList fields);

	QStringList getAllUserID();
	bool RegisterUser(const UserInfo&);
};

#endif


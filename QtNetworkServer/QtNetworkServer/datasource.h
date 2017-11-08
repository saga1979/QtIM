#ifndef __DATASOURCE_H__
#define __DATASOURCE_H__

#include <QtCore>
#include <QtSql>
#include <string>
using std::string;

struct UserInfo
{
	QString name;
	QString pwd;
	QByteArray img;
	QString info;
	QString id;//这是一个字符化的数字,类似QQ号
};



class DataSource
{
protected:
	DataSource();
	QSqlDatabase m_sqlDatabase;
	int generateUserID() ;
public:	
	virtual ~DataSource();
	static DataSource& Instance();
	UserInfo* getUserInfo(const QString&);
	UserInfo* getUserInfo(const string&);
	
	//QList<QVariant> getUserInfoField(const QString& id, QStringList fields);

	QStringList getAllUserID();
	//如果成功注册,会在参数中返回注册ID
	bool RegisterUser(UserInfo&);
};

#endif


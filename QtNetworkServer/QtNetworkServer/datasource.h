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
	QString id;//����һ���ַ���������,����QQ��
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
	//����ɹ�ע��,���ڲ����з���ע��ID
	bool RegisterUser(UserInfo&);
};

#endif


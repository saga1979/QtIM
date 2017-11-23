#pragma once
#include "command_interface.h"

#include <string>
#include <list>
using std::string;
using std::list;

struct UserStatus
{
	string id;
	bool online;
	UserStatus() :online(false) {}
};

class QTNETWORKPLATFORM_EXPORT CommandUserStatus : public Command
{
	list<UserStatus> m_userStatus;
public:
	void add(const UserStatus&);
	void remove(const string&);
	void data(list<UserStatus>&);
	bool userExist(const string& id);

	virtual int from_data(const string &) override;
	virtual CommandType type() const override;
protected:
	// Inherited via Command
	virtual const string internal_to_data() const override;
	virtual int internal_length() const override;
};


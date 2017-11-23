#include "command_user_status.h"
#include "command_utilies.h"

void CommandUserStatus::add(const UserStatus &status)
{
	m_userStatus.push_back(status);
}

void CommandUserStatus::remove(const string &id)
{
	for (list<UserStatus>::iterator it = m_userStatus.begin(); it != m_userStatus.end(); it++)
	{
		if (it->id == id)
		{
			m_userStatus.erase(it);
			break;
		}
	}
}

void CommandUserStatus::data(list<UserStatus>& status)
{
	status = m_userStatus;	
}
bool CommandUserStatus::userExist(const string & id)
{
	for (list<UserStatus>::const_iterator it = m_userStatus.cbegin(); it != m_userStatus.cend(); it++)
	{
		if (it->id == id)
			return true;
	}
	return false;
}
/*
* <status>0xxx;1xxx;</status> //可选
*
*/
const string CommandUserStatus::internal_to_data() const
{
	string users;

	for (list<UserStatus>::const_iterator it = m_userStatus.cbegin(); it != m_userStatus.cend(); it++)
	{
		users += it->online ? "1" : "0";
		users += it->id;
		users += ";";
	}

	string data = "<status>";
	data += users;
	data += "</status>";

	return data;
}

int CommandUserStatus::from_data(const string &data)
{
	string strData = get_value(data, "status");
	
	int start_index = 0;
	size_t find_index = string::npos;

	UserStatus status;
	while ((find_index = strData.find(";", start_index)) != string::npos)
	{
		status.online = strData[start_index] == '1' ? true : false;
		status.id = strData.substr(start_index+1, find_index - start_index-1);
		m_userStatus.push_back(status);

		start_index = find_index + 1;
		if (start_index >= strData.length() )
		{
			break;
		}
	}
	
	return 0;
}

CommandType CommandUserStatus::type() const
{
	return CT_USER_STATUS;
}

int CommandUserStatus::internal_length() const
{
	int len = strlen("<status>") * 2 + 1;

	for (list<UserStatus>::const_iterator it = m_userStatus.cbegin(); it != m_userStatus.cend(); it++)
	{
		len += it->id.length();//name
		len += 2;//前面有"0"或者"1",后面有";"
	}
	return len;
}

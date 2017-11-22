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
/*
* <users>xxx;xx;xxx;</users><onlines>0;1;1;</onlines>
*
*/
const string CommandUserStatus::to_internal_data() const
{
	string users;
	string onlines;

	for (list<UserStatus>::const_iterator it = m_userStatus.cbegin(); it != m_userStatus.cend(); it++)
	{
		users += it->id;
		users += ";";

		onlines += it->online ? "1" : "0";
		onlines += ";";
	}

	string data = "<users>";
	data += users;
	data += "</users>";

	data += "<onlines>";
	data += onlines;
	data += "</onlines>";

	return data;
}

int CommandUserStatus::from_data(const string &data)
{
	string users = get_value(data, "users");
	string onlines = get_value(data, "onlines");

	
	int start_index = 0;
	size_t find_index = string::npos;

	UserStatus status;
	while ((find_index = users.find(";", start_index)) != string::npos)
	{
		status.id = users.substr(start_index, find_index - start_index);
		m_userStatus.push_back(status);

		start_index = find_index + 1;
		if (start_index >= users.length())
		{
			break;
		}
	}

	//todo... online status
	
	return 0;
}

CommandType CommandUserStatus::type() const
{
	return CT_USER_STATUS;
}

int CommandUserStatus::internal_length() const
{
	int len = strlen("<users>") * 2 + 1;
	len += strlen("<onlines") * 2 + 1;


	for (list<UserStatus>::const_iterator it = m_userStatus.cbegin(); it != m_userStatus.cend(); it++)
	{
		len += it->id.length();//name
		len += 1;//";"

		len += 1;//"0" or "1"
		len += 1;//";"
	}
	return len;
}

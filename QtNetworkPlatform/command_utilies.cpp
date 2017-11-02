

#include "command_utilies.h"


string get_value(const string& data, const string& start_name, const string& end_name)
{
	size_t start = data.find(start_name) + start_name.length();

	size_t end = data.find(end_name);

	string ret = data.substr(start, end - start);

	return ret;
}

string get_value(const string& data, const string& name)
{

	string field_start = '<' + name + '>';
	string field_end = "</" + name + '>';

	return get_value(data, field_start, field_end);
}

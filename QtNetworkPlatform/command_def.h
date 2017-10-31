#ifndef __COMMAND_DEF_H__
#define __COMMAND_DEF_H__


#include "qtnetworkplatform_global.h"


#include <string>
#include <cstdint>

using std::string;

enum CommandType
{
	CT_REGISTER,
	CT_REGISTER_RESPONSE,
	CT_MESSAGE,

	CT_END
};

struct ISerializable
{
	virtual const string to_data() const = 0;
	virtual int from_data(const string&) = 0;
};

struct Command : public ISerializable
{
	virtual  CommandType type() const = 0;

	virtual  int  length() const = 0;

	virtual ~Command() {}

};


struct QTNETWORKPLATFORM_EXPORT CommandRegister : public Command
{
	string name;
	string pwd;
	string info;
	string img;
	// Inherited via CommandMessage
	virtual const string  to_data() const override;
	virtual int from_data(const string &) override;
	virtual  CommandType type() const;
	// Inherited via CommandMessage
	virtual int  length() const override;
};

struct QTNETWORKPLATFORM_EXPORT CommandRegisterResponse : public Command
{
	CommandRegisterResponse();
	bool success;
	// Inherited via CommandMessage
	virtual const string  to_data() const override;
	virtual int  from_data(const string &) override;
	virtual  CommandType type() const;
	// Inherited via CommandMessage
	virtual int  length() const override;
};


struct QTNETWORKPLATFORM_EXPORT Package : public ISerializable
{
	Package();
	Package(Command* cmd);
	~Package();

	const Command* getCmd()const ;

	int data_len() const;

	// Inherited via ISerializable
	virtual const string to_data() const override;

	virtual int  from_data(const string &) override;

	static const string to_data(const Command&);

private:
	Command *command;
};


#endif




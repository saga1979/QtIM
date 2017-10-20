#ifndef __COMMAND_DEF_H__
#define __COMMAND_DEF_H__

#include <string>
#include <cstdint>

using std::string;

enum CommandType
{
	CT_REGISTER,
	CT_MESSAGE,

	CT_END
};

struct ISerializable
{
	virtual const string to_data() const = 0;
	virtual void from_data(const string&) = 0;
};

struct Command : public ISerializable
{
	CommandType type;

	virtual uint16_t len() = 0;

};

struct CommandMessage : public Command
{
	// Inherited via Command
	virtual const string to_data() const override;
	virtual void from_data(const string &) override;
	virtual uint16_t len() override;
};


struct CommandRegister : public Command
{
	string name;
	string pwd;
	string info;
	string img;

	// Inherited via CommandMessage
	virtual const string  to_data() const override;
	virtual void from_data(const string &) override;

	// Inherited via CommandMessage
	virtual uint16_t len() override;
};


struct Package : public ISerializable
{
	Package();
	~Package();

	Command *message;

	// Inherited via ISerializable
	virtual const string to_data() const override;

	virtual void from_data(const string &) override;

};


#endif




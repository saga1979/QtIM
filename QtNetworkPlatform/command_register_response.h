#pragma once

#include "command_interface.h"

struct QTNETWORKPLATFORM_EXPORT CommandRegisterResponse : public Command
{
	CommandRegisterResponse();
	bool success;
	string data;//���ʧ��,�洢ʧ����Ϣ;�ɹ�,��洢�û�ID
	// Inherited via CommandMessage
	virtual const string  to_data() const override;
	virtual int  from_data(const string &) override;
	virtual  CommandType type() const;
	// Inherited via CommandMessage
	virtual int  length() const override;
};


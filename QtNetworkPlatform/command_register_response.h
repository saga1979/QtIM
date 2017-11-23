#pragma once

#include "command_interface.h"

struct QTNETWORKPLATFORM_EXPORT CommandRegisterResponse : public Command
{
	CommandRegisterResponse();
	bool success;
	string data;//���ʧ��,�洢ʧ����Ϣ;�ɹ�,��洢�û�ID

	virtual int  from_data(const string &) override;
	virtual  CommandType type() const;
protected:
	// Inherited via CommandMessage
	virtual const string  internal_to_data() const override;
	// Inherited via CommandMessage
	virtual int  internal_length() const override;
};


#pragma once

#include "qtnetworkplatform_global.h"


enum CommandType
{
	CT_REGISTER,
	CT_REGISTER_RESPONSE,
	CT_LOGIN,
	CT_LOGIN_RESPONSE,
	CT_MESSAGE,
	CT_GENERAL_RESPONSE,
	CT_USER_STATUS,
	CT_END
};


typedef uint32_t LenType;
typedef uint32_t EnumType;
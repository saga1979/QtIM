#ifndef __COMMAND_DEF_H__
#define __COMMAND_DEF_H__
/*
增加协议命令的步骤:
1.在command_type.h中增加协议类型enum
2.为新增的命令增加相应的类型( 实现command_interface.h中得Command接口,实现数据与C++对象的相互转换)
3.在命令导出头文件中增加新命令的头文件
4.在命令工厂中增加相应的命令处理(支持相应命令到网络数据包的相互转换)

*/
#include "network_package.h"
#include "command_login.h"
#include "command_login_response.h"
#include "command_register.h"
#include "command_register_response.h"
#include "command_general_response.h"
#include "command_message.h"
#include "command_user_status.h"



#endif




#include "userinfoshower.h"
#include "datasource.h"

UserInfoShower::UserInfoShower(UserInfo* info, QWidget *parent)
	: QWidget(parent), m_info(info)
{
	ui.setupUi(this);

	ui.m_name->setText(info->name);
	ui.m_pwd->setText(info->pwd);
	ui.m_info->setText(info->info);
	QPixmap pix;
	if (pix.loadFromData(info->img))
	{	

		ui.m_img->setPixmap(pix);
	}
}

UserInfoShower::~UserInfoShower()
{
}

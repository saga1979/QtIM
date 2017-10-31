#include <cassert>
#include "userinfoshower.h"
#include "datasource.h"

UserInfoShower::UserInfoShower(UserInfo* info, QWidget *parent)
	: QWidget(parent), m_info(info)
{
	assert(info != 0);
	ui.setupUi(this);

	ui.m_name->setText(info->name);
	ui.m_pwd->setText(info->pwd);
	ui.m_info->setText(info->info);
	QPixmap pix;
	if (pix.loadFromData(info->img))
	{	

		ui.m_img->setPixmap(pix);
	}
	this->setEnabled(false);
}

UserInfoShower::~UserInfoShower()
{
	if (m_info != 0)
	{
		delete m_info;
	}
}

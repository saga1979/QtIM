#pragma once

#include <QWidget>

#include "ui_userinfoshower.h"

class UserInfo;

class UserInfoShower : public QWidget
{
	Q_OBJECT

public:
	UserInfoShower(UserInfo*, QWidget *parent = Q_NULLPTR);
	~UserInfoShower();

private:
	Ui::UserInfoShower ui;
	UserInfo *m_info;
};

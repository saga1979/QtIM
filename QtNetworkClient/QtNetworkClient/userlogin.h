#pragma once

#include <QDialog>
#include "ui_userlogin.h"

class UserLogin : public QDialog
{
	Q_OBJECT

public:
	UserLogin(QWidget *parent = Q_NULLPTR);
	~UserLogin();

private:
	Ui::UserLogin ui;
};

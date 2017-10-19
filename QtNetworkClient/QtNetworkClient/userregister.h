#pragma once

#include <QDialog>
#include "ui_userregister.h"

class UserRegister : public QDialog
{
	Q_OBJECT

public:
	UserRegister(QWidget *parent = Q_NULLPTR);
	~UserRegister();

private:
	Ui::UserRegister ui;
};

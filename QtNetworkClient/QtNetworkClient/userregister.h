#pragma once

#include <QDialog>
#include "ui_userregister.h"

class CommandRegister;

class UserRegister : public QDialog
{
	Q_OBJECT

public:
	UserRegister(QWidget *parent = Q_NULLPTR);
	~UserRegister();

    CommandRegister*  message();

Q_SIGNALS:
	void userRegister();

private Q_SLOTS:
	void OnRegister();

private:
	Ui::UserRegister ui;
	CommandRegister* m_cmd;

};

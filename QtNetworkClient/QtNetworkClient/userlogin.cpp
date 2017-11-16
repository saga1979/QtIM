#include "userlogin.h"
#include "command_def.h"
#include <QMessageBox>

UserLogin::UserLogin(QWidget *parent)
	: QDialog(parent), m_socket(0)
{
	ui.setupUi(this);
	QObject::connect(ui.m_pbLogin, SIGNAL(clicked()), this, SLOT(OnLogin()));
}

UserLogin::~UserLogin()
{
}



void UserLogin::OnLogin()
{
	LoginInfo info;
	info.server  = ui.m_leServer->text();
	info.port = ui.m_lePort->text().toInt();
	info.id = ui.m_leUser->text();
	info.pwd = ui.m_lePwd->text();

	//ui.m_pbLogin->setDisabled(true);
	ui.m_pbLogin->setText("connectiong...");	
	emit LoginRequest(info);
}

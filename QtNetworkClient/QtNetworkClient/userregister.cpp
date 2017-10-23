#include "userregister.h"

#include "command_def.h"

#include <QFile>

UserRegister::UserRegister(QWidget *parent)
	: QDialog(parent),m_cmd(0)
{
	ui.setupUi(this);

	ui.m_lbImage->setImage(":/menu/resources/default_user_image.png");	
	QObject::connect(ui.m_pbRegister, SIGNAL(clicked()), this, SLOT(OnRegister()));

}

UserRegister::~UserRegister()
{
	if (m_cmd != 0)
	{
		delete m_cmd;
	}
}

void UserRegister::OnRegister()
{
	emit userRegister();
}

CommandRegister*  UserRegister::message()
{
	if (m_cmd)
	{
		delete m_cmd;
	}

	m_cmd = new CommandRegister;
	m_cmd->name = ui.m_leName->text().toStdString();
	m_cmd->pwd = ui.m_lePwd1->text().toStdString();
	m_cmd->info = ui.m_teInfo->toPlainText().toStdString();

	const QString& fileName = ui.m_lbImage->getImage();

	QFile file(fileName);

	if (file.open(QIODevice::ReadOnly))
	{
		QByteArray bytes = file.readAll();

	    m_cmd->img = bytes.toStdString();
	}
	else
	{
		delete m_cmd;
		m_cmd = 0;
	}

	return m_cmd;
}

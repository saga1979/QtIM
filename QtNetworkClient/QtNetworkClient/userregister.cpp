#include "userregister.h"



UserRegister::UserRegister(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.m_lbImage->setImage(":/menu/resources/default_user_image.png");

}

UserRegister::~UserRegister()
{
}

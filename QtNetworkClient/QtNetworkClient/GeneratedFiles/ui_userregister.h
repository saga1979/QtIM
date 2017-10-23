/********************************************************************************
** Form generated from reading UI file 'userregister.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERREGISTER_H
#define UI_USERREGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "imagelabel.h"

QT_BEGIN_NAMESPACE

class Ui_UserRegister
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *m_leName;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *m_lePwd1;
    QLabel *label_4;
    QLineEdit *m_lePwd2;
    ImageLabel *m_lbImage;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *m_teInfo;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_pbRegister;
    QPushButton *pushButton_2;

    void setupUi(QWidget *UserRegister)
    {
        if (UserRegister->objectName().isEmpty())
            UserRegister->setObjectName(QStringLiteral("UserRegister"));
        UserRegister->resize(455, 389);
        verticalLayout_3 = new QVBoxLayout(UserRegister);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(UserRegister);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        m_leName = new QLineEdit(UserRegister);
        m_leName->setObjectName(QStringLiteral("m_leName"));

        horizontalLayout->addWidget(m_leName);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_3 = new QLabel(UserRegister);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);

        m_lePwd1 = new QLineEdit(UserRegister);
        m_lePwd1->setObjectName(QStringLiteral("m_lePwd1"));

        horizontalLayout_4->addWidget(m_lePwd1);

        label_4 = new QLabel(UserRegister);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        m_lePwd2 = new QLineEdit(UserRegister);
        m_lePwd2->setObjectName(QStringLiteral("m_lePwd2"));

        horizontalLayout_4->addWidget(m_lePwd2);


        verticalLayout_2->addLayout(horizontalLayout_4);


        horizontalLayout_2->addLayout(verticalLayout_2);

        m_lbImage = new ImageLabel(UserRegister);
        m_lbImage->setObjectName(QStringLiteral("m_lbImage"));
        m_lbImage->setMinimumSize(QSize(64, 64));
        m_lbImage->setMaximumSize(QSize(64, 64));

        horizontalLayout_2->addWidget(m_lbImage);


        verticalLayout_3->addLayout(horizontalLayout_2);

        groupBox = new QGroupBox(UserRegister);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        m_teInfo = new QPlainTextEdit(groupBox);
        m_teInfo->setObjectName(QStringLiteral("m_teInfo"));

        verticalLayout->addWidget(m_teInfo);


        verticalLayout_3->addWidget(groupBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        m_pbRegister = new QPushButton(UserRegister);
        m_pbRegister->setObjectName(QStringLiteral("m_pbRegister"));

        horizontalLayout_3->addWidget(m_pbRegister);

        pushButton_2 = new QPushButton(UserRegister);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_3->addWidget(pushButton_2);


        verticalLayout_3->addLayout(horizontalLayout_3);


        retranslateUi(UserRegister);

        QMetaObject::connectSlotsByName(UserRegister);
    } // setupUi

    void retranslateUi(QWidget *UserRegister)
    {
        UserRegister->setWindowTitle(QApplication::translate("UserRegister", "UserRegister", Q_NULLPTR));
        label_2->setText(QApplication::translate("UserRegister", "Name:", Q_NULLPTR));
        label_3->setText(QApplication::translate("UserRegister", "password:", Q_NULLPTR));
        label_4->setText(QApplication::translate("UserRegister", "repeat password:", Q_NULLPTR));
        m_lbImage->setText(QString());
        groupBox->setTitle(QApplication::translate("UserRegister", "Person Infomation", Q_NULLPTR));
        m_pbRegister->setText(QApplication::translate("UserRegister", "Register", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("UserRegister", "cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class UserRegister: public Ui_UserRegister {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERREGISTER_H

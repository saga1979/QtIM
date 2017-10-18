/********************************************************************************
** Form generated from reading UI file 'qtnetworkclient.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTNETWORKCLIENT_H
#define UI_QTNETWORKCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtNetworkClientClass
{
public:
    QWidget *centralWidget;
    QLineEdit *lineEdit;
    QSpinBox *spinBox;
    QPushButton *m_btConnect;
    QListWidget *m_lwMessages;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtNetworkClientClass)
    {
        if (QtNetworkClientClass->objectName().isEmpty())
            QtNetworkClientClass->setObjectName(QStringLiteral("QtNetworkClientClass"));
        QtNetworkClientClass->resize(600, 400);
        centralWidget = new QWidget(QtNetworkClientClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(60, 90, 113, 20));
        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(200, 90, 42, 22));
        m_btConnect = new QPushButton(centralWidget);
        m_btConnect->setObjectName(QStringLiteral("m_btConnect"));
        m_btConnect->setGeometry(QRect(340, 90, 75, 23));
        m_lwMessages = new QListWidget(centralWidget);
        m_lwMessages->setObjectName(QStringLiteral("m_lwMessages"));
        m_lwMessages->setGeometry(QRect(50, 140, 371, 181));
        QtNetworkClientClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtNetworkClientClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        QtNetworkClientClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtNetworkClientClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtNetworkClientClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtNetworkClientClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtNetworkClientClass->setStatusBar(statusBar);

        retranslateUi(QtNetworkClientClass);

        QMetaObject::connectSlotsByName(QtNetworkClientClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtNetworkClientClass)
    {
        QtNetworkClientClass->setWindowTitle(QApplication::translate("QtNetworkClientClass", "QtNetworkClient", Q_NULLPTR));
        m_btConnect->setText(QApplication::translate("QtNetworkClientClass", "connect", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtNetworkClientClass: public Ui_QtNetworkClientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTNETWORKCLIENT_H

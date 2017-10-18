/********************************************************************************
** Form generated from reading UI file 'QtNetworkServer.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTNETWORKSERVER_H
#define UI_QTNETWORKSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtNetworkServerClass
{
public:
    QWidget *centralWidget;
    QPushButton *m_btStart;
    QLineEdit *lineEdit;
    QPushButton *m_btSend;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtNetworkServerClass)
    {
        if (QtNetworkServerClass->objectName().isEmpty())
            QtNetworkServerClass->setObjectName(QStringLiteral("QtNetworkServerClass"));
        QtNetworkServerClass->resize(600, 400);
        centralWidget = new QWidget(QtNetworkServerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        m_btStart = new QPushButton(centralWidget);
        m_btStart->setObjectName(QStringLiteral("m_btStart"));
        m_btStart->setGeometry(QRect(110, 50, 75, 23));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(70, 150, 241, 20));
        m_btSend = new QPushButton(centralWidget);
        m_btSend->setObjectName(QStringLiteral("m_btSend"));
        m_btSend->setGeometry(QRect(360, 150, 75, 23));
        QtNetworkServerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtNetworkServerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        QtNetworkServerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtNetworkServerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtNetworkServerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtNetworkServerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtNetworkServerClass->setStatusBar(statusBar);

        retranslateUi(QtNetworkServerClass);

        QMetaObject::connectSlotsByName(QtNetworkServerClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtNetworkServerClass)
    {
        QtNetworkServerClass->setWindowTitle(QApplication::translate("QtNetworkServerClass", "QtNetworkServer", Q_NULLPTR));
        m_btStart->setText(QApplication::translate("QtNetworkServerClass", "start", Q_NULLPTR));
        m_btSend->setText(QApplication::translate("QtNetworkServerClass", "send", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtNetworkServerClass: public Ui_QtNetworkServerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTNETWORKSERVER_H

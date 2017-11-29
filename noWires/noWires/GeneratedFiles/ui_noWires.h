/********************************************************************************
** Form generated from reading UI file 'noWires.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOWIRES_H
#define UI_NOWIRES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_noWiresClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *noWiresClass)
    {
        if (noWiresClass->objectName().isEmpty())
            noWiresClass->setObjectName(QStringLiteral("noWiresClass"));
        noWiresClass->resize(600, 400);
        centralWidget = new QWidget(noWiresClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        noWiresClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(noWiresClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        noWiresClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(noWiresClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        noWiresClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(noWiresClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        noWiresClass->setStatusBar(statusBar);

        retranslateUi(noWiresClass);

        QMetaObject::connectSlotsByName(noWiresClass);
    } // setupUi

    void retranslateUi(QMainWindow *noWiresClass)
    {
        noWiresClass->setWindowTitle(QApplication::translate("noWiresClass", "noWires", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class noWiresClass: public Ui_noWiresClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOWIRES_H

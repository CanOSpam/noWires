/********************************************************************************
** Form generated from reading UI file 'noWires.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
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
    QAction *actionOpen_File;
    QAction *actionSend;
    QAction *actionRVI;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *noWiresClass)
    {
        if (noWiresClass->objectName().isEmpty())
            noWiresClass->setObjectName(QStringLiteral("noWiresClass"));
        noWiresClass->resize(600, 400);
        actionOpen_File = new QAction(noWiresClass);
        actionOpen_File->setObjectName(QStringLiteral("actionOpen_File"));
        actionSend = new QAction(noWiresClass);
        actionSend->setObjectName(QStringLiteral("actionSend"));
        actionRVI = new QAction(noWiresClass);
        actionRVI->setObjectName(QStringLiteral("actionRVI"));
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

        mainToolBar->addAction(actionOpen_File);
        mainToolBar->addAction(actionSend);
        mainToolBar->addAction(actionRVI);

        retranslateUi(noWiresClass);

        QMetaObject::connectSlotsByName(noWiresClass);
    } // setupUi

    void retranslateUi(QMainWindow *noWiresClass)
    {
        noWiresClass->setWindowTitle(QApplication::translate("noWiresClass", "noWires", 0));
        actionOpen_File->setText(QApplication::translate("noWiresClass", "Open File", 0));
#ifndef QT_NO_TOOLTIP
        actionOpen_File->setToolTip(QApplication::translate("noWiresClass", "Choose a file to open", 0));
#endif // QT_NO_TOOLTIP
        actionSend->setText(QApplication::translate("noWiresClass", "Send", 0));
        actionRVI->setText(QApplication::translate("noWiresClass", "RVI", 0));
#ifndef QT_NO_TOOLTIP
        actionRVI->setToolTip(QApplication::translate("noWiresClass", "Send an RVI", 0));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class noWiresClass: public Ui_noWiresClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOWIRES_H

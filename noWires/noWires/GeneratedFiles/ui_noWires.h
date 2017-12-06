/********************************************************************************
** Form generated from reading UI file 'noWires.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
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

class Ui_mainWindow
{
public:
    QAction *actionOpen_File;
    QAction *actionSend;
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionRVI;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *mainWindow)
    {
        if (mainWindow->objectName().isEmpty())
            mainWindow->setObjectName(QStringLiteral("mainWindow"));
        mainWindow->resize(600, 400);
        actionOpen_File = new QAction(mainWindow);
        actionOpen_File->setObjectName(QStringLiteral("actionOpen_File"));
        actionSend = new QAction(mainWindow);
        actionSend->setObjectName(QStringLiteral("actionSend"));
        actionConnect = new QAction(mainWindow);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        actionDisconnect = new QAction(mainWindow);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        actionRVI = new QAction(mainWindow);
        actionRVI->setObjectName(QStringLiteral("actionRVI"));
        centralWidget = new QWidget(mainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        mainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(mainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        mainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(mainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(mainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        mainWindow->setStatusBar(statusBar);

        mainToolBar->addAction(actionOpen_File);
        mainToolBar->addAction(actionSend);
        mainToolBar->addAction(actionConnect);
        mainToolBar->addAction(actionDisconnect);
        mainToolBar->addAction(actionRVI);

        retranslateUi(mainWindow);

        QMetaObject::connectSlotsByName(mainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *mainWindow)
    {
        mainWindow->setWindowTitle(QApplication::translate("mainWindow", "noWires", Q_NULLPTR));
        actionOpen_File->setText(QApplication::translate("mainWindow", "Open File", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionOpen_File->setToolTip(QApplication::translate("mainWindow", "Choose a file to open", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionSend->setText(QApplication::translate("mainWindow", "Send", Q_NULLPTR));
        actionConnect->setText(QApplication::translate("mainWindow", "Connect", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionConnect->setToolTip(QApplication::translate("mainWindow", "Connect to a serial port", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionDisconnect->setText(QApplication::translate("mainWindow", "Disconnect", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionDisconnect->setToolTip(QApplication::translate("mainWindow", "Disconnect from serial port", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionRVI->setText(QApplication::translate("mainWindow", "RVI", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionRVI->setToolTip(QApplication::translate("mainWindow", "Send an RVI", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class mainWindow: public Ui_mainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOWIRES_H

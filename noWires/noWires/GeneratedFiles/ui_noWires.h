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

class Ui_mainWindow
{
public:
    QAction *actionOpen_File;
    QAction *actionSend;
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
    } // retranslateUi

};

namespace Ui {
    class mainWindow: public Ui_mainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOWIRES_H

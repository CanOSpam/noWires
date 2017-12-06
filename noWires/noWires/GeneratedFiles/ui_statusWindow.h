/********************************************************************************
** Form generated from reading UI file 'statusWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATUSWINDOW_H
#define UI_STATUSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_statusWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *BERname;
    QLabel *BERNum;
    QFrame *line;
    QLabel *label_4;
    QLabel *FramesNum;
    QFrame *line_2;
    QLabel *ACKname;
    QLabel *AckNum;

    void setupUi(QWidget *statusWindow)
    {
        if (statusWindow->objectName().isEmpty())
            statusWindow->setObjectName(QStringLiteral("statusWindow"));
        statusWindow->resize(184, 175);
        verticalLayout = new QVBoxLayout(statusWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        BERname = new QLabel(statusWindow);
        BERname->setObjectName(QStringLiteral("BERname"));

        verticalLayout->addWidget(BERname);

        BERNum = new QLabel(statusWindow);
        BERNum->setObjectName(QStringLiteral("BERNum"));

        verticalLayout->addWidget(BERNum);

        line = new QFrame(statusWindow);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        label_4 = new QLabel(statusWindow);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        FramesNum = new QLabel(statusWindow);
        FramesNum->setObjectName(QStringLiteral("FramesNum"));

        verticalLayout->addWidget(FramesNum);

        line_2 = new QFrame(statusWindow);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        ACKname = new QLabel(statusWindow);
        ACKname->setObjectName(QStringLiteral("ACKname"));

        verticalLayout->addWidget(ACKname);

        AckNum = new QLabel(statusWindow);
        AckNum->setObjectName(QStringLiteral("AckNum"));

        verticalLayout->addWidget(AckNum);


        retranslateUi(statusWindow);

        QMetaObject::connectSlotsByName(statusWindow);
    } // setupUi

    void retranslateUi(QWidget *statusWindow)
    {
        statusWindow->setWindowTitle(QApplication::translate("statusWindow", "Form", 0));
        BERname->setText(QApplication::translate("statusWindow", "Bit Error Rate", 0));
        BERNum->setText(QApplication::translate("statusWindow", "0", 0));
        label_4->setText(QApplication::translate("statusWindow", "Frames Received", 0));
        FramesNum->setText(QApplication::translate("statusWindow", "0", 0));
        ACKname->setText(QApplication::translate("statusWindow", "ACKs Received", 0));
        AckNum->setText(QApplication::translate("statusWindow", "0", 0));
    } // retranslateUi

};

namespace Ui {
    class statusWindow: public Ui_statusWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATUSWINDOW_H

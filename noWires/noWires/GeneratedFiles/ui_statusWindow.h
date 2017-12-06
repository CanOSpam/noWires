/********************************************************************************
** Form generated from reading UI file 'statusWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
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
    QLabel *FrameRXName_2;
    QLabel *FramesTXNum;
    QFrame *line_3;
    QLabel *FramesRXName;
    QLabel *FramesRXNum;
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

        FrameRXName_2 = new QLabel(statusWindow);
        FrameRXName_2->setObjectName(QStringLiteral("FrameRXName_2"));

        verticalLayout->addWidget(FrameRXName_2);

        FramesTXNum = new QLabel(statusWindow);
        FramesTXNum->setObjectName(QStringLiteral("FramesTXNum"));

        verticalLayout->addWidget(FramesTXNum);

        line_3 = new QFrame(statusWindow);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        FramesRXName = new QLabel(statusWindow);
        FramesRXName->setObjectName(QStringLiteral("FramesRXName"));

        verticalLayout->addWidget(FramesRXName);

        FramesRXNum = new QLabel(statusWindow);
        FramesRXNum->setObjectName(QStringLiteral("FramesRXNum"));

        verticalLayout->addWidget(FramesRXNum);

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
        statusWindow->setWindowTitle(QApplication::translate("statusWindow", "Form", Q_NULLPTR));
        BERname->setText(QApplication::translate("statusWindow", "Bit Error Rate", Q_NULLPTR));
        BERNum->setText(QApplication::translate("statusWindow", "0", Q_NULLPTR));
        FrameRXName_2->setText(QApplication::translate("statusWindow", "Frames Sent", Q_NULLPTR));
        FramesTXNum->setText(QApplication::translate("statusWindow", "0", Q_NULLPTR));
        FramesRXName->setText(QApplication::translate("statusWindow", "Frames Received", Q_NULLPTR));
        FramesRXNum->setText(QApplication::translate("statusWindow", "0", Q_NULLPTR));
        ACKname->setText(QApplication::translate("statusWindow", "ACKs Received", Q_NULLPTR));
        AckNum->setText(QApplication::translate("statusWindow", "0", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class statusWindow: public Ui_statusWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATUSWINDOW_H

#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushbutton>
#include <QFiledialog>
#include <QDesktopservices>
#include <QDebug>
#include <QSerialPort>
#include <QInputDialog>

#include <iostream>
#include <fstream> 

#include "ui_noWires.h"
#include "controlFrame.h"
#include "dataFrame.h"
#include "textBox.h"
#include "CRCpp.h"


#define ACK 0x06
#define ENQ 0x05
#define SYN 0x16


class noWires : public QMainWindow
{
	Q_OBJECT

public:
	noWires(QWidget *parent = Q_NULLPTR);

private:

	QString fileName;
	std::ifstream inputFile;
	bool fileOpen;
	QSerialPort *serial;
	TextBox *textBox;

	Ui::noWiresClass ui;
	inline void addButtons();
	void startSending();
	void openAFile();
	void sendData(QByteArray toSend);
	void connectPort();
	void getControlToSend();



public slots:
	void readData();
};


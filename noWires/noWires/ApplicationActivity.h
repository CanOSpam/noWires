#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushbutton>
#include <QFiledialog>
#include <QDesktopservices>
#include <QDebug>
#include <QSerialPort>
#include <QMessageBox>

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


class ApplicationActivity : public QMainWindow
{
	Q_OBJECT

public:
	ApplicationActivity(QWidget *parent = Q_NULLPTR);
	virtual ~ApplicationActivity();

private:

	QString fileName;
	std::ifstream inputFile;
	bool fileOpen;
	QSerialPort *serial;
	TextBox *textBox;

	Ui::mainWindow ui;
	inline void addButtons();
	void startSending();
	void openAFile();
	void sendData(QByteArray toSend);
	void connectPort();
	void getControlToSend();
	void receivingFrame(QByteArray toReceive);
	void closePort();
	void handleException(QSerialPort::SerialPortError e);
	void demo_Frames();


public slots:
	void readData();
};


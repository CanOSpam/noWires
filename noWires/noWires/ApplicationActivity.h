#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushbutton>
#include <QFiledialog>
#include <QDesktopservices>
#include <QDebug>
#include <QSerialPort>
#include <QInputDialog>
#include <QMessageBox>

#include <iostream>
#include <fstream> 
#include <ctime>

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

	QString comPort;
	QString fileName;
	std::ifstream inputFile;
	bool bFileOpen;
	bool bReceivedENQ;
	bool bReceivedACK;
	QSerialPort *serial;
	TextBox *textBox;

	Ui::mainWindow ui;
	inline void addButtons();
	//void startSending();
	//void openAFile();
	void getControlToSend();
	void closePort();
	void handlePortExceptions(QSerialPort::SerialPortError e);
	void sendData(QByteArray toSend);
	void fileToSend();
	void prepareToSend();
	bool bidForLine();
	void filePicker();

	void demo_Frames();

public slots:
	void readData();
	void startSending();
	void connectPort();
};


#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushbutton>
#include <QFiledialog>
#include <QDesktopservices>
#include <QDebug>
#include <QSerialPort>
#include <QInputDialog>
#include <QMessageBox>
#include <QTime>

#include <iostream>
#include <fstream> 
#include <chrono>
#include <thread>

#include "ui_noWires.h"
#include "controlFrame.h"
#include "dataFrame.h"
#include "textBox.h"
#include "CRCpp.h"
#include "statusWindow.h"

#define ACK 0x06
#define ENQ 0x05
#define SYN 0x16
#define RVI 0x07


namespace Ui 
{
	class ui;
};

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
	bool retransmit;
	bool bReceivedENQ;
	bool bReceivedACK;
	QSerialPort *serial;
	TextBox *textBox;
	QByteArray buffer;
	Ui::mainWindow ui;
	statusWindow *monitor;

	void closePort();
	void handlePortExceptions(QSerialPort::SerialPortError e);
	void prepareToSend();
	bool bidForLine();

	inline void addButtons();
	void filePicker(); //orig openAFile
	void sendOneDataFrame();
	void sendData(QByteArray toSend);
	void sendENQ();
	void sendACK();

public slots:
	void readData();
	void fileToSend(); //orig startSending();
	void connectPort();
	void disconnectPort();
	void sendRVI();

};


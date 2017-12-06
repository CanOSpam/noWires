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
#include "statusWindow.h"


#define ACK 0x06
#define ENQ 0x05
#define SYN 0x16
#define RVI 0x07

class noWires : public QMainWindow
{
	Q_OBJECT

public:
	noWires(QWidget *parent = Q_NULLPTR);
	~noWires();

private:
	QString comPort;
	QString fileName;
	std::ifstream inputFile;
	bool fileOpen;
	QSerialPort *serial;
	TextBox *textBox;
	QByteArray buffer;
	Ui::noWiresClass ui;
	statusWindow *monitor;

	
	inline void addButtons();
	void openAFile();
	void sendData(QByteArray toSend);
	void sendENQ();

	void sendACK();



public slots:
	void readData();
	void startSending();
	void connectPort();
	void sendRVI();

};


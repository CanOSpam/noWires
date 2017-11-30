#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushbutton>
#include <QFiledialog>
#include <QDesktopservices>
#include <QDebug>
#include <QSerialPort>

#include <iostream>
#include <fstream> 

#include "ui_noWires.h"

#define ACK 0x06
#define ENQ 0x05

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

	Ui::noWiresClass ui;
	inline void addButtons();
	void startSending();
	void openAFile();
	void sendData(QByteArray toSend);
	void connectPort();

public slots:
	void readData();
};


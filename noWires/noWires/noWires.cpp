#include "noWires.h"

noWires::noWires(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	fileOpen = false;

	addButtons();
	serial =  &QSerialPort("COM1", this);

	
	connectPort();
	
}

inline void noWires::addButtons()
{

	connect(ui.actionSend, &QAction::triggered, this, &noWires::startSending);
	connect(ui.actionOpen_File, &QAction::triggered, this, &noWires::openAFile);
	ui.actionSend->setEnabled(false);
}

void noWires::startSending()
{
	//Start Protocol
	statusBar()->showMessage(tr("Sending"));
}

void noWires::openAFile()
{
	fileName = QFileDialog::getOpenFileName(this,
		tr("Choose File to Send"), "./", tr("Text File (*.txt)"));

	qDebug() << fileName;

	inputFile.open(fileName.toStdString());
	ui.actionSend->setEnabled(false);

	if (inputFile.is_open())
	{
		fileOpen = true;
		ui.actionSend->setEnabled(true);
		statusBar()->showMessage(tr("Ready to send"));
	}
}


void noWires::readData()
{
	QByteArray data = serial->readAll();

	//enq
	if (data[0] = 0x05)
	{
		QByteArray send;
		send.resize(1);
		send[0] = 0x06; //ack
		sendData(send);
	}
}

void noWires::sendData(QByteArray toSend)
{
	serial->write(toSend);
}

void noWires::connectPort()
{
	//Set defaults
	serial->setBaudRate(QSerialPort::Baud9600);
	serial->setDataBits(QSerialPort::Data8);
	serial->setParity(QSerialPort::NoParity);
	serial->setStopBits(QSerialPort::OneStop);
	serial->setFlowControl(QSerialPort::NoFlowControl);

	if (!serial->open(QIODevice::ReadWrite)) {
		qDebug() << serial->errorString();
		return;
	}
	else
	{
		qDebug() << serial->isOpen();
		qDebug() << serial->baudRate();
		qDebug() << serial->portName();
		connect(serial, &QSerialPort::readyRead, this, &noWires::readData);
	}
}
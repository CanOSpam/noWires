#include "noWires.h"


noWires::noWires(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	fileOpen = false;

	addButtons();

	bool ok;

	//Show Com select dialog
	comPort = QInputDialog::getText(this, tr("Com picker"),
		tr("Pick a com port"), QLineEdit::Normal, "COM1", &ok);

	//Show Status monitor
	monitor = new statusWindow();
	monitor->show();

	serial = new QSerialPort(comPort, this);
	textBox = new TextBox;
	setCentralWidget(textBox);
	textBox->setLocalEchoEnabled(false);


	connectPort();
}

inline void noWires::addButtons()
{

	connect(ui.actionSend, &QAction::triggered, this, &noWires::startSending);
	connect(ui.actionOpen_File, &QAction::triggered, this, &noWires::openAFile);
	connect(ui.actionRVI, &QAction::triggered, this, &noWires::sendRVI);
	ui.actionSend->setEnabled(false);
}

//jc
void noWires::startSending()
{
	//Start Protocol
	statusBar()->showMessage(tr("Sending"));

	char character;
	while (true)
	{
		QByteArray data;
		for (int i = 0; i < 512; i++) {
			inputFile.get(character);
			if (inputFile.fail())
			{
				break;
			}
			data[i] = character;
		}
		dataFrame frame(data);
		qDebug() << frame.getFrame();
		serial->write(frame.getFrame());
		serial->flush();
		break;

	}
	inputFile.close();
	monitor->incrementTXFrames();
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
	buffer.append(serial->readAll());

	if ((buffer[0] == (char)SYN) && (buffer[1] == (char)ACK))
	{
		monitor->incrementAck();
	}
	if ((buffer[0] == (char)SYN) && (buffer[1] == (char)ENQ))
	{
		buffer.remove(0, 2);
		sendACK();
	}
	else if ((buffer[0] == (char)SYN) && (buffer[1] == (char)STX))
	{
		if (buffer.size() >= 518)
		{
			monitor->incrementRXFrames();
			//Data
			QByteArray toRead(buffer, 518);
			buffer.remove(0, 518);
			QByteArray data;
			QByteArray receivedCheckSum;

			toRead.remove(0, 2);
			data.append(toRead, 512);
			toRead.remove(0, 512);
			receivedCheckSum.append(toRead, 4);

			qDebug() << "DATA SIZE: " << data.size();
			qDebug() << "DATA: " << data;

			//calculate and check CRC
			quint32 crc = CRC::Calculate(data, 512, CRC::CRC_32());

			QByteArray calculatedByteCheckSum;
			calculatedByteCheckSum << crc;

			qDebug() << "RECE CRC: " << receivedCheckSum;
			qDebug() << "CALC CRC: " << calculatedByteCheckSum;

			if (calculatedByteCheckSum == receivedCheckSum)
			{
				textBox->putData(data);
				sendACK();
			}
			else 
			{
				monitor->incrementErrors();
			}
			toRead.clear();
		}
	}



}

void noWires::sendENQ()
{
	controlFrame enq(QByteArray(1, ENQ));
	serial->write(enq.getFrame());
}

void noWires::sendACK()
{
	controlFrame ack(QByteArray(1, ACK));
	serial->write(ack.getFrame());
}

void noWires::sendRVI()
{
	controlFrame ack(QByteArray(1, RVI));
	serial->write(ack.getFrame());
}

void noWires::sendData(QByteArray toSend)
{
	serial->write(toSend);
}

void noWires::connectPort()
{
	//Set defaults
	serial->setPortName(comPort);
	serial->setBaudRate(QSerialPort::Baud9600);
	serial->setDataBits(QSerialPort::Data8);
	serial->setParity(QSerialPort::NoParity);
	serial->setStopBits(QSerialPort::OneStop);
	serial->setFlowControl(QSerialPort::NoFlowControl);

	if (!serial->open(QIODevice::ReadWrite))
	{
		qDebug() << serial->errorString();
		return;
	}
	else
	{
		qDebug() << serial->isOpen();
		qDebug() << serial->baudRate();
		qDebug() << serial->portName();
		connect(serial, &QSerialPort::readyRead, this, &noWires::readData);
		connect(textBox, &TextBox::getData, this, &noWires::startSending);

	}
}

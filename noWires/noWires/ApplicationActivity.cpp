#include "ApplicationActivity.h"

ApplicationActivity::ApplicationActivity(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	bFileOpen = false;
	bReceivedENQ = false;
	bReceivedACK = false;

	addButtons();

	textBox = new TextBox;
	setCentralWidget(textBox);
	textBox->setLocalEchoEnabled(false);

	bool ok;
	comPort = QInputDialog::getText(this, tr("Com picker"),
 		tr("Pick a com port"), QLineEdit::Normal, "COM1", &ok);
 	//serial port not usable until opened
 	serial = new QSerialPort(comPort, this); 
	connectPort(); //dont call it here
}

ApplicationActivity::~ApplicationActivity()
{
	closePort();
	delete textBox;
}

inline void ApplicationActivity::addButtons()
{
	connect(ui.actionSend, &QAction::triggered, this, &ApplicationActivity::fileToSend);
	connect(ui.actionOpen_File, &QAction::triggered, this, &ApplicationActivity::filePicker);
	ui.actionSend->setEnabled(false);
}

void ApplicationActivity::filePicker()
{
	fileName = QFileDialog::getOpenFileName(this,
		tr("Choose File to Send"), "./", tr("Text File (*.txt)"));

	qDebug() << fileName;

	inputFile.open(fileName.toStdString());
	ui.actionSend->setEnabled(false);

	if (inputFile.is_open())
	{
		bFileOpen = true;
		ui.actionSend->setEnabled(true);
		statusBar()->showMessage(tr("Ready to send"));
	}
}

bool ApplicationActivity::bidForLine() 
{
	controlFrame enq(QByteArray(1, ENQ));
	sendData(enq.getFrame());
	auto startTimer = std::clock();
	while( (std::clock() - startTimer) < 2 )
	{
		if (bReceivedACK && !bReceivedENQ)
		{
			return true;
		}
	}
	//success;
	return false;
}

void ApplicationActivity::connectPort()
{
	//Set defaults
	if (comPort == "")
	{
		comPort = "COM1";
	}
	serial->setPortName(comPort);
	serial->setBaudRate(QSerialPort::Baud9600);
	serial->setDataBits(QSerialPort::Data8);
	serial->setParity(QSerialPort::NoParity);
	serial->setStopBits(QSerialPort::OneStop);
	serial->setFlowControl(QSerialPort::NoFlowControl);

	if (!serial->open(QIODevice::ReadWrite))
	{
		qDebug() << serial->errorString();
		handlePortExceptions(serial->error()); // serial->error() : QSerialPort::SerialPortError 
		return;
	}
	else
	{
		qDebug() << serial->isOpen();
		qDebug() << serial->baudRate();
		qDebug() << serial->portName();
		//RX all
		connect(serial, &QSerialPort::readyRead, this, &ApplicationActivity::readData);
		connect(textBox, &TextBox::getData, this, &ApplicationActivity::fileToSend);
	}
}

//vetoed as usual
int timer()
{
	std::clock_t timer;
	double start = std::clock(); 
	double duration = (std::clock() - start); 
	return duration;
}

//orig startSending
void ApplicationActivity::fileToSend()
{
	//Start Protocol
	statusBar()->showMessage(tr("Sending"));
	/*if (!bidForLine())
	{
		qDebug() << "Bidding failed. Did not receive ACK in time" << "\n";
		closePort();
		return;
	}*/
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
		std::cout << frame.getFrame().toStdString();
		sendData(frame.getFrame());
		break;
	}
	inputFile.close();
} 

void ApplicationActivity::readData()
{

	buffer.append(serial->readAll());

	//enq
	if ((buffer[0] == (char)SYN) && (buffer[1] == (char)ENQ))
	{
		buffer.remove(0, 2);
		sendACK();
	}
	//ack
	if ((buffer[0] == (char)SYN) && (buffer[1] == (char)ACK))
	{
		
		bReceivedACK = true;
	}
	//data
	if ((buffer[0] == (char)SYN) && (buffer[1] == (char)STX))
	{
		if (buffer.size() >= 518)
		{
			qDebug() << "FRAME SIZE: " << buffer.count();
			std::cout << "FRAME : " << buffer.toStdString() << "\n";
			//Data
			//check CRC
			QByteArray toRead(buffer, 518);
			buffer.remove(0, 518);
			QByteArray data;
			QByteArray receivedCheckSum;

			//discard header, ie rip ticket on admission
			toRead.remove(0, 2);
			data.append(toRead, 512);
			toRead.remove(0, 512);
			receivedCheckSum.append(toRead, 4);

			qDebug() << "DATA SIZE: " << data.size();
			std::cout << "DATA: " << data.toStdString();

			quint32 CRCInt = CRC::Calculate(data, 512, CRC::CRC_32()); //orig crc
			QByteArray calculatedCRCBytes; //orig calculatedByteCheckSum
			calculatedCRCBytes << CRCInt;
			
			qDebug() << "\nRECE CRC: " << receivedCheckSum;
			qDebug() << "CALC CRC: " << calculatedCRCBytes;
			if (calculatedCRCBytes == receivedCheckSum)
			{
				textBox->putData(data);
				controlFrame ack(QByteArray(1, ACK));
				serial->write(ack.getFrame());
			}
			toRead.clear();
		}
  	}
}

void ApplicationActivity::getControlToSend()
{
	controlFrame enq(QByteArray(1, ENQ));
	sendData(enq.getFrame());
}

void ApplicationActivity::sendACK()
{
	controlFrame ack(QByteArray(1, ACK));
	sendData(ack.getFrame());
}

void ApplicationActivity::sendData(QByteArray toSend)
{
	if (serial->isOpen())
	{
		serial->write(toSend);
		serial->flush();
	}
} 

/* Handles unexpected errors QSerialPort might throw.
Does not check for or handle mistakes in data.  */
void ApplicationActivity::handlePortExceptions(QSerialPort::SerialPortError e)
{
	QMessageBox msgBox;
	msgBox.setText("Serial Port did not open successfully");
	msgBox.setInformativeText("Serial Port[" + serial->portName() + "] : " + serial->errorString());
	msgBox.setDefaultButton(QMessageBox::Ok);
	msgBox.exec();
	closePort();
}

void ApplicationActivity::closePort()
{
	// this if statment isnt actually needed, Qt handles closing null ports itself
	// but makes logical sense to put here
	if (serial->isOpen())
	{
		serial->close();
	}
}
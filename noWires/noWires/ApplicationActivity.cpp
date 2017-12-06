#include "ApplicationActivity.h"
/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: ApplicationActivity.cpp
--
-- PROGRAM: noWries
--
-- FUNCTIONS:
-- PUT FUNCTION ONCE FINALIZED
--
--
-- DATE: Dec 05, 2017
--
-- REVISIONS: None
--
-- DESIGNERS: Tim Bruecker, JC Tee, Keir Forster, Alex Xia
--
-- PROGRAMMERS: Tim Bruecker, JC Tee, Keir Forster, Alex Xia
--
-- NOTES:
-- This is the core class that runs the main window and executes most of the logic of the application. The protocol
-- decision structure and all the serial port and file handling happens in this file.
----------------------------------------------------------------------------------------------------------------------*/
ApplicationActivity::ApplicationActivity(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	bFileOpen = false;

	addButtons();

	//Show Status monitor
	monitor = new statusWindow();
	monitor->show();

	//Show frames status
	textBox = new TextBox;
	setCentralWidget(textBox);
	textBox->setLocalEchoEnabled(false);

 	//serial port not usable until opened
 	serial = new QSerialPort(comPort, this); 
}

ApplicationActivity::~ApplicationActivity()
{
	closePort();
	delete textBox;
	delete monitor;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: addButtons
--
-- DATE: Dec 05, 2017
--
-- REVISIONS: None
--
-- DESIGNER: Tim Bruecker
--
-- PROGRAMMER: Tim Bruecker
--
-- INTERFACE: void addButtons()
--
-- RETURNS: void
--
-- NOTES:
-- This function connects all the UI buttons to appropriate functions and disables the start sending button, as you can't
-- send before you have a file.
----------------------------------------------------------------------------------------------------------------------*/
inline void ApplicationActivity::addButtons()
{
	connect(ui.actionSend, &QAction::triggered, this, &ApplicationActivity::fileToSend);
	connect(ui.actionOpen_File, &QAction::triggered, this, &ApplicationActivity::filePicker);
	connect(ui.actionConnect, &QAction::triggered, this, &ApplicationActivity::connectPort);
	connect(ui.actionRVI, &QAction::triggered, this, &ApplicationActivity::sendRVI);
	connect(ui.actionDisconnect, &QAction::triggered, this, &ApplicationActivity::disconnectPort);
	
	ui.actionSend->setEnabled(false);
	ui.actionDisconnect->setEnabled(false);
}

void ApplicationActivity::filePicker()
{
	fileName = QFileDialog::getOpenFileName(this,
		tr("Choose File to Send"), "./", tr("Text File (*.txt)"));

	qDebug() << fileName;

	inputFile.open(fileName.toStdString());
	
	if (ui.actionDisconnect->isEnabled())
	{
		ui.actionSend->setEnabled(false);

		if (inputFile.is_open())
		{
			bFileOpen = true;
			ui.actionSend->setEnabled(true);
			statusBar()->showMessage(tr("File & Port ready. Ready to send."));
		}
	}
	else {
		statusBar()->showMessage(tr("File ready. Open port to send."));
	}
}

bool ApplicationActivity::bidForLine() 
{
	sendENQ();
	// QTime time = QTime::currentTime();
	serial->waitForReadyRead(getRandomTimeout());
	// std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	if( !bReceivedACK && !bReceivedENQ )
	{
		return false;
	}
	return true;
}
void ApplicationActivity::disconnectPort()
{
	if (serial->isOpen())
	{
		serial->close();
		if (serial->error())
		{
			handlePortExceptions(serial->error());
		}
	}
	ui.actionConnect->setEnabled(true);
	ui.actionDisconnect->setEnabled(false);
	ui.actionSend->setEnabled(false);
	statusBar()->showMessage(tr("Port closed."));
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: connectPort
--
-- DATE: Dec 05, 2017
--
-- REVISIONS: None
--
-- DESIGNER: Tim Bruecker
--
-- PROGRAMMER: Tim Bruecker
--
-- INTERFACE: void connectPort()
--
-- RETURNS: void
--
-- NOTES:
-- This passes the port name supplied by the user and sets the port name to the required settings to work with the
-- wireless modem. Then writes an error message or some basic data for the port to the console.
----------------------------------------------------------------------------------------------------------------------*/
void ApplicationActivity::connectPort()
{
	bool ok;
	comPort = QInputDialog::getText(this, tr("Com picker"),
		tr("Pick a com port"), QLineEdit::Normal, "COM1", &ok);
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
		ui.actionConnect->setEnabled(false);
		ui.actionDisconnect->setEnabled(true);
	}

	if (inputFile.is_open())
	{
		bFileOpen = true;
		ui.actionSend->setEnabled(true);
		statusBar()->showMessage(tr("File & Port ready. Ready to send."));
	} 
	else
	{
		statusBar()->showMessage(tr("Port ready. Choose a file to send."));
	}
}

//orig startSending
void ApplicationActivity::fileToSend()
{
	//Start Protocol
	statusBar()->showMessage(tr("Sending"));
	if (!bidForLine())
	{
		qDebug() << "Bidding failed. Did not receive ACK in time" << "\n";
		return;
	}

	while (inputFile.is_open() )
	{
		// sendOneDataFrame();
		for (int i = 0; i < 10; i++)
		{
			//will return false (timeout) after 2000
			//if receive serial data b4 then, returns true
			// {
				sendOneDataFrame();
				// std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				if (!inputFile.is_open())
				{
					return;
				}
				serial->waitForReadyRead(getRandomTimeout());
			// } 
		// 	else 
		// 	{
		// 		if (retransmit())
		// 		{
		// 			continue;
		// 		}
		// 		else 
		// 		{
		// 			QMessageBox msgBox;
		// 			msgBox.setText("Receiver timed out");
		// 			msgBox.setDefaultButton(QMessageBox::Ok);
		// 			msgBox.exec();
		// 			return;
		// 		}
		// 	}
		}
	}
} 

bool ApplicationActivity::retransmit() 
{
	//get position in file
	int fseekPos = inputFile.tellg();
	for (int i = 0; i < 3; i++)
	{
		inputFile.seekg(fseekPos);
		sendOneDataFrame();
		//on timeout, restart loop
		if (!serial->waitForReadyRead(getRandomTimeout())) 
		{
			continue;
		} 
		else 
		{
			return true;
		}
	}
	//3 attempts used
	return false;
}

size_t ApplicationActivity::getRandomTimeout()
{
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> rngRange(1, 10);
	size_t rngNum = rngRange(rng);
	//the formula the class(Benny) decided on
	return 2000u + rngNum * 100u;
}

void ApplicationActivity::sendOneDataFrame()
{
	char character;
	QByteArray data;
	for (int i = 0; i < 512; i++) 
	{
		inputFile.get(character);
		if (inputFile.fail())
		{
			inputFile.close();
			break;
		}
		data[i] = character;
	}

	dataFrame frame(data);
	std::cout << frame.getFrame().toStdString();
	sendData(frame.getFrame());
	//inputFile.close();
	monitor->incrementTXFrames();
	statusBar()->showMessage(tr("Finished sending"));
}

void ApplicationActivity::readData()
{

	buffer.append(serial->readAll());

	//enq
	if ((buffer[0] == (char)SYN) && (buffer[1] == (char)ENQ))
	{
		bReceivedENQ = true;
		buffer.remove(0, 2);
		sendACK();
	}
	//ack
	if ((buffer[0] == (char)SYN) && (buffer[1] == (char)ACK))
	{
		bReceivedACK = true;
		monitor->incrementAck();
		std::cout << "\n" << buffer[0] << buffer[1] << "\n";
		buffer.remove(0, 2);
	}
	//data
	if ((buffer[0] == (char)SYN) && (buffer[1] == (char)STX))
	{
		//reset bid controls on receiving data frame
		bReceivedENQ = true;
		bReceivedACK = true;
		if (buffer.size() >= 518)
		{
			monitor->incrementRXFrames();
			qDebug() << "FRAME SIZE: " << buffer.count();
			std::cout << "FRAME : " << buffer.toStdString() << "\n";
			//Data
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
			else 
			{
				monitor->incrementErrors();
			}
			toRead.clear();
		}
  	}
}
/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: sendENQ
--
-- DATE: Dec 05, 2017
--
-- REVISIONS: None
--
-- DESIGNER: Tim Bruecker
--
-- PROGRAMMER: Tim Bruecker
--
-- INTERFACE: void sendENQ()
--
-- RETURNS: void
--
-- NOTES:
-- This function frames an ENQ and writes it to the serial port.
----------------------------------------------------------------------------------------------------------------------*/
void ApplicationActivity::sendENQ()
{
	controlFrame enq(QByteArray(1, ENQ));
	// sendData(enq.getFrame());
	serial->write(enq.getFrame());
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: sendACK
--
-- DATE: Dec 05, 2017
--
-- REVISIONS: None
--
-- DESIGNER: Tim Bruecker
--
-- PROGRAMMER: Tim Bruecker
--
-- INTERFACE: void sendACK()
--
-- RETURNS: void
--
-- NOTES:
-- This function frames an ACK and writes it to the serial port.
----------------------------------------------------------------------------------------------------------------------*/
void ApplicationActivity::sendACK()
{
	controlFrame ack(QByteArray(1, ACK));
	sendData(ack.getFrame());
	// serial->write(ack.getFrame());
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: sendRVI
--
-- DATE: Dec 05, 2017
--
-- REVISIONS: None
--
-- DESIGNER: Tim Bruecker
--
-- PROGRAMMER: Tim Bruecker
--
-- INTERFACE: void sendRVI()
--
-- RETURNS: void
--
-- NOTES:
-- This function frames an RVI and writes it to the serial port.
----------------------------------------------------------------------------------------------------------------------*/
void ApplicationActivity::sendRVI()
{
	controlFrame rvi(QByteArray(1, RVI));
	// sendData(rvi.getFrame());
	serial->write(rvi.getFrame());
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: sendData
--
-- DATE: Dec 05, 2017
--
-- REVISIONS: None
--
-- DESIGNER: Tim Bruecker
--
-- PROGRAMMER: Tim Bruecker
--
-- INTERFACE: void sendData(QByteArray toSend)
--
-- RETURNS: void
--
-- NOTES:
-- This writes the QByteArray passed to it to the serial port.
----------------------------------------------------------------------------------------------------------------------*/
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
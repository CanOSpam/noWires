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
	QString comPort = QInputDialog::getText(this, tr("Com picker"),
 		tr("Pick a com port"), QLineEdit::Normal, "COM1", &ok);
 	//serial port not usable until opened
 	serial = new QSerialPort(comPort, this); 
	//connectPort(); //dont call it here
	//TESTING FRAMES DELETE IN RELEASE
	// demo_Frames();
}

ApplicationActivity::~ApplicationActivity()
{
	closePort();
	delete textBox;
}

void ApplicationActivity::demo_Frames()
{
	QByteArray full(512, 0x07);
	QByteArray notFull(300, 0x07);

	dataFrame dataFrameFull(full);
	dataFrame dataFrameNotFull(notFull);

	controlFrame ack(QByteArray(1, ACK));
	controlFrame enq(QByteArray(1, ENQ));

	qDebug() << "dataframe full\n" << dataFrameFull.getFrame() << "\n";
	qDebug() << "size: " << dataFrameFull.getFrame().size() << "\n";
	qDebug() << "dataframe not full\n" << dataFrameNotFull.getFrame() << "\n";
	qDebug() << "size: " << dataFrameNotFull.getFrame().size() << "\n";
	qDebug() << "controlframe ack\n" << ack.getFrame() << "\n";
	qDebug() << "controlframe enq\n" << enq.getFrame() << "\n";
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
	serial->setPortName("COM1");
	serial->setBaudRate(QSerialPort::Baud9600);
	serial->setDataBits(QSerialPort::Data8);
	serial->setParity(QSerialPort::NoParity);
	serial->setStopBits(QSerialPort::OneStop);
	serial->setFlowControl(QSerialPort::NoFlowControl);

	if (!serial->open(QIODevice::ReadWrite))
	{
		qDebug() << serial->errorString();
		// i'd call handleException here but i dont have a ref to the exception variable
		handlePortExceptions(serial->error());//QSerialPort::SerialPortError);
		return;
	}
	else
	{
		qDebug() << serial->isOpen();
		qDebug() << serial->baudRate();
		qDebug() << serial->portName();
		//RX all
		connect(serial, &QSerialPort::readyRead, this, &ApplicationActivity::readData);
	}
}
//ax
int timer()
{
	std::clock_t timer;
	double start = std::clock(); 
	double duration = (std::clock() - start); 
	return duration;
}

//jc 
void ApplicationActivity::fileToSend()
{
	//Start Protocol
	connectPort();
	statusBar()->showMessage(tr("Sending"));
	if (!bidForLine())
	{
		qDebug() << "Bidding failed. Did not receive ACK in time" << "\n";
		closePort();
		return;
	}
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
	QByteArray toReceive = serial->readAll();

	//enq
	if ((toReceive[0] == (char)SYN) && (toReceive[1] == (char)ENQ))
	{
		bReceivedENQ = true;
		controlFrame ack(QByteArray(1, ACK));
		sendData(ack.getFrame());
	}
	//ack
	if ((toReceive[0] == (char)SYN) && (toReceive[1] == (char)ACK))
	{
		bReceivedACK = true;
	}
	//data
  	else if ((toReceive[0] == (char)SYN) & (toReceive[1] == (char)STX))
  	{
  		//check CRC
  		QByteArray data;
  		QByteArray receivedCheckSum;
  
  		for (int i = 0; i < 512; i++)
  		{
  			data[i] = toReceive[i + 2];
  		}
  		for (int i = 514; i < 518; i++)
  		{
  			receivedCheckSum.append(toReceive[i]);
  		}
  
  		quint32 crc = CRC::Calculate(data, 512, CRC::CRC_32());
  
  		QByteArray calculatedByteCheckSum;
  		calculatedByteCheckSum << crc;
  
  		if (calculatedByteCheckSum == receivedCheckSum)
  		{
  			textBox->putData(data);
  		}
  
  
  	}
}

void ApplicationActivity::getControlToSend()
{
	controlFrame enq(QByteArray(1, ENQ));
	sendData(enq.getFrame());
}


void ApplicationActivity::sendData(QByteArray toSend)
{
	if (serial->isOpen())
	{
		serial->write(toSend);
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
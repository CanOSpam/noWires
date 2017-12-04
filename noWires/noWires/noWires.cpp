#include "noWires.h"


noWires::noWires(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	fileOpen = false;

	addButtons();
	serial = new QSerialPort("COM1", this);
	textBox = new TextBox;
	setCentralWidget(textBox);
	textBox->setLocalEchoEnabled(false);

	//connectPort(); //dont call it here
	demo_Frames();
	//TESTING FRAMES DELETE IN RELEASE
	
}
void noWires::demo_Frames()
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

inline void noWires::addButtons()
{
	connect(ui.actionSend, &QAction::triggered, this, &noWires::startSending);
	connect(ui.actionOpen_File, &QAction::triggered, this, &noWires::openAFile);
	ui.actionSend->setEnabled(false);
}

//jc
void noWires::startSending()
{
	//Start Protocol
	connectPort();
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
		std::cout << frame.getFrame().toStdString();
		//serial->write(frame.getFrame());
		receivingFrame(frame.getFrame());
		break;
	}
	inputFile.close();
}

//jc
void noWires::receivingFrame(QByteArray toReceive)
{
	if ((toReceive[0] == (char)SYN) & (toReceive[1] == (char)STX))
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
		
		if (*calculatedByteCheckSum == *receivedCheckSum)
		{
			textBox->putData(data);
		}


	}
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
	if ((data[0] = SYN) && (data[1] = ENQ))
	{
		controlFrame ack(QByteArray(1, ACK));
		serial->write(ack.getFrame());
	}
}

void noWires::getControlToSend()
{
	controlFrame enq(QByteArray(1, ENQ));
	serial->write(enq.getFrame());
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
		// i'd call handleException here but i dont have a ref to the exception variable
		QMessageBox msgBox;
		msgBox.setText("Serial Port did not open successfully");
		msgBox.setInformativeText(serial->errorString());
		msgBox.setDefaultButton(QMessageBox::Ok);
		msgBox.exec();
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

/* Handles unexpected errors QSerialPort might throw.
Does not check for or handle mistakes in data.  */
void noWires::handleException(QSerialPort::SerialPortError e)
{
	if (e == QSerialPort::ResourceError) {
		// same popup as in openPort
		QMessageBox msgBox;
		msgBox.setText("Serial Port did not open successfully");
		msgBox.setInformativeText(serial->errorString());
		msgBox.setDefaultButton(QMessageBox::Ok);
		msgBox.exec();
		closePort();
	}
}

void noWires::closePort()
{
	// this if statment isnt actually needed, Qt handles closing null ports itself
	// but makes logical sense to put here
	if (serial->isOpen())
	{
		serial->close();
	}
}
#include "noWires.h"

noWires::noWires(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	fileOpen = false;

	addButtons();
}

inline void noWires::addButtons()
{
	QToolBar* toolbar = ui.mainToolBar;

	openButton = new QPushButton("Open File", this);
	sendButton = new QPushButton("Send", this);
	sendButton->setEnabled(false);

	connect(sendButton, &QPushButton::pressed, this, &noWires::startSending);
	connect(openButton, &QPushButton::pressed, this, &noWires::openAFile);
	
	toolbar->addWidget(openButton);
	toolbar->addWidget(sendButton);
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

	inputFile.open(fileName.toStdString());

	if (inputFile.is_open())
	{
		fileOpen = true;
		sendButton->setEnabled(true);
		statusBar()->showMessage(tr("Ready to send"));
	}
}
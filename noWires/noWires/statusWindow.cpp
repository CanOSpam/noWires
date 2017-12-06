#include "statusWindow.h"

statusWindow::statusWindow(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::statusWindow)
{
	ui->setupUi(this);

	acks = 0;
	ber = 0;
	TXframes = 0;
	RXframes = 0;
	errors = 0;
}

void statusWindow::incrementAck()
{
	acks++;
	ui->AckNum->setText(QString::number(acks));
}

void statusWindow::incrementRXFrames()
{
	RXframes++;
	ui->FramesRXNum->setText(QString::number(RXframes));
}

void statusWindow::incrementTXFrames()
{
	TXframes++;
	ui->FramesTXNum->setText(QString::number(TXframes));
}

void statusWindow::incrementErrors()
{
	errors++;
	ber = errors / RXframes;
	ui->BERNum->setText(QString::number(ber));
}

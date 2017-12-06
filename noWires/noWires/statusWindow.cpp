#include "statusWindow.h"

statusWindow::statusWindow(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::statusWindow)
{
	ui->setupUi(this);

	acks = 0;
	ber = 0;
	frames = 0;
	errors = 0;
}

void statusWindow::incrementAck()
{
	acks++;
	ui->AckNum->setText(QString::number(acks));
}

void statusWindow::incrementFrame()
{
	frames++;
	ui->FramesNum->setText(QString::number(frames));
}

void statusWindow::incrementErrors()
{
	errors++;
	ber = errors / frames;
	ui->BERNum->setText(QString::number(ber));
}

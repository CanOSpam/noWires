#include "statusWindow.h"
/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: statusWindow.cpp
--
-- PROGRAM: noWires
--
-- FUNCTIONS:
-- void incrementAck()
-- void incrementRXFrames()
-- void incrementTXFrames()
-- void incrementErrors()
--
-- DATE: December 05, 2017
--
-- REVISIONS: None
--
-- DESIGNER: Tim Bruecker
--
-- PROGRAMMER: Tim Bruecker
--
-- NOTES:
-- This is a class that creates a window that tracks metadata related to the transmissions, including frames transmitted
-- and received, Acks received, and the bit error rate.
----------------------------------------------------------------------------------------------------------------------*/

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

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: incrementAck
--
-- DATE: December 05, 2017
--
-- REVISIONS: None
--
-- DESIGNER: Tim Bruecker
--
-- PROGRAMMER: Tim Bruecker
--
-- INTERFACE: void incrementAck()
--
-- RETURNS: void
--
-- NOTES:
-- This function should be called every time an ack is received. It increments the ack count, and renders the ack count
-- in the monitoring window.
----------------------------------------------------------------------------------------------------------------------*/
void statusWindow::incrementAck()
{
	acks++;
	ui->AckNum->setText(QString::number(acks));
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: incrementRXFrames
--
-- DATE: December 05, 2017
--
-- REVISIONS: None
--
-- DESIGNER: Tim Bruecker
--
-- PROGRAMMER: Tim Bruecker
--
-- INTERFACE: void incrementRXFrames()
--
-- RETURNS: void
--
-- NOTES:
-- This function should be called every time a frame is received. It increments the RXFrame count, and renders the 
-- RXFrame count in the monitoring window.
----------------------------------------------------------------------------------------------------------------------*/
void statusWindow::incrementRXFrames()
{
	RXframes++;
	ui->FramesRXNum->setText(QString::number(RXframes));
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: incrementTXFrames
--
-- DATE: December 05, 2017
--
-- REVISIONS: None
--
-- DESIGNER: Tim Bruecker
--
-- PROGRAMMER: Tim Bruecker
--
-- INTERFACE: void incrementTXFrames()
--
-- RETURNS: void
--
-- NOTES:
-- This function should be called every time a frame is transmitted. It increments the TXFrame count, and renders the
-- TXFrame count in the monitoring window.
----------------------------------------------------------------------------------------------------------------------*/
void statusWindow::incrementTXFrames()
{
	TXframes++;
	ui->FramesTXNum->setText(QString::number(TXframes));
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: incrementErrors
--
-- DATE: December 05, 2017
--
-- REVISIONS: None
--
-- DESIGNER: Tim Bruecker
--
-- PROGRAMMER: Tim Bruecker
--
-- INTERFACE: void incrementErrors()
--
-- RETURNS: void
--
-- NOTES:
-- This function should be called every time an error is received. It finds the error rate by divided the errors read
-- by the succesfully read frames. Ideally ber should remain 0.
----------------------------------------------------------------------------------------------------------------------*/
void statusWindow::incrementErrors()
{
	errors++;
	ber = errors / RXframes;
	ui->BERNum->setText(QString::number(ber));
}

#include "controlFrame.h"
/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: controlFrame.cpp - Inherited from frame.cpp
--
-- PROGRAM: noWires
--
-- FUNCTIONS:
-- QByteArray getframe()
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
-- This is the data class for control frames. Its purpose is to make framing control frames easier. It is essentially
-- a wrapper around a QByteArray with convience functions.
----------------------------------------------------------------------------------------------------------------------*/
controlFrame::controlFrame(QByteArray data)
	: frame(data)
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getFrame
--
-- DATE: MDecember 05, 2017
--
-- REVISIONS: None
--
-- DESIGNER: Tim Bruecker
--
-- PROGRAMMER: Tim Bruecker
--
-- INTERFACE: QByteArray getFrame()
--
-- RETURNS: A QByteArray that is the entire control frame.
--
-- NOTES:
-- This function takes the mData that is a control character, and adds it and a SYN character to a QByteArray, then
-- returns that QByteArray which is now a fully framed control frame.
----------------------------------------------------------------------------------------------------------------------*/
QByteArray controlFrame::getFrame()
{
	//Make a frame and return it
	QByteArray frame;
	frame.append(SYN);
	frame.append(mData);
	return frame;
}

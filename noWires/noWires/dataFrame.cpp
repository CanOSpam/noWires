#include "dataFrame.h"

/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: dataFrame.cpp - Inherited from frame.cpp
--
-- PROGRAM: noWires
--
-- FUNCTIONS:
-- QByteArray getframe()
-- QByteArray getCRC()
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
-- This is the data class for data frames. It offers two methods, one to create a frame so it can be sent over the QSerialPort,
-- and one to create the CRC from the data passed into the class.
----------------------------------------------------------------------------------------------------------------------*/
dataFrame::dataFrame(QByteArray data)
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
-- RETURNS: A QByteArray that is the entire data frame.
--
-- NOTES:
-- This function takes the mData that is an array of characters, then adds the data, a SYN character, a STX character,
-- and the CRC to a QByteArray. This packages everything together and returns a QByteArray that is ready to be sent as
-- a packet.
----------------------------------------------------------------------------------------------------------------------*/
QByteArray dataFrame::getFrame()
{
	//Make a frame and return it
	QByteArray frame;
	frame.append(SYN);
	frame.append(STX);

	if (mData.size() < 512)
	{
		frame.append(mData);
		frame.append(QByteArray(512 - mData.size(), 0x00));
		mStuffedData.clear();
		mStuffedData.append(mData);
		mStuffedData.append(QByteArray(512 - mData.size(), 0x00));
	}
	else
	{
		frame.append(mData);
		mStuffedData.append(mData);
	}

	frame.append(getCRC());
	
	return frame;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getCRC
--
-- DATE: MDecember 05, 2017
--
-- REVISIONS: None
--
-- DESIGNER: Tim Bruecker
--
-- PROGRAMMER: Tim Bruecker
--
-- INTERFACE: QByteArray getCRC()
--
-- RETURNS: A QByteArray that contains the CRC.
--
-- NOTES:
-- This function takes the mData and uses the CRC++ library to generate a 32 bit CRC. It then uses the uint operators
-- written by Matteo Italia to split that 32 bit uint into a 4 Byte QByteArray.
----------------------------------------------------------------------------------------------------------------------*/
QByteArray dataFrame::getCRC()
{
	QByteArray byteCheckSum;

	quint32 crc = CRC::Calculate(mStuffedData, 512, CRC::CRC_32());

	byteCheckSum << crc;

	return byteCheckSum;
}

#include "dataFrame.h"

dataFrame::dataFrame(QByteArray data)
	: frame(data)
{
}

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
	}
	else
	{
		frame.append(mData);
	}

	frame.append(getCRC(frame));
	
	return frame;
}

QByteArray dataFrame::getCRC(QByteArray data)
{
	QByteArray byteCheckSum;

	quint16 checkSum = qChecksum(data, 514);
	byteCheckSum << checkSum;

	return byteCheckSum;
}

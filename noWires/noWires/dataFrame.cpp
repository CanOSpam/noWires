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

QByteArray dataFrame::getCRC()
{
	QByteArray byteCheckSum;

	quint16 checkSum = qChecksum(mStuffedData, 512);
	byteCheckSum << checkSum;

	return byteCheckSum;
}

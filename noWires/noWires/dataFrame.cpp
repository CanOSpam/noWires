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
		frame.append(QByteArray(512 - mData.size(), 0));
	}
	else
	{
		frame.append(mData);
	}

	frame.append(getCRC());
	
	return frame;
}

QByteArray dataFrame::getCRC()
{
	QByteArray byteCheckSum;

	quint16 checkSum = qChecksum(mData, mData.size());
	byteCheckSum << checkSum;
	return byteCheckSum;
}

// From https://stackoverflow.com/questions/30660127/append-quint16-unsigned-short-to-qbytearray-quickly
// Designed and implemented by Matteo Italia https://stackoverflow.com/users/214671/matteo-italia
QByteArray &operator<<(QByteArray& l, quint8 r)
{
	l.append(r);
	return l;
}

// From https://stackoverflow.com/questions/30660127/append-quint16-unsigned-short-to-qbytearray-quickly
// Designed and implemented by Matteo Italia https://stackoverflow.com/users/214671/matteo-italia
QByteArray &operator<<(QByteArray& l, quint16 r)
{
	return l << quint8(r >> 8) << quint8(r);
}

// From https://stackoverflow.com/questions/30660127/append-quint16-unsigned-short-to-qbytearray-quickly
// Designed and implemented by Matteo Italia https://stackoverflow.com/users/214671/matteo-italia
QByteArray &operator<<(QByteArray &l, quint32 r)
{
	return l << quint16(r >> 16) << quint16(r);
}
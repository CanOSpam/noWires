#include "controlFrame.h"

controlFrame::controlFrame(QByteArray data)
	: frame(data)
{
}

QByteArray controlFrame::getFrame()
{
	//Make a frame and return it
	QByteArray frame;
	frame.append(SYN);
	frame.append(mData);
	return frame;
}

#pragma once
#include <QByteArray>


#define SYN 0x16
#define STX 0x02


class frame
{
public:
	virtual QByteArray getFrame() = 0;
	frame(QByteArray data);

protected:
	QByteArray mData;

};
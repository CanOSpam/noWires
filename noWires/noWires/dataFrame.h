#pragma once
#include "frame.h"


class dataFrame : public frame
{
public:
	dataFrame(QByteArray data);
	QByteArray getFrame() override;
	QByteArray getCRC();
};
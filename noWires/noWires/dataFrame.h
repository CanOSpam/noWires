#pragma once
#include "frame.h"
#include "uintOperators.h"


class dataFrame : public frame
{
public:
	dataFrame(QByteArray data);
	QByteArray getFrame() override;
	QByteArray getCRC(QByteArray data);
};
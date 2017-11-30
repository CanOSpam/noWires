#pragma once
#include "frame.h"

class controlFrame : public frame
{
public:
	controlFrame(QByteArray data);
	QByteArray getFrame() override;
};
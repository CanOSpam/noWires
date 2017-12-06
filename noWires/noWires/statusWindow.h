#pragma once

#include <QWidget>

#include "ui_statusWindow.h"

class statusWindow : public QWidget
{
	Q_OBJECT

public:
	explicit statusWindow(QWidget *parent = 0);
	void incrementAck();
	void incrementRXFrames();
	void incrementTXFrames();
	void incrementErrors();

private:
	Ui::statusWindow *ui;
	int acks;
	int TXframes;
	int RXframes;
	int ber;
	int errors;
};
#pragma once

#include <QWidget>

#include "ui_statusWindow.h"

class statusWindow : public QWidget
{
	Q_OBJECT

public:
	explicit statusWindow(QWidget *parent = 0);
	void incrementAck();
	void incrementFrame();
	void incrementErrors();

private:
	Ui::statusWindow *ui;
	int acks;
	int frames;
	int ber;
	int errors;
};
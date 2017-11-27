#pragma once

#include <QtWidgets/QMainWindow>
#include <QStatusBar>
#include "ui_noWires.h"


class noWires : public QMainWindow
{
	Q_OBJECT

public:
	noWires(QWidget *parent = Q_NULLPTR);

private:
	Ui::noWiresClass ui;
};

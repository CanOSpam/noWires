#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushbutton>
#include <QFiledialog>
#include <QDesktopservices>
#include <QDebug>

#include <iostream>
#include <fstream> 

#include "ui_noWires.h"

class noWires : public QMainWindow
{
	Q_OBJECT

public:
	noWires(QWidget *parent = Q_NULLPTR);

private:

	QString fileName;
	std::ifstream inputFile;
	bool fileOpen;

	Ui::noWiresClass ui;
	inline void addButtons();
	void startSending();
	void openAFile();
};


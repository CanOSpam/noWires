#include "noWires.h"

noWires::noWires(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	statusBar()->showMessage(tr("Ready"), 2000);
}

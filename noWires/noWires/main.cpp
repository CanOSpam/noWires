#include "noWires.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	noWires w;
	w.show();
	return a.exec();
}

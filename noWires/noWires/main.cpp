#include "ApplicationActivity.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ApplicationActivity aa;
	aa.show();
	return a.exec();
}

#include "qtnetworkclient.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtNetworkClient w;
	w.show();
	return a.exec();
}

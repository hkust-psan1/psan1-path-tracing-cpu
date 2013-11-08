#include "mainwindow.h"

#ifdef __APPLE__
	#include <QApplication>
#else
	#include <QtWidgets/QApplication>
#endif

int main(int argc, char *argv[])
{
    srand(time(0));
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}

#include "OpenGLES20QT.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	OpenGLES20QT w;
	w.show();
	return a.exec();
}

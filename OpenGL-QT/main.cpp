#include "OpenGLQT.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	OpenGLQT w;
	w.show();
	return a.exec();
}

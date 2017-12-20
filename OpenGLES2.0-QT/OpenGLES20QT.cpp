#include "OpenGLES20QT.h"

OpenGLES20QT::OpenGLES20QT(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	_GLESContent.Begin((HWND)winId());

	connect(&_timer, SIGNAL(timeout()), this, SLOT(Render()));
	_timer.start(16);
}

OpenGLES20QT::~OpenGLES20QT()
{
	_GLESContent.End();
}

void OpenGLES20QT::Render()
{
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	_GLESContent.SwapBuffer();
}
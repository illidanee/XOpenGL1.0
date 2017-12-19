#include "OpenGLQT.h"

OpenGLQT::OpenGLQT(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	_GLContent.Begin((HWND)winId());

	connect(&_Timer, SIGNAL(timeout()), this, SLOT(Render()));
	_Timer.start(33.33f);
}

OpenGLQT::~OpenGLQT()
{
	_Timer.stop();

	_GLContent.End();
}

void OpenGLQT::Render()
{
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	_GLContent.SwapBuffer();
}
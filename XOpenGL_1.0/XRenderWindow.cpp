#include "XRenderWindow.h"

namespace Smile
{
	void XRenderWindow::Begin()
	{

	}

	void XRenderWindow::Render()
	{
		//Çå¿Õ
		glClearColor(0.15f, 0.25f, 0.35f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void XRenderWindow::End()
	{
	}
}


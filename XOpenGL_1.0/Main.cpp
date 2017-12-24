#include <tchar.h>
#include <windows.h>


#include "XResource.h"
#include "XGLWindow.h"


using namespace Smile;

#define M_PI 3.14159265358979323846

struct Vertex
{
	float x, y, z;
	float u, v;
};

class LogWindow : public XGLWindow
{
	void Begin()
	{

	}
	void Render()
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void End()
	{

	}
};

Vertex vertices[] = {
	{ -1, -1, 1, 0, 0 },
	{ +1, -1, 1, 1, 0 },
	{ -1, +1, 1, 0, 1 },
	{ +1, +1, 1, 1, 1 },
};

class MainWindow : public XGLWindow
{
	GLuint _texture;

	void Begin()
	{
		char* pBuffer;
		int w;
		int h;
		int res = XResource::LoadTextureFile("../Resources/1.jpg", &pBuffer, &w, &h);
		if (res)
		{
			glEnable(GL_TEXTURE_2D);
			glGenBuffers(1, &_texture);
			glBindTexture(GL_TEXTURE_2D, _texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, pBuffer);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
	void Render()
	{
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//glOrtho(0, _w, 0, _h, -100, 100);
		gluPerspective(60.0f, (float)_w / _h, 0.01f, 1000.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -3.0f);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &vertices[0].x);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &vertices[0].u);

		glBindTexture(GL_TEXTURE_2D, _texture);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	}
	void End()
	{

	}
};

int __stdcall WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//注册窗口信息。
	XGLWindow::RegisterInstance(hInstance);
	XGLWindow::RegisterWndClass(_T("illidan"));

	//创建窗口
	XGLWindow* pWindow1 = XGLWindow::Create<LogWindow>(_T("illidan"), _T("LogWindow"), 100, 200, 300, 600);
	XGLWindow* pWindow2 = XGLWindow::Create<MainWindow>(_T("illidan"), _T("MainWindow"), 450, 200, 800, 600);

	XGLWindow::Update();

	//销毁窗口信息
	XGLWindow::ClearWndClass();
	XGLWindow::ClearInstance();

	return 0;
}
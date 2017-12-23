#include <tchar.h>
#include <windows.h>

#include "XGLWindow.h"

using namespace Smile;

#define M_PI 3.14159265358979323846

struct float3
{
	float x, y, z;
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

class MainWindow : public XGLWindow
{
	float _cx;
	float _cy;
	float _cz;
	float _R;
	float3* _vertices;

	void Begin()
	{
		_cx = 400;
		_cy = 300;
		_cz = 0;
		_R = 200;
		_vertices = new float3[362];

		_vertices[0].x = _cx;
		_vertices[0].y = _cy;
		_vertices[0].z = _cz;

		for (int i = 0; i <= 360; ++i)
		{
			_vertices[i + 1].x = _cx + (float)cos(i * M_PI / 180.0f) * _R;
			_vertices[i + 1].y = _cy + (float)sin(i * M_PI / 180.0f) * _R;
			_vertices[i + 1].z = _cz;
		}
	}
	void Render()
	{
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, _w, 0, _h, -100, 100);

		glPointSize(10);
		glColor3f(1, 1, 1);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(float3), _vertices);
		glDrawArrays(GL_POINTS, 0, 362);

		
		//glBegin(GL_POINT);
		//glVertex2f(400, 300);
		//glEnd();
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
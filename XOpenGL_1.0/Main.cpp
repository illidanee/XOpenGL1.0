#include <tchar.h>
#include <windows.h>

#include "XGLWindow.h"

using namespace Smile;

class LogWindow : public XGLWindow
{
	void Event(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_DESTROY:
		{
			this->_die = true;
		}
			break;
		}
	}
	void Begin()
	{

	}
	void Render()
	{
		glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void End()
	{

	}
};

class MainWindow : public XGLWindow
{
	void Event(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_DESTROY:
		{
			this->_die = true;
		}
		break;
		}
	}
	void Begin()
	{

	}
	void Render()
	{
		glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
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
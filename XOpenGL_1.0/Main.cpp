#include <tchar.h>
#include <windows.h>

#include "XGLWindow.h"

using namespace Smile;

class IGLWindow : public XGLWindow
{
	virtual void Render()
	{
		_content.MakeCurrent();
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		_content.SwapBuffer();
	}
};

int __stdcall WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//注册窗口信息。
	XGLWindow::RegisterInstance(hInstance);
	XGLWindow::RegisterWndClass(_T("illidan"));

	//创建窗口
	XGLWindow* pWindow1 = XGLWindow::Create<IGLWindow>(_T("illidan"), _T("illidan1"), 800, 600);
	XGLWindow* pWindow2 = XGLWindow::Create<IGLWindow>(_T("illidan"), _T("illidan2"), 800, 600);

	XGLWindow::Update();

	delete pWindow1;
	delete pWindow2;

	//销毁窗口信息
	XGLWindow::ClearWndClass();
	XGLWindow::ClearInstance();

	return 0;
}
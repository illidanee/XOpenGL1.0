#include <tchar.h>
#include <windows.h>

#include "XGLWindow.h"

int __stdcall WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{

	Smile::XGLWindow::RegisterInstance(hInstance);
	Smile::XGLWindow::RegisterWndClass(_T("illidan"));

	Smile::XGLWindow* pWindow = Smile::XGLWindow::CreateXGLWindow<Smile::XGLWindow>(_T("illidan"), _T("illidan"), 800, 600);
	pWindow->Update();
	pWindow->Destroy();

	return 0;
}
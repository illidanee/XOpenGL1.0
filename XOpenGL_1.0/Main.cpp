#include <tchar.h>
#include <windows.h>

#include "XGLWindow.h"

int __stdcall WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{

	Smile::XGLWindow::RegisterWndClass(hInstance);

	Smile::XGLWindow mainWindow;
	mainWindow.Create();
	mainWindow.Update();
	mainWindow.Destroy();
	
	return 0;
}
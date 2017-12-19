#include <tchar.h>
#include <windows.h>

#include "XGLESContent.h"

/****************************************************************************************************************
 *    Date    : 2017/12/19 16:13
 *
 *    Author  : Smile
 *    Contact : smile@illidan.org
 *
 *    Brief   : 设置窗口为全屏
 *
 ****************************************************************************************************************/
void ChangleToFullScreen(int w, int h)
{
	DEVMODE dmSettings = {0};
	if (!EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dmSettings))
		return;

	dmSettings.dmPelsWidth = w;
	dmSettings.dmPelsHeight = h;
	dmSettings.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

	int res = ChangeDisplaySettings(&dmSettings, CDS_FULLSCREEN);
	if (res != DISP_CHANGE_SUCCESSFUL)
		PostQuitMessage(0);
}

LRESULT CALLBACK WindowProc(
	_In_ HWND   hwnd,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;		
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int __stdcall WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	WNDCLASSEX wc;
	memset(&wc, 0, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = 0;
	wc.hCursor = 0;
	wc.hIcon = 0;
	wc.hIconSm = 0;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = _T("illidan");
	wc.lpszMenuName = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;

	RegisterClassEx(&wc);

	int screenW = GetSystemMetrics(SM_CXSCREEN);
	int screenH = GetSystemMetrics(SM_CYSCREEN);

	/*
		使用全屏窗口时:
			1 - 创建窗口风格需要为：WS_POPUP | WS_VISIBLE。
			2 - 创建窗口大小需要显示设置，不能为CW_USEDEFAULT。
	*/
	HWND hWnd = CreateWindowEx(0, _T("illidan"), _T("Window"), WS_POPUP | WS_VISIBLE, 0, 0, screenW, screenH, 0, 0, hInstance, 0);
	
	ChangleToFullScreen(screenW, screenH);
	
	UpdateWindow(hWnd);
	ShowWindow(hWnd, SW_SHOW);
	
	Smile::XGLESContent _glesContent;
	_glesContent.Begin(hWnd);

	MSG msg = { 0 };

	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		{
			glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			_glesContent.SwapBuffer();
			Sleep(1);
		}
	}

	_glesContent.End();

	return 0;
}
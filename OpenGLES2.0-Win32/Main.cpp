#include <tchar.h>
#include <windows.h>

#include "XGLESContent.h"

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

	HWND hWnd = CreateWindowEx(0, _T("illidan"), _T("Window"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, hInstance, 0);
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
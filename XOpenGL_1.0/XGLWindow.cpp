#include "XGLWindow.h"

namespace Smile
{
	HINSTANCE XGLWindow::_hInstance = 0;

	XGLWindow::XGLWindow()
	{

	}

	XGLWindow::~XGLWindow()
	{

	}

	void XGLWindow::Create()
	{
		_hWnd = CreateWindowEx(0, _T("illidan"), _T("Window"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, _hInstance, 0);
		UpdateWindow(_hWnd);
		ShowWindow(_hWnd, SW_SHOW);

		_glContent.Begin(_hWnd);
	}

	void XGLWindow::Update()
	{
		MSG msg = { 0 };

		while (WM_QUIT != msg.message)
		{
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			{
				Render();
				_glContent.SwapBuffer();
				Sleep(1);
			}
		}
	}

	void XGLWindow::Render()
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void XGLWindow::Destroy()
	{
		_glContent.End();
	}

	void XGLWindow::RegisterWndClass(HINSTANCE hInstance)
	{
		_hInstance = hInstance;

		WNDCLASSEX wc;
		memset(&wc, 0, sizeof(wc));
		wc.cbSize = sizeof(wc);
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hbrBackground = 0;
		wc.hCursor = 0;
		wc.hIcon = 0;
		wc.hIconSm = 0;
		wc.hInstance = _hInstance;
		wc.lpfnWndProc = WindowProc;
		wc.lpszClassName = _T("illidan");
		wc.lpszMenuName = 0;
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;

		RegisterClassEx(&wc);
	}

	LRESULT CALLBACK XGLWindow::WindowProc(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

}
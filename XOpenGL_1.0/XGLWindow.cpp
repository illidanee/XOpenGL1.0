#include "XGLWindow.h"

namespace Smile
{
	std::map<LPCTSTR, WNDCLASSEX*> XGLWindow::_WCCache;
	HINSTANCE XGLWindow::_hInstance = 0;

	void XGLWindow::RegisterInstance(HINSTANCE hInstance)
	{
		_hInstance = hInstance;
	}

	void XGLWindow::RegisterWndClass(LPCTSTR wcName)
	{
		if (_WCCache.find(wcName) != _WCCache.end())
			return;

		WNDCLASSEX* pWC = new WNDCLASSEX;

		memset(pWC, 0, sizeof(WNDCLASSEX));
		pWC->cbSize = sizeof(WNDCLASSEX);
		pWC->cbClsExtra = 0;
		pWC->cbWndExtra = 0;
		pWC->hbrBackground = 0;
		pWC->hCursor = 0;
		pWC->hIcon = 0;
		pWC->hIconSm = 0;
		pWC->hInstance = _hInstance;
		pWC->lpfnWndProc = WindowProc;
		pWC->lpszClassName = wcName;
		pWC->lpszMenuName = 0;
		pWC->style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;

		RegisterClassEx(pWC);

		_WCCache.insert(std::pair<LPCTSTR, WNDCLASSEX*>(wcName, pWC));
	}

	XGLWindow::XGLWindow()
	{

	}

	XGLWindow::~XGLWindow()
	{

	}

	void XGLWindow::Create(LPCTSTR wcName, LPCTSTR wName, int w, int h)
	{
		//计算窗口大小和位置
		int screenW = GetSystemMetrics(SM_CXSCREEN);
		int screenH = GetSystemMetrics(SM_CYSCREEN);

		RECT rect
		{
			(screenW - w) / 2,
			(screenH - h) / 2,
			rect.left + w,
			rect.top + h
		};

		_hWnd = CreateWindowEx(0, wcName, wName, WS_OVERLAPPEDWINDOW, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, _hInstance, 0);
		UpdateWindow(_hWnd);
		ShowWindow(_hWnd, SW_SHOW);

		_content.Begin(_hWnd);
	}

	void XGLWindow::Register()
	{
		if (_WindowCache.find(_hWnd) != _WindowCache.end())
			return;

		_WindowCache.insert(std::pair<HWND, XGLWindow*>(_hWnd, this));
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
				
				Sleep(1);
			}
		}
	}

	void XGLWindow::Render()
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		_content.SwapBuffer();
	}

	void XGLWindow::Destroy()
	{
		_content.End();
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
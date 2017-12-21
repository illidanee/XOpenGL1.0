#include "XGLWindow.h"

namespace Smile
{
/*
	静态区
*/
	std::map<LPCTSTR, WNDCLASSEX*> XGLWindow::_WCCache;
	std::map<HWND, XGLWindow*> XGLWindow::_WindowCache;
	HINSTANCE XGLWindow::_hInstance = 0;
	CRITICAL_SECTION XGLWindow::_CS;

	void XGLWindow::RegisterInstance(HINSTANCE hInstance)
	{
		_hInstance = hInstance;
	}

	void XGLWindow::ClearInstance()
	{
		_hInstance = 0;
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

	void XGLWindow::ClearWndClass()
	{
		for (std::map<LPCTSTR, WNDCLASSEX*>::iterator it = _WCCache.begin(); it != _WCCache.end(); ++it)
		{
			UnregisterClass(it->first, _hInstance);
			delete it->second;
		}

		_WCCache.clear();
	}

	void XGLWindow::Update()
	{
		InitializeCriticalSection(&_CS);

		for (std::map<HWND, XGLWindow*>::iterator it = _WindowCache.begin(); it != _WindowCache.end(); ++it)
		{
			EnterCriticalSection(&_CS);

			it->second->Begin();
			UpdateWindow(it->first);
			ShowWindow(it->first, SW_SHOW);

			LeaveCriticalSection(&_CS);
		}

		MSG msg = { 0 };
		while (WM_QUIT != msg.message)
		{
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			{
				for (std::map<HWND, XGLWindow*>::iterator it = _WindowCache.begin(); it != _WindowCache.end(); ++it)
				{
					EnterCriticalSection(&_CS);

					it->second->Render();

					LeaveCriticalSection(&_CS);
				}
				
				Sleep(16);
			}
		}
		
		for (std::map<HWND, XGLWindow*>::iterator it = _WindowCache.begin(); it != _WindowCache.end(); ++it)
		{
			EnterCriticalSection(&_CS);

			it->second->End();

			LeaveCriticalSection(&_CS);
		}

		DeleteCriticalSection(&_CS);
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


/*
	成员区
*/
	XGLWindow::~XGLWindow()
	{

	}

	XGLWindow::XGLWindow()
	{

	}

	XGLWindow::XGLWindow(const XGLWindow& that)
	{

	}

	XGLWindow XGLWindow::operator = (const XGLWindow& that)
	{
		return *this;
	}

	void XGLWindow::Construct(LPCTSTR wcName, LPCTSTR wName, int w, int h)
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
	}

	void XGLWindow::Register()
	{
		if (_WindowCache.find(_hWnd) != _WindowCache.end())
			return;

		_WindowCache.insert(std::pair<HWND, XGLWindow*>(_hWnd, this));
	}

	void XGLWindow::Begin()
	{
		_content.Begin(_hWnd);
	}

	void XGLWindow::Render()
	{
		_content.MakeCurrent();
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		_content.SwapBuffer();
	}

	void XGLWindow::End()
	{
		_content.End();
	}
}
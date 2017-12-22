#include "XGLWindow.h"

namespace Smile
{
/*
	��̬��
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

			it->second->BeginInner();
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
			else
			{
				//����
				for (std::map<HWND, XGLWindow*>::iterator it = _WindowCache.begin(); it != _WindowCache.end(); ++it)
				{
					EnterCriticalSection(&_CS);

					it->second->RenderInner();

					LeaveCriticalSection(&_CS);
				}
				
				//������������
				for (std::map<HWND, XGLWindow*>::iterator it = _WindowCache.begin(); it != _WindowCache.end(); )
				{
					if (it->second->_die)
					{
						//DestroyWindow()�������� WM_DESTROY ��Ϣ�����յ�����ϢҲ��˵��������DestroyWindow()������
						//DestroyWindow(it->first);
						//����˴���delete,����Ҫ������ɾ������������Ҫ����������������
						delete it->second;
						it = _WindowCache.erase(it);
					}
					else
					{
						++it;
					}
				}

				//�ж��˳�
				if (_WindowCache.size() == 0)
					PostQuitMessage(0);

				Sleep(16);
			}
		}
		
		for (std::map<HWND, XGLWindow*>::iterator it = _WindowCache.begin(); it != _WindowCache.end(); ++it)
		{
			EnterCriticalSection(&_CS);

			it->second->EndInner();

			LeaveCriticalSection(&_CS);
		}

		DeleteCriticalSection(&_CS);
	}

	LRESULT CALLBACK XGLWindow::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (uMsg == WM_CREATE)
		{
			LPCREATESTRUCT pData = (LPCREATESTRUCT)lParam;
			if (pData)
			{
				XGLWindow* pWindow = (XGLWindow*)pData->lpCreateParams;
				if (pWindow)
				{
					SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pWindow);
				}
			}
		}
		else
		{
			XGLWindow* pThis = (XGLWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			if (pThis)
			{
				//���������¼�����
				pThis->Event(hWnd, uMsg, wParam, lParam);

				if (uMsg == WM_DESTROY)
				{
					pThis->_die = true;
				}
			}
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}


/*
	��Ա��
*/
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

	XGLWindow::~XGLWindow()
	{

	}

	void XGLWindow::Construct(LPCTSTR wcName, LPCTSTR wName, int x, int y, int w, int h)
	{
		//���㴰�ڴ�С��λ��
		int screenW = GetSystemMetrics(SM_CXSCREEN);
		int screenH = GetSystemMetrics(SM_CYSCREEN);

		RECT rect
		{
			(screenW - w) / 2,
			(screenH - h) / 2,
			rect.left + w,
			rect.top + h
		};

		AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, 0);

		if ( x == 0 && y == 0)
			_hWnd = CreateWindowEx(0, wcName, wName, WS_OVERLAPPEDWINDOW, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, 0, this);
		else
			_hWnd = CreateWindowEx(0, wcName, wName, WS_OVERLAPPEDWINDOW, x, y, rect.right - rect.left, rect.bottom - rect.top, 0, 0, 0, this);

		_w = w;
		_h = h;

		_die = false;
	}

	void XGLWindow::Register()
	{
		if (_WindowCache.find(_hWnd) != _WindowCache.end())
			return;

		_WindowCache.insert(std::pair<HWND, XGLWindow*>(_hWnd, this));
	}

	void XGLWindow::BeginInner()
	{
		_content.Begin(_hWnd);

		Begin();
	}

	void XGLWindow::RenderInner()
	{
		_content.MakeCurrent();
		Render();
		_content.SwapBuffer();
	}

	void XGLWindow::EndInner()
	{
		End();
		_content.End();
	}

	void XGLWindow::Event(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{

	}

	void XGLWindow::Begin()
	{
		
	}

	void XGLWindow::Render()
	{	
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void XGLWindow::End()
	{
		
	}
}
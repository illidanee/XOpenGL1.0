#pragma once

#include <map>

#include <tchar.h>
#include <windows.h>

#include "XGLContent.h"

namespace Smile
{
	class XGLWindow
	{

/*
	静态区
*/
	protected:
		static std::map<LPCTSTR, WNDCLASSEX*> _WCCache;

		static HINSTANCE _hInstance;

	public:
		static void RegisterInstance(HINSTANCE hInstance);
		static void RegisterWndClass(LPCTSTR wcName);

		template<typename T>
		static T* CreateXGLWindow(LPCTSTR wcName, LPCTSTR wName, int w, int h)
		{
			T* pWindow = new T;
			pWindow->Create(wcName, wName, w, h);
			pWindow->Register();
			return pWindow;
		}
/*
	成员区
*/
	protected:
		std::map<HWND, XGLWindow*> _WindowCache;

		HWND _hWnd;
		XGLContent _content;

	public:
		XGLWindow();
		virtual ~XGLWindow();

		void Create(LPCTSTR wcName, LPCTSTR wName, int w, int h);
		void Register();
		void Update();
		void Destroy();

	protected:
		virtual void Render();

	protected:
		static LRESULT CALLBACK WindowProc(
			_In_ HWND   hwnd,
			_In_ UINT   uMsg,
			_In_ WPARAM wParam,
			_In_ LPARAM lParam
		);
	};
}
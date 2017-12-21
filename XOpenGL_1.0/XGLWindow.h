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
		static std::map<HWND, XGLWindow*> _WindowCache;

		static HINSTANCE _hInstance;

		static CRITICAL_SECTION _CS;

	public:
		static void RegisterInstance(HINSTANCE hInstance);
		static void ClearInstance();

		static void RegisterWndClass(LPCTSTR wcName);
		static void ClearWndClass();
		
		template<typename T>
		static T* Create(LPCTSTR wcName, LPCTSTR wName, int w, int h)
		{
			T* pWindow = new T;
			pWindow->Construct(wcName, wName, w, h);
			pWindow->Register();
			return pWindow;
		}
		static void Update();

	protected:
		static LRESULT CALLBACK WindowProc(
			_In_ HWND   hwnd,
			_In_ UINT   uMsg,
			_In_ WPARAM wParam,
			_In_ LPARAM lParam
		);

	
/*
	成员区
*/
	protected:
		HWND _hWnd;
		XGLContent _content;

	public:
		virtual ~XGLWindow();

	protected:
		XGLWindow();
		XGLWindow(const XGLWindow& that);
		XGLWindow operator= (const XGLWindow& that);

		void Construct(LPCTSTR wcName, LPCTSTR wName, int w, int h);
		void Register();

		virtual void Begin();
		virtual void Render();
		virtual void End();
	};
}
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
	��̬��
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
		static T* Create(LPCTSTR wcName, LPCTSTR wName, int x, int y, int w, int h)
		{
			T* pWindow = new T;
			pWindow->Construct(wcName, wName, x, y, w, h);
			pWindow->Register();
			return pWindow;
		}
		static void Update();

	protected:
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	
/*
	��Ա��
*/
	protected:
		HWND _hWnd;
		XGLContent _content;

		bool _die;

	protected:
		XGLWindow();
		XGLWindow(const XGLWindow& that);
		XGLWindow operator= (const XGLWindow& that);
		~XGLWindow();

		void Construct(LPCTSTR wcName, LPCTSTR wName, int x, int y, int w, int h);
		void Register();

		void BeginInner();
		void RenderInner();
		void EndInner();

	protected:
		virtual void Event(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		virtual void Begin();
		virtual void Render();
		virtual void End();
	};
}
#pragma once

#include <tchar.h>
#include <windows.h>

#include "XGLContent.h"

namespace Smile
{
	class XGLWindow
	{
	public:
		XGLWindow();
		virtual ~XGLWindow();

		void Create();
		void Update();
		void Destroy();
	
	protected:
		virtual void Render();

	public:
		static void RegisterWndClass(HINSTANCE hInstance);

	protected:
		static LRESULT CALLBACK WindowProc(
			_In_ HWND   hwnd,
			_In_ UINT   uMsg,
			_In_ WPARAM wParam,
			_In_ LPARAM lParam
		);

	protected:
		static HINSTANCE _hInstance;
		HWND _hWnd;
		Smile::XGLContent _glContent;
	};
}
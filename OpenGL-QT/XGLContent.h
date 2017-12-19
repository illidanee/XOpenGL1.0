#pragma once

#include <tchar.h>
#include <windows.h>
#include <gl/GL.h>

namespace Smile
{
	class XGLContent
	{
	public:
		XGLContent();

		void Begin(HWND hWnd);
		void SwapBuffer();
		void End();

	private:
		HWND _hWnd;
		HDC _hDC;
		HGLRC _hGLRC;
	};
}
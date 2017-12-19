#pragma once

#include <tchar.h>
#include <windows.h>
#include "gles2/gl2.h"
#include "gles2/egl.h"

namespace Smile
{
	class XGLESContent
	{
	public:
		XGLESContent();

		void Begin(HWND hWnd);
		void SwapBuffer();
		void End();

	private:
		HWND _hWnd;
		
		EGLDisplay _display;
		EGLSurface _surface;
		EGLContext _context;

		EGLint _width;
		EGLint _height;
	};
}
#pragma once

#include <tchar.h>
#include <windows.h>
#include <gl/glew.h>
#include <gl/wglew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

namespace Smile
{
	class XGLContent
	{
	public:
		XGLContent();

		void Construct(HWND hWnd);
		void ConstructMSAA(HWND hWnd);
		void Begin();
		void MakeCurrent();
		void SwapBuffer();
		void End();

	private:
		int GetMultiSamplePixelFormat();

	private:
		HWND _hWnd;
		HDC _hDC;
		HGLRC _hGLRC;
	};
}
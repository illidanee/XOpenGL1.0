#pragma once

#include <gl/glew.h>
#include <gl/wglew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

namespace Smile
{
	class XGLPBuffer
	{
	public:
		XGLPBuffer();
		~XGLPBuffer();

		void Init(HWND hWnd, HDC hDC, HGLRC hGLRC, int w, int h);
		void Destroy();
		void MakeCurrent();

	private:
		HWND _hParentWnd;
		HDC _hParentDC;
		HGLRC _hParentGLRC;

		HDC _hDC;
		HPBUFFERARB _hPBuffer;
		HGLRC _hGLRC;
		int _w;
		int _h;

	public:
		int GetW() { return _w; }
		int GetH() { return _h; }
	};
}
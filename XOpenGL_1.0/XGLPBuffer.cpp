#include "XGLPBuffer.h"

namespace Smile
{
	XGLPBuffer::XGLPBuffer()
	{
		_hParentWnd = 0;
		_hParentDC = 0;
		_hParentGLRC = 0;

		_hDC = 0;
		_hPBuffer = 0;
		_hGLRC = 0;
		_w = 0;
		_h = 0;
	}

	XGLPBuffer::~XGLPBuffer()
	{

	}

	void XGLPBuffer::Init(HWND hWnd, HDC hDC, HGLRC hGLRC, int w, int h)
	{
		_hParentWnd = hWnd;
		_hParentDC = hDC;
		_hParentGLRC = hGLRC;
		_w = w;
		_h = h;

		int attribs[] = 
		{
			WGL_SUPPORT_OPENGL_ARB, TRUE,       // P-buffer will be used with OpenGL
			WGL_DRAW_TO_PBUFFER_ARB, TRUE,      // Enable render to p-buffer
			WGL_RED_BITS_ARB, 8,                // At least 8 bits for RED channel
			WGL_GREEN_BITS_ARB, 8,              // At least 8 bits for GREEN channel
			WGL_BLUE_BITS_ARB, 8,               // At least 8 bits for BLUE channel
			WGL_ALPHA_BITS_ARB, 8,              // At least 8 bits for ALPHA channel
			WGL_DEPTH_BITS_ARB, 16,             // At least 16 bits for depth buffer
			WGL_DOUBLE_BUFFER_ARB, FALSE,       // We don't require double buffering
			0                                   // Zero terminates the list
		};

		int iFormatID;
		UINT iFormatNum;
		wglChoosePixelFormatARB(_hParentDC, attribs, NULL, 1, &iFormatID, &iFormatNum);
		if (iFormatNum == 0)
			return;

		_hPBuffer = wglCreatePbufferARB(_hParentDC, iFormatID, _w, _h, NULL);
		_hDC = wglGetPbufferDCARB(_hPBuffer);
		_hGLRC = wglCreateContext(_hDC);

		wglShareLists(_hParentGLRC, _hGLRC);

		MakeCurrent();
	}

	void XGLPBuffer::Destroy()
	{
		wglMakeCurrent(0, 0);
		wglDeleteContext(_hGLRC);
		_hGLRC = 0;
		wglReleasePbufferDCARB(_hPBuffer, _hDC);
		wglDestroyPbufferARB(_hPBuffer);
		_hPBuffer = 0;
		ReleaseDC(_hParentWnd, _hDC);
		_hDC = 0;
	}

	void XGLPBuffer::MakeCurrent()
	{
		wglMakeCurrent(_hDC, _hGLRC);
	}
}
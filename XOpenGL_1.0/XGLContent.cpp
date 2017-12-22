#include "XGLContent.h"

namespace Smile
{
	XGLContent::XGLContent()
	{
		_hWnd = 0;
		_hDC = 0;
		_hGLRC = 0;
	}

	void XGLContent::Begin(HWND hWnd)
	{
		//��ʼ��OpenGL����
		_hWnd = hWnd;
		_hDC = GetDC(_hWnd);

		PIXELFORMATDESCRIPTOR pfd;
		memset(&pfd, 0, sizeof(pfd));
		pfd.nSize = sizeof(pfd);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;
		pfd.iLayerType = PFD_MAIN_PLANE;

		int iPixelFormat = ChoosePixelFormat(_hDC, &pfd);
		SetPixelFormat(_hDC, iPixelFormat, &pfd);

		_hGLRC = wglCreateContext(_hDC);

		//���õ�ǰ
		MakeCurrent();

		//��ʼ��OpenGL��չ����  -- ע��������MakeCurrent()����ܳ�ʼ���ɹ���
		GLenum err = glewInit();

		//���ô�ֱͬ�� -- ע����Ҫͷ�ļ�<gl/wglew.h>
		wglSwapIntervalEXT(1);
	}

	void XGLContent::MakeCurrent()
	{
		//���õ�ǰ
		wglMakeCurrent(_hDC, _hGLRC);
	}

	void XGLContent::SwapBuffer()
	{
		SwapBuffers(_hDC);
	}

	void XGLContent::End()
	{
		wglMakeCurrent(0, 0);
		wglDeleteContext(_hGLRC);
		_hGLRC = 0;
		ReleaseDC(_hWnd, _hDC);
		_hDC = 0;
		_hWnd = 0;
	}
}
#include "XGLesContent.h"

namespace Smile
{
	XGLESContent::XGLESContent()
	{
		_hWnd = 0;
		
		_display = EGL_NO_DISPLAY;
		_context = EGL_NO_CONTEXT;
		_surface = EGL_NO_SURFACE;

		_width = 0;
		_height = 0;
	}

	void XGLESContent::Begin(HWND hWnd)
	{
		_hWnd = hWnd;

		//获取Display
		_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

		//初始化Display
		EGLint major;
		EGLint minor;
		eglInitialize(_display, &major, &minor);

		//选择Config
		EGLConfig config;
		const EGLint attribs[] = 
		{
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_RED_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_BLUE_SIZE, 8,
			EGL_ALPHA_SIZE, 8,
			EGL_DEPTH_SIZE, 24,
			EGL_NONE
		};
		EGLint	numConfigs = 0;
		eglChooseConfig(_display, attribs, &config, 1, &numConfigs);
		//EGLint format = 0;
		//eglGetConfigAttrib(_display, _config, EGL_NATIVE_VISUAL_ID, &format);

		//创建Surface
		_surface = eglCreateWindowSurface(_display, config, _hWnd, NULL);

		//创建Context
		EGLint attr[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
		_context = eglCreateContext(_display, config, EGL_NO_CONTEXT, attr);

		//设置
		eglMakeCurrent(_display, _surface, _surface, _context);

		//获取Surface的属性
		eglQuerySurface(_display, _surface, EGL_WIDTH, &_width);
		eglQuerySurface(_display, _surface, EGL_HEIGHT, &_height);
	}

	void XGLESContent::SwapBuffer()
	{
		eglSwapBuffers(_display, _surface);
	}

	void XGLESContent::End()
	{
		eglMakeCurrent(_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		eglDestroyContext(_display, _context);
		eglDestroySurface(_display, _surface);
		eglTerminate(_display);

		_hWnd = 0;

		_display = EGL_NO_DISPLAY;
		_context = EGL_NO_CONTEXT;
		_surface = EGL_NO_SURFACE;

		_width = 0;
		_height = 0;
	}
}
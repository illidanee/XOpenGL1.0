#pragma once

#include <gl/glew.h>
#include <gl/wglew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

namespace Smile
{
	class XGLFrameBufferObject
	{
	public:
		XGLFrameBufferObject();
		~XGLFrameBufferObject();

		void Init(int w, int h);
		void Destroy();
		void Begin(GLuint texture);
		void End();

	private:
		int _w;
		int _h;

		GLuint _FBO;
		GLuint _RBO;
	};
}
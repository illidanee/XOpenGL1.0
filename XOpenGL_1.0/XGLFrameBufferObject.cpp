#include "XGLFrameBufferObject.h"

namespace Smile
{
	XGLFrameBufferObject::XGLFrameBufferObject()
	{

	}

	XGLFrameBufferObject::~XGLFrameBufferObject()
	{

	}

	void XGLFrameBufferObject::Init(int w, int h)
	{
		_w = w;
		_h = h;

		glGenFramebuffers(1, &_FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, _FBO);

		glGenRenderbuffers(1, &_RBO);
		glBindRenderbuffer(GL_RENDERBUFFER, _RBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, _w, _h);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _RBO);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void XGLFrameBufferObject::Destroy()
	{
		glDeleteRenderbuffers(1, &_RBO);
		glDeleteFramebuffers(1, &_FBO);
		_RBO = 0;
		_FBO = 0;
	}

	void XGLFrameBufferObject::Begin(GLuint texture)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _FBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
	}
	void XGLFrameBufferObject::End()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}
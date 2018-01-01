#include "XRenderWindow.h"

#include "XGLFrameBufferObject.h"

namespace Smile
{
	struct Vertex
	{
		float x, y, z;
		float u, v;
	};

	Vertex g_cubeVertices[] =
	{
		{ 200,150,0.0f,	0.0f,0.0f},
		{ 600,150,0.0f, 1.0f,0.0f},
		{ 600,450,0.0f, 1.0f,1.0f},
		{ 200,450,0.0f,	0.0f,1.0f}
	};

	GLuint _texture;
	GLuint _dynamic;

	XGLFrameBufferObject _fbo;

	void DrawOnCPU(GLuint texture)
	{
		//模型矩阵
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glBindTexture(GL_TEXTURE_2D, texture);

		//绑定数据
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &g_cubeVertices[0].x);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &g_cubeVertices[0].u);

		//绘制
		glDrawArrays(GL_QUADS, 0, 4);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Smile::XRenderWindow::Begin()
	{
		char* pBuffer;
		int w, h;

		glEnable(GL_TEXTURE_2D);
		XResource::LoadTextureFile("../Resources/1.jpg", &pBuffer, &w, &h);
		{
			glGenTextures(1, &_texture);
			glBindTexture(GL_TEXTURE_2D, _texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pBuffer);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		glEnable(GL_TEXTURE_2D);
		{
			glGenTextures(1, &_dynamic);
			glBindTexture(GL_TEXTURE_2D, _dynamic);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _w, _h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		_fbo.Init(_w, _h);
	}

	void Smile::XRenderWindow::Render()
	{
		_fbo.Begin(_dynamic);

		//清空
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//正交投影绘制平面
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, _w, 0, _h, -100, 100);

		DrawOnCPU(_texture);

		//保存图片
		char* pBuffer = new char[_w * _h * 4];
		memset(pBuffer, 0, _w * _h * 4);
		glReadPixels(0, 0, _w, _h, GL_RGBA, GL_UNSIGNED_BYTE, pBuffer);
		XResource::SaveTextureFile("D:/abc.png", pBuffer, _w, _h);

		_fbo.End();

		//清空
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//正交投影绘制平面
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, _w, 0, _h, -100, 100);

		DrawOnCPU(_dynamic);

		//保存图片
		char* pBuffer = new char[_w * _h * 4];
		memset(pBuffer, 0, _w * _h * 4);
		glReadPixels(0, 0, _w, _h, GL_RGBA, GL_UNSIGNED_BYTE, pBuffer);
		XResource::SaveTextureFile("D:/abc.png", pBuffer, _w, _h);
	}

	void Smile::XRenderWindow::End()
	{
		glDeleteTextures(1, &_texture);
		glDeleteTextures(1, &_dynamic);

		_fbo.Destroy();
	}
}


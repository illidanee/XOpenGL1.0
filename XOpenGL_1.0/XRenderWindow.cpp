#include "XRenderWindow.h"

#include "XGLPBuffer.h"

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

	XGLPBuffer _pBuffer;

	GLuint _dynamic;

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

		_pBuffer.Init(_hWnd, _content.GetHDC(), _content.GetHGLRC(), _w, _h);
		_pBuffer.MakeCurrent();

		glEnable(GL_TEXTURE_2D);
		{
			glGenTextures(1, &_dynamic);
			glBindTexture(GL_TEXTURE_2D, _dynamic);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _w, _h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	void Smile::XRenderWindow::Render()
	{
		_pBuffer.MakeCurrent();

		//清空
		glEnable(GL_DEPTH_TEST);
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//正交投影绘制平面
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, _w, 0, _h, -100, 100);

		DrawOnCPU(_texture);

		//------------------------------------------离屏渲染------------------------------------------
		glBindTexture(GL_TEXTURE_2D, _dynamic);
		glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, _pBuffer.GetW(), _pBuffer.GetH());
		glBindTexture(GL_TEXTURE_2D, 0);

		_content.MakeCurrent();
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//正交投影绘制平面
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, _w, 0, _h, -100, 100);

		DrawOnCPU(_dynamic);
	}

	void Smile::XRenderWindow::End()
	{
		_pBuffer.MakeCurrent();
		glDeleteTextures(1, &_texture);

		//--BUG - 1282
		//		此处调用会有1282错误产生。
		//_pBuffer.Destroy();
	}
}


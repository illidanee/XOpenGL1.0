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

	GLuint _pbo[2];
	int _DMA;
	int _Write;
	
	void RandomBuffer(char* pData, int w, int h)
	{
		for (unsigned int i = 0; i < w * h * 4; ++i)
		{
			pData[i] = rand();
		}
	}

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

		glGenBuffers(2, _pbo);

		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, _pbo[0]);
		glBufferData(GL_PIXEL_UNPACK_BUFFER, _w * _h * 4, 0, GL_STREAM_READ);

		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, _pbo[1]);
		glBufferData(GL_PIXEL_UNPACK_BUFFER, _w * _h * 4, 0, GL_STREAM_READ);

		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

		_DMA = 0;
		_Write = 1;
	}

	void Smile::XRenderWindow::Render()
	{
		//清空
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//正交投影绘制平面
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, _w, 0, _h, -100, 100);

		//保存图片
		glBindTexture(GL_TEXTURE_2D, _dynamic);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, _pbo[_DMA]);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _w, _h, GL_RGBA, GL_UNSIGNED_BYTE, 0);

		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, _pbo[_Write]);
		void* pData = glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_READ_ONLY);
		if (pData)
		{
			RandomBuffer((char*)pData, _w, _h);
		}
		glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
		std::swap(_DMA, _Write);

		DrawOnCPU(_dynamic);
	}

	void Smile::XRenderWindow::End()
	{
		glDeleteTextures(1, &_texture);
		glDeleteTextures(1, &_dynamic);
	}
}


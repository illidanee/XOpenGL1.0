#include "XRenderWindow.h"

namespace Smile
{
	struct Vertex
	{
		float x, y, z;
		float u, v;
	};

	const float size = 20.0f;

	Vertex g_PlaneVertices[] =
	{
		{ -size / 2.0f,  0.0f,  size / 2.0f,     0.0f,  0.0f },
		{ -size / 2.0f,  0.0f, -size / 2.0f,     0.0f,  size },
		{  size / 2.0f,  0.0f,  size / 2.0f,     size,  0.0f },
		{  size / 2.0f,  0.0f, -size / 2.0f,     size,  size },
	};

	Vertex g_CubeVertices[] =
	{
		{ -1.0f,-1.0f, 1.0f,	0,  0 },
		{  1.0f,-1.0f, 1.0f,	1,  0 },
		{  1.0f, 1.0f, 1.0f,	1,  1 },
		{ -1.0f, 1.0f, 1.0f,	0,  1 },

		{ -1.0f,-1.0f,-1.0f,	0,  0 },
		{ -1.0f, 1.0f,-1.0f,	1,  0 },
		{  1.0f, 1.0f,-1.0f,	1,  1 },
		{  1.0f,-1.0f,-1.0f,	0,  1 },

		{ -1.0f, 1.0f,-1.0f,	0,  0 },
		{ -1.0f, 1.0f, 1.0f,	1,  0 },
		{  1.0f, 1.0f, 1.0f,	1,  1 },
		{  1.0f, 1.0f,-1.0f,	0,  1 },

		{ -1.0f,-1.0f,-1.0f,	0,  0 },
		{  1.0f,-1.0f,-1.0f,	1,  0 },
		{  1.0f,-1.0f, 1.0f,	1,  1 },
		{ -1.0f,-1.0f, 1.0f,	0,  1 },

		{  1.0f,-1.0f,-1.0f,	0,  0 },
		{  1.0f, 1.0f,-1.0f,	1,  0 },
		{  1.0f, 1.0f, 1.0f,	1,  1 },
		{  1.0f,-1.0f, 1.0f,	0,  1 },

		{ -1.0f,-1.0f,-1.0f,	0,  0 },
		{ -1.0f,-1.0f, 1.0f,	1,  0 },
		{ -1.0f, 1.0f, 1.0f,	1,  1 },
		{ -1.0f, 1.0f,-1.0f,	0,  1 },
	};

	GLuint _texture1;
	GLuint _texture2;

	void DrawPlane(GLuint texture)
	{
		glBindTexture(GL_TEXTURE_2D, texture);

		//绑定数据
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &g_PlaneVertices[0].x);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &g_PlaneVertices[0].u);

		//绘制
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void DrawCube(GLuint texture)
	{
		glBindTexture(GL_TEXTURE_2D, texture);

		//绑定数据
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &g_CubeVertices[0].x);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &g_CubeVertices[0].u);

		//绘制
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 24);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Smile::XRenderWindow::Begin()
	{
		char* pBuffer;
		int w, h;

		glEnable(GL_TEXTURE_2D);
		XResource::LoadTextureFile("../Resources/grass.png", &pBuffer, &w, &h);
		{
			glGenTextures(1, &_texture1);
			glBindTexture(GL_TEXTURE_2D, _texture1);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pBuffer);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		XResource::LoadTextureFile("../Resources/1.jpg", &pBuffer, &w, &h);
		{
			glGenTextures(1, &_texture2);
			glBindTexture(GL_TEXTURE_2D, _texture2);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pBuffer);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	void Smile::XRenderWindow::Render()
	{
		//清空
		glClearColor(0.16f, 0.26f, 0.36f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//正交投影绘制平面
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60.0f, (float)_w / _h, 0.01f, 1000.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0.0f, 10.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

		DrawPlane(_texture1);

		glTranslatef(0.0f, 2.0f, 0.0f);
		DrawCube(_texture2);
	}

	void Smile::XRenderWindow::End()
	{
		glDeleteTextures(1, &_texture1);
	}
}


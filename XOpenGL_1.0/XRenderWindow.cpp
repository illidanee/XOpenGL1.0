#include "XRenderWindow.h"

namespace Smile
{
	int _col = 9;
	int _imageW = 108;
	int _imageH = 108;

	//全局数据
	struct Vertex
	{
		float x, y, z;
		float u, v;
	};

	char* pBuffer;
	int w;
	int h;

	GLuint _texture1;

	void Smile::XRenderWindow::Begin()
	{
		int res = 0;

		//读取纹理数据
		res = XResource::LoadTextureFile("../Resources/xx.png", &pBuffer, &w, &h);
		if (res)
		{
			glEnable(GL_TEXTURE_2D);
			glGenTextures(1, &_texture1);
			glBindTexture(GL_TEXTURE_2D, _texture1);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pBuffer);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	void Smile::XRenderWindow::Render()
	{
		//变量
		static float tm = 0;

		tm += 0.5;
		if (tm >= 64)
		{
			tm = 0;
		}

		//清空
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//设置投影矩阵
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//glOrtho(0, _w, 0, _h, -100, 100);
		gluPerspective(60.0f, (float)_w / _h, 0.01f, 1000.0f);

		//设置模型矩阵
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -3.0f);

		//绑定纹理
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _texture1);

		//绑定顶点
		int frame = (int)tm;

		int     col = frame % _col;
		int     row = frame / _col;

		float u = (float)(_imageW * col) / w;
		float v = (float)(_imageW * row) / h;

		++col;
		++row;

		float u1 = (float)(_imageW * col) / w;
		float v1 = (float)(_imageW * row) / h;

		Vertex vertices[] = {
			{ -1, -1, 0,  u, v },
			{ +1, -1, 0,  u1, v },
			{ -1, +1, 0,  u, v1 },
			{ +1, +1, 0,  u1, v1 },
		};

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &vertices[0].x);

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &vertices[0].u);
		
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

	void Smile::XRenderWindow::End()
	{
		delete[] pBuffer;
		glDeleteTextures(1, &_texture1);
	}
}


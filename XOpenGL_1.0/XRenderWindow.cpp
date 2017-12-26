#include "XRenderWindow.h"

#include "XVideo.h"

namespace Smile
{
	//全局数据
	struct Vertex
	{
		float x, y, z;
		float u, v;
	};

	XVideo _Video;

	GLuint _texture1;

	

	void Smile::XRenderWindow::Begin()
	{
		XVideo::Init();
		_Video.LoadVideoFile("../Resources/1.avi");

		//读取纹理数据
		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &_texture1);
		glBindTexture(GL_TEXTURE_2D, _texture1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _Video.GetW(), _Video.GetH(), 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
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
		glTranslatef(0.0f, 0.0f, -2.0f);

		//绑定纹理
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _texture1);

		void*   data = _Video.ReadFrame();
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _Video.GetW(), _Video.GetH(), GL_RGB, GL_UNSIGNED_BYTE, data);

		Vertex vertices[] = {
			{ -1, -1, 0,  0, 1 },
			{ +1, -1, 0,  1, 1 },
			{ -1, +1, 0,  0, 0 },
			{ +1, +1, 0,  1, 0 },
		};

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &vertices[0].x);

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &vertices[0].u);
		
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

	void Smile::XRenderWindow::End()
	{
		glDeleteTextures(1, &_texture1);
	}
}


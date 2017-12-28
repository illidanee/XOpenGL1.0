#include "XRenderWindow.h"

namespace Smile
{
	struct Vertex
	{
		float _x, _y, _z;
		float _u, _v;
	};

	GLuint _texture0;
	GLuint _texture1;
	GLuint _texture2;

	//透视投影绘制3D
	void Render3D(int w, int h)
	{
		//启用深度测试
		glEnable(GL_DEPTH_TEST);

		//设置投影矩阵
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60.0f, (float)w / h, 0.01f, 1000.0f);

		//设置模型矩阵
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -5.0f);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glBindTexture(GL_TEXTURE_2D, _texture0);

		glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2f(0.0f, 16.0f);	glVertex3f(-16, -1, -16);
			glTexCoord2f(0.0f, 0.0f);	glVertex3f(-10, -1, 16);
			glTexCoord2f(16.0f, 16.0f);	glVertex3f(16, -1, -16);
			glTexCoord2f(16.0f, 0.0f);	glVertex3f(16, -1, 16);
		glEnd();
	}

	//正交投影绘制2D
	void Render2D(int w, int h)
	{
		//关闭深度测试
		glDisable(GL_DEPTH_TEST);

		//正交投影绘制平面
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, w, 0, h, -100, 100);

		//***
		//		纹理坐标错误可能会造成画片不正确。常见的现象是混合后画面出现对角斜线，并在对角斜线两侧表现相反的显示结果。
		//***
		Vertex  vert[] =
		{
			{ 0,			0,			20,		0.0f, 0.0f },
			{ 0,			(float)h,	20,		0.0f, 1.0f },
			{ (float)w,		0,			20,		1.0f, 0.0f },
			{ (float)w,		(float)h,	20,		1.0f, 1.0f },
		};

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &vert[0]._x);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &vert[0]._u);

		glEnable(GL_BLEND);

		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, _texture1);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glBlendFunc(GL_ONE, GL_ONE);
		glBindTexture(GL_TEXTURE_2D, _texture2);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glDisable(GL_BLEND);
	}

	void Smile::XRenderWindow::Begin()
	{
		char* pBuffer;
		int w, h;

		{
			XResource::LoadTextureFile("../Resources/floor.bmp", &pBuffer, &w, &h);

			//读取纹理数据
			glEnable(GL_TEXTURE_2D);
			glGenTextures(1, &_texture0);
			glBindTexture(GL_TEXTURE_2D, _texture0);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, pBuffer);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		{
			XResource::LoadTextureFile("../Resources/CrossHairMask.bmp", &pBuffer, &w, &h);

			//读取纹理数据
			glEnable(GL_TEXTURE_2D);
			glGenTextures(1, &_texture1);
			glBindTexture(GL_TEXTURE_2D, _texture1);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, pBuffer);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		{
			XResource::LoadTextureFile("../Resources/CrossHair.bmp", &pBuffer, &w, &h);

			//读取纹理数据
			glEnable(GL_TEXTURE_2D);
			glGenTextures(1, &_texture2);
			glBindTexture(GL_TEXTURE_2D, _texture2);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, pBuffer);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

	}

	void Smile::XRenderWindow::Render()
	{
		//清空
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Render3D(_w, _h);
		Render2D(_w, _h);
	}

	void Smile::XRenderWindow::End()
	{
		glDeleteTextures(1, &_texture0);
		glDeleteTextures(1, &_texture1);
		glDeleteTextures(1, &_texture2);
	}
}


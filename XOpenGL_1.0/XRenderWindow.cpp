#include "XRenderWindow.h"

namespace Smile
{
	//全局数据
	struct Vertex
	{
		float x, y, z;
		float u1, v1;
		float u2, v2;
	};

	Vertex vertices[] = {
		{ -1, -1, 1,  0, 0,  0, 0 },
		{ +1, -1, 1,  1, 0,  1, 0 },
		{ -1, +1, 1,  0, 1,  0, 1 },
		{ +1, +1, 1,  1, 1,  1, 1 },
	};

	char* pBuffer;
	int w;
	int h;

	GLuint _texture1;

	GLUquadricObj *quadratic;

	void Smile::XRenderWindow::Begin()
	{
		int res = 0;

		//读取纹理数据
		res = XResource::LoadTextureFile("../Resources/BG.bmp", &pBuffer, &w, &h);
		if (res)
		{
			glEnable(GL_TEXTURE_2D);
			glGenTextures(1, &_texture1);
			glBindTexture(GL_TEXTURE_2D, _texture1);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, pBuffer);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		quadratic = gluNewQuadric();
		gluQuadricDrawStyle(quadratic, GLU_FILL);
		gluQuadricOrientation(quadratic, GLU_OUTSIDE);
		gluQuadricNormals(quadratic, GLU_SMOOTH);
		gluQuadricTexture(quadratic, GL_TRUE);

		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	}

	void Smile::XRenderWindow::Render()
	{
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

		gluSphere(quadratic, 1.3f, 32, 32);
	}

	void Smile::XRenderWindow::End()
	{
		//释放会报错。
		//delete[] pBuffer;
		glDeleteTextures(1, &_texture1);
	}
}


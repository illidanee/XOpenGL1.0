#include "XRenderWindow.h"

namespace Smile
{
	struct Vertex
	{
		float x, y, z;
		float u, v;
	};

	Vertex vertices[] = {
		{ -1, -1, 1, 0, 0 },
		{ +1, -1, 1, 1, 0 },
		{ -1, +1, 1, 0, 1 },
		{ +1, +1, 1, 1, 1 },
	};

	char* pBuffer;
	int w;
	int h;

	void Smile::XRenderWindow::Begin()
	{
		int res = XResource::LoadTextureFile("../Resources/1.jpg", &pBuffer, &w, &h);
		if (res)
		{
			glEnable(GL_TEXTURE_2D);
			glGenTextures(1, &_texture);
			glBindTexture(GL_TEXTURE_2D, _texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, pBuffer);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	void Smile::XRenderWindow::Render()
	{
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//glOrtho(0, _w, 0, _h, -100, 100);
		gluPerspective(60.0f, (float)_w / _h, 0.01f, 1000.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -3.0f);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &vertices[0].x);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &vertices[0].u);

		glBindTexture(GL_TEXTURE_2D, _texture);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

	void Smile::XRenderWindow::End()
	{
		// Õ∑≈ª·±®¥Ì°£
		//delete[] pBuffer;
		glDeleteTextures(1, &_texture);
	}
}


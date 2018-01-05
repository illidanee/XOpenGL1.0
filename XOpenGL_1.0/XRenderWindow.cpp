#include "XRenderWindow.h"

#include "XCamera3rd.h"


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
		{ -1.0f, 1.0f, 1.0f,	0,  1 },
		{  1.0f,-1.0f, 1.0f,	1,  0 },
		{  1.0f, 1.0f, 1.0f,	1,  1 },

		{  1.0f,-1.0f,-1.0f,	0,  0 },
		{  1.0f, 1.0f,-1.0f,	0,  1 },
		{ -1.0f,-1.0f,-1.0f,	1,  0 },
		{ -1.0f, 1.0f,-1.0f,	1,  1 },

		{ -1.0f, 1.0f, 1.0f,	0,  0 },
		{ -1.0f, 1.0f,-1.0f,	0,  1 },
		{  1.0f, 1.0f, 1.0f,	1,  0 },
		{  1.0f, 1.0f,-1.0f,	1,  1 },

		{ -1.0f,-1.0f,-1.0f,	0,  0 },
		{ -1.0f,-1.0f, 1.0f,	0,  1 },
		{  1.0f,-1.0f,-1.0f,	1,  0 },
		{  1.0f,-1.0f, 1.0f,	1,  1 },
		
		{  1.0f,-1.0f, 1.0f,	0,  0 },
		{  1.0f, 1.0f, 1.0f,	0,  1 },
		{  1.0f,-1.0f, -1.0f,	1,  0 },
		{  1.0f, 1.0f, -1.0f,	1,  1 },

		{ -1.0f,-1.0f, 1.0f,	0,  0 },
		{ -1.0f, 1.0f, 1.0f,	0,  1 },
		{ -1.0f,-1.0f, -1.0f,	1,  0 },
		{ -1.0f, 1.0f, -1.0f,	1,  1 },

	};

	GLuint _texture1;
	GLuint _texture2;

	XCamera3rd _camera;
	XVec3f _rolePos;

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

	void XRenderWindow::Event(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_RBUTTONDOWN:
		{
			_x = GET_X_LPARAM(lParam);
			_y = GET_Y_LPARAM(lParam);
			_RButtonDown = true;
		}
		break;
		case WM_RBUTTONUP:
		{
			_RButtonDown = false;
		}
		break;
		case WM_MOUSEMOVE:
		{
			if (_RButtonDown)
			{
				int x = GET_X_LPARAM(lParam);
				int y = GET_Y_LPARAM(lParam);
				int offsetX = x - _x;
				int offsetY = y - _y;
				_camera.OnRotateX(offsetY * 0.1f);
				_camera.OnRotateY(-offsetX * 0.1f);
				_x = x;
				_y = y;
			}
		}
		break;
		case WM_MOUSEWHEEL:
		{
			short zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
			if (zDelta > 0)
				_camera.OnScaleLength(1.2f);
			else
				_camera.OnScaleLength(0.8f);
		}
		break;
		case WM_CHAR:
		{
			switch (wParam)
			{
			case 'W':
			{
				//_camera.OnFront();
				_rolePos._x += 1.0f;
			}
			break;
			case 'S':
			{
				//_camera.OnBack();
				_rolePos._x -= 1.0f;
			}
			break;
			case 'A':
			{
				//_camera.OnLeft();
				_rolePos._z -= 1.0f;
			}
			break;
			case 'D':
			{
				//_camera.OnRight();
				_rolePos._z += 1.0f;
			}
			break;
			}
		}
		break;
		}
	}

	void XRenderWindow::Begin()
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

		_camera.Init(XVec3f(0.0f, 10.0f, 10.0f), XVec3f(0.0f, 0.0f, 0.0f),XVec3f(0.0f, 1.0f, 0.0f));
		_rolePos._x = 0;
		_rolePos._y = 2.0f;
		_rolePos._z = 0;
		_camera.LookAt(_rolePos);

		_RButtonDown = false;
		_x = 0;
		_y = 0;


	}

	void XRenderWindow::Render()
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
		_camera.LookAt(_rolePos);
		_camera.Update();

		glPushMatrix();
		glTranslatef(_rolePos._x, _rolePos._y, _rolePos._z);
		DrawCube(_texture2);
		glPopMatrix();

		DrawPlane(_texture1);
	}

	void XRenderWindow::End()
	{
		glDeleteTextures(1, &_texture1);
		glDeleteTextures(1, &_texture2);
	}
}


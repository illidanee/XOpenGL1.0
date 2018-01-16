#include "XRenderWindow.h"

#include "XCamera3rd.h"
#include "XFrustum.h"

#include "XFront.h"
#include "XUIObject.h"

namespace Smile
{
	struct Vertex
	{
		float x, y, z;
		float u, v;
	};

	const float size = 100.0f;

	Vertex g_PlaneVertices[] =
	{
		{ -size,  0.0f,  size,     0.0f,  0.0f },
		{ -size,  0.0f, -size,     0.0f,  size },
		{  size,  0.0f,  size,     size,  0.0f },
		{  size,  0.0f, -size,     size,  size },
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
	XFrustumf _frustum;


	/****************************************************************************************************************
	 *
	 *    Brief   : 抽象可绘制对象。
	 *
	 ****************************************************************************************************************/
	class XRenderable
	{
		GLuint _Texture;
		Vertex* _Vertices;
		int _Len;

	public:
		void Init(GLuint texture, Vertex* vertices, int len)
		{
			_Texture = texture;
			_Vertices = vertices;
			_Len = len;
		}

		void Render()
		{
			glBindTexture(GL_TEXTURE_2D, _Texture);

			//绑定数据
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &_Vertices[0].x);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &_Vertices[0].u);

			//绘制
			glDrawArrays(GL_TRIANGLE_STRIP, 0, _Len);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);

			glBindTexture(GL_TEXTURE_2D, 0);
		}
	};

	/****************************************************************************************************************
	 *
	 *    Brief   : 抽象节点对象。
	 *
	 ****************************************************************************************************************/
	class XNode
	{
	public:
		XVec3f _pos;
		XRenderable* _pRenderable;

		void Render()
		{
			if (_pRenderable)
			{
				glPushMatrix();

				glTranslatef(_pos._x, _pos._y, _pos._z);

				_pRenderable->Render();

				glPopMatrix();
			}
		}
	};

	/****************************************************************************************************************
	 *
	 *    Brief   : 定义绘制对象和节点
	 *
	 ****************************************************************************************************************/
	XRenderable g_Plane;
	XRenderable g_Cube;
	const int g_Size = 100;
	XNode* g_pPlane;
	XNode* g_pNodes;

	/****************************************************************************************************************
	 *
	 *    Brief   : UI
	 *
	 ****************************************************************************************************************/
	
	wchar_t* pText = L"你好   Hello gg!";
	XFront* pFront;
	XUIText* pUIText;

	/****************************************************************************************************************
	 *
	 *    Brief   : 类
	 *
	 ****************************************************************************************************************/
	void XRenderWindow::Event(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_SIZE:
		{
			if (::IsWindow(hWnd))
			{
				RECT rect;
				GetClientRect(_hWnd, &rect);
				int w = rect.right - rect.left;
				int h = rect.bottom - rect.top;
				glViewport(0, 0, w, h);
				_camera.SetViewport(w, h);
			}
		}
		break;
		case WM_LBUTTONDOWN:
		{
			//int xPos = GET_X_LPARAM(lParam);
			//int yPos = GET_Y_LPARAM(lParam);
			//XVec2f screen(xPos, _h - yPos);
			//XRayf ray = _camera.CreateRayFromScreen(screen);
			//XVec3f origin = ray.GetOrigin();
			//float time = origin._y / ray.GetDir()._y;
			//XVec3f aim = origin + ray.GetDir() * abs(time);
			//_rolePos = aim;

			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);
			POINT screen = { xPos, _h - yPos };

			XRectf rect1 = pUIText->GetRect();
			RECT rect2 = { rect1._x, rect1._y, rect1._x + rect1._w, rect1._y + rect1._h };

			if (PtInRect(&rect2, screen))
			{
				_lx = GET_X_LPARAM(lParam);
				_ly = _h - GET_Y_LPARAM(lParam);
				_LButtonDown = true;
			}
		}
		break;
		case WM_LBUTTONUP:
		{
			_LButtonDown = false;
		}
		break;
		case WM_RBUTTONDOWN:
		{
			_rx = GET_X_LPARAM(lParam);
			_ry = GET_Y_LPARAM(lParam);
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
			if (_LButtonDown)
			{
				int x = GET_X_LPARAM(lParam);
				int y = _h - GET_Y_LPARAM(lParam);
				int offsetX = x - _lx;
				int offsetY = y - _ly;

				_lx = x;
				_ly = y;

				XVec3f pos = pUIText->GetPos();
				pos._x += offsetX;
				pos._y += offsetY;
				pUIText->SetPos(pos);
			}

			if (_RButtonDown)
			{
				int x = GET_X_LPARAM(lParam);
				int y = GET_Y_LPARAM(lParam);
				int offsetX = x - _rx;
				int offsetY = y - _ry;
				
				_camera.OnRotateX(offsetY * 0.1f);
				_camera.OnRotateY(offsetX * 0.1f);
				
				_rx = x;
				_ry = y;
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

		_camera.Init(XVec3f(-10.0f, 10.0f, 10.0f), XVec3f(0.0f, 0.0f, 0.0f),XVec3f(0.0f, 1.0f, 0.0f));
		_rolePos._x = 0.0f;
		_rolePos._y = 0.0f;
		_rolePos._z = 0.0f;

		_LButtonDown = false;
		_lx = 0;
		_ly = 0;

		_RButtonDown = false;
		_rx = 0;
		_ry = 0;

		g_Plane.Init(_texture1, g_PlaneVertices, 4);
		g_Cube.Init(_texture2, g_CubeVertices, 24);
		
		g_pPlane = new XNode;
		g_pPlane->_pos = XVec3f(0.0f, 0.0f, 0.0f);
		g_pPlane->_pRenderable = &g_Plane;

		g_pNodes = new XNode[g_Size];
		for (int i = 0; i < g_Size; ++i)
		{
			g_pNodes[i]._pos._x = rand() % 200 - 100;
			g_pNodes[i]._pos._y = rand() % 20;
			g_pNodes[i]._pos._z = rand() % 200 - 100;
			g_pNodes[i]._pRenderable = &g_Cube;
		}


		/****************************************************************************************************************
		*
		*    Brief   : UI
		*
		****************************************************************************************************************/

		pFront = new XFront();
		pFront->Init("../Resources/simsun.ttc", 1024, 1024, 32);
		pUIText = new XUIText();
		XRectf rect = pFront->GetSize(100.0f, 100.0f, 0.0f, pText);
		pUIText->Init(XVec3f(100.0f, 100.0f, 0.0f), rect, BGRA8U(255, 255, 0, 255), pText);


		//XLog::AddString(L"初始化成功！");
	}

	void XRenderWindow::Render()
	{
		//清空
		glClearColor(0.16f, 0.26f, 0.36f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		_camera.SetViewport(_w, _h);
		_camera.LookAtAim(_rolePos);
		_camera.View();
		_camera.Proj(60.0f, (float)_w / _h, 0.01f, 1000.0f);

		XMat4f _mat = _camera.GetMatPV();
		glLoadMatrixf(_mat.GetData());

		_frustum.Init(_mat);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);

		//绘制场景
		g_pPlane->Render();

		int count = 0;
		for (int i = 0; i < g_Size; ++i)
		{
			if (_frustum.PointInFrustum(g_pNodes[i]._pos))
			{
				++count;
				g_pNodes[i].Render();
			}
		}

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);

		//绘制UI
		XVec3f pos = pUIText->GetPos();
		BGRA8U color = pUIText->GetColor();
		wchar_t* pText = pUIText->GetText();

		pFront->Begin(_w, _h);
		XRectf rect = pFront->Draw(pos._x, pos._y, pos._z, color, pText, true);
		pUIText->SetRect(rect);
		pFront->End();

		//打印日志
		wchar_t title[32];
		swprintf(title, L"Info: 当前绘制个数：%d", count);
		XLog::AddString(title);
	}

	void XRenderWindow::End()
	{
		glDeleteTextures(1, &_texture1);
		glDeleteTextures(1, &_texture2);

		pFront->Done();
		delete pFront;
		delete pUIText;
	}
}


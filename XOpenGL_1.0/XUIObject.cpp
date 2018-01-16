#include "XUIObject.h"


namespace Smile
{
	/****************************************************************************************************************
	 *
	 *    Brief   : UIObject
	 *
	 ****************************************************************************************************************/
	XUIObject::XUIObject()
	{
		_Pos = XVec3f(0.0f, 0.0f, 0.0f);
		_Rect = XRectf(0.0f, 0.0f, 0.0f, 0.0f);
	}

	XUIObject::XUIObject(XVec3f pos, XRectf rect)
	{
		_Pos = pos;
		_Rect = rect;
	}

	XUIObject::~XUIObject()
	{

	}

	void XUIObject::OnMsgMouseIn(XPointf point)
	{

	}

	void XUIObject::OnMsgMouseOut(XPointf point)
	{

	}

	void XUIObject::OnMsgClick(XPointf point)
	{

	}

	void XUIObject::Render()
	{

	}

	/****************************************************************************************************************
	*
	*    Brief   : 全局回调函数
	*
	****************************************************************************************************************/
	void OnClick(XUIObject& obj)
	{
		//打印日志
		wchar_t title[32];
		swprintf(title, L"Info: 点击了UI!");
		XLog::AddString(title);
	}

	/****************************************************************************************************************
	 *
	 *    Brief   : UIText
	 *
	 ****************************************************************************************************************/
	XUIText::XUIText()
	{
		_Color = BGRA8U(0, 0, 0, 0);
		_pText = NULL;
	}

	XUIText::XUIText(XVec3f pos, XRectf rect, BGRA8U color, wchar_t* pText) : XUIObject(pos, rect), _Color(color), _pText(pText)
	{

	}

	void XUIText::Init(XVec3f pos, XRectf rect, BGRA8U color, wchar_t* pText)
	{
		_Pos = pos;
		_Rect = rect;

		_Color = color;
		_pText = pText;
	}

	/****************************************************************************************************************
	 *
	 *    Brief   : UIButton
	 *
	 ****************************************************************************************************************/

	XUIButton::XUIButton()
	{
		_iStatus = STATUS_NORMAL;
		_Color[STATUS_NORMAL] = BGRA8U(200, 200, 200, 255);
		_Color[STATUS_HOVER] = BGRA8U(255, 255, 255, 255);
		_Color[STATUS_PUSH] = BGRA8U(255, 200, 200, 255);
		_Color[STATUS_DISABLE] = BGRA8U(100, 100, 100, 255);
	}

	void XUIButton::Init(XVec3f pos, XRectf rect)
	{
		_Pos = pos;
		_Rect = rect;
	}

	void XUIButton::OnMsgMouseIn(XPointf point)
	{
		_iStatus = STATUS_HOVER;

		wchar_t title[32];
		swprintf(title, L"Info: OnMsgMouseIn!");
		XLog::AddString(title);
	}

	void XUIButton::OnMsgMouseOut(XPointf point)
	{
		_iStatus = STATUS_NORMAL;

		wchar_t title[32];
		swprintf(title, L"Info: OnMsgMouseOut!");
		XLog::AddString(title);
	}

	void XUIButton::OnMsgClick(XPointf point)
	{
		_iStatus = STATUS_PUSH;

		wchar_t title[32];
		swprintf(title, L"Info: OnMsgClick!");
		XLog::AddString(title);;
	}

	void XUIButton::Render()
	{
		XVertex vertices[] = {
			XVec3f(_Rect._x, _Rect._y, 0),							XVec2f(0, 0), _Color[_iStatus],
			XVec3f(_Rect._x + _Rect._w, _Rect._y, 0),				XVec2f(0, 0), _Color[_iStatus],
			XVec3f(_Rect._x + _Rect._w, _Rect._y + _Rect._h, 0),	XVec2f(0, 0), _Color[_iStatus],
			XVec3f(_Rect._x, _Rect._y + _Rect._h, 0),				XVec2f(0, 0), _Color[_iStatus],
		};

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glVertexPointer(3, GL_FLOAT, sizeof(XVertex), &vertices[0]._Pos);
		glTexCoordPointer(2, GL_FLOAT, sizeof(XVertex), &vertices[0]._UV);
		glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(XVertex), &vertices[0]._Color);

		glDrawArrays(GL_QUADS, 0, 4);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
	}

	/****************************************************************************************************************
	 *
	 *    Brief   : Manager
	 *
	 ****************************************************************************************************************/
	XUIManager::XUIManager()
	{
		_pObjMouseMove = NULL;
		_pObjLButtonDown = NULL;
	}

	void XUIManager::OnMsgMouseIn(XUIObject* obj, XPointf point)
	{
		obj->OnMsgMouseIn(point);
	}

	void XUIManager::OnMsgMouseOut(XUIObject* obj, XPointf point)
	{
		obj->OnMsgMouseOut(point);
	}

	void XUIManager::OnMsgClick(XUIObject* obj, XPointf point)
	{
		obj->OnMsgClick(point);
	}

	void XUIManager::OnMsg(int msg, XPointf point)
	{
		switch (msg)
		{
		case WM_LBUTTONDOWN:
		{
			_pObjLButtonDown = NULL;
			for (std::list<XUIObject*>::iterator it = _UI.begin(); it != _UI.end(); ++it)
			{
				XUIObject* pObj = *it;
				XRectf rect = pObj->GetRect();
				if (PointInRect(point, rect))
				{
					_pObjLButtonDown = pObj;
					
					break;
				}
			}
		}
		break;
		case WM_LBUTTONUP:
		{
			for (std::list<XUIObject*>::iterator it = _UI.begin(); it != _UI.end(); ++it)
			{
				XUIObject* pObj = *it;
				XRectf rect = pObj->GetRect();
				if (PointInRect(point, rect))
				{
					if (_pObjLButtonDown == pObj)
					{
						OnMsgClick(pObj, point);
						
						break;
					}
				}
			}
		}
		break;
		case WM_MOUSEMOVE:
		{
			bool bIn = false;
			for (std::list<XUIObject*>::iterator it = _UI.begin(); it != _UI.end(); ++it)
			{
				XUIObject* pObj = *it;
				XRectf rect = pObj->GetRect();
				if (PointInRect(point, rect))
				{
					bIn = true;

					if (_pObjMouseMove == NULL)
					{
						_pObjMouseMove = pObj;
						OnMsgMouseIn(_pObjMouseMove, point);
					}
					else if (_pObjMouseMove != pObj)
					{
						OnMsgMouseOut(_pObjMouseMove, point);
						_pObjMouseMove = pObj;
						OnMsgMouseIn(_pObjMouseMove, point);
					}

					break;
				}
			}
			if (bIn == false && _pObjMouseMove != NULL)
			{
				OnMsgMouseOut(_pObjMouseMove, point);
				_pObjMouseMove = NULL;
			}
		}
		break;
		}
	}

	void XUIManager::Begin(int screenW, int screenH)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, screenW, 0, screenH, -100, 100);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
	}

	void XUIManager::Render()
	{
		for (std::list<XUIObject*>::iterator it = _UI.begin(); it != _UI.end(); ++it)
		{
			XUIObject* pObj = *it;
			pObj->Render();
		}
	}

	void XUIManager::End()
	{
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
	}

	void XUIManager::AddObj(XUIObject* obj)
	{
		_UI.push_back(obj);
	}
}
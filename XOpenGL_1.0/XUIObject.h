#pragma once

#include <stdio.h>
#include <list>

#include "XMath.h"
#include "CommonType.h"

#include "XLog.h"

namespace Smile
{
	/****************************************************************************************************************
	 *
	 *    Brief   : UIObject
	 *
	 ****************************************************************************************************************/
	class XUIObject
	{
	public:
		XUIObject();
		XUIObject(XVec3f pos, XRectf rect);
		virtual ~XUIObject();

	public:
		virtual void OnMsgMouseIn(XPointf point);
		virtual void OnMsgMouseOut(XPointf point);
		virtual void OnMsgClick(XPointf point);
		virtual void Render();

	public:
		XVec3f GetPos() { return _Pos; }
		void SetPos(XVec3f pos) { _Pos = pos; }

		XRectf GetRect() { return _Rect; }
		void SetRect(XRectf rect) { _Rect = rect; }

	protected:
		//UI��λ�á�
		XVec3f _Pos;
		//UI�ľ���λ�ã�_Pos��һ����Rect��һ���ǵ㣬���ڿ��ܴ���ƫ�ƣ�������һ����
		XRectf _Rect;
	};

	/****************************************************************************************************************
	*
	*    Brief   : ȫ�ֻص�����
	*
	****************************************************************************************************************/
	typedef void(*LPFUNC) (XUIObject& obj);
	//�ص�������
	void OnClick(XUIObject& obj);

	/****************************************************************************************************************
	 *
	 *    Brief   : UIText
	 *
	 ****************************************************************************************************************/
	class XUIText : public XUIObject
	{
	public:
		XUIText();
		XUIText(XVec3f pos, XRectf rect, BGRA8U color, wchar_t* pText);

		void Init(XVec3f pos, XRectf rect, BGRA8U color, wchar_t* pText);

	public:
		BGRA8U GetColor() { return _Color; }
		void SetColor(BGRA8U color) { _Color = color; }

		wchar_t* GetText() { return _pText; }
		void SetText(wchar_t* pText) { _pText = pText; }

	protected:
		BGRA8U _Color;
		wchar_t* _pText;

	public:
		LPFUNC _pFunc;
	};

	/****************************************************************************************************************
	 *
	 *    Brief   : UIButton
	 *
	 ****************************************************************************************************************/
	class XUIButton : public XUIObject
	{
	public:
		XUIButton();
		void Init(XVec3f pos, XRectf rect);
		virtual void OnMsgMouseIn(XPointf point);
		virtual void OnMsgMouseOut(XPointf point);
		virtual void OnMsgClick(XPointf point);
		virtual void Render();

	protected:
		enum
		{
			STATUS_NORMAL,
			STATUS_HOVER,
			STATUS_PUSH,
			STATUS_DISABLE,
			STATUS_MAX,
		};

		int _iStatus;
		BGRA8U _Color[STATUS_MAX];
	};

	/****************************************************************************************************************
	 *
	 *    Brief   : Manager
	 *
	 ****************************************************************************************************************/
	class XUIManager
	{
	public:
		XUIManager();
		void OnMsgMouseIn(XUIObject* obj, XPointf point);
		void OnMsgMouseOut(XUIObject* obj, XPointf point);
		void OnMsgClick(XUIObject* obj, XPointf point);
		void OnMsg(int msg, XPointf point);

		void Begin(int screenW, int screenH);
		void Render();
		void End();

		void AddObj(XUIObject* obj);

	protected:
		std::list<XUIObject*> _UI;
		XUIObject* _pObjMouseMove;
		XUIObject* _pObjLButtonDown;
	};

}
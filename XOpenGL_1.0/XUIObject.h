#pragma once

#include <stdio.h>

#include "CommonType.h"
#include "XMath.h"
#include "XLog.h"

namespace Smile
{
	class XUIObject
	{
	public:
		XUIObject()
		{
			_Pos = XVec3f(0.0f, 0.0f, 0.0f);
			_Rect = XRectf(0.0f, 0.0f, 0.0f, 0.0f);
		}

		XUIObject(XVec3f pos, XRectf rect)
		{
			_Pos = pos;
			_Rect = rect;
		}

		XVec3f GetPos() { return _Pos; }
		void SetPos(XVec3f pos) { _Pos = pos; }

		XRectf GetRect() { return _Rect; }
		void SetRect(XRectf rect) { _Rect = rect; }

	protected:
		XVec3f _Pos;
		XRectf _Rect;
	};

	typedef void(*LPFUNC) (XUIObject& obj);

	class XUIText : public XUIObject
	{
	public:
		XUIText()
		{
			_Color = BGRA8U(0, 0, 0, 0);
			_pText = NULL;
		}

		XUIText(XVec3f pos, XRectf rect, BGRA8U color, wchar_t* pText)
			: XUIObject(pos, rect), _Color(color), _pText(pText)
		{

		}

		void Init(XVec3f pos, XRectf rect, BGRA8U color, wchar_t* pText)
		{
			_Pos = pos;
			_Rect = rect;

			_Color = color;
			_pText = pText;
		}

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

	//»Øµ÷º¯Êý£º
	void OnClick(XUIObject& obj);
}
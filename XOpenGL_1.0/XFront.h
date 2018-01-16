#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_BITMAP_H

#include <gl/glew.h>
#include <gl/wglew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "XMath.h"

namespace Smile
{

	struct FrontVertex
	{
		FrontVertex()
		{
			_Pos = XVec3f(0.0f, 0.0f, 0.0f);
			_UV = XVec2f(0.0f, 0.0f);
			_Color = BGRA8U(0, 0, 0, 0);
		}

		XVec3f _Pos;
		XVec2f _UV;
		BGRA8U _Color;
	};

	struct Character
	{
		Character()
		{
			_found = false;
			_Texture = 0;
			_Pos = XVec2f(0.0f, 0.0f);
			_Size = XVec2f(0.0f, 0.0f);
			_Offset = XVec2f(0.0f, 0.0f);
			_Span = XVec2f(0.0f, 0.0f);
		}

		bool _found;
		GLuint _Texture;
		XVec2f _Pos;
		XVec2f _Size;
		XVec2f _Offset;
		XVec2f _Span;
	};

	class XFront
	{
	public:
		XFront();
		~XFront();

		void Init(const char* pFront, int texW, int texH, int size);
		void Done();

		void Begin(int screenW, int screenH);
		void End();
		XRectf Draw(float x, float y, float z, BGRA8U color, const wchar_t* text, bool bDrawBorder = false);
		XRectf GetSize(float x, float y, float z, const wchar_t* text);

	private:
		Character& GetCharacter(unsigned int cIndex);

	private:
		/****************************************************************************************************************
		 *
		 *    Brief   : Freetype相关
		 *
		 ****************************************************************************************************************/
		FT_Library _Library;
		FT_Face _Face;

		/****************************************************************************************************************
		 *
		 *    Brief   : 字体相关
		 *
		 ****************************************************************************************************************/
		int _Size;

		/****************************************************************************************************************
		 *
		 *    Brief   : 缓冲相关
		 *
		 ****************************************************************************************************************/
		int _TextureW;
		int _TextureH;
		GLuint _Texture;

		Character* _Characters;
		FrontVertex* _FrontVertices;

		/****************************************************************************************************************
		 *
		 *    Brief   : 其他
		 *
		 ****************************************************************************************************************/
		float _offsetX;
		float _offsetY;

		float _FrontMaxX;    //一行字体的最大宽度
		float _FrontMaxY;	 //一行字体的最高点－最低点。

		float maxOffsetY;	//最大Y偏移。
	};
}
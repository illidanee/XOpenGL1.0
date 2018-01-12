#pragma once

#include "XGLWindow.h"

#include <string>
#include <list>

#include "XFront.h"

namespace Smile
{
	class XLog : public XGLWindow
	{
	public:
		static void AddString(const wchar_t* text);

	public:
		static std::list<std::wstring> _ListString;

	private:
		void Begin();
		void Render();
		void End();

	private:
		XFront* g_Front;
	};
}
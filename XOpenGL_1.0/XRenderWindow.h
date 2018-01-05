#pragma once

#include "XResource.h"
#include "XGLWindow.h"

namespace Smile
{
	class XRenderWindow : public XGLWindow
	{
		void Event(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		void Begin();
		void Render();
		void End();

		bool _RButtonDown;
		int _x;
		int _y;
	};
}
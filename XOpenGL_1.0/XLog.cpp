#include "XLog.h"


namespace Smile
{
	std::list<std::wstring> XLog::_ListString;

	void XLog::AddString(const wchar_t* text)
	{
		std::wstring c = text;
		_ListString.push_back(c);

		if (_ListString.size() > 27)
			_ListString.pop_front();
	}

	void XLog::Begin()
	{
		g_Front = new XFront();
		g_Front->Init("../Resources/simsun.ttc", 1024, 1024, 16);
	}

	void XLog::Render()
	{
		//修正最小化后字体大小发生变化的BUG
		glViewport(0, 0, _w, _h);

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		g_Front->Begin(_w, _h);

		int y = 560;
		for (std::list<std::wstring>::iterator it = _ListString.begin(); it != _ListString.end(); ++it)
		{
			if (y > 20)
			{
				std::wstring str = *it;
				g_Front->Draw(10, y, 0, BGRA8U(255, 255, 0, 125), str.c_str());
				y -= 20;
			}
			else
			{
				break;
			}
		}

		g_Front->End();
	}

	void XLog::End()
	{
		g_Front->Done();
	}
}
#pragma once

#include "XGLWindow.h"

namespace Smile
{
	class XLog : public XGLWindow
	{
		void Begin();
		void Render();
		void End();
	};
}
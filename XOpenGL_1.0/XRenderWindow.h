#pragma once

#include "XResource.h"
#include "XGLWindow.h"

namespace Smile
{
	class XRenderWindow : public XGLWindow
	{
		void Begin();
		void Render();
		void End();
	};
}
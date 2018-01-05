#pragma once

#include <gl/glew.h>
#include <gl/wglew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "XMath.h"

namespace Smile
{
	class XCamera
	{
	public:
		XCamera();
		~XCamera();

		void Init(XVec3f pos, XVec3f aim, XVec3f up);

		void Update();

		void OnLeft();
		void OnRight();
		void OnFront();
		void OnBack();

		void OnRotateX(float delta);
		void OnRotateY(float delta);

	private:
		XVec3f _pos;
		XVec3f _aim;
		XVec3f _up;

		XVec3f _dir;
		XVec3f _right;

		float _speed;
	};
}

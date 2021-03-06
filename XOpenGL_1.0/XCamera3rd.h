#pragma once

#include <gl/glew.h>
#include <gl/wglew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "XMath.h"

namespace Smile
{
	class XCamera3rd
	{
	public:
		XCamera3rd();
		~XCamera3rd();

		void Init(XVec3f pos, XVec3f aim, XVec3f up);

		void LookAtAim(XVec3f aim);
		void View();
		void Proj(float fovy, float aspect, float zNear, float zFar);

		void OnRotateX(float delta);
		void OnRotateY(float delta);
		void OnScaleLength(float delta);

		XMat4f GetMatPV();
		void SetViewport(int w, int h);
		void ScreenToWorld(XVec4f& screenPos, XVec4f& worldPos);
		XRayf CreateRayFromScreen(const XVec2f screenPos);

	private:
		XVec3f _pos;
		XVec3f _aim;
		XVec3f _up;

		XVec3f _dir;
		XVec3f _right;

		float _length;
		float _speed;

		XMat4f _matView;
		XMat4f _matProj;

		int _w;
		int _h;
	};
}

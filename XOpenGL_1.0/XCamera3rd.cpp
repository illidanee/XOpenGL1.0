#include "XCamera3rd.h"

namespace Smile
{
	XCamera3rd::XCamera3rd()
	{

	}

	XCamera3rd::~XCamera3rd()
	{

	}

	void XCamera3rd::Init(XVec3f pos, XVec3f aim, XVec3f up)
	{
		_pos = pos;
		_aim = aim;
		_up = up;

		_dir = Normalize(_aim - _pos);
		_right = Normalize(Cross(_dir, _up));

		_length = 6.0f;
		_speed = 0.1f;
	}

	void XCamera3rd::LookAtAim(XVec3f aim)
	{
		_pos = aim - _dir * _length;
		_aim = aim;
	}

	void XCamera3rd::View()
	{
		_matView = LookAt(_pos, _aim, _up);
	}

	void XCamera3rd::Proj(float fovy, float aspect, float zNear, float zFar)
	{
		_matProj = Perspective(fovy, aspect, zNear, zFar);
	}

	void XCamera3rd::OnRotateX(float delta)
	{
		XMat4f rotMat;
		rotMat.Rotate(delta, _right);
		XVec4f tempDir = XVec4f(_dir._x, _dir._y, _dir._z, 1.0f);
		tempDir = rotMat * tempDir;
		_dir = XVec3f(tempDir._x, tempDir._y, tempDir._z);

		float len = Length(_aim - _pos);
		_pos = _aim - _dir * len;
	}

	void XCamera3rd::OnRotateY(float delta)
	{
		XMat4f rotMat;
		rotMat.Rotate(delta, _up);
		XVec4f tempDir = XVec4f(_dir._x, _dir._y, _dir._z, 1.0f);
		tempDir = rotMat * tempDir;
		_dir = XVec3f(tempDir._x, tempDir._y, tempDir._z);

		float len = Length(_aim - _pos);
		_pos = _aim - _dir * len;

		_right = Normalize(Cross(_dir, _up));
	}

	void XCamera3rd::OnScaleLength(float delta)
	{
		_length *= delta;
	}

	XMat4f XCamera3rd::GetMatPV() 
	{ 
		return _matProj * _matView; 
	}

	void XCamera3rd::SetViewport(int w, int h) 
	{ 
		_w = w;
		_h = h;
	}

	void XCamera3rd::ScreenToWorld(XVec4f& screenPos, XVec4f& worldPos)
 	{
		screenPos._x = screenPos._x / _w;
		screenPos._y = screenPos._y / _h;
		
		screenPos._x = screenPos._x * 2.0f - 1.0f;
		screenPos._y = screenPos._y * 2.0f - 1.0f;
		screenPos._z = screenPos._z * 2.0f - 1.0f;

		XMat4f matInverse;
		Inverse<float>(_matProj * _matView, matInverse);

		worldPos = matInverse * screenPos;

		worldPos._x = worldPos._x / worldPos._w;
		worldPos._y = worldPos._y / worldPos._w;
		worldPos._z = worldPos._z / worldPos._w;
		worldPos._w = 1.0f;
	}

	XRayf XCamera3rd::CreateRayFromScreen(const XVec2f screenPos)
	{

		XVec4f screenNear(screenPos._x, screenPos._y, 0.0f, 1.0f);
		XVec4f screenFar(screenPos._x, screenPos._y, 1.0f, 1.0f);

		XVec4f worldNear;
		XVec4f worldFar;

		ScreenToWorld(screenNear, worldNear);
		ScreenToWorld(screenFar, worldFar);

		XVec4f direction = worldFar - worldNear;

		XVec3f origin(worldNear._x, worldNear._y, worldNear._z);
		XVec3f dir(direction._x, direction._y, direction._z);

		return XRayf(origin, dir);

	}
}
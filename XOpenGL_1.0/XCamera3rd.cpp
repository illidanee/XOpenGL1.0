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
}
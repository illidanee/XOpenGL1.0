#include "XCamera.h"

namespace Smile
{
	XCamera::XCamera()
	{

	}

	XCamera::~XCamera()
	{

	}

	void XCamera::Init(XVec3f pos, XVec3f aim, XVec3f up)
	{
		_pos = pos;
		_aim = aim;
		_up = up;

		_dir = Normalize(_aim - _pos);
		_right = Normalize(Cross(_dir, _up));

		_speed = 0.1f;
	}

	void XCamera::View()
	{
		_matView = LookAt(_pos, _aim, _up);
	}

	void XCamera::Proj(float fovy, float aspect, float zNear, float zFar)
	{
		_matProj = Perspective(fovy, aspect, zNear, zFar);
	}

	void XCamera::OnLeft()
	{
		_pos = _pos - _right * _speed;
		_aim = _aim - _right * _speed;
	}

	void XCamera::OnRight()
	{
		_pos = _pos + _right * _speed;
		_aim = _aim + _right * _speed;
	}

	void XCamera::OnFront()
	{
		_pos = _pos + _dir * _speed;
		_aim = _aim + _dir * _speed;
	}

	void XCamera::OnBack()
	{
		_pos = _pos - _dir * _speed;
		_aim = _aim - _dir * _speed;
	}

	void XCamera::OnRotateX(float delta)
	{
		XMat4f rotMat;
		rotMat.Rotate(delta, _right);
		XVec4f tempDir = XVec4f(_dir._x, _dir._y, _dir._z, 1.0f);
		tempDir = rotMat * tempDir;
		_dir = XVec3f(tempDir._x, tempDir._y, tempDir._z);

		float len = Length(_aim - _pos);
		_aim = _pos + _dir * len;

	}

	void XCamera::OnRotateY(float delta)
	{
		XMat4f rotMat;
		rotMat.Rotate(delta, _up);
		XVec4f tempDir = XVec4f(_dir._x, _dir._y, _dir._z, 1.0f);
		tempDir = rotMat * tempDir;
		_dir = XVec3f(tempDir._x, tempDir._y, tempDir._z);

		float len = Length(_aim - _pos);
		_aim = _pos + _dir * len;

		_right = Normalize(Cross(_dir, _up));
	}
}
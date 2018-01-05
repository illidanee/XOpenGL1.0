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

	void XCamera3rd::LookAt(XVec3f aim)
	{
		_pos = aim - _dir * _length;
		_aim = aim;
	}

	void XCamera3rd::Update()
	{
		gluLookAt(_pos._x, _pos._y, _pos._z, _aim._x, _aim._y, _aim._z, _up._x, _up._y, _up._z);
	}

	void XCamera3rd::OnRotateX(float delta)
	{
		_dir = Normalize(RotateX(_dir, delta));
		float len = Length(_aim - _pos);
		_pos = _aim - _dir * len;

	}

	void XCamera3rd::OnRotateY(float delta)
	{
		_dir = Normalize(RotateY(_dir, delta));
		float len = Length(_aim - _pos);
		_pos = _aim - _dir * len;

		_right = Normalize(Cross(_dir, _up));
	}

	void XCamera3rd::OnScaleLength(float delta)
	{
		_length *= delta;
	}
}
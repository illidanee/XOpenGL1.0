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

	void XCamera::Update()
	{
		gluLookAt(_pos._x, _pos._y, _pos._z, _aim._x, _aim._y, _aim._z, _up._x, _up._y, _up._z);
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
		_dir = Normalize(RotateX(_dir, delta));
		float len = Length(_aim - _pos);
		_aim = _pos + _dir * len;

	}

	void XCamera::OnRotateY(float delta)
	{
		_dir = Normalize(RotateY(_dir, delta));
		float len = Length(_aim - _pos);
		_aim = _pos + _dir * len;

		_right = Normalize(Cross(_dir, _up));
	}
}
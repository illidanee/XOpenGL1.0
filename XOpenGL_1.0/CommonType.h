#pragma once


namespace Smile 
{
	//��ɫ
	template<typename T>
	class _BGRA
	{
	public:
		_BGRA() {}
		_BGRA(T b, T g, T r, T a) : _b(b), _g(g), _r(r), _a(a) { }
		_BGRA(unsigned int color) : _color(color) { }

		union
		{
			struct 
			{
				T _b;
				T _g;
				T _r;
				T _a;
			};
			unsigned int _color;
		};
	};

	typedef _BGRA<unsigned char> BGRA8U;

//ȫ�ֺ���
	template<typename T>
	_BGRA<T> operator + (const _BGRA<T>& left, const _BGRA<T>& right)
	{
		return  _BGRA<T>(
			left._b + (255 - left._b) * ((float)right._b / 255),
			left._g + (255 - left._g) * ((float)right._g / 255),
			left._r + (255 - left._r) * ((float)right._r / 255),
			left._a + (255 - left._a) * ((float)right._a / 255)
			);
	}

	template<typename T>
	class _XRect
	{
	public:
		_XRect() {}
		_XRect(T x, T y, T w, T h) : _x(x), _y(y), _w(w), _h(h) {}

		struct  
		{
			T _x;
			T _y;
			T _w;
			T _h;
		};
	};

	typedef _XRect<float> XRectf;
}
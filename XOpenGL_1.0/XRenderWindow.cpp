#include "XRenderWindow.h"

#include "XVideo.h"

#define _PI           3.14159265358979323846f 



namespace Smile
{
	//全局数据
	struct float3
	{
		float3() {}
		float3(float x, float y, float z) : _x(x), _y(y), _z(z) {}
		float3 operator * (const float& o)
		{
			return float3(_x * o, _y * o, _z * o);
		}
		float3 operator + (const float3& o)
		{
			return float3(_x + o._x, _y + o._y, _z + o._z);
		}

		float _x, _y, _z;
	};

	struct Particle
	{
		float3 _Pos;
		float3 _Vel;
		unsigned char _r;
		unsigned char _g;
		unsigned char _b;
		unsigned char _a;
	};

	const int PARTICLE_SIZE = 500;

	const float speed = 0.005f;

	Particle particles[PARTICLE_SIZE];

	GLuint _texture1;

	float RandomIdentity()
	{
		return ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
	}

	float3 RandomVector()
	{
		float3 vVector;
		vVector._z = RandomIdentity();

		float r = (float)sqrt(1 - vVector._z * vVector._z);
		float t = (float)RandomIdentity() * _PI;

		vVector._x = (float)cosf(t) * r;
		vVector._y = (float)sinf(t) * r;

		return vVector;
	}

	void Smile::XRenderWindow::Begin()
	{
		char* pBuffer;
		int w, h;
		XResource::LoadTextureFile("../Resources/particle.bmp", &pBuffer, &w, &h);

		//读取纹理数据
		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &_texture1);
		glBindTexture(GL_TEXTURE_2D, _texture1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pBuffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		for (int i = 0; i < PARTICLE_SIZE; ++i)
		{
			particles[i]._Pos = float3(0.0f, 0.0f, 0.0f);
			particles[i]._Vel = RandomVector() * (rand() % 5 + 0.5f);
			particles[i]._r = rand() % 255;
			particles[i]._g = rand() % 255;
			particles[i]._b = rand() % 255;
			particles[i]._a = 255;
		}
	}

	void Smile::XRenderWindow::Render()
	{
		//变量
		static float tm = 0;

		tm += 0.5;
		if (tm >= 64)
		{
			tm = 0;
		}

		//清空
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//设置投影矩阵
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//glOrtho(0, _w, 0, _h, -100, 100);
		gluPerspective(60.0f, (float)_w / _h, 0.01f, 1000.0f);

		//设置模型矩阵
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -2.0f);

		//绑定纹理
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _texture1);

		//混合
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);

		//点精灵设置
		//float maxSize = 0.0f;
		//glGetFloatv(GL_POINT_SIZE_MAX_ARB, &maxSize);
		//// size of 1024.0f!
		//if (maxSize > 100.0f)
		//	maxSize = 100.0f;

		glPointSize(10);

		//glPointParameterfARB(GL_POINT_FADE_THRESHOLD_SIZE_ARB, 60.0f);
		//glPointParameterfARB(GL_POINT_SIZE_MIN_ARB, 1.0f);
		//glPointParameterfARB(GL_POINT_SIZE_MAX_ARB, 100);

		glTexEnvf(GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, GL_TRUE);
		glEnable(GL_POINT_SPRITE_ARB);


		//更新和设置数据
		static DWORD dStartAppTime = GetTickCount();
		float fElpasedAppTime = ((GetTickCount() - dStartAppTime) * 0.001f);

		static DWORD dLastFrameTime = GetTickCount();
		DWORD dCurrenFrameTime = GetTickCount();
		float dElpasedFrameTime = ((dCurrenFrameTime - dLastFrameTime) * speed);
		dLastFrameTime = dCurrenFrameTime;

		if (fElpasedAppTime >= 10.0f)
		{
			for (int i = 0; i < PARTICLE_SIZE; ++i)
				particles[i]._Pos = float3(0.0f, 0.0f, 0.0f);

			dStartAppTime = GetTickCount();
		}

		for (int i = 0; i < PARTICLE_SIZE; ++i)
			particles[i]._Pos = particles[i]._Pos + particles[i]._Vel *(float)dElpasedFrameTime * 0.1f;

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(Particle), &particles[0]._Pos._x);

		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Particle), &particles[0]._r);
		
		glDrawArrays(GL_POINTS, 0, PARTICLE_SIZE);

		glDisable(GL_POINT_SPRITE_ARB);
	}

	void Smile::XRenderWindow::End()
	{
		glDeleteTextures(1, &_texture1);
	}
}


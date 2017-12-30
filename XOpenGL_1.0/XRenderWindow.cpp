#include "XRenderWindow.h"

namespace Smile
{
	struct Vertex
	{
		float x, y, z;
		float u, v;
		float r, g, b;
	};

	Vertex g_cubeVertices[] =
	{
		{ -1.0f,-1.0f, 1.0f,  0.0f,0.0f, 1.0f,0.0f,0.0f, }, // 0
		{ 1.0f,-1.0f, 1.0f ,  0.0f,0.0f, 0.0f,1.0f,0.0f, }, // 1
		{ 1.0f, 1.0f, 1.0f ,  0.0f,0.0f, 0.0f,0.0f,1.0f, }, // 2
		{ -1.0f, 1.0f, 1.0f,  0.0f,0.0f, 1.0f,1.0f,0.0f, }, // 3
		{ -1.0f,-1.0f,-1.0f,  0.0f,0.0f, 1.0f,0.0f,1.0f, }, // 4
		{ -1.0f, 1.0f,-1.0f,  0.0f,0.0f, 0.0f,1.0f,1.0f, }, // 5
		{ 1.0f, 1.0f,-1.0f ,  0.0f,0.0f, 1.0f,1.0f,1.0f, }, // 6
		{ 1.0f,-1.0f,-1.0f ,  0.0f,0.0f, 1.0f,0.0f,0.0f, }, // 7
	};

	GLubyte g_cubeIndices[] =
	{
		0, 1, 2, 3, // Quad 0
		4, 5, 6, 7, // Quad 1
		5, 3, 2, 6, // Quad 2
		4, 7, 1, 0, // Quad 3
		7, 6, 2, 1, // Quad 4
		4, 0, 3, 5 // Quad 5
	};

	GLuint _vbo1;
	GLuint _vbo2;
	GLuint _ibo2;

	void CheckError()
	{
		GLenum err = glGetError();
		if (err != GL_NO_ERROR)
		{
			switch (err)
			{
			case GL_INVALID_ENUM:
				printf("GL Error: GL_INVALID_ENUM.\n");
				break;
			case GL_INVALID_VALUE:
				printf("GL Error: GL_INVALID_VALUE.\n");
				break;
			case GL_INVALID_OPERATION:
				printf("GL Error: GL_INVALID_OPERATION.\n");
				break;
			case GL_STACK_OVERFLOW:
				printf("GL Error: GL_STACK_OVERFLOW.\n");
				break;
			case GL_STACK_UNDERFLOW:
				printf("GL Error: GL_STACK_UNDERFLOW.\n");
				break;
			case GL_OUT_OF_MEMORY:
				printf("GL Error: GL_OUT_OF_MEMORY.\n");
				break;
			default:
				printf("GL Error!\n");
				break;
			}
		}
	}

	void DrawOnCPU()
	{
		//模型矩阵
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(-2.0f, 0.0f, -5);

		//绑定数据
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &g_cubeVertices[0].x);
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(3, GL_FLOAT, sizeof(Vertex), &g_cubeVertices[0].r);

		//绘制
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, g_cubeIndices);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
	}

	void BeginDrawOnGPU()
	{
		glGenBuffers(1, &_vbo1);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo1);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_cubeVertices), g_cubeVertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &_vbo2);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo2);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_cubeVertices), g_cubeVertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &_ibo2);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo2);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_cubeIndices), g_cubeIndices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void DrawOnGPU()
	{
		//模型矩阵
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(2.0f, 0.0f, -5);

		glBindBuffer(GL_ARRAY_BUFFER, _vbo2);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo2);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (const void*)0);
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(3, GL_FLOAT, sizeof(Vertex), (const void*)(sizeof(float) * 5));

		//绘制
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, 0);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void EndDrawOnGPU()
	{
		glDeleteBuffers(1, &_vbo1);
		glDeleteBuffers(1, &_vbo2);
		glDeleteBuffers(1, &_ibo2);
	}

	void Smile::XRenderWindow::Begin()
	{
		BeginDrawOnGPU();

		CheckError();
	}

	void Smile::XRenderWindow::Render()
	{
		//清空
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//正交投影绘制平面
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60.0f, float(_w) / float(_h), 0.1f, 100.0f);

		//******************************************************************************************************************
		//这里有一个Bug，如果注释掉DrawOnCPU（），点击关闭主窗口会Crash。但是如果不注释则没有问题。OpenGL glGetError() 无错误提示。
		DrawOnCPU();
		DrawOnGPU();

		CheckError();
	}

	void Smile::XRenderWindow::End()
	{
		EndDrawOnGPU();

		CheckError();
	}
}


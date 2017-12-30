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
		{ -1.0f,-1.0f, 1.0f,0.0f, 0.0f,1.0f, 0.0f, 0.0f },
		{ 1.0f,-1.0f, 1.0f,1.0f, 0.0f,1.0f, 0.0f, 0.0f },
		{ 1.0f, 1.0f, 1.0f,1.0f, 1.0f,1.0f, 0.0f, 0.0f },
		{ -1.0f, 1.0f, 1.0f,0.0f, 1.0f,1.0f, 0.0f, 0.0f },

		{ -1.0f,-1.0f,-1.0f,1.0f, 0.0f,0.0f, 1.0f, 0.0f },
		{ -1.0f, 1.0f,-1.0f,1.0f, 1.0f,0.0f, 1.0f, 0.0f },
		{ 1.0f, 1.0f,-1.0f,0.0f, 1.0f,0.0f, 1.0f, 0.0f },
		{ 1.0f,-1.0f,-1.0f,0.0f, 0.0f,0.0f, 1.0f, 0.0f },

		{ -1.0f, 1.0f,-1.0f,0.0f, 1.0f,0.0f, 0.0f, 1.0f },
		{ -1.0f, 1.0f, 1.0f,0.0f, 0.0f,0.0f, 0.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f,1.0f, 0.0f,0.0f, 0.0f, 1.0f },
		{ 1.0f, 1.0f,-1.0f,1.0f, 1.0f,0.0f, 0.0f, 1.0f },

		{ -1.0f,-1.0f,-1.0f,1.0f, 1.0f,1.0f, 1.0f, 0.0f },
		{ 1.0f,-1.0f,-1.0f,0.0f, 1.0f,1.0f, 1.0f, 0.0f },
		{ 1.0f,-1.0f, 1.0f,0.0f, 0.0f,1.0f, 1.0f, 0.0f },
		{ -1.0f,-1.0f, 1.0f,1.0f, 0.0f,1.0f, 1.0f, 0.0f },

		{ 1.0f,-1.0f,-1.0f,1.0f, 0.0f,1.0f, 0.0f, 1.0f },
		{ 1.0f, 1.0f,-1.0f,1.0f, 1.0f,1.0f, 0.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f,0.0f, 1.0f,1.0f, 0.0f, 1.0f },
		{ 1.0f,-1.0f, 1.0f,0.0f, 0.0f,1.0f, 0.0f, 1.0f },

		{ -1.0f,-1.0f,-1.0f,0.0f, 0.0f,0.0f, 1.0f, 1.0f },
		{ -1.0f,-1.0f, 1.0f,1.0f, 0.0f,0.0f, 1.0f, 1.0f },
		{ -1.0f, 1.0f, 1.0f,1.0f, 1.0f,0.0f, 1.0f, 1.0f },
		{ -1.0f, 1.0f,-1.0f,0.0f, 1.0f,0.0f, 1.0f, 1.0f }
	};

	GLuint _texture0;

	GLuint _vbo;

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
		//ģ�;���
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(-2.0f, 0.0f, -5);

		//������
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &g_cubeVertices[0].x);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &g_cubeVertices[0].u);
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(3, GL_FLOAT, sizeof(Vertex), &g_cubeVertices[0].r);

		//����
		glBindTexture(GL_TEXTURE_2D, _texture0);

		glDrawArrays(GL_QUADS, 0, 24);

		glBindTexture(GL_TEXTURE_2D, 0);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
	}

	void BeginDrawOnGPU()
	{
		glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_cubeVertices), g_cubeVertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void DrawOnGPU()
	{
		//ģ�;���
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(2.0f, 0.0f, -5);

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (const void*)0);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (const void*)(sizeof(float) * 3));
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(3, GL_FLOAT, sizeof(Vertex), (const void*)(sizeof(float) * 5));

		//����
		glBindTexture(GL_TEXTURE_2D, _texture0);

		glDrawArrays(GL_QUADS, 0, 24);

		glBindTexture(GL_TEXTURE_2D, 0);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void EndDrawOnGPU()
	{
		glDeleteBuffers(1, &_vbo);
	}

	void Smile::XRenderWindow::Begin()
	{
		char* pBuffer;
		int w, h;

		{
			XResource::LoadTextureFile("../Resources/floor.bmp", &pBuffer, &w, &h);

			//��ȡ��������
			glEnable(GL_TEXTURE_2D);
			glGenTextures(1, &_texture0);
			glBindTexture(GL_TEXTURE_2D, _texture0);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, pBuffer);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		BeginDrawOnGPU();

		CheckError();
	}

	void Smile::XRenderWindow::Render()
	{
		//���
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//����ͶӰ����ƽ��
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60.0f, float(_w) / float(_h), 0.1f, 100.0f);

		//******************************************************************************************************************
		//������һ��Bug�����ע�͵�DrawOnCPU����������ر������ڻ�Crash�����������ע����û�����⡣OpenGL glGetError() �޴�����ʾ��
		DrawOnCPU(); 
		DrawOnGPU();

		CheckError();
	}

	void Smile::XRenderWindow::End()
	{
		glDeleteTextures(1, &_texture0);

		EndDrawOnGPU();

		CheckError();
	}
}


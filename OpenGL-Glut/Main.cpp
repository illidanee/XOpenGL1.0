#include "glut.h"

/****************************************************************************************************************
 *    Date    : 2017/12/19 16:44
 *
 *    Author  : Smile
 *    Contact : smile@illidan.org
 *
 *    Brief   : 由于使用OpenGL官网上，预编译好Glut为x86版本，所以本程序须在x86平台下运行。
				如果需要在x64平台下运行，需要自己编译Glut的x64版本。
 *
 ****************************************************************************************************************/

void OnDisplay()
{
	glClearColor(1, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	//初始化
	glutInit(&argc, argv);

	//创建窗口
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow("illidan");

	//注册回调
	glutDisplayFunc(OnDisplay);

	//主循环
	glutMainLoop();

	return  0;
}
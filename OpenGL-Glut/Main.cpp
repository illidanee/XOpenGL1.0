#include "glut.h"

/****************************************************************************************************************
 *    Date    : 2017/12/19 16:44
 *
 *    Author  : Smile
 *    Contact : smile@illidan.org
 *
 *    Brief   : ����ʹ��OpenGL�����ϣ�Ԥ�����GlutΪx86�汾�����Ա���������x86ƽ̨�����С�
				�����Ҫ��x64ƽ̨�����У���Ҫ�Լ�����Glut��x64�汾��
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
	//��ʼ��
	glutInit(&argc, argv);

	//��������
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow("illidan");

	//ע��ص�
	glutDisplayFunc(OnDisplay);

	//��ѭ��
	glutMainLoop();

	return  0;
}
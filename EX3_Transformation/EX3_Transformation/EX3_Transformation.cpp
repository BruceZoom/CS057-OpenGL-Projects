// EX3_Transformation.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "glut.h"

void glDrawAxis(float length)
{
	glBegin(GL_LINES);
	{
		glColor3f(1, 0, 0);
		glVertex3f(-length, 0, 0);
		glVertex3f(length, 0, 0);
	}
	glEnd();
	glBegin(GL_LINES);
	{
		glColor3f(0, 1, 0);
		glVertex3f(0, -length, 0);
		glVertex3f(0, length, 0);
	}
	glEnd();
	glBegin(GL_LINES);
	{
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, -length);
		glVertex3f(0, 0, length);
	}
	glEnd();
}

// view port transformation
void handleReshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// glTranslatef(0, 0, -1);

	gluPerspective(90, (float)w / h, 1, 2000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// model transformation
void ModelTransform()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0, 0, -1);

	// glDrawAxis(3);

	gluLookAt(0, 0, 0, 0, 1, 1, 0, 1, 0);

	glColor3f(0, 0, 1);
	glRotatef(90.0, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 0.5, 0.0);

	glutWireTeapot(0.5);

	// glLoadIdentity();
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();

	glColor3f(1, 0, 0);
	glTranslatef(0.0, -0.5, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);

	glutWireTeapot(0.5);

}

void Display()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawAxis(3);

	ModelTransform();

	glutSwapBuffers();
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(400, 100);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutCreateWindow("EX3");

	glutReshapeFunc(handleReshape);
	glutDisplayFunc(Display);

	glutMainLoop();
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

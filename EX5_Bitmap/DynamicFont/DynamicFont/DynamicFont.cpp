// DynamicFont.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "string.h"
#include "glut.h"

const char *Text = "OpenGL\0";
const char *c;

void init()
{
	glClearColor(0, 0, 0, 1);
}

void display()
{
	static float angle = 0.;
	angle += 0.1;

	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);

	glTranslatef(0, 0, -10);
	glRotatef(angle, 0, 0, 1);
	glColor3f(1, 1, 0);

	glRasterPos3f(-3, 3, -10);
	for (c = Text; *c != '\0'; c++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);

	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)w / h, 0.1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void Idle()
{
	glutPostRedisplay();
}

void main()
{
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Dynamic Font");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(Idle);
	glutMainLoop();
}
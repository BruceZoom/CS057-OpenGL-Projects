// EX4_Lighting.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "glut.h"
#include "cmath"

#define PI 3.14159

using namespace std;

void light_init(void)
{
	// ================光源和材料属性数组==============================
	GLfloat mat_specular[] = { 1.,1.,1.,1. };
	GLfloat mat_shininess[] = { 128. };

	GLfloat light0_diffuse[] = { 1.,1.,1.,1. };
	//GLfloat light0_position[]={1.05,1.05,1.05,1.};
	//GLfloat light0_position[]={0,0,0,1.};
	GLfloat light0_position[] = { 50.0,42.0,-40.0,1. };

	GLfloat light1_diffuse[] = { 1.,0.,0.,1. };
	//GLfloat light1_specular[] = { 0.,0.,0.,0. };
	//	GLfloat light1_position[]={1.05,1.05,1.05,1.};
	//	GLfloat light1_position[]={2.0,2.0,2.0,1.};
	GLfloat light1_position[] = { 0,0,0,1. };
	//GLfloat light1_spot_direction[] = { 5.0,-5.0,-20.0 };


	//*************用数组设置光源和材料属性====================

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_BACK, GL_SHININESS, mat_shininess);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	//-------多光源－－－－－
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
}

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

void DrawSphere(float X, float Y, float Z,
				float Radius, float Slices, float Stacks,
				float colorR=1, float colorG=1, float colorB=1)
{
	glPolygonMode(GL_FRONT, GL_FILL);

	float dy = 2 * Radius / Stacks;
	float omega = 2 * PI / Slices;

	int i, j, k;
	float y1, y2, r1, r2;
	float tmpc, tmps;

	glBegin(GL_TRIANGLE_STRIP);
	for (i = 1; i < Stacks + 1; i++)
	{
		y1 = (i - 1) * dy - Radius;
		y2 = i * dy - Radius;
		r1 = sqrt(Radius * Radius - y1 * y1);
		r2 = sqrt(Radius * Radius - y2 * y2);
		for (j = 0; j < Slices; j++)
		{
			tmpc = cos(j * omega);
			tmps = sin(j * omega);
			// specify normal vector
			glNormal3f(r2 * tmpc / Radius, y2 / Radius, r2 * tmps / Radius);
			// specify color
			glColor3f(colorR, colorG, colorB);
			glVertex3f(
				X + r2 * tmpc,
				Y + y2,
				Z + r2 * tmps
			);
			// specify normal vector
			glNormal3f(r1 * tmpc / Radius, y1 / Radius, r1 * tmps / Radius);
			// specify color
			glColor3f(colorR, colorG, colorB);
			glVertex3f(
				X + r1 * tmpc,
				Y + y1,
				Z + r1 * tmps
			);
		}
	}
	glEnd();
}

void Reshape(GLint w, GLint h)
{
	glViewport(0, 0, w, h);
}

void Display()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// draw my yellow sphere
	DrawSphere(-0.5, 0, 0, 0.4, 30, 50, 0, 1, 0);
	
	glLoadIdentity();
	// draw glut blue sphere
	glColor3f(0.0, 0.0, 1.0);
	glTranslatef(0.5, 0, 0);
	glutSolidSphere(0.4, 30, 50);

	glDisable(GL_COLOR_MATERIAL);

	glutSwapBuffers();
}

int main(int argc, char ** argv)
{
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(400, 100);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Sphere");
	light_init();
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);

	glutMainLoop();
	return 0;
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

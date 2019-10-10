// EX2_SphereAndSpring.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "glut.h"
#include "cmath"

#define PI 3.14159

using namespace std;

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
void ZXCDrawSphere(float Radius, int Slices, int Stacks)
{
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_POINT);
	glColor3f(1, 1, 0);

	float dAngle_H = 2.0f * PI / Slices;
	float dAngle_V = 2.0f * PI / Stacks;
	float x, y, z;

	int i, j;
	for (i = 0; i <= Stacks; i++)
	{
		float CircleRadius1 = sin(i * dAngle_V);
		float CircleRadius2 = sin((i + 1) * dAngle_V);
		float y1 = -cos(i * dAngle_V);
		float y2 = -cos((i + 1) * dAngle_V);

		glBegin(GL_TRIANGLE_STRIP);
		for (j = 0; j <= Slices; j++)
		{
			x = cos(j * dAngle_H) * CircleRadius2;
			y = y2;
			z = -sin(j * dAngle_H) * CircleRadius2;
			glVertex3f(x* Radius, y* Radius, z* Radius);

			x = cos(j * dAngle_H) * CircleRadius1;
			y = y1;
			z = -sin(j * dAngle_H) * CircleRadius1;
			glVertex3f(x* Radius, y* Radius, z* Radius);
		}
		glEnd();
	}
}

//	DrawTriangle:
//		Draw a simple triangle
void DrawTriangle()
{
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_POINT);
	glColor3f(1, 1, 0);

	glBegin(GL_TRIANGLES);
	{
		glVertex3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(1, 0, 0);
	}
	glEnd();
}

//	DrawSphereLine
//		Draw a sphere using lines instead of triangles
//	Param:
//		Radius: radius of the sphere
//		Slices: how many slices the circle is divided into
//		Stacks: how many stacks the sphere is divided into vertically
void DrawSphereLine(float Radius, float Slices, float Stacks)
{
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_POINT);
	glColor3f(1, 1, 0);

	float dy = 2 * Radius / Stacks;
	float omega = 2 * PI / Slices;

	int i, j, k;
	float y1, y2, r1, r2;
	float tmpc, tmps;

	glBegin(GL_LINE_LOOP);
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
			glVertex3f(
				r1 * tmpc,
				y1,
				r1 * tmps
			);
			glVertex3f(
				r2 * tmpc,
				y2,
				r2 * tmps
			);
		}
	}
	glEnd();
}

//	DrawSpringEnd:
//		Close two ends of the spring.
//	Param:
//		memo: {x0, y0, z0}
//		radius: radius of the string
//		rRation: radius / Radius
//		Slices: how many slices the circle is divided into
//		flip: which end of the spring
void DrawSpringEnd(float* memo, float radius, float rRatio, float yRatio, int Slices, bool flip = false)
{
	float dAngle = 2 * PI / Slices;
	int i, j;
	int sign = (flip ? -1 : 1) * yRatio;

	glBegin(GL_TRIANGLE_STRIP);
	for (i = 0, j = Slices - 1; i < Slices / 2; i++, j--)
	{
		glVertex3f(
			memo[0] + rRatio * cos(i * dAngle) * memo[0],
			memo[1] + radius * sin(i * dAngle) * sign,
			memo[2] + rRatio * cos(i * dAngle) * memo[2]
		);
		glVertex3f(
			memo[0] + rRatio * cos(j * dAngle) * memo[0],
			memo[1] + radius * sin(j * dAngle) * sign,
			memo[2] + rRatio * cos(j * dAngle) * memo[2]
		);
	}
	glEnd();
}

//	DrawSpring:
//		Draw the entire Spring.
//	Param:
//		Radius: radius of the circle which the spring revolves,
//			from the y-axis to the center of the string
//		Height: the height of the spring
//		Turns: how many turns the spring revolves
//		radius: radius of the string
//		Slices: how many slices the circle is divided into
//		Stacks: how many stacks the spring is divided into along the string
void DrawSpring(float Radius, float Height, float Turns, float radius, int Slices, int Stacks)
{
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_POINT);
	glColor3f(1, 1, 0);

	float dy = Height / Stacks;
	float omega = 2 * Turns * PI / Height;
	float dAngle = 2 * PI / Slices;

	// multiple the y ratio to the y-axis shift to simulate ellipse
	float sinphi = sin(1.0 / Radius / omega);
	float yRatio = 1 / (1 - sinphi * sinphi);

	int i, j, k;
	float theta;
	float x0, y0, z0;
	float rRatio = radius / Radius;		// to speed up calculation
	float tmpc, tmps;					// to speed up calculation
	// used for remembering last center
	float memo[3] = {
		Radius * cos(-Height / 2 * omega),	// initial x0
		-Height / 2,						// initial y0
		Radius * sin(-Height / 2 * omega)	// initial z0
	};

	// draw the lower end
	DrawSpringEnd(memo, radius, rRatio, yRatio, Slices);

	// draw the body of the spring from bottom to top
	glBegin(GL_TRIANGLE_STRIP);
	for (i = 1; i < Stacks; i++)
	{
		// calculate the center of the current stack
		y0 = i * dy - Height / 2;
		theta = omega * y0;
		x0 = Radius * cos(theta);
		z0 = Radius * sin(theta);
		// revolve around the center to form the surface of the string
		for (j = 0; j < Slices; j++)
		{
			tmpc = cos(j * dAngle);
			tmps = sin(j * dAngle);
			glVertex3f(
				x0 + rRatio * tmpc * x0,	// much faster than the following
				// x0 + radius * cos(j * dAngle) * cos(last_theta)
				y0 + radius * tmps * yRatio,
				z0 + rRatio * tmpc * z0		// much faster than the following
				// z0 + radius * cos(j * dAngle) * sin(last_theta)
			);
			glVertex3f(
				memo[0] + rRatio * tmpc * memo[0],
				memo[1] + radius * tmps * yRatio,
				memo[2] + rRatio * tmpc * memo[2]
			);
		}
		memo[0] = x0;
		memo[1] = y0;
		memo[2] = z0;
	}
	glEnd();

	// draw the upper end
	DrawSpringEnd(memo, radius, rRatio, yRatio, Slices, true);
}

void Reshape(GLint w, GLint h)
{
	glViewport(0, 0, w, h);

}

void Display()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glRotatef(.05, 1, 1, 0);

	glDrawAxis(3);
	
	// draw the sphere, from the course material
	// ZXCDrawSphere(0.4, 30, 50);

	// draw trianlge
	//DrawTriangle();

	// draw the sphere using lines
	//DrawSphereLine(0.4, 30, 50);

	// draw the spring
	DrawSpring(0.3, 1, 3, 0.05, 20, 100);
	
	glutSwapBuffers();

}


int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(400, 100);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Sphere");

	glutReshapeFunc(Reshape);
	glutIdleFunc(Display);
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

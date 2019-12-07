#include "pch.h"
#include "Utils.h"
#include "glut.h"

void DrawSphere(float X, float Y, float Z, float Radius, int Slices, int Stacks)
{
	float dAngle_H = 2.0f * PI / Slices;
	float dAngle_V = 2.0f * PI / Stacks;
	float x, y, z;

	int i, j;
	for (i = 0; i < Stacks; i++)
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
			glNormal3f(x, y, z);
			glTexCoord2f((float)j / Slices, (float)(i + 1) / Stacks * 2);
			glVertex3f(X + x* Radius, Y + y* Radius, Z + z* Radius);

			x = cos(j * dAngle_H) * CircleRadius1;
			y = y1;
			z = -sin(j * dAngle_H) * CircleRadius1;
			glNormal3f(x, y, z);
			glTexCoord2f((float)j / Slices, (float)i / Stacks * 2);
			glVertex3f(X + x* Radius, Y + y* Radius, Z + z* Radius);
		}
		glEnd();
	}
}

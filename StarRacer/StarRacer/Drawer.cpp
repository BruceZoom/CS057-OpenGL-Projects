#include "pch.h"
#include "Utils.h"
#include "glut.h"
#include "SpaceShip.h"
#include "GameController.h"

void SpaceShip::DrawBody()
{
	int iFace, iPoint;
	glBegin(GL_TRIANGLES);
	for (iFace = 0; iFace < 3704; iFace++)  // Each new triangle starts here
		for (iPoint = 0; iPoint < 3; iPoint++) // Each vertex specified here
		{
			// Lookup the texture value
			glTexCoord2fv(texturesBody[face_indiciesBody[iFace][iPoint + 6]]);

			// Lookup the normal value
			glNormal3fv(normalsBody[face_indiciesBody[iFace][iPoint + 3]]);

			// Lookup the vertex value
			glVertex3fv(verticesBody[face_indiciesBody[iFace][iPoint]]);
		}
	glEnd();
}

void SpaceShip::DrawGlass()
{
	int iFace, iPoint;
	glBegin(GL_TRIANGLES);
	for (iFace = 0; iFace < 352; iFace++)  // Each new triangle starts here
		for (iPoint = 0; iPoint < 3; iPoint++) // Each vertex specified here
		{
			// Lookup the texture value
			glTexCoord2fv(texturesGlass[face_indiciesGlass[iFace][iPoint + 6]]);

			// Lookup the normal value
			glNormal3fv(normalsGlass[face_indiciesGlass[iFace][iPoint + 3]]);

			// Lookup the vertex value
			glVertex3fv(verticesGlass[face_indiciesGlass[iFace][iPoint]]);
		}
	glEnd();
}

void DrawSphere(float X, float Y, float Z, float Radius, int Slices, int Stacks, int mode)
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
			if (mode == 0) {
				glTexCoord2f((float)j / Slices, (float)(i + 1) / Stacks * 2);
			}
			if (mode == 1) {
				glColor3f(0, 0, 0);
			}
			glVertex3f(X + x* Radius, Y + y* Radius, Z + z* Radius);

			x = cos(j * dAngle_H) * CircleRadius1;
			y = y1;
			z = -sin(j * dAngle_H) * CircleRadius1;
			glNormal3f(x, y, z);
			if (mode == 0) {
				glTexCoord2f((float)j / Slices, (float)i / Stacks * 2);
			}
			if (mode == 1) {
				glColor3f(0, 0, 0);
			}
			glVertex3f(X + x* Radius, Y + y* Radius, Z + z* Radius);
		}
		glEnd();
	}
}

void GameController::DrawUI()
{
	const char *text = "Test GUI";

	//glDisable(GL_LIGHTING);
	//glColor4f(0.9, 0.9, 0.9, 1);
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos3f(0, 0, -0.5);
	for(const char *c = text; *c != '\0'; c++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	//glEnable(GL_LIGHTING);
}


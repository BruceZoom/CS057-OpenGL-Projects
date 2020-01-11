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
	char ckptText[] = "Checkpoint Passed: ";
	char ckpt[5];
	char deathText[] = "Total Death: ";
	char death[5];
	char currentLap[15];
	char historyLap[50];

	sprintf_s(ckpt, 5, "%d", timeElapsedVector.size());
	ckpt[strlen(ckpt)] = '\0';
	sprintf_s(death, 5, "%d", deathCount);
	death[strlen(death)] = '\0';
	sprintf_s(currentLap, 15, "%7.2fs", currentTimeElapsed);
	currentLap[strlen(currentLap)] = '\0';

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glColor3f(1, 1, 1);
	// checkpoint
	glRasterPos3f(0, 0.26, -0.5);
	for(char *c = ckptText; *c != '\0'; c++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	for (char *c = ckpt; *c != '\0'; c++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	// death
	glRasterPos3f(0, 0.24, -0.5);
	for (char *c = deathText; *c != '\0'; c++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	for (char *c = death; *c != '\0'; c++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	// current lap
	glRasterPos3f(-0.07, 0.25, -0.5);
	for (char *c = currentLap; *c != '\0'; c++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	// history laps
	int n = timeElapsedVector.size();
	for (int i = n; i > Max(0, n - MaxLapsDisplayed); --i) {
		glRasterPos3f(-0.5, 0.26 - 0.01 * (n - i), -0.5);
		sprintf_s(historyLap, 50, "Lap %d: %7.2fs", i, timeElapsedVector[i-1]);
		historyLap[strlen(historyLap)] = '\0';
		for (char *c = historyLap; *c != '\0'; c++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
	}

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}


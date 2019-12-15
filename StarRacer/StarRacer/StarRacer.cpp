#include "pch.h"
#include "glut.h"
#include <iostream>

#include "BMPLoad.h"
#include "Utils.h"
#include "Galaxy.h"
#include"PlayerController.h"

#define PI 3.1415

BMPPic * ppic;
Galaxy * galaxy;
PlayerController * controller;

void init()
{
	// set up galaxy
	//string textures[] = { "Textures/earth.bmp" };
	//galaxy = new Galaxy(1, textures);
	//galaxy->SetStar(0, 1, 0, 0, 0.5);
	galaxy = new Galaxy(3, "");

	controller = new PlayerController();

	glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

void Render() {
	static float degree = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glPushMatrix();
	//glRotatef(degree, 0, 1, 0);
	degree += 0.05;
	glTranslatef(0, 0, -10);

	galaxy->DrawGalaxy();

	glPopMatrix();
	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	GLfloat fAspect;
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	fAspect = (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, fAspect, 1.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void TimerFunction(int value)
{
	glutPostRedisplay();

	galaxy->UpdateStar(0);
	galaxy->UpdateStar(1);
	galaxy->UpdateStar(2);

	controller->Reset();
	
	glutTimerFunc(5, TimerFunction, 1);
}

void KeyProcess(unsigned char key, int x, int y)
{
	controller->HandleInput(key, x, y);
	cout << controller->Rotation.x << " " << controller->Rotation.y << " " << controller->Rotation.z << endl;
	cout << controller->Forward << " " << controller->Horizontal << " " << controller->Brake << endl;
}

void SpecialKey(int key, int xx, int yy)
{
	controller->HandleInput(key, xx, yy);
	cout << controller->Rotation.x << " " << controller->Rotation.y << " " << controller->Rotation.z << endl;
	cout << controller->Forward << " " << controller->Horizontal << " " << controller->Brake << endl;
}

int main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Star Racer");
	init();

	// control handler
	glutKeyboardFunc(KeyProcess);
	glutSpecialFunc(SpecialKey);

	// display handler
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Render);
	glutIdleFunc(Render);

	glutTimerFunc(5, TimerFunction, 1);
	glutMainLoop();

	delete galaxy;

	return 0;
}

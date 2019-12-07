#include "pch.h"
#include "glut.h"
#include "BMPLoad.h"
#include <iostream>
#include "Utils.h"
#include "Galaxy.h"

#define PI 3.1415

BMPPic * ppic;
Galaxy * galaxy;

void init()
{
	// set up galaxy
	//string textures[] = { "Textures/earth.bmp" };
	//galaxy = new Galaxy(1, textures);
	//galaxy->SetStar(0, 1, 0, 0, 0.5);
	galaxy = new Galaxy(3, "");

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
	galaxy->UpdateStar(0);
	galaxy->UpdateStar(1);
	galaxy->UpdateStar(2);

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

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Star Racer");
	init();
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Render);
	glutIdleFunc(Render);
	glutMainLoop();

	delete galaxy;
}

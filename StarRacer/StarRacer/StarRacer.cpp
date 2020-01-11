#include "pch.h"
#include "glut.h"
#include <iostream>

#include "BMPLoad.h"
#include "zxcSkyBox.h"

#include "Utils.h"
#include "Galaxy.h"
#include "PlayerController.h"
#include "SpaceShip.h"
#include "Track.h"
#include "GameController.h"

#define PI 3.1415

BMPPic * ppic;
CzxcSkyBox * skybox;

Galaxy * galaxy;
PlayerController * controller;
SpaceShip * ship;
Track * track;

void init()
{
	GLfloat fAmbLight[] = { 0.0f, 0.1f, 0.9f, 0.0f };
	GLfloat fDiffLight[] = { 1.0f, 1.0f, 1.0f, 0.0f };
	GLfloat fSpecLight[] = { 0.5f, 0.5f, 0.5f, 0.0f };
	GLfloat lightPos[] = { -100.0f, 100.0f, 100.0f, 1.0f };
	GLfloat fScale = 0.01f;
	
	glClearColor(0.0f, 0.0f, .50f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Set up lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, fDiffLight);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	//glLightfv(GL_LIGHT0, GL_AMBIENT, fAmbLight);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, fDiffLight);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, fSpecLight);
	//glLightModeli(0x81F8, 0x81FA);

	// Light never changes, put it here
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glEnable(0x803A);

	// set up galaxy
	galaxy = new Galaxy(9, "");

	// set up controller
	controller = new PlayerController();

	// set up space ship
	ship = new SpaceShip({ 5, 0, -10 });

	// initiate track
	track = new Track({ 4.8, 0.2, -8 }, 0.2, 0.05, 2);

	// set up sky box
	skybox = new CzxcSkyBox(50000,
		"Textures/ame_nebula/purplenebula_lf.tga",
		"Textures/ame_nebula/purplenebula_rt.tga",
		"Textures/ame_nebula/purplenebula_ft.tga",
		"Textures/ame_nebula/purplenebula_bk.tga",
		"Textures/ame_nebula/purplenebula_up.tga",
		"Textures/ame_nebula/purplenebula_dn.tga");

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

	GameController::DrawUI();

	//glRotatef(degree, 0, 1, 0);
	//degree += 0.05;
	//glTranslatef(0, 0, -10);
	ship->DrawSpaceShip();

	galaxy->DrawGalaxy();
	track->DrawTrack();

	skybox->ShowSky();

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
	gluPerspective(60.0f, fAspect, 0.01f, 50000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void TimerFunction(int value)
{
	glutPostRedisplay();

	GameController::UpdateTime(5.0 / 1000);

	//galaxy->UpdateStar(0);
	//galaxy->UpdateStar(1);
	//galaxy->UpdateStar(2);
	galaxy->UpdateGalaxy();

	ship->UpdateSpaceShip(*controller);

	//controller->Reset();

	glutTimerFunc(5, TimerFunction, 1);
}

void KeyBoard(unsigned char key, int x, int y)
{
	controller->HandleInput(key, x, y);
}

void SpecialKey(int key, int xx, int yy)
{
	controller->HandleInput(key, xx, yy);
}

void KeyBoardUp(unsigned char key, int x, int y)
{
	controller->ResetInput(key, x, y);
}

void SpecialKeyUp(int key, int xx, int yy)
{
	controller->ResetInput(key, xx, yy);
}

int main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Star Racer");
	init();

	// control handler
	glutKeyboardFunc(KeyBoard);
	glutSpecialFunc(SpecialKey);
	glutKeyboardUpFunc(KeyBoardUp);
	glutSpecialUpFunc(SpecialKeyUp);

	// display handler
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Render);
	glutIdleFunc(Render);

	glutTimerFunc(5, TimerFunction, 1);
	glutMainLoop();

	delete galaxy;
	delete controller;
	delete ship;
	delete track;

	return 0;
}

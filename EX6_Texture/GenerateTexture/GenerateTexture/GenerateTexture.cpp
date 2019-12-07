#include <iostream>
#include "pch.h"
#include "glut.h"

/* 创建纹理 */
#define ImageWidth 64
#define ImageHeight 64
GLubyte Image[ImageWidth][ImageHeight][3];
GLuint textPic[1];

void makeImage(void)
{
	int i, j, r, g, b;
	for (i = 0; i < ImageWidth; i++)
	{
		for (j = 0; j < ImageHeight; j++)
		{
			r = (i*j) % 255;
			g = (4 * i) % 255;
			b = (4 * j) % 255;

			Image[i][j][0] = (GLubyte)r;
			Image[i][j][1] = (GLubyte)g;
			Image[i][j][2] = (GLubyte)b;
		}
	}
}


void myinit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	makeImage();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, textPic);
	glBindTexture(GL_TEXTURE_2D, textPic[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, Image);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glEnable(GL_TEXTURE_2D);
}

void display(void)
{
	static int degree = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//glPushMatrix();
	glTranslatef(0.0, 0.0, -4);
	glRotatef(degree, 0, 0, 1);
	degree = (degree + 1) % 360;

	glBindTexture(GL_TEXTURE_2D, textPic[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -1.0, 0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-2.0, 1.0, 0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 1.0, 0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.0, -1.0, 0.0);
	glEnd();

	//glPopMatrix();
	glutSwapBuffers();
	//glFlush();
}


void Reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0*(GLfloat)w / (GLfloat)h, 1.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void main(void)
{
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Texture ");
	myinit();
	glutReshapeFunc(Reshape);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMainLoop();
}

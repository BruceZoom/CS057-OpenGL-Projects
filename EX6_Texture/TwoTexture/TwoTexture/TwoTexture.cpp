// TwoTexture.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "glut.h"
#include "BMPLoad.h"
#include <iostream>

BMPPic * ppic;
GLuint textPic[2];

void init()
{
	glGenTextures(2, textPic);
	
	glBindTexture(GL_TEXTURE_2D, textPic[0]);
	ppic = ZXCLoadBMP("image.bmp");
	glPixelStoref(GL_UNPACK_ALIGNMENT, 4);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ppic->iwidth, ppic->iheight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, ppic->pByte);
	free(ppic->pByte);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, textPic[1]);
	ppic = ZXCLoadBMP("wood.bmp");
	glPixelStoref(GL_UNPACK_ALIGNMENT, 4);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ppic->iwidth, ppic->iheight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, ppic->pByte);
	free(ppic->pByte);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

void Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glPushMatrix();
	glTranslatef(0, 0, -10);

	glBindTexture(GL_TEXTURE_2D, textPic[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0., 0.); glVertex3f(-1, -1, 0);
	glTexCoord2f(1., 0.); glVertex3f(1, -1, 0);
	glTexCoord2f(1., 1.); glVertex3f(1, 0, 0);
	glTexCoord2f(0., 1.); glVertex3f(-1, 0, 0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textPic[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0., 0.); glVertex3f(0, 0, 0);
	glTexCoord2f(1., 0.); glVertex3f(1, 0, 0);
	glTexCoord2f(1., 1.); glVertex3f(1, 1, 0);
	glTexCoord2f(0., 1.); glVertex3f(0, 1, 0);
	glEnd();

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
	gluPerspective(45.0f, fAspect, 1.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("TwoTexture");
	init();
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Render);
	glutMainLoop();
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

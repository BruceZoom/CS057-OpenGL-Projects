// ShowImage.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "glut.h"
#include "BMPLoad.h"

BMPPic * bmpPic;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glRasterPos3f(-40, -41, -200);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	glDrawPixels(bmpPic->iwidth, bmpPic->iheight, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmpPic->pByte);

	glFlush();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 1.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main()
{
	bmpPic = ZXCLoadBMP("c6407b176d224f4aeea9f1d100f790529922d179.bmp");
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(bmpPic->iheight, bmpPic->iwidth);
	glutCreateWindow("Show Image");
	glutReshapeFunc(Reshape);
	glutDisplayFunc(RenderScene);
	glutMainLoop();
}


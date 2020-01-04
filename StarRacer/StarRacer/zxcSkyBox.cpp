#include "pch.h"
#include "zxcSkyBox.h"


CzxcSkyBox::CzxcSkyBox(GLfloat SkyWidth, string Lpic, string Rpic, string Fpic, string Bpic, string Tpic, string Dpic)
{
	GLint iWidth, iHeight, iComponents;
	GLenum eFormat;
	GLbyte *pBytes;

	nPicStyle = 0;
	fSky_W = SkyWidth;
	//fSky_H = fSky_W / 2;
	glGenTextures(5, nTextureNum);

	// 说明映射方式
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	//  启动纹理映射
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);

	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // 改成GL_LINE 纹理就全没了！
	glEnable(GL_DEPTH_TEST);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, mPic[i].GetAlignment()); // 4字节对齐

	// left
	glBindTexture(GL_TEXTURE_2D, nTextureNum[0]);
	pBytes = gltLoadTGA(Lpic.c_str(), &iWidth, &iHeight, &iComponents, &eFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, (void *)pBytes);
	free(pBytes);
	// right
	glBindTexture(GL_TEXTURE_2D, nTextureNum[1]);
	pBytes = gltLoadTGA(Rpic.c_str(), &iWidth, &iHeight, &iComponents, &eFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, (void *)pBytes);
	free(pBytes);
	// front
	glBindTexture(GL_TEXTURE_2D, nTextureNum[2]);
	pBytes = gltLoadTGA(Fpic.c_str(), &iWidth, &iHeight, &iComponents, &eFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, (void *)pBytes);
	free(pBytes);
	// back
	glBindTexture(GL_TEXTURE_2D, nTextureNum[3]);
	pBytes = gltLoadTGA(Bpic.c_str(), &iWidth, &iHeight, &iComponents, &eFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, (void *)pBytes);
	free(pBytes);
	// up
	glBindTexture(GL_TEXTURE_2D, nTextureNum[4]);
	pBytes = gltLoadTGA(Tpic.c_str(), &iWidth, &iHeight, &iComponents, &eFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, (void *)pBytes);
	free(pBytes);
	// down
	glBindTexture(GL_TEXTURE_2D, nTextureNum[5]);
	pBytes = gltLoadTGA(Dpic.c_str(), &iWidth, &iHeight, &iComponents, &eFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, (void *)pBytes);
	free(pBytes);

	fSky_H = fSky_W * iHeight / iWidth; // 保证天空盒子和图片尺寸成比例，否则图象变形失真！
}
/*
使用天空盒时常遇到缝隙无法消除的问题，最简单的方法是使用边缘截取（GL_CLAMP_TO_EDGE）：总是忽略边界。处于纹理边缘或者靠近纹理边缘的纹理单元都用作纹理计算，但是不包括边界上的纹理单元。
但这一参数只出现在OpenGL1.2及其后续版本中，而我们使用的VC中的opengl开发包仅为1.1,所以编译时VC会报错:GL_CLAMP_TO_EDGE没有声明。
事实上由于我们目前系统中使用的opengl库文件均为最新版本，只是VC附带开发包为1.1，而GL_CLAMP_TO_EDGE本质上仅为一个宏定义，所以我们可以在代码中不使用该宏定义而直接使用数值0x812F来替代，同样可以设置成边缘截取的这一个功能。
即使用：
glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,0x812F);
glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,0x812F);
作为如下代码的替代品。
glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
*/
void CzxcSkyBox::SetTex(GLuint texNum)
{
	glBindTexture(GL_TEXTURE_2D, texNum);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
}

void CzxcSkyBox::ShowSky()
{
	if (nPicStyle == 0) // 6个单独图片形式
	{
		SetTex(nTextureNum[0]); //LEFT
		glBegin(GL_QUADS); // 左
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-fSky_W / 2., -fSky_H/2, fSky_W / 2.);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(-fSky_W / 2., -fSky_H/2, -fSky_W / 2.);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(-fSky_W / 2., fSky_H/2, -fSky_W / 2.);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-fSky_W / 2., fSky_H/2, fSky_W / 2.);
		glEnd();
		SetTex(nTextureNum[1]); //right
		glBegin(GL_QUADS); // 右侧
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(fSky_W / 2., -fSky_H/2, -fSky_W / 2.);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(fSky_W / 2., -fSky_H/2, fSky_W / 2.);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(fSky_W / 2., fSky_H/2, fSky_W / 2.);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(fSky_W / 2., fSky_H/2, -fSky_W / 2.);
		glEnd();
		SetTex(nTextureNum[2]);
		glBegin(GL_QUADS); // 前
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-fSky_W / 2., -fSky_H/2, -fSky_W / 2.);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(fSky_W / 2., -fSky_H/2, -fSky_W / 2.);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(fSky_W / 2., fSky_H/2, -fSky_W / 2.);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-fSky_W / 2., fSky_H/2, -fSky_W / 2.);
		glEnd();
		SetTex(nTextureNum[3]);
		glBegin(GL_QUADS); // 后
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(fSky_W / 2., -fSky_H/2, fSky_W / 2.);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(-fSky_W / 2., -fSky_H/2, fSky_W / 2.);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(-fSky_W / 2., fSky_H/2, fSky_W / 2.);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(fSky_W / 2., fSky_H/2, fSky_W / 2.);
		glEnd();
		SetTex(nTextureNum[4]);
		glBegin(GL_QUADS); // 上
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-fSky_W / 2., fSky_H/2, -fSky_W / 2.);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(fSky_W / 2., fSky_H/2, -fSky_W / 2.);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(fSky_W / 2., fSky_H/2, fSky_W / 2.);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-fSky_W / 2., fSky_H/2, fSky_W / 2.);
		glEnd();
		SetTex(nTextureNum[5]);
		glBegin(GL_QUADS); // 下
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-fSky_W / 2., -fSky_H/2,  fSky_W / 2.);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( fSky_W / 2., -fSky_H / 2,  fSky_W / 2.);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( fSky_W / 2., -fSky_H / 2, -fSky_W / 2.);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-fSky_W / 2., -fSky_H / 2, -fSky_W / 2.);
		glEnd();
	}
}
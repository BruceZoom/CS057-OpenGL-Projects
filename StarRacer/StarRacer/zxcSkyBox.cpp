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

	// ˵��ӳ�䷽ʽ
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	//  ��������ӳ��
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);

	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // �ĳ�GL_LINE �����ȫû�ˣ�
	glEnable(GL_DEPTH_TEST);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, mPic[i].GetAlignment()); // 4�ֽڶ���

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

	fSky_H = fSky_W * iHeight / iWidth; // ��֤��պ��Ӻ�ͼƬ�ߴ�ɱ���������ͼ�����ʧ�棡
}
/*
ʹ����պ�ʱ��������϶�޷����������⣬��򵥵ķ�����ʹ�ñ�Ե��ȡ��GL_CLAMP_TO_EDGE�������Ǻ��Ա߽硣���������Ե���߿��������Ե������Ԫ������������㣬���ǲ������߽��ϵ�����Ԫ��
����һ����ֻ������OpenGL1.2��������汾�У�������ʹ�õ�VC�е�opengl��������Ϊ1.1,���Ա���ʱVC�ᱨ��:GL_CLAMP_TO_EDGEû��������
��ʵ����������Ŀǰϵͳ��ʹ�õ�opengl���ļ���Ϊ���°汾��ֻ��VC����������Ϊ1.1����GL_CLAMP_TO_EDGE�����Ͻ�Ϊһ���궨�壬�������ǿ����ڴ����в�ʹ�øú궨���ֱ��ʹ����ֵ0x812F�������ͬ���������óɱ�Ե��ȡ����һ�����ܡ�
��ʹ�ã�
glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,0x812F);
glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,0x812F);
��Ϊ���´�������Ʒ��
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
	if (nPicStyle == 0) // 6������ͼƬ��ʽ
	{
		SetTex(nTextureNum[0]); //LEFT
		glBegin(GL_QUADS); // ��
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-fSky_W / 2., -fSky_H/2, fSky_W / 2.);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(-fSky_W / 2., -fSky_H/2, -fSky_W / 2.);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(-fSky_W / 2., fSky_H/2, -fSky_W / 2.);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-fSky_W / 2., fSky_H/2, fSky_W / 2.);
		glEnd();
		SetTex(nTextureNum[1]); //right
		glBegin(GL_QUADS); // �Ҳ�
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(fSky_W / 2., -fSky_H/2, -fSky_W / 2.);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(fSky_W / 2., -fSky_H/2, fSky_W / 2.);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(fSky_W / 2., fSky_H/2, fSky_W / 2.);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(fSky_W / 2., fSky_H/2, -fSky_W / 2.);
		glEnd();
		SetTex(nTextureNum[2]);
		glBegin(GL_QUADS); // ǰ
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-fSky_W / 2., -fSky_H/2, -fSky_W / 2.);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(fSky_W / 2., -fSky_H/2, -fSky_W / 2.);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(fSky_W / 2., fSky_H/2, -fSky_W / 2.);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-fSky_W / 2., fSky_H/2, -fSky_W / 2.);
		glEnd();
		SetTex(nTextureNum[3]);
		glBegin(GL_QUADS); // ��
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(fSky_W / 2., -fSky_H/2, fSky_W / 2.);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(-fSky_W / 2., -fSky_H/2, fSky_W / 2.);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(-fSky_W / 2., fSky_H/2, fSky_W / 2.);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(fSky_W / 2., fSky_H/2, fSky_W / 2.);
		glEnd();
		SetTex(nTextureNum[4]);
		glBegin(GL_QUADS); // ��
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-fSky_W / 2., fSky_H/2, -fSky_W / 2.);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(fSky_W / 2., fSky_H/2, -fSky_W / 2.);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(fSky_W / 2., fSky_H/2, fSky_W / 2.);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-fSky_W / 2., fSky_H/2, fSky_W / 2.);
		glEnd();
		SetTex(nTextureNum[5]);
		glBegin(GL_QUADS); // ��
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-fSky_W / 2., -fSky_H/2,  fSky_W / 2.);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( fSky_W / 2., -fSky_H / 2,  fSky_W / 2.);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( fSky_W / 2., -fSky_H / 2, -fSky_W / 2.);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-fSky_W / 2., -fSky_H / 2, -fSky_W / 2.);
		glEnd();
	}
}
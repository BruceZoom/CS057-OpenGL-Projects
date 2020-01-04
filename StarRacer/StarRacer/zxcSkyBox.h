
#ifndef _ZXCSKYBOX_H
#define _ZXCSKYBOX_H
#include <string>
#include "glut.h"
#include "BMPLoad.h"

using namespace std;

class CzxcSkyBox
{
private:
	GLfloat fSky_W;
	GLfloat fSky_H;
	GLuint  nPic_W; // ��պ���ͼƬΪ��һͼƬ��ʽ��ͼƬ���
	GLuint  nPic_H; // ��պ���ͼƬΪ��һͼƬ��ʽ��ͼƬ�߶�
	GLuint  nTextureNum[6]; // ����5�ţ�ȱ����ͼ�󣩻�6��ͼƬ������Skybox,����5��6��ͼƬ��������õ�ͼƬ��ʽ����ͼƬ������nTextureNum[0]�С�
	GLuint  nPicStyle; //�����ǵ�ͼƬ��ʽ�����Ƕ�ͼƬ��ʽ���е���ղ���5��ͼƬ(������nPicStyle=0)���еİ�����ͼƬ�ŵ���һ�ļ�����ͼƬ��ʽҲ�ж��ָ�ʽ����������ʽ��������Ե��Ǻ��ŵ�ͼƬ�ļ��ǡ�-+--����ʽ(nPicStyle=1)��
	void SetTex(GLuint texNum);
public:
	CzxcSkyBox(GLfloat SkyWidth, string Lpic, string Rpic, string Fpic, string Bpic, string Tpic, string Dpic); // 6��ͼƬ��ʽ�ĳ�ʼ������,5�ž���û�������ʽ
	void ShowSky(void);
};

#endif

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
	GLuint  nPic_W; // 天空盒子图片为单一图片形式，图片宽度
	GLuint  nPic_H; // 天空盒子图片为单一图片形式，图片高度
	GLuint  nTextureNum[6]; // 采用5张（缺地面图象）或6张图片来绘制Skybox,保存5或6个图片。如果采用单图片方式，则图片保存在nTextureNum[0]中。
	GLuint  nPicStyle; //表明是单图片方式，还是多图片方式。有的天空采用5张图片(则，设置nPicStyle=0)，有的把所有图片放到单一文件。单图片形式也有多种格式，横竖、格式，这里针对的是横排单图片文件是“-+--”格式(nPicStyle=1)。
	void SetTex(GLuint texNum);
public:
	CzxcSkyBox(GLfloat SkyWidth, string Lpic, string Rpic, string Fpic, string Bpic, string Tpic, string Dpic); // 6张图片方式的初始化函数,5张就是没地面的形式
	void ShowSky(void);
};

#endif
#ifndef BMPLOAD_H_INCLUDE
#define BMPLOAD_H_INCLUDE

//!!!!!!!#pragma pack(1) tells compiler to align with 1 byte
#pragma pack(1)

#include <cstring>
#include <string> 
#include <math.h>   
#include <stdio.h>   
#include <stdlib.h>   
#include <malloc.h>
#include "glut.h"

#define   WIDTHBYTES(bits) (((bits)+31)/32*4)

typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef long LONG;


//位图文件头信息结构定义,14字节
//其中不包含文件类型信息（由于结构体的内存结构决定，要是加了的话将不能正确读取文件信息）

typedef struct tagBITMAPFILEHEADER_BMP {
	DWORD bfSize;           //文件大小
	WORD   bfReserved1; 	//保留字，不考虑
	WORD   bfReserved2; 	//保留字，同上
	DWORD bfOffBits;        //实际位图数据的偏移字节数，即前三个部分长度之和
} BITMAPFILEHEADER_BMP; 


//信息头BITMAPINFOHEADER，也是一个结构，其定义如下：
typedef struct tagBITMAPINFOHEADER_BMP{
	//public:
	DWORD   biSize;         	//指定此结构体的长度，为40
	LONG    biWidth;       		//位图宽
	LONG    biHeight;       	//位图高
	WORD    biPlanes;       	//平面数，为1
	WORD    biBitCount;     	//采用颜色位数，可以是1，2，4，8，16，24，新的可以是32
	DWORD   biCompression;  	//压缩方式，可以是0，1，2，其中0表示不压缩
	DWORD   biSizeImage;    	//实际位图数据占用的字节数
	LONG    biXPelsPerMeter;	//X方向分辨率
	LONG    biYPelsPerMeter;	//Y方向分辨率
	DWORD   biClrUsed;      	//使用的颜色数，如果为0，则表示默认值(2^颜色位数)
	DWORD   biClrImportant; 	//重要颜色数，如果为0，则表示所有颜色都是重要的
} BITMAPINFOHEADER_BMP; 


//调色板Palette，当然，这里是对那些需要调色板的位图文件而言的。24位和32位是不需要调色板的。
//（似乎是调色板结构体个数等于使用的颜色数。）

typedef struct tagRGBQUAD_BMP { 
	//public:
	BYTE     rgbBlue; //该颜色的蓝色分量
	BYTE     rgbGreen; //该颜色的绿色分量
	BYTE     rgbRed; //该颜色的红色分量
	BYTE     rgbReserved; //保留值
} RGBQUAD_BMP;

typedef struct 
{
	WORD    iwidth;    //位图宽
	WORD    iheight;   //位图高
	BYTE    *pByte;		//图片数据指针
}BMPPic;

void showBmpHead(BITMAPFILEHEADER_BMP* pBmpHead);
void showBmpInforHead(tagBITMAPINFOHEADER_BMP* pBmpInforHead);
void showRgbQuan(tagRGBQUAD_BMP* pRGB);
BMPPic *ZXCLoadBMP(const char *szFileName);

typedef struct
{
	GLbyte	identsize;              // Size of ID field that follows header (0)
	GLbyte	colorMapType;           // 0 = None, 1 = paletted
	GLbyte	imageType;              // 0 = none, 1 = indexed, 2 = rgb, 3 = grey, +8=rle
	unsigned short	colorMapStart;          // First colour map entry
	unsigned short	colorMapLength;         // Number of colors
	unsigned char 	colorMapBits;   // bits per palette entry
	unsigned short	xstart;                 // image x origin
	unsigned short	ystart;                 // image y origin
	unsigned short	width;                  // width in pixels
	unsigned short	height;                 // height in pixels
	GLbyte	bits;                   // bits per pixel (8 16, 24, 32)
	GLbyte	descriptor;             // image descriptor
} TGAHEADER;

GLbyte *gltLoadTGA(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat);

#endif // BMPLOAD_H_INCLUDE

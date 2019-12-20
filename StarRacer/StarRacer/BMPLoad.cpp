#include "pch.h"
#include "BMPLoad.h"
#define _CRT_SECURE_NO_WARNINGS

void showBmpHead(BITMAPFILEHEADER* pBmpHead)
{
	printf("位图文件头:\n");
	printf("文件大小:%d\n",pBmpHead->bfSize);
	printf("保留字:%d\n",pBmpHead->bfReserved1);
	printf("保留字:%d\n",pBmpHead->bfReserved2);
	printf("实际位图数据的偏移字节数:%d\n",pBmpHead->bfOffBits);

}


void showBmpInforHead(tagBITMAPINFOHEADER* pBmpInforHead)
{
	printf("位图信息头:\n");
	printf("结构体的长度:%d\n",pBmpInforHead->biSize);
	printf("位图宽:%d\n",pBmpInforHead->biWidth);
	printf("位图高:%d\n",pBmpInforHead->biHeight);
	printf("biPlanes平面数:%d\n",pBmpInforHead->biPlanes);
	printf("biBitCount采用颜色位数:%d\n",pBmpInforHead->biBitCount);
	printf("压缩方式:%d\n",pBmpInforHead->biCompression);
	printf("biSizeImage实际位图数据占用的字节数:%d\n",pBmpInforHead->biSizeImage);
	printf("X方向分辨率:%d\n",pBmpInforHead->biXPelsPerMeter);
	printf("Y方向分辨率:%d\n",pBmpInforHead->biYPelsPerMeter);
	printf("使用的颜色数:%d\n",pBmpInforHead->biClrUsed);
	printf("重要颜色数:%d\n",pBmpInforHead->biClrImportant);
}

void showRgbQuan(tagRGBQUAD* pRGB)
{ 
	printf("(%-3d,%-3d,%-3d)   ",pRGB->rgbRed,pRGB->rgbGreen,pRGB->rgbBlue);
}

BMPPic *ZXCLoadBMP(const char *szFileName)
{
	static BMPPic pic={0,0,NULL};
	BITMAPFILEHEADER   bitHead;
	BITMAPINFOHEADER bitInfoHead; 
	FILE* pfile;

	//char strFile[50];
	//printf("please input the .bmp file name:\n");
	//scanf("%s",strFile);

	fopen_s(&pfile, szFileName,"rb");//打开文件

	if(pfile!=NULL)
	{
	   // printf("file bkwood.bmp open success.\n");
	   //读取位图文件头信息
	   WORD fileType;
	   fread(&fileType,1,sizeof(WORD),pfile);
	   if(fileType != 0x4d42)
	   {
		//printf("file is not .bmp file!");
		return NULL;
	   }
	   //fseek(pfile,2,SEEK_CUR);   // "BM"
	   fread(&bitHead,sizeof(tagBITMAPFILEHEADER),1,pfile);
  
	   //showBmpHead(&bitHead);
	   printf("\n\n");

	   //读取位图信息头信息
	   fread(&bitInfoHead,sizeof(BITMAPINFOHEADER),1,pfile);
	   //showBmpInforHead(&bitInfoHead);
	   printf("\n");
	}
	else
	{
	   printf("file open fail!\n");
	   return NULL;
	}


	tagRGBQUAD *pRgb ;

	if(bitInfoHead.biBitCount < 24)//有调色板 *******************************************************
	{ 
	   //读取调色盘结信息
	   long nPlantNum = long(pow(2,double(bitInfoHead.biBitCount)));    //   Mix color Plant Number;
	   pRgb=(tagRGBQUAD *)malloc(nPlantNum*sizeof(tagRGBQUAD)); 
	   memset(pRgb,0,nPlantNum*sizeof(tagRGBQUAD));
	   int num = fread(pRgb,4,nPlantNum,pfile);
  
	   printf("Color Plate Number: %d\n",nPlantNum);

	   printf("颜色板信息:\n");
	   for (int i =0; i<nPlantNum;i++)
	   {
		if (i%5==0)
		{
		 printf("\n");
		}
		showRgbQuan(&pRgb[i]);
	   }
	   printf("\n");
	}

	// 24位、32位位图*********************************************************************************
	int width = bitInfoHead.biWidth;
	int height = bitInfoHead.biHeight;
	pic.iwidth = width;
	pic.iheight = height;
	
	//分配内存空间把源图存入内存   
//	int l_width   = WIDTHBYTES(width* bitInfoHead.biBitCount);//计算位图的实际宽度并确保它为32的倍数,看BMPLoad.h中的#define，实现4字节对齐!!!!!!!
	int l_width   = WIDTHBYTES(width)*height;//计算位图的实际宽度并确保它为32的倍数,看BMPLoad.h中的#define，实现4字节对齐!!!!!!!
	pic.pByte = (BYTE *)malloc(height*l_width); 
	memset(pic.pByte,0,height*l_width);   
	long nData = height*l_width;

	//把位图数据信息读到数组里   
	fread(pic.pByte,1,nData,pfile);   
    
	return &pic;
}

GLbyte *gltLoadTGA(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat)
{
	FILE *pFile;			// File pointer
	TGAHEADER tgaHeader;		// TGA file header
	unsigned long lImageSize;		// Size in bytes of image
	short sDepth;			// Pixel depth;
	GLbyte	*pBits = NULL;          // Pointer to bits

	// Default/Failed values
	*iWidth = 0;
	*iHeight = 0;
	*eFormat = GL_BGR_EXT;
	*iComponents = GL_RGB8;

	// Attempt to open the fil
	fopen_s(&pFile, szFileName, "rb");
	if (pFile == NULL)
		return NULL;
	// Read in header (binary)
	fread(&tgaHeader, 18/* sizeof(TGAHEADER)*/, 1, pFile);

	// Get width, height, and depth of texture
	*iWidth = tgaHeader.width;
	*iHeight = tgaHeader.height;
	sDepth = tgaHeader.bits / 8;

	// Put some validity checks here. Very simply, I only understand
	// or care about 8, 24, or 32 bit targa's.
	if (tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32)
		return NULL;

	// Calculate size of image buffer
	lImageSize = tgaHeader.width * tgaHeader.height * sDepth;

	// Allocate memory and check for success
	pBits = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));
	if (pBits == NULL)
		return NULL;

	// Read in the bits
	// Check for read error. This should catch RLE or other 
	// weird formats that I don't want to recognize
	if (fread(pBits, lImageSize, 1, pFile) != 1)
	{
		free(pBits);
		return NULL;
	}

	// Set OpenGL format expected
	switch (sDepth)
	{
	case 3:     // Most likely case
		*eFormat = GL_BGR_EXT;
		*iComponents = GL_RGB8;
		break;
	case 4:
		*eFormat = GL_BGRA_EXT;
		*iComponents = GL_RGBA8;
		break;
	case 1:
		*eFormat = GL_LUMINANCE;
		*iComponents = GL_LUMINANCE8;
		break;
	};


	// Done with File
	fclose(pFile);

	// Return pointer to image data
	return pBits;
}

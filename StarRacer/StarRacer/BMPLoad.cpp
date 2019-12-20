#include "pch.h"
#include "BMPLoad.h"
#define _CRT_SECURE_NO_WARNINGS

void showBmpHead(BITMAPFILEHEADER* pBmpHead)
{
	printf("λͼ�ļ�ͷ:\n");
	printf("�ļ���С:%d\n",pBmpHead->bfSize);
	printf("������:%d\n",pBmpHead->bfReserved1);
	printf("������:%d\n",pBmpHead->bfReserved2);
	printf("ʵ��λͼ���ݵ�ƫ���ֽ���:%d\n",pBmpHead->bfOffBits);

}


void showBmpInforHead(tagBITMAPINFOHEADER* pBmpInforHead)
{
	printf("λͼ��Ϣͷ:\n");
	printf("�ṹ��ĳ���:%d\n",pBmpInforHead->biSize);
	printf("λͼ��:%d\n",pBmpInforHead->biWidth);
	printf("λͼ��:%d\n",pBmpInforHead->biHeight);
	printf("biPlanesƽ����:%d\n",pBmpInforHead->biPlanes);
	printf("biBitCount������ɫλ��:%d\n",pBmpInforHead->biBitCount);
	printf("ѹ����ʽ:%d\n",pBmpInforHead->biCompression);
	printf("biSizeImageʵ��λͼ����ռ�õ��ֽ���:%d\n",pBmpInforHead->biSizeImage);
	printf("X����ֱ���:%d\n",pBmpInforHead->biXPelsPerMeter);
	printf("Y����ֱ���:%d\n",pBmpInforHead->biYPelsPerMeter);
	printf("ʹ�õ���ɫ��:%d\n",pBmpInforHead->biClrUsed);
	printf("��Ҫ��ɫ��:%d\n",pBmpInforHead->biClrImportant);
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

	fopen_s(&pfile, szFileName,"rb");//���ļ�

	if(pfile!=NULL)
	{
	   // printf("file bkwood.bmp open success.\n");
	   //��ȡλͼ�ļ�ͷ��Ϣ
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

	   //��ȡλͼ��Ϣͷ��Ϣ
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

	if(bitInfoHead.biBitCount < 24)//�е�ɫ�� *******************************************************
	{ 
	   //��ȡ��ɫ�̽���Ϣ
	   long nPlantNum = long(pow(2,double(bitInfoHead.biBitCount)));    //   Mix color Plant Number;
	   pRgb=(tagRGBQUAD *)malloc(nPlantNum*sizeof(tagRGBQUAD)); 
	   memset(pRgb,0,nPlantNum*sizeof(tagRGBQUAD));
	   int num = fread(pRgb,4,nPlantNum,pfile);
  
	   printf("Color Plate Number: %d\n",nPlantNum);

	   printf("��ɫ����Ϣ:\n");
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

	// 24λ��32λλͼ*********************************************************************************
	int width = bitInfoHead.biWidth;
	int height = bitInfoHead.biHeight;
	pic.iwidth = width;
	pic.iheight = height;
	
	//�����ڴ�ռ��Դͼ�����ڴ�   
//	int l_width   = WIDTHBYTES(width* bitInfoHead.biBitCount);//����λͼ��ʵ�ʿ�Ȳ�ȷ����Ϊ32�ı���,��BMPLoad.h�е�#define��ʵ��4�ֽڶ���!!!!!!!
	int l_width   = WIDTHBYTES(width)*height;//����λͼ��ʵ�ʿ�Ȳ�ȷ����Ϊ32�ı���,��BMPLoad.h�е�#define��ʵ��4�ֽڶ���!!!!!!!
	pic.pByte = (BYTE *)malloc(height*l_width); 
	memset(pic.pByte,0,height*l_width);   
	long nData = height*l_width;

	//��λͼ������Ϣ����������   
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

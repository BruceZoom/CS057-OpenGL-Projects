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
//	int l_width   = WIDTHBYTES(width* bitInfoHead.biBitCount);//����λͼ��ʵ�ʿ��Ȳ�ȷ����Ϊ32�ı���,��BMPLoad.h�е�#define��ʵ��4�ֽڶ���!!!!!!!
	int l_width   = WIDTHBYTES(width)*height;//����λͼ��ʵ�ʿ��Ȳ�ȷ����Ϊ32�ı���,��BMPLoad.h�е�#define��ʵ��4�ֽڶ���!!!!!!!
	pic.pByte = (BYTE *)malloc(height*l_width); 
	memset(pic.pByte,0,height*l_width);   
	long nData = height*l_width;

	//��λͼ������Ϣ����������   
	fread(pic.pByte,1,nData,pfile);   
    
	return &pic;
}
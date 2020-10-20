#ifndef __R61505V_H
#define __R61505V_H

//---����ͷ�ļ�---//
#include<reg51.h>

//---�ض���ؼ���---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint  unsigned int
#endif

//---����ʹ�õ�IO��---//
sbit	  TFT_RST = P3^3;  	//��λ
sbit	  TFT_CS  = P2^7;	//Ƭѡ
sbit	  TFT_RS  = P2^6;	//��������ѡ���
sbit	  TFT_WR  = P2^5;	//��д����
sbit      TFT_RD  = P3^2;   //��д����

#define   TFT_DATAPORTH  P1 //���ø�8λ����
#define   TFT_DATAPORTL  P0 //���õ�8λ����

//---�������Ĵ�С---//
#define TFT_XMAX 175//		//����TFT���Ĵ�С
#define TFT_YMAX 219//

//---����ȫ�ֱ���---//
void TFT_WriteCmd(uint cmd);
void TFT_WriteData(uint dat);
void TFT_WriteCmdData(uint cmd, uint dat);
void TFT_Init(void);
void TFT_SetWindow(uint xStart, uint yStart, uint xEnd, uint yEnd);
void TFT_ClearScreen(uint color);

#endif


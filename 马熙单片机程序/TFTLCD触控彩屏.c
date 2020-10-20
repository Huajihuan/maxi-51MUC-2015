#include"touch.h"

void TOUCH_SPI_Start(void)
{
	TOUCH_CLK = 0;
	TOUCH_CS  = 1;
	TOUCH_DIN = 1;
	TOUCH_CLK = 1;
	TOUCH_CS  = 0;		
}

void TOUCH_SPI_Write(uchar dat)
{
	uchar i;
	TOUCH_CLK = 0;
	for(i=0; i<8; i++)
	{
		TOUCH_DIN = dat >>7;  	//�������λ
		dat <<= 1;
		TOUCH_CLK = 0;			//�����ط�������

		TOUCH_CLK = 1;

	}
}

uint TOUCH_SPI_Read(void)
{
	uint i, dat=0;
	TOUCH_CLK = 0;
	for(i=0; i<12; i++)		//����12λ����
	{
		dat <<= 1;

		TOUCH_CLK = 1;
		TOUCH_CLK = 0;

		dat |= TOUCH_DOUT;

	}
	return dat;	
}

#define XY_READ_TIMS  10		   //��ȡ�Ĵ���

uint TOUCH_XPT_ReadData(uchar cmd)
{
	uchar i, j;
	uint readValue[XY_READ_TIMS];
	long endValue;

	TOUCH_CLK = 0;    //������ʱ��
	TOUCH_CS  = 0;    //ѡ��оƬ
	
	for(i=0; i<XY_READ_TIMS; i++)	 	//��ȡXY_READ_TIMS�ν��
	{	
		TOUCH_SPI_Write(cmd);  //����ת������
		//Delay_6us();
		for(j=6; j>0; j--); 	//��ʱ�ȴ�ת�����
		TOUCH_CLK = 1;	  //����һ��ʱ�����ڣ����BUSY
		_nop_();
		_nop_();
		TOUCH_CLK = 0;
		_nop_();
		_nop_();
	
		readValue[i] = TOUCH_SPI_Read();
	}
	TOUCH_CS = 1; //�ͷ�Ƭѡ

	//---����˲�---//
	//---�ȴ�С���򣬳�ȥ���ֵ����ȥ���ֵ������ƽ��ֵ---//
   	for(i=0; i<XY_READ_TIMS - 1; i++)	//�Ӵ�С����
	{
		for(j= i+1; j<XY_READ_TIMS; j++)
		{
			if(readValue[i] < readValue[j])
			{
				endValue = readValue[i];
				readValue[i] = readValue[j];
				readValue[j] = endValue;
			}  
		}
	}
//	if((readValue[2] - readValue[3]) > 5)
//	{
//		return 0;
//	}
	endValue = 0;
	for(i=2; i<XY_READ_TIMS-2; i++)		   
	{
		endValue += readValue[i]; 
	}
	endValue = endValue/ (XY_READ_TIMS - 4);//��ƽ��ֵ

	return endValue;
}


XPT_XY xpt_xy;	 //����һ��ȫ�ֱ�������X��Y��ֵ
uchar TOUCH_XPT_ReadXY(void)
{	
	uint x1, x2, x, y1, y2, y;

	TOUCH_SPI_Start();
	//---�ֱ������Xֵ��Yֵ, �����Ŷ��������һЩ��ȡ����---//
	x1 = TOUCH_XPT_ReadData(XPT_CMD_X);
	y1 = TOUCH_XPT_ReadData(XPT_CMD_Y);
	x2 = TOUCH_XPT_ReadData(XPT_CMD_X);
	y2 = TOUCH_XPT_ReadData(XPT_CMD_Y);

	//---��ȡXֵ�Ĳ�ֵ---//
	if (x1 > x2)
	{
		x = x1 - x2;
	}
	else
	{
		x = x2 - x1;
	}

	//---��ȡYֵ�Ĳ�ֵ---//
	if (y1 > y2)
	{
		y = y1 - y2;
	}
	else
	{
		y = y2 - y1;
	}

	//---�жϲ�ֵ�Ƿ����50�����ھͷ���0����ʾ��ȡʧ��---//
	if((x > 50) || (y > 50))  
	{
		return 0;
	}

	//---��ȡ���ζ�ȡֵ��ƽ������Ϊ��ȡ����XYֵ---//
	xpt_xy.x = (x1 + x2) / 2;
	xpt_xy.y = (y1 + y2) / 2;

	xpt_xy.x &= 0xFFF0;	//ȥ������λ
	xpt_xy.y &= 0xFFF0;
	 
	//---ȷ��XYֵ�ķ�Χ�����ڴ���������TFTʱ---//
	if((xpt_xy.x < 100) || (xpt_xy.y > 3800))
	{
		return 0;
	}

	return 1;  // ����1����ʾ��ȡ�ɹ�
}



#include"r61505v.h"

/****************************************************************************
*��������TFT_WriteCmd
*��  �룺cmd
*��  ����
*��  �ܣ�д���
****************************************************************************/	  

void TFT_WriteCmd(uint cmd)
{
	uchar cmdH, cmdL;
	
	cmdH = cmd >> 8;
	cmdL = cmd & 0x00FF;  //�Ƚ������ݻ��㣬תΪ8λ��

	TFT_WR = 1;	 		  //��ʼ��WR
	TFT_CS = 0;			  //��Ƭѡ
	TFT_RS = 0;			  //ѡ������
	TFT_RD = 1;           //ѡ��д

	TFT_DATAPORTH = cmdH; //������������
	TFT_DATAPORTL = cmdL;

	TFT_WR = 0;			  //д��ʱ��
	TFT_WR = 1;

	TFT_CS = 1;			  //�ر�Ƭѡ
}

/****************************************************************************
*��������TFT_WriteData
*��  �룺dat
*��  ����
*��  �ܣ�д���ݡ�
****************************************************************************/	  

void TFT_WriteData(uint dat)
{
	uchar datH, datL;
	datH = dat >> 8;
	datL = dat & 0x00FF;  //�Ƚ������ݻ��㣬תΪ8λ��

	TFT_WR = 1;	 		  //��ʼ��WR
	TFT_CS = 0;			  //��Ƭѡ
	TFT_RS = 1;			  //ѡ��������
	TFT_RD = 1;           //ѡ��д

	TFT_DATAPORTH = datH; //������������
	TFT_DATAPORTL = datL;

	TFT_WR = 0;			  //д��ʱ��
	TFT_WR = 1;

	TFT_CS = 1;			  //�ر�Ƭѡ
}

/****************************************************************************
*��������TFT_WriteCmdData
*��  �룺cmd, dat
*��  ����
*��  �ܣ�д��� д���ݡ�
****************************************************************************/	  

void TFT_WriteCmdData(uint cmd, uint dat)
{
	TFT_WriteCmd(cmd);
	TFT_WriteData(dat);
}

/****************************************************************************
*��������TFT_Init
*��  �룺
*��  ����
*��  �ܣ���ʼ��TFT��
****************************************************************************/	  

void TFT_Init(void)
{
	uint i;

	TFT_RST = 1;
	for(i=500; i>0; i--);
	TFT_RST = 0;
	for(i=500; i>0; i--);
	TFT_RST = 1;
	for(i=5000; i>0; i--);
	
	TFT_CS = 0;

 	TFT_WriteCmdData(0x0000, 0x0001);
	TFT_WriteCmdData(0x0000, 0x0000);			
	TFT_WriteCmdData(0x0000, 0x0000);       
	TFT_WriteCmdData(0x0000, 0x0001);

	for(i=5000; i>0; i--);

//--------GAMMA SETTINGS---------
	TFT_WriteCmdData(0x0008, 0x0808); 
	TFT_WriteCmdData(0x0018 ,0x0001);			
	TFT_WriteCmdData(0x0010, 0x11B0);			
	TFT_WriteCmdData(0x0011, 0x0000);
	TFT_WriteCmdData(0x0012, 0x1115);
	TFT_WriteCmdData(0x0013, 0x8B0B);
	TFT_WriteCmdData(0x0012, 0x1135);			
	TFT_WriteCmdData(0x0014, 0x8000);
	TFT_WriteCmdData(0x0001, 0x0100);
	TFT_WriteCmdData(0x0002, 0x0700); 
	TFT_WriteCmdData(0x0003, 0x1030);
	TFT_WriteCmdData(0x0070, 0x1B00);

	TFT_WriteCmdData(0x0071, 0x0001);
	TFT_WriteCmdData(0x0090, 0x0002);           
	TFT_WriteCmdData(0x0091, 0x0000);
	TFT_WriteCmdData(0x0092, 0x0001);
	TFT_WriteCmdData(0x0007, 0x0001);
	for(i=5000; i>0; i--);

	TFT_WriteCmdData(0x0007, 0x0021);
	for(i=5000; i>0; i--);

	TFT_WriteCmdData(0x0012, 0x1135);                  
	TFT_WriteCmdData(0x0007, 0x0233);                 
			
	TFT_WriteCmd(0x0022);
	
}

/****************************************************************************
*��������TFT_SetWindow
*��  �룺xStart, yStart, xEnd, yEnd
*��  ����
*��  �ܣ�����Ҫ�����Ĵ��ڡ�
****************************************************************************/	  

void TFT_SetWindow(uint xStart, uint yStart, uint xEnd, uint yEnd)
{
	

	TFT_WriteCmdData(0x0050, xStart);	 //ˮƽ����ʼ
	TFT_WriteCmdData(0x0052, yStart);	 //��ֱ����ʼ
	TFT_WriteCmdData(0x0051, xEnd);	 //ˮƽ�߽���
	TFT_WriteCmdData(0x0053, yEnd);	 //��ֱ�߽���

	TFT_WriteCmdData(0x0020, xEnd);
	TFT_WriteCmdData(0x0021, yEnd);

	TFT_WriteCmd(0x0022);	
}

/****************************************************************************
*��������GUI_Clearcreen
*��  �룺backColor
*��  ����
*��  �ܣ�������Ϳ����ɫ��
****************************************************************************/
	  
void TFT_ClearScreen(uint color)
{
  	uint i, j;

	TFT_SetWindow(0, 0, TFT_XMAX, TFT_YMAX);	 //��������
  	for(i=0; i<TFT_XMAX+1; i++)
	{
		for (j=0; j<TFT_YMAX+1; j++)
		{
			TFT_WriteData(color);
		}

	}
}
#include<reg51.h>
#include"gui.h"
#include"touch.h"

void main(void)
{
	uchar rst = 0;
	//--���������ֵʹ�������ڴ��������ı����ָ���--//
	uchar  xValue[6] = {0, 0, 0, 0, 0, 0}, yValue[6] = {0, 0, 0, 0, 0, 0};
	long x, y;

	TFT_Init();
	rst = 1;

	while(1)
	{
		if(rst == 1)
		{	
			TFT_ClearScreen(0x0000);
			GUI_Write32CnChar(20, 24, "���пƼ�", 0xF800, 0x0000);
			GUI_Line(20, 54, 140, 54, 0xF800);
			GUI_Line(20, 54, 140, 54, 0xF800);
			GUI_WriteASCII(127, 0, "RST", 0xF800, 0x0000);
			rst = 0;
		}

		if(TOUCH_XPT_ReadXY() == 1)
		{
			//--�����������ʾ����ƫ�ƣ����Ը�����ʾADֵ--//
			//--�������湫ʽ�������ֵ--//
			x = xpt_xy.x;
			x = (x - 100) * 454 / 10000 ; 
			y =	xpt_xy.y;
			y = (y - 240) * 628 / 10000;

			if (x > 175 )
			{
				x = 175;
			}
			if (y > 219)
			{
				y = 219;
			}
			if ((x > 127) && (y < 24))
			{
				rst = 1;
			}
			else
			{
				GUI_Dot((uint)x , (uint)y, 0x001F);
			}
		}
	}
}
#include"gui.h"

//---���ֵ��ֿ�ͷ�ļ�---//
#include"charcode.h"

//---���Ҫ��ʾͼƬ��������ͷ�ļ�---//
#ifdef PICTURE_SHOW

#include"picture.h"

#endif

/****************************************************************************
*��������GUI_Dot
*��  �룺x�����X���ꣻ
*      * y�����Y����
*      * color�������ɫ
*��  ����
*��  �ܣ�����������Ϳ����ɫ��
****************************************************************************/	  

void GUI_Dot(uint x, uint y, uint color)
{  
	uchar i;

	TFT_SetWindow(x-1, y, x+2, y+2);  //��������

	for(i=0; i<16; i++)
	{
		TFT_WriteData(color);
	}
}

///****************************************************************************
//*��������GUI_Box
//*��  �룺sx����ʼX����, sy����ʵY����, 
//*      * ex����ֹX����, ey����ֹY����,
//*      * color���������ɫ
//*��  ����
//*��  �ܣ���һ������Ϳ����ɫ��
//****************************************************************************/	  
//void GUI_Box(uint sx, uint sy, uchar ex, uint ey, uint color)
//{ 
//	uint temp;   
//	TFT_SetWindow(sx, sy, ex, ey); 
//  sx = ex - sx + 1;
//	sy = ey - sy + 1;
//	while (sx--)
//	{
//	 	temp = sy;
//		while (temp--)
//	 	{	
//			TFT_WriteData(color);
//		}
//	}
//}

/****************************************************************************
*��������GUI_Line 
*��  �룺xStart���ߵ���ʼX����,
*      * yStart���ߵ���ʵY����,
*      * xEnd���ߵ���ֹX����,
*      * yEnd���ߵ���ֹY����,
*      * color����������ɫ
*��  ����
*��  �ܣ���һ��ֱ��
****************************************************************************/	  

void GUI_Line(uint xStart, uint yStart, uchar xEnd, uint yEnd, uint color)
{
	uint t;  
	int xerr = 0, yerr = 0, delta_x, delta_y, distance;  
	int incx, incy;  
	uint row, col;  
	delta_x = xEnd - xStart;//������������  
	delta_y = yEnd - yStart;  
	col = xStart;  
	row = yStart;  
	if (delta_x > 0)
	{
		incx=1;//���õ�������
	} 	  
	else    
	{  
	    if (delta_x == 0)
		{
			incx = 0;//��ֱ�� 
		} 		 
	    else 
			{
				incx = -1;
				delta_x = -delta_x;
			}  
	}  
	if (delta_y > 0)
	{
		incy = 1;
	}	  
	else  
	{  
	    if (delta_y == 0)
		{
			incy = 0;//ˮƽ��  
		} 
	    else 
		{
			incy = -1;
			delta_y = -delta_y;
		}  
	}  
	if (delta_x > delta_y)
	{ 
		distance = delta_x;//ѡȡ��������������  
	}
	else
	{
		distance = delta_y; 
	} 	
	for (t=0; t<=distance+1; t++)  
	{                                     //�������  
	    GUI_Dot(col, row, color);
	    xerr += delta_x;  
	    yerr += delta_y;  
	  	if(xerr > distance)  
	    {  
	        xerr -= distance;  
	        col += incx;  
	    }  
	    if(yerr > distance)  
	    {  
	        yerr -= distance;  
	        row += incy;  
	    }  
	}  
}

/****************************************************************************
*��������GUI_WriteCnChar 
*��  �룺x����ʾ��ʼX����
*      * y����ʾ��ʼY����
*      * *cn��Ҫ��ʾ���ַ���
*      * wordColor���������ɫ
*      * backColor��������ɫ
*��  ����
*��  �ܣ�д���ſ��庺��
****************************************************************************/	  

#ifdef CHAR32_SHOW

void GUI_Write32CnChar(uint x, uint y, uchar *cn, uint wordColor, uint backColor)	 
{  
	uchar i, j, wordNum;
	uint color;
	while (*cn != '\0')
	{
		TFT_SetWindow(x, y, x+31, y+28);
		for (wordNum=0; wordNum<20; wordNum++)
		{	//wordNumɨ���ֿ������
			if ((CnChar32x29[wordNum].Index[0]==*cn)
			     &&(CnChar32x29[wordNum].Index[1]==*(cn+1)))
			{
				for(i=0; i<116; i++) 
				{	//MSK��λ��
					color=CnChar32x29[wordNum].Msk[i];
					for(j=0;j<8;j++) 
					{
						if((color&0x80)==0x80)
						{
							TFT_WriteData(wordColor);
						} 						
						else
						{
							TFT_WriteData(backColor);
						} 
						color<<=1;
					}//for(j=0;j<8;j++)����
				}    
			}
		} //for (wordNum=0; wordNum<20; wordNum++)���� 	
		cn += 2;
		x += 32;
	}
}
#endif

/****************************************************************************
*��������GUI_WriteEnChar 
*��  �룺x����ʾ��ʼX����
*      * y����ʾ��ʼY����
*      * *cn��Ҫ��ʾ���ַ���
*      * wordColor���������ɫ
*      * backColor��������ɫ
*��  ����
*��  �ܣ�д�ĺ�����ĸ
****************************************************************************/	  
#ifdef CHAR14_SHOW

void GUI_Write14CnChar(uint x,uint y,uchar *cn,uint wordColor,uint backColor)	 
{  
	uchar i, j, wordNum;
	uint color;
	while (*cn != '\0')
	{
		TFT_SetWindow(x, y, x+23, y+18);
		for (wordNum=0; wordNum<20; wordNum++)
		{	//wordNumɨ���ֿ������
			if ((CnChar19x24[wordNum].Index[0]==*cn)
			     &&(CnChar19x24[wordNum].Index[1]==*(cn+1)))
			{
				for(i=0; i<57; i++) 
				{	//MSK��λ��
					color=CnChar19x24[wordNum].Msk[i];
					for(j=0;j<8;j++) 
					{
						if((color&0x80)==0x80)
						{
							TFT_WriteData(wordColor);
						} 						
						else
						{
							TFT_WriteData(backColor);
						} 
						color<<=1;
					}//for(j=0;j<8;j++)����
				}    
			}
		} //for (wordNum=0; wordNum<20; wordNum++)���� 	
		cn += 2;
		x += 24;
	}
}

#endif 
/****************************************************************************
*��������GUI_WriteASCII 
*��  �룺x����ʾ��ʼX����
*      * y����ʾ��ʼY����
*      * *p��Ҫ��ʾ���ַ���
*      * wordColor���������ɫ
*      * backColor��������ɫ
*��  ����
*��  �ܣ�д16X24��ASCII�ַ�
****************************************************************************/	  

#ifdef USE_ASCII

void GUI_WriteASCII(uint x, uint y, uchar *p, uint wordColor, uint backColor)
{
	uchar j, wordByte,wordNum;
	uint color;
	while(*p != '\0')
	{
		wordNum = *p - 32;
		TFT_SetWindow(x,y,x+15, y+23);
		for (wordByte=0; wordByte<48; wordByte++)
		{
			color = ASCII16x24[wordNum][wordByte];
			for (j=0; j<8; j++) 
			{
				if ((color&0x80) == 0x80)
				{
					TFT_WriteData(wordColor);
				} 						
				else
				{
					TFT_WriteData(backColor);
				} 	
				color <<= 1;
			}
		}
		p++;
		x +=16;
	}
}
#endif

/****************************************************************************
*��������GUI_ShowPicture 
*��  �룺x����ʾ��ʼX����
*      * y����ʾ��ʼY����
*      * wide��ͼƬ�Ŀ��
*      * high��ͼƬ�ĸ߶�
*��  ����
*��  �ܣ���һ��ֱ��
****************************************************************************/	  
#ifdef PICTURE_SHOW

void GUI_ShowPicture(uint x, uint y, uchar wide, uint high)
{
	uint temp = 0, tmp = 0, num = 0;
	TFT_SetWindow(x, y, x+wide-1, y+high-1);
	num = wide * high * 2;
	do
	{  
		temp = pic[tmp + 1];
		temp = temp << 8;
		temp = temp | pic[tmp];
		TFT_WriteData(temp);//�����ʾ
		tmp += 2;
	}
	while(tmp < num);	
}

#endif
















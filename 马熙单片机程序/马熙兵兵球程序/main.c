/*******************************************************************/
/*                      ƹ������Ϸ��ʾ����                     */
/*                                                                 */
/* Ӳ��ƽ̨: TOP51+12LE5A60S2   ����22.1184MHZ                 */ 
/* ���ƽ̨: KEIL C51                                            */
/* ˵���� ��SW0��SW1��������λ�ã�������Ĳ��ܽӵ��򣬾�ʧ��*/ 
/* TFT����ģ���12LE5A60S2�����ӣ�                   	*/
/* TFT_RS������/�����4�ţ�		---- P1.0          	*/
/* TFT_WR��д����5�ţ� 				---- P1.1   		*/
/* TFT_RD��������6�ţ�   			---- P4.6   		*/
/* TFT_CS��Ƭѡ����15�ţ�  			---- P4.5         	*/
/* TFT_RST����λ����17�ţ� 			---- P4.4       	*/
/* TFT_DATA��8λ���ݿڣ���7--14�ţ�	---- P0   			*/
/* ��˾: ��������                                                   */
/* ��ַ��http://www.ajdz.net                                        */
/* ����              		����         		ע��                  */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* ��ΰ��            2010-5-4          ԭʼ����*/

#include "stc.h"/*����STC��Ƭ��ͷ�ļ�*/
#include "top51.h"/*����TOP51������ͷ�ļ�*/
#include "LCM/ILI9325.h"/*����TFT������������ͷ�ļ�*/
#include "GUI/gui.h"/*�������������ṩGUI����ͷ�ļ�*/
#include "delay.h"/*�������������ṩ��ʱ����ͷ�ļ�*/
//#include "uart.h"/*�������������ṩ������غ���ͷ�ļ�*/

unsigned char x=71,dir=1;
unsigned int y=166;

unsigned char racket_x=20;
unsigned char racket_dir;
#define RACKET_HALF_LENGTH 20/*�������İ볤��*/

void main(void)
{
	top51_init();/*top51�����ʼ��*/
	delayms(20);
		
	ILI9325_initial();/*TFT������ʼ��*/
	delayms(20);

	GUI_clearscreen(0);//����

	COL0=1;/*ѡ��4λ����ܵ����ұ�һλ����ʹSW0-SW2����Ϊ��������ʹ��*/
	P0=0;/*����ܲ���ʾ*/
	
	TMOD=0x11;/*���ö�ʱ��0��1Ϊ������ʽ1*/

	TH0=0xac;/*T0�����ó�ֵ*/
	TL0=0;


	ET0=1;/*����ʱ��0�ж�*/
	ET1=1;/*����ʱ��1�ж�*/
	EA=1;/*�����ж�*/

	TR0=1;/*������ʱ��0*/
	TR1=1;/*ֹͣ��ʱ��1*/

	GUI_line(racket_x-RACKET_HALF_LENGTH,219,racket_x+RACKET_HALF_LENGTH,219,0xffff);/*��������*/

	while(1)
	{
		if (SW1==0) 
		{
			TR1=1;/*������ʱ��1*/
			racket_dir=0;/*���ĳ����˶�*/
		}
		/*���SW0���£�*/
		else if (SW2==0)/*���SW1���£�*/
		{
			TR1=1;/*������ʱ��1*/
			racket_dir=1;/*���ĳ����˶�*/
		}
		else 
		{
			TR1=0;/*ֹͣ��ʱ��1*/
			TH1=0Xff;/*��֤���¼�ʱ����Ӧʱ����̣���ʵ�ֶ԰����Ŀ�����Ӧ*/
			TL1=0Xff;
		}
	}
}


/*---�����˶��жϷ������---*/
void timer1 (void) interrupt 3
{
	TH1=0Xb8;/*T1�����ó�ֵ(10ms)*/
	TL1=0X00;
	COL0=0;
	if (racket_dir==0)
	{
		racket_x--;
		if (racket_x<RACKET_HALF_LENGTH) racket_x=RACKET_HALF_LENGTH;
		GUI_Point(racket_x+RACKET_HALF_LENGTH+1, 219, 0);/*����*/
		GUI_Point(racket_x-RACKET_HALF_LENGTH, 219, 0XFFFF);/*����*/
	}
	else 
	{
		racket_x++;
		if (racket_x>239-RACKET_HALF_LENGTH) racket_x=175-RACKET_HALF_LENGTH;
		GUI_Point(racket_x-RACKET_HALF_LENGTH-1, 219, 0);/*����*/
		GUI_Point(racket_x+RACKET_HALF_LENGTH, 219, 0XFFFF);/*����*/
	}
	P0=0;
	COL0=1;
}


/*---С���˶��жϷ������---*/
void Timer0_Routine(void) interrupt 1
{
	unsigned char n;
	TH0=0xb8;/*T0�����ó�ֵ(10ms)*/
	TL0=0;

	COL0=0;
	GUI_Point(x, y, 0);/*����*/

	/*���˶�����һλ��*/
	switch (dir)
	{
		case 1:	x++;y--;break;/*����1�˶�*/
		case 2:	x--;y--;break;/*����2�˶�*/
		case 3:	x--;y++;break;/*����3�˶�*/
		case 4:	x++;y++;break;/*����4�˶�*/
	}

	GUI_Point(x, y, 0xffff);/*����*/
	/*�Ƿ������߽���,�������߽磬��ı��˶�����*/
	if (x==0)
	{
		if (dir==2)	dir=1;/*����1�˶�*/
			else dir=4;
	}
	if (x==175)
	{
		if (dir==1)	dir=2;/*����1�˶�*/
			else dir=3;
	}
	if (y==0)
	{
		if (dir==1)	dir=4;/*����1�˶�*/
			else dir=3;
	}
	if (y==218)
	{
		if ((x<racket_x+RACKET_HALF_LENGTH)&&(x>racket_x-RACKET_HALF_LENGTH))/*�ж��Ƿ����Ľ�ס*/
		{
			/*�����Ľ�ס*/
			if (dir==3)	dir=2;/*����1�˶�*/
			else dir=1;
		}
		else
		{
			/*û�б����Ľ�ס*/
			GUI_sprintf_string(84,140,"GAME OVER",0xcc88,0xBE5F); /*��ʾ��Ϸ����*/
			while(1);
		}
	}
	P0=0;
	COL0=1;
}




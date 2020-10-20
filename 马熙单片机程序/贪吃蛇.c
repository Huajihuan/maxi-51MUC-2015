#include<reg51.h>
#include"gui.h"
#include"R61505V.h"

void delay(uchar z) // �ӳٺ���
{
uchar y;
for(z;z>0;z--)
   for(y=0;y<110;y++);
}

//�����������֮����ɣ�������ô��������㻹��ʲô��
//��ͬ������Ҫ����TFTƾ����ɣ�������GUI������ص㡣
/*********************************************************************
 *
 *                          ̰������Ϸ���ĳ���
 *
 *********************************************************************
 * �ļ���: snake.c
 * ����: ̰������Ϸ���ĳ���
 * ��˾: ��������
 * ����              		����         			ע��
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * ��ΰ��				2010/3/20				ԭʼ�ļ�
 ********************************************************************/

//#include "stc.h"/*����STC��Ƭ��ͷ�ļ�*/
//#include "top51.h"/*����TOP51������ͷ�ļ�*/
#include "key_sweep.h"
//#include "LCM/ILI9325.h"
//#include "GUI/gui.h"
#include "snake.h"
//#include "delay.h"/*�������������ṩ��ʱ����ͷ�ļ�*/

//=================================================================
//    ʹ�ýṹ�嶨�����,ʹ����������
//=================================================================
struct 
{
	uchar X;	//ʳ��λ��
	uchar Y;			 
	uchar Yes;
}Food;	//����ʳ��ṹ��


struct 
{
	uchar X[SNAKE_MAX_LONG];
	uchar Y[SNAKE_MAX_LONG];
	uchar Long;  			//�ߵĳ���
	uchar Life; 			//�ߵ�����
	uchar Score;			//�ߵķ���
	uchar Level;			//�ߵĵȼ�              
}Snake;	//�����߽ṹ��

uchar Key_V_temp=Key_Right;     	//ȡ���ϴΰ���ֵ
uchar Over;     	//=1��ʾ���ֻ�ȫ���������


//=================================================================
//�������ƣ�void Init_time(void)
//�������ܣ���ʱ��0 : �����ߵ��˶��ٶ�
//��ʱ��1 : ���ڲ������������ �����ڷ���ʳ��
//��ڲ�������
//���ڲ�������
//=================================================================
void Init_time (void)
{
	TMOD=0x11;/*���ö�ʱ��0��1Ϊ������ʽ1*/
	TH0=0xb8;/*T0�����ó�ֵ*/
	TL0=0;
//	TH1=0X00;/*T1�����ó�ֵ*/
//	TL1=0X00;
	ET0=1;/*����ʱ��0�ж�*/
	//ET1=1;/*����ʱ��1�ж�*/
	EA=1;/*�����ж�*/
	TR0=1;/*������ʱ��0*/
	TR1=1;/*������ʱ��1*/
}

/*---�жϷ������---*/
void timer0(void) interrupt 1
{
	unsigned int t;
	unsigned char a;
	TH0=0xb8;/*T0�����ó�ֵ*/
	TL0=0;
	a++;
	/*ÿ���ж����Ϊ0.01S*/
	/*�޸��¾���Ե�����Ϸ�ٶ�*/
	//t=120-Snake.Level*10;
t=100;
	if (a>t)/*�趨ʱ�䵽����*/
	//if (a>100)/*�趨ʱ�䵽����*/
	{
		a=0;/*�ǣ�ʱ�䵽*/
		COL0=0;P0=0;COL1=0;COL2=0;COL3=0;/*��ͣ����ɨ�裬����������ϳ���������ʾ*/
    	Run_SNAKE();
		P0=0;/*�������ã��ڼ���ɨ������н�ֹ4λ�������ʾ������������ϳ���������ʾ*/
	}
}


//void timer1 (void) interrupt 3
//{
//	TH1=0X00;
//	TL1=0X00;
//}


//=================================================================
//�������ƣ�Trun_On_Point     Trun_Off_Point (uchar x,uchar y)
//�������ܣ���������Ϩ��һ���㡣������ʾ������
//��ڲ�������
//���ڲ�������
//�ر�˵������ Trun_On���������������ľͿ��Լ���������Һ��
//          ��8*8 ����   12864 ��
//=================================================================
void Trun_On_Point (uchar x,uint y,uint color)
{
	GUI_box((8*(x+1)),(8*(y+1)),(8*(x+2)),(8*(y+2)),color);
}

void Trun_Off_Point (uchar x,uint y)
{
	GUI_box((8*(x+1)),(8*(y+1)),(8*(x+2)),(8*(y+2)),0xBE5F);	
}

//=================================================================
//�������ƣ�void Init_SNAKE(void)  
//�������ܣ�������Ϸ���棬��ʼ����Ϸ�ȼ��Ȳ���
//��ڲ�������
//���ڲ�������
//=================================================================
void Init_SNAKE(void)   
{
	uchar i;

	Init_time();
	
	//***********��ʼ���߲���********************//
	Snake.Long=2;	    			//�����ʼ���ߵĳ���
	Snake.Life=0;	    			//��ʼ���߻�����
	Snake.Score=0;
	Food.Yes=1;					
	Key_Value=Key_Right;
	Over=0;



	for(i=0;i<Snake.Long;i++)		//���߸���ֵ
	{
		Snake.X[i]=i+2;
		Snake.Y[i]=2;
	}
	
	//***********������Ϸ����********************//
   LCD_clearscreen(0xBE5F);//����
	GUI_box(0,304,239,319,0x001f);
	GUI_sprintf_HZ(32, 304, 0x07ff,0x001f);//��ʾԤ���庺���ַ���
	GUI_Rectangle(8-1,8-1,184+1,288+1,0xaa);//����һ�����ο�, 0-127
	GUI_sprintf_String(192,8,"SCORE",0x8b00,0xBE5F);
	GUI_sprintf_chartodec(200,24,Snake.Score,0xf800,0xBE5F);
 	GUI_sprintf_String(192,81,"LEVEL",0x8b00,0xBE5F);
	GUI_sprintf_chartodec(200,97,Snake.Level,0xf800,0xBE5F);
					
	for(i=0;i<Snake.Long;i++)		//���߸�������
	{
		Trun_On_Point(Snake.X[i],Snake.Y[i],0x001f);
	}							
}
//=================================================================
//�������ƣ�void Display_dead(uchar i) 
//�������ܣ���ʾ��������
//��ڲ�������
//���ڲ�������
//=================================================================
void Display_dead(void)
{
	GUI_sprintf_String(60,140,"GAME OVER",0xcc88,0xBE5F); 
	Over=1;
	TR0=0;/*ֹͣ��ʱ��0����ֹͣ�˶�*/
	P0=0;/*�������ã��ڼ���ɨ������н�ֹ4λ�������ʾ������������ϳ���������ʾ*/
}
//=================================================================
//�������ƣ�void Display_Pass(uchar i)
//�������ܣ���ʾ���ؽ���
//��ڲ�������
//���ڲ�������
//=================================================================
void Display_Pass(void)
{
	Snake.Level++;	
	GUI_sprintf_String(68,124,"You are",0xcc88,0xBE5F); 
	GUI_sprintf_String(80,156,"WIN!",0xcc88,0xBE5F); 
	Over=1;
	TR0=0;/*ֹͣ��ʱ��0����ֹͣ�˶�*/
	P0=0;/*�������ã��ڼ���ɨ������н�ֹ4λ�������ʾ������������ϳ���������ʾ*/
}
//=================================================================
//�������ƣ�void Run_SNAKE(void)
//�������ܣ����˶����� ����Ϸ������
//��ڲ�������
//���ڲ�������
//=================================================================
void Run_SNAKE(void)
{
	uchar i=0;

	/*********************���ݰ���ѡ���ߵ��˶�����*******************/
	if((Key_Value==Key_Right&&Key_V_temp!=Key_Left)||(Key_Value==Key_Left&&Key_V_temp==Key_Right))
	{
		Trun_Off_Point(Snake.X[0],Snake.Y[0]); 	       //�Ȱ���β��Ϩ��� 

		for(i=0;i<Snake.Long-1;i++)                    //��������ǰһ�ε������λ��
		{
			Snake.X[i]=Snake.X[i+1];
			Snake.Y[i]=Snake.Y[i+1];
		} 

		Snake.X[Snake.Long-1]=Snake.X[Snake.Long-2]+1;
		Snake.Y[Snake.Long-1]=Snake.Y[Snake.Long-2]+0; //��ͷ����Ҫ��ķ����ƶ�
		
		for(i=0;i<Snake.Long;i++)			            //���������ʾ�����ĺ���
		{
			Trun_On_Point(Snake.X[i],Snake.Y[i],0x001f);
		}
		Key_V_temp=Key_Right;
	}

	if((Key_Value==Key_Left&&Key_V_temp!=Key_Right)||(Key_Value==Key_Right&&Key_V_temp==Key_Left))
	{

		Trun_Off_Point(Snake.X[0],Snake.Y[0]); 		   //�Ȱ���β��Ϩ��� 
		
		for(i=0;i<Snake.Long-1;i++)                     //��������ǰһ�ε������λ��
		{
			Snake.X[i]=Snake.X[i+1];
			Snake.Y[i]=Snake.Y[i+1];
		} 
		
		Snake.X[Snake.Long-1]=Snake.X[Snake.Long-2]-1;
		Snake.Y[Snake.Long-1]=Snake.Y[Snake.Long-2]+0; //��ͷ����Ҫ��ķ����ƶ�
		
		for(i=0;i<Snake.Long;i++)			            //���������ʾ�����ĺ���
		{
			Trun_On_Point(Snake.X[i],Snake.Y[i],0x001f);
		}
		Key_V_temp=Key_Left;
	}
	if(( Key_Value==Key_Up&&Key_V_temp!=Key_Down)||( Key_Value==Key_Down&&Key_V_temp==Key_Up))
	{
		Trun_Off_Point(Snake.X[0],Snake.Y[0]); 		  //�Ȱ���β��Ϩ��� 
		
		for(i=0;i<Snake.Long-1;i++)                   //��������ǰһ�ε������λ��
		{
			Snake.X[i]=Snake.X[i+1];
			Snake.Y[i]=Snake.Y[i+1];
		} 
		
		Snake.X[Snake.Long-1]=Snake.X[Snake.Long-2]+0;
		Snake.Y[Snake.Long-1]=Snake.Y[Snake.Long-2]-1; //��ͷ����Ҫ��ķ����ƶ�
		
		for(i=0;i<Snake.Long;i++)			           //���������ʾ�����ĺ���
		{
			Trun_On_Point(Snake.X[i],Snake.Y[i],0x001f);
		}
		Key_V_temp=Key_Up;
	}
	if(( Key_Value==Key_Down&&Key_V_temp!=Key_Up)||( Key_Value==Key_Up&&Key_V_temp==Key_Down))
	{
		Trun_Off_Point(Snake.X[0],Snake.Y[0]); 		 //�Ȱ���β��Ϩ��� 
		
		for(i=0;i<Snake.Long-1;i++)                  //��������ǰһ�ε������λ��
		{
			Snake.X[i]=Snake.X[i+1];
			Snake.Y[i]=Snake.Y[i+1];
		} 
		
		Snake.X[Snake.Long-1]=Snake.X[Snake.Long-2]+0;
		Snake.Y[Snake.Long-1]=Snake.Y[Snake.Long-2]+1; //��ͷ����Ҫ��ķ����ƶ�
		
		for(i=0;i<Snake.Long;i++)			           //���������ʾ�����ĺ���
		{
			Trun_On_Point(Snake.X[i],Snake.Y[i],0x001f);
		}
		Key_V_temp=Key_Down;
	}
	

	/****************���ݰ���ѡ���ߵ��˶��������*******************/
	/////////////////////////////////////////////////////////////////

	
	/************************�ж����Ƿ�����***********************/
	if(Snake.X[Snake.Long-1]>=22||Snake.Y[Snake.Long-1]>=35)//����ͷ�Ƿ�ײ��ǽ��
	{
		Snake.Life=1;
	}
	for(i=3;i<Snake.Long;i++)//�ӵ����ڿ�ʼ�ж���ͷ�Ƿ�ҧ���Լ�
	{
		if(Snake.X[i]==Snake.X[0]&&Snake.Y[i]==Snake.Y[0])
		{
			Snake.Life=1;
		}
	}
	if(Snake.Life==1)	  //if the snake over
	{
		Key_V_temp=Key_Value;
		Display_dead();
	}
	/******************�ж����Ƿ������������***********************/
	/////////////////////////////////////////////////////////////////


	/************************�ж����Ƿ����**********************/
	if(Snake.Long==SNAKE_MAX_LONG)
	{
		Key_V_temp=Key_Value;
		Display_Pass();
	}
	/////////////////////////////////////////////////////////////////										   

	/*************************�����Ƿ�Ե�ʳ��**********************/		
	if(Snake.X[Snake.Long-1]==Food.X&&Snake.Y[Snake.Long-1]==Food.Y)//
	{
		//Trun_Off_Point(Food.X,Food.Y); 		 //����ʳ��
		Snake.Long++;//�߽�����1
		Snake.X[Snake.Long-1]=Food.X;
		Snake.Y[Snake.Long-1]=Food.Y;
		Snake.Score+=10;
		GUI_sprintf_chartodec(200,24,Snake.Score,0xcc88,0xBE5F);
		Food.Yes=1;  //ʳ���־��1
	}
	/////////////////////////////////////////////////////////////////
	

	/***************************�Ź��ӳ���*************************/
	if(Food.Yes==0)
	{
		Trun_On_Point(Food.X,Food.Y,0xf81f);
	}											   
	if(Food.Yes==1)
	{
		while(1)
		{
			Food.X=TL1/12;      			//��������
			if (Food.X>21)Food.Y=Food.Y-21;
			Food.Y=TL1/7;
			if (Food.Y>34)Food.Y=Food.Y-34;

		    for(i=0;i<Snake.Long;i++)				//�жϲ�����ʳ�������Ƿ�������غ�
			{
				if((Food.X==Snake.X[i])&&(Food.X==Snake.Y[i]))
					break;
			}
			if(i==Snake.Long)
			{
				Food.Yes=0;
				break;								//������Ч��ʳ������
			}
		}
	}
}


//��������ΰ��д��̰���ߵĺ��ĳ���
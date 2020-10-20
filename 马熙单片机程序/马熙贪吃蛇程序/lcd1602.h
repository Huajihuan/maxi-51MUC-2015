/*********************************************************************
 *
 *                           LCD1602.H
 *
 *********************************************************************
 * �ļ���: LCD1602.H
 * ����: 
 * ��˾: ��������
 *
 * ����              		����         			ע��
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * ��ΰ��					08/04/01				ԭʼ�ļ�
 ********************************************************************/
#ifndef LCD1602_H
#define LCD1602_H

/*�������ͱ�ʶ�ĺ궨��,ͨ������*/
#define uchar unsigned char
#define uint unsigned int

/*ע��Һ���Ĺܽ���LCD1602.H�ж���*/
/*��Ƭ����LCD1602���������߶���*/
sbit LCD_RS  = P1^0;     //RSΪ�Ĵ���ѡ��1=���ݼĴ�����0=ָ��Ĵ�����
sbit LCD_RW  = P1^1;      //RWΪ��д�ź��ߣ�1=��������0=д������
                   //��RS=RW=0����д��ָ�������ʾ��ַ��
                   //��RS=0��RW=1���Զ�æ�źţ�
                   //��RS=1��RW=0����д�����ݡ�
sbit LCD_EN	 = P2^5;      //��en���ɸߵ�ƽ����ɵ͵�ƽʱ��Һ��ģ��ִ�����

sbit LCD_BUSY=P0^7;    //æָʾ
#define LCD_DATA P0  //�����������

#define LCD_DATA_IN  {\ 
P0M1=0xff;\ 
P0M0=0x00;\ 
} /*��Ƭ����LCD���ݿ�����Ϊȫ����*/

	
#define LCD_DATA_OUT  {\ 
P0M1=0x00;\ 
P0M0=0xff;\ 
} /*��Ƭ����LCD���ݿ�����Ϊȫ���*/	

#define LCD_CTR_OUT   {\ 
P1M1&=0xfc;/*0b11111100*/\
P1M0|=0x03;/*0b00000011*/\
P2M1&=0xdf;/*0b11011111*/\
P2M0|=0x20;/*0b00100000*/\
} /*���õ�Ƭ��LCD��������RW\RS\ENȫΪ���*/

#define SOME_NOP   {\ 
   	_nop_();\
	_nop_();\
	_nop_();\
	_nop_();\
} /*���õ�Ƭ��LCD��������RW\RS\ENȫΪ���*/

	

/*-------------------1602Һ�������-------------------*/

/*��ʼ������*/
#define DISP_CLR		0x01/*0b00000001.����ʾ,��긴λ����һ����(��ַ00H��*/
#define CUR_HOME		0x02/*0b00000010.��긴λ����귵�ص���һ����*/

/*������ʾģʽ����*/
#define CUR_AUTO_R		0x06/*0b00000110.���ù�������ֲ�����Զ�����*/
#define CUR_AUTO_L		0x04/*0b00000100.���ù�������ֲ�����Զ�����*/
#define DISP_AUTO_R		0x07/*0b00000111.������ʾ�����ֲ�����Զ�����*/
#define DISP_AUTO_L		0x05/*0b00000101.������ʾ�����ֲ�����Զ�����*/

/*��ʾ���ؿ���*/
#define DISP_ON			0x0f/*0b00001111.��ʾ��*/
#define DISP_OFF		0x0b/*0b00001011.��ʾ��*/
#define CUR_ON			0x0f/*0b00001111.��꿪*/
#define CUR_OFF			0x0d/*0b00001101.����*/
#define BLINK_ON		0x0f/*0b00001111.�����˸��*/
#define BLINK_OFF		0x0e/*0b00001110.�����˸��*/

/*������ʾ��λ*/
#define CUR_SHIFT_L		0x10/*0b00010000.�������*/
#define CUR_SHIFT_R		0x14/*0b00010100.�������*/
#define DISP_SHIFT_L		0x18/*0b00011000.��ʾ����*/
#define DISP_SHIFT_R		0x1c/*0b00011100.��ʾ����*/


/*����ģʽ����*/
#define LCD_MODE_STD		0x38		/*1602��׼����ģʽ��8λ���ݴ��ͣ�2����ʾ���ַ�����5*7*/


/*�ַ�������RAM��ַ����*/
#define SET_ADDR_CGRAM		0x40	/*����CGRAM��ַ*/

/*���ݴ洢����ַ����*/
#define SET_ADDR_DDRAM		0x80	/*����DDRAM��ַ*/

/*�Զ����ַ�*/
#define USER_CHAR1				0x00/*�Զ����ַ�1:��*/
#define USER_CHAR2				0x01/*�Զ����ַ�2:��*/
#define USER_CHAR3				0x02/*�Զ����ַ�3:��*/
#define USER_CHAR4				0x03/*�Զ����ַ�4:��*/
#define USER_CHAR5				0x04/*�Զ����ַ�5:Ԫ*/
#define USER_CHAR6				0x05/*�Զ����ַ�6:��*/
#define USER_CHAR7				0x06/*�Զ����ַ�7:��*/
#define USER_CHAR8				0x07/*�Զ����ַ�8:С����ͼ��*/

/* ����ԭ��*/
void LCD_init(void)			;/*��ʼ��*/
void wait_until_LCDready(void)	;/*���æ��־��æ��ȴ�*/
void LCD_wrcmd(unsigned char cmd)		;/*д���������*/
void LCD_setxy(char x,char y)	;/*�趨��ʾλ�ã���x=1/2,��y=1~16����������*/
void LCD_wrchar(char str)		;/*д��Ҫ��ʾ���ַ�*/
void LCD_wrstr(char code *s);/*д��Ҫ��ʾ���ַ����������ú����൱��C18 ���е�putrsXLCD�������ӳ���洢��дһ���ַ�����LCD*/
void LCD_wrul(unsigned long num);/*д��Ҫ��ʾ���޷��ų�������*/
void LCD_wrlval(unsigned long num,unsigned char bits,unsigned char dp);/*д��Ҫ��ʾ�ĳ�����*/
void CG_Write(void);/*�����Զ����ַ���*/


#endif

/*********************************************************************
 *
 *                           top51.h
 *
 *********************************************************************
 * �ļ���: top51.h
 * ��  ��: TOP51������ͷ�ļ�
 * ��  ˾: ��������
 * ����              		����         			ע��
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * ��ΰ��		09/04/01				ԭʼ�ļ�
 * ��ΰ��		09/10/20				v1.1
 ********************************************************************/

#ifndef TOP51_H
#define TOP51_H

/*�������ͱ�ʶ�ĺ궨��,ͨ������*/
#define uchar unsigned char
#define uint unsigned int
#define ON 1
#define OFF 0

/*���徧��Ƶ�ʣ���λ Hz��*/
//#define FOSC  11059200 
//#define FOSC  12000000 
#define FOSC  22118400 


/* top51 ���Ŷ��� */
sbit D0  = P0^0;
sbit D1  = P0^1;
sbit D2  = P0^2;
sbit D3  = P0^3;
sbit D4  = P0^4;
sbit D5  = P0^5;
sbit D6  = P0^6;
sbit D7  = P0^7;

sbit RS  = P1^0;   //RSΪ�Ĵ���ѡ��1=���ݼĴ�����0=ָ��Ĵ�����
sbit RW  = P1^1;   //RWΪ��д�ź��ߣ�1=��������0=д������
                   //��RS=RW=0����д��ָ�������ʾ��ַ��
                   //��RS=0��RW=1���Զ�æ�źţ�
                   //��RS=1��RW=0����д�����ݡ�
sbit IO  = P1^2;
sbit AN  = P1^3;
sbit DAC  = P1^4;
sbit SDI  = P1^5;
sbit SDO  = P1^6;
sbit SCK  = P1^7;

sbit COL0 = P2^0;
sbit COL1= P2^1;
sbit COL2= P2^2;
sbit COL3= P2^3;
sbit CS88= P2^4;
sbit EN	 = P2^5;   //��EN���ɸߵ�ƽ����ɵ͵�ƽʱ��Һ��ģ��ִ�����
sbit CS  = P2^6;
sbit RST = P2^7;

sbit RX  = P3^0;
sbit TX  = P3^1;
sbit IR  = P3^2;
sbit SW0 = P3^3;
sbit SW1 = P3^4;
sbit SW2 = P3^5;
sbit B20 = P3^6;
sbit BZ = P3^7;


/*Ϊ����ʹ�ã����ֹܽŵĶ��ض���*/

#define M_0   COL0 
#define M_1   COL1 
#define M_2   COL2 
#define M_3   COL3 

#define CLK SW0
#define DAT SW1

sbit LED0  = P0^0;
sbit LED1  = P0^1;
sbit LED2  = P0^2;
sbit LED3  = P0^3;
sbit LED4  = P0^4;
sbit LED5  = P0^5;
sbit LED6  = P0^6;
sbit LED7  = P0^7;


//ϵͳ��ʼ������
void top51_init(void);/*top51�����ʼ��*/


#endif
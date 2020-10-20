/*********************************************************************
 *
 *                ILI9325 TFT������������
 *
 *********************************************************************
 * �ļ���: ILI9325.c
 * ����: 
 * ��˾: ��������
 * ����              		����         			ע��
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * ��ΰ��				2010/3/20				ԭʼ�ļ�
 ********************************************************************/

#include "stc.h"
//#include <stdio.h>
#include "ILI9325.h"
#include "delay.h"

//=============================================================
//TFT��ʼ��
//���ܣ��ú������ڳ�ʼ��TFT����ģ�顣
//��ڲ���: ��
//���ڲ���: ��
void ILI9325_initial(void)
{ 
	//TFT_CS=1;
	//delayms(5);
	//TFT_RST=0;
	//delayms(5);
	//TFT_RST=1;
	//delayms(50);//�����ʵ�������ʱ�������ȶ���ʾ
	//write_cmd_data(0x0001,0x0100); //Դɨ������SS=0, ������ƶ������Ǵ�S1��S720
	 //��Դɨ������SS=1, ������ƶ������Ǵ�S720��S1��
	 //SM=0������ɨ�裨SM=1������ɨ�裩

	//write_cmd_data(0x0002,0x0700); //B/C=1��EOR=1���е��ã�B/C=0��֡/�����ã�
	//write_cmd_data(0x0003,0x1030); //AM=0����ַ��ˮƽ�����Զ���1
	 //I/D[1:0] = 11��ˮƽ��ֱ���������
	 //BGR=1:����BGR��ʽ
	 //TRI=0��DFM=*��8λ�����������ݴ���
	//write_cmd_data(0x0004,0x0000); //�����������ã�������
	
	 //��ʾ����
	//write_cmd_data(0x0008,0x0207); //���ú���غ�ǰ�� 
	//write_cmd_data(0x0009,0x0000);//���÷���ʾ��ʱ����ISC[3:0]
	//write_cmd_data(0x000A,0x0000); //֡��ǹ���

	//write_cmd_data(0x000C,0x0000);//RGB��ʾ�ӿڿ���1
	//write_cmd_data(0x000D,0x0000);//֡���λ��
	//write_cmd_data(0x000F,0x0000);//RGB��ʾ�ӿڿ���2
	
	 //��Դ����
	//write_cmd_data(0x0010,0x0000);   
	//write_cmd_data(0x0011,0x0007);  
	//write_cmd_data(0x0012,0x0000);  
	//write_cmd_data(0x0013,0x0000); 
	 //vgh 
	//write_cmd_data(0x0010,0x1290);   
	//write_cmd_data(0x0011,0x0227);
	 //delayms(100);
	 //vregiout 
	// write_cmd_data(0x0012,0x001d); //0x001b
	 //delayms(100); 
	 //vom amplitude
	//write_cmd_data(0x0013,0x1500);
	 //delayms(100); 
	 //vom H
	//write_cmd_data(0x0029,0x0018); 
	//write_cmd_data(0x002B,0x000D); 
	
	 //٤��У��
	//write_cmd_data(0x0030,0x0004);
	//write_cmd_data(0x0031,0x0307);
	//write_cmd_data(0x0032,0x0002);//0006
	//write_cmd_data(0x0035,0x0206);
	//write_cmd_data(0x0036,0x0408);
	//write_cmd_data(0x0037,0x0507); 
	//write_cmd_data(0x0038,0x0204);//0200
	//write_cmd_data(0x0039,0x0707); 
	//write_cmd_data(0x003C,0x0405);//0504
	//write_cmd_data(0x003D,0x0F02); 
	
	 //��������
	//write_cmd_data(0x0050,0x0000);//ˮƽ��ʼλ��
	//write_cmd_data(0x0051,0x00EF);//ˮƽ��ֹλ��
	//write_cmd_data(0x0052,0x0000);//��ֱ��ʼλ��
	//write_cmd_data(0x0053,0x013F);//��ֱ��ֹλ��

	//write_cmd_data(0x0060,0xA700);//��ɨ�����ã�GS=1����G320ɨ�赽G1��320��
	//write_cmd_data(0x0061,0x0001); 
	//write_cmd_data(0x006A,0x0000);
	 //
	//write_cmd_data(0x0080,0x0000); 
	//write_cmd_data(0x0081,0x0000); 
	//write_cmd_data(0x0082,0x0000); 
	//write_cmd_data(0x0083,0x0000); 
	//write_cmd_data(0x0084,0x0000); 
	//write_cmd_data(0x0085,0x0000); 
	 //
	//write_cmd_data(0x0090,0x0010); 
	//write_cmd_data(0x0092,0x0600); 
	//write_cmd_data(0x0093,0x0003); 
	//write_cmd_data(0x0095,0x0110); 
	//write_cmd_data(0x0097,0x0000); 
	//write_cmd_data(0x0098,0x0000);
	//write_cmd_data(0x0007,0x0133);
	//write_cmd_data(0x0022);
	 //������R61505��
	
	
	unsigned int i;

	TFT_RST = 1;
	for(i=500; i>0; i--);
	TFT_RST = 0;
	for(i=500; i>0; i--);
	TFT_RST = 1;
	for(i=5000; i>0; i--);
	
	TFT_CS = 0;

 	write_cmd_data(0x0000, 0x0001);
	write_cmd_data(0x0007, 0x0000);			
	write_cmd_data(0x0012, 0x0000);       
	write_cmd_data(0x00A4, 0x0001);

	for(i=5000; i>0; i--);

//--------GAMMA SETTINGS---------
	write_cmd_data(0x0008, 0x0808); 
    write_cmd_data(0x0018 ,0x0001);			
	write_cmd_data(0x0010, 0x11B0);			
	write_cmd_data(0x0011, 0x0000);
	write_cmd_data(0x0012, 0x1115);
	write_cmd_data(0x0013, 0x8B0B);
	write_cmd_data(0x0012, 0x1135);			
	write_cmd_data(0x0014, 0x8000);
	write_cmd_data(0x0001, 0x0100);
	write_cmd_data(0x0002, 0x0700); 
	write_cmd_data(0x0003, 0x1030);
	write_cmd_data(0x0070, 0x1B00);

	write_cmd_data(0x0071, 0x0001);
	write_cmd_data(0x0090, 0x0002);           
	write_cmd_data(0x0091, 0x0000);
	write_cmd_data(0x0092, 0x0001);
	write_cmd_data(0x0007, 0x0001);
	for(i=5000; i>0; i--);

	write_cmd_data(0x0007, 0x0021);
	for(i=5000; i>0; i--);

	write_cmd_data(0x0012, 0x1135);                  
	write_cmd_data(0x0007, 0x0233);                 
		
	write_cmd(0x00,0x22);
			
}


//=============================================================
//д����
//���ܣ�дһ�����TFT��������
//��ڲ���: CH,CL�ֱ�Ϊ�����ֵĸ�8λ�͵�8λ��ָ��Ҫִ�е����
//���ڲ���: ��
void write_cmd(unsigned char CH,unsigned char CL)
{
	TFT_CS=0;
	TFT_RS=0;
	TFT_DATAPORTH=CH;
	TFT_WR=0;
	TFT_WR=1;
	TFT_DATAPORTL=CL;
	TFT_WR=0;
	TFT_WR=1;
	TFT_CS=1;
}


//===================================================================
//д����
//���ܣ�дһ�����ݵ�TFT��������
//��ڲ���: DH,DL�ֱ�Ϊ�����ֵĸ�8λ�͵�8λ��ָ��Ҫд������ݡ�
//���ڲ���: ��
void write_data(unsigned char DH,unsigned char DL)
{
	TFT_CS=0;
	TFT_RS=1;
	TFT_DATAPORTH=DH;
	TFT_WR=0;
	TFT_WR=1;
	TFT_DATAPORTL=DL;	
	TFT_WR=0;
	TFT_WR=1;
	TFT_CS=1;
}


//==============================================================
//д16λ����
//���ܣ� дһ�����ݵ�TFT��������
//��ڲ���: datΪҪд���16λ���ݡ�
//���ڲ���: ��
void write_data_u16(unsigned int dat)
{
	unsigned char m,n;
	m=dat>>8;
	n=dat;
	write_data(m,n);
}


//===============================================================
//д��������
//���ܣ� д�������ݵ�TFT��������
//��ڲ���: cmdΪҪд��������ֽڣ�datΪҪд���16λ���ݡ�
//���ڲ���: ��
void write_cmd_data (unsigned char cmd,unsigned int dat)
{
	unsigned char m,n;
	m=dat>>8;
	n=dat;
	write_cmd(0x00,cmd);
	write_data(m,n);
}


//===============================================================
//���ô���
//��ڲ���: x0 y0,Ϊ��ʾ�������Ͻ����ꣻx1,y1Ϊ��ʾ�������½����ꡣ
//���ڲ���: ��
//˵�����ú�������TFTģ�����ʾ���ڡ�
void LCD_setwindow(unsigned char x0,unsigned int y0,unsigned char x1,unsigned int y1)
{
	write_cmd_data(WINDOW_XADDR_START,x0);//ˮƽ��ʼλ��
	write_cmd_data(WINDOW_XADDR_END,x1);//ˮƽ��ֹλ��
	write_cmd_data(WINDOW_YADDR_START,y0);//��ֱ��ʼλ��
	write_cmd_data(WINDOW_YADDR_END,y1);//��ֱ��ֹλ��
	write_cmd_data(GRAM_XADDR,x0);//����X����λ��
	write_cmd_data(GRAM_YADDR,y0);//����Y����λ��
	write_cmd(0x00,0x22);//LCD_WriteCMD(GRAMWR);
}


//===============================================================
//�趨��ǰ��ʾ����
//��ڲ���: x,yΪ��ǰ��ʾ���ꡣ
//���ڲ���: ��
//˵����������ʵ������LCD_setwindow������һ����������ʾ����Ϊ��С������һ�����ص㡣
void LCD_setxy(unsigned char x,unsigned int y)
{
	LCD_setwindow(x,y,x,y);	
}







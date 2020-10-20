#ifndef ILI9325_H
#define ILI9325_H
//============================================================
//����оƬ���϶���
#define WINDOW_XADDR_START	0x0050 // Horizontal Start Address Set
#define WINDOW_XADDR_END	0x0051 // Horizontal End Address Set
#define WINDOW_YADDR_START	0x0052 // Vertical Start Address Set
#define WINDOW_YADDR_END	0x0053 // Vertical End Address Set
#define GRAM_XADDR		0x0020 // GRAM Horizontal Address Set
#define GRAM_YADDR		0x0021 // GRAM Vertical Address Set
#define GRAMWR 			0x0022 // memory write
#define GUI_LCM_YMAX 219
#define GUI_LCM_XMAX 175

//=============================================================
//����TFT����ģ��ӿ�
sbit	  TFT_RST = P3^3;  	//��λ
sbit	  TFT_CS  = P2^7;	//Ƭѡ
sbit	  TFT_RS  = P2^6;	//��������ѡ���
sbit	  TFT_WR  = P2^5;	//��д����
sbit      TFT_RD  = P3^2;   

#define   TFT_DATAPORTH  P1 //���ø�8λ����
#define   TFT_DATAPORTL  P0 //���õ�8λ����



//=============================================================
//��������
void ILI9325_initial(void);//TFT��ʼ��
void write_cmd(unsigned char CH,unsigned char CL);//д����
void write_data(unsigned char DH,unsigned char DL);//д����
void write_data_u16(unsigned int dat);//д16λ����
void write_cmd_data (unsigned char cmd,unsigned int dat);//д��������
void LCD_setwindow(unsigned char x0,unsigned int y0,unsigned char x1,unsigned int y1);//���ô���
void LCD_setxy(unsigned char x,unsigned int y);//�趨��ǰ��ʾ����




#endif












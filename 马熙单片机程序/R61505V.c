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
	TFT_WriteCmdData(0x0007, 0x0000);			
	TFT_WriteCmdData(0x0012, 0x0000);       
	TFT_WriteCmdData(0x00A4, 0x0001);

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

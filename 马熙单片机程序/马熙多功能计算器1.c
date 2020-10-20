 

#include "delay.h"
void delay_us(unsigned int cnt)     
{ 
	     while(--cnt);
}
void delay_ms(unsigned int cnt) 
{ 
	    unsigned int i, j; 
	    for (i = 0; i < cnt; i++) 
	    {
		    for (j = 0;j < 65; j++) 
		    {   
			    delay_us(1);  
		    } 
	    }
}
 


#include "includes.h"
sbit RS = P2^6;            //����˿�  ��������ѡ��H/L
sbit RW = P2^5;	        //��д H/L
sbit EN = P2^7;	        //ʹ��
extern unsigned char sk;
#define RS_CLR RS=0 
#define RS_SET RS=1
#define RW_CLR RW=0 
#define RW_SET RW=1 
#define EN_CLR EN=0
#define EN_SET EN=1
/******************************************************************/
/*                   д�������                                 */
/******************************************************************/
void LCD_write_com(unsigned char com) 
{  
	RS_CLR; 
	RW_CLR; 
	EN_SET; 
	P0 = com; 
	delay_us(5); 
	EN_CLR;
}
/******************************************************************/
/*                   д�����ݺ���                                 */
/******************************************************************/
void LCD_write_Data(unsigned char Data) 
{ 
	RS_SET; 
	RW_CLR; 
	EN_SET; 
	P0 = Data; 
	delay_us(5); 
	EN_CLR;
}
/******************************************************************/
/*                   ��������                                     */
/******************************************************************/
void LCD_clear(void) 
{ 
	LCD_write_com(0x01);
	delay_ms(5);
	 if(sk == 1)
	{
	    LCD_write_char(0,1,0xde);
		LCD_write_com(0x80); 
	}
	else
	{
		LCD_write_char(0,1,0x20);
	    LCD_write_com(0x80);
	} 
}
/******************************************************************/
/*                   д���ַ�������                               */
/******************************************************************/
void LCD_write_str(unsigned char x,unsigned char y,unsigned char *s) 
{ 
	unsigned char i,j;    
	if (y == 0) 
	{     
		LCD_write_com(0x80 + x);     
	}
	else 
	{     
		LCD_write_com(0xC0 + x);     
	}
	for(i=4;i>0;i--)
	{
		if(s[14] == '0' || s[14] == '.')
		{
		    for(j=14;j>1;j--)
			{
				s[j] = s[j-1];
			}
		}	
		else break;
	}       
	while (*s)                              
	{     
		LCD_write_Data(*s);     
		s++;     
	}
}
/******************************************************************/
/*                   д���ֽں���                                 */
/******************************************************************/
void LCD_write_char(unsigned char x,unsigned char y,unsigned char Data) 
{     
	if (y == 0) 
	{     
		LCD_write_com(0x80 + x);     
	}    
	else 
	{     
		LCD_write_com(0xC0 + x);     
	}        
	LCD_write_Data(Data);  
}
/******************************************************************/
/*                   ��ʼ������                                   */
/******************************************************************/
void LCD_init(void) 
{
	LCD_write_com(0x38);    /*��ʾģʽ����*/ 
	delay_ms(5); 
	LCD_write_com(0x38); 
	delay_ms(5); 
	LCD_write_com(0x38); 
	delay_ms(5); 
	LCD_write_com(0x38);  
	LCD_write_com(0x08);    /*��ʾ�ر�*/ 
	LCD_write_com(0x01);    /*��ʾ����*/ 
	LCD_write_com(0x06);    /*��ʾ����ƶ�����*/ 
	delay_ms(5); 
	LCD_write_com(0x0C);    /*��ʾ�����������*/
}

#include "includes.h"
extern unsigned char sk;
sbit key0=P2^0;
sbit key1=P2^1;				 
sbit key2=P2^2;
sbit key3=P2^3;
sbit speak=P2^4;
unsigned char KeyProcess(void)
{
unsigned char key;
	unsigned char keyvalue = 16;
	key=keyscan();					   //���ü���ɨ��                  
	switch(key)
	    {				
		    case 0xee:keyvalue = 0;break;  //0 ������Ӧ�ļ���ʾ���Ӧ����ֵ
		    case 0xde:keyvalue = 1;break;  //1 ������Ӧ�ļ���ʾ���Ӧ����ֵ 
		    case 0xbe:keyvalue = 2;break;  //2
		    case 0x7e:keyvalue = 3;break;  //3
		    case 0xed:keyvalue = 5;break;  //4
		    case 0xdd:keyvalue = 6;break;  //5
		    case 0xbd:keyvalue = 7;break;  //6
		    case 0x7d:keyvalue = 8;break;  //7
		    case 0xeb:keyvalue = 10;break;  //8
		    case 0xdb:keyvalue = 11;break;  //9
		    case 0xbb:keyvalue = 12;break; //10
		    case 0x7b:keyvalue = 13;break; //11
		    case 0xe7:keyvalue = 15;break; //12
		    case 0xd7:keyvalue = 16;break; //13
		    case 0xb7:keyvalue = 17;break; //14
		    case 0x77:keyvalue = 18;break; //15
		    case 0x00:keyvalue = 4;break; //key0
		    case 0x01:keyvalue = 9;break; //key1
		    case 0x02:keyvalue = 14;break; //key2
		    case 0x03:keyvalue = 19;break; //key3
		    case 0xff:keyvalue = 20;break;
		    default: keyvalue = 20;break;
	 }	
	return keyvalue;
}
unsigned char keyscan(void)           //����ɨ�躯����ʹ�����з�תɨ�跨
{
	unsigned char cord_h,cord_l;      //����ֵ�м����
	P3=0x0f;                          //�������ȫΪ1,�������ȫΪ0
	cord_h=P3&0x0f;                   //��������ֵ
	if(cord_h!=0x0f)                    //�ȼ�����ް�������
	{
		delay_us(100);                  //ȥ��
		if(cord_h!=0x0f)
		{
			cord_h=P3&0x0f;           //��������ֵ
			P3=cord_h|0xf0;            //�����ǰ����ֵ
			cord_l=P3&0xf0;           //��������ֵ		
			while(P3 != 0x0f)
			{
				P3 = 0x0f;
				speak = !sk;
			}
			speak=0;
			delay_ms(20);			
			return(cord_h+cord_l);       //������������ֵ
		}
	}
	if(key0 == 0)
	{
	    delay_us(100);
		if(key0==0)
		{
			while(key0 == 0)
			{
				speak = !sk;
			}
			speak = 0;
			delay_ms(3);
			return 0x00;
		}	
	}
	if(key1 == 0)
	{
	    delay_us(100);
		if(key1==0)
		{
			while(key1 == 0)
			{
				speak = !sk;
			}
			speak = 0;
			delay_ms(3);
			return 0x01;
		}	
	}
	if(key2 == 0)
	{
	    delay_us(100);
		if(key2==0)
		{
			while(key2 == 0)
			{
				speak = !sk;
			}
			speak = 0;
			delay_ms(3);
			return 0x02;
		}	
	}
	if(key3 == 0)
	{
	    delay_us(100);
		if(key3==0)
		{
			while(key3 == 0)
			{
				speak = !sk;
			}
			speak = 0;
			delay_ms(3);
			return 0x03;
		    }	
}
	    return(0xff);                       //���ظ�ֵ
}


#include "includes.h"
unsigned char code yxj[7][7] = {
				// + - * / ( ) #
            2,2,0,0,0,2,2,  // +
            2,2,0,0,0,2,2,  // -
			    2,2,2,2,0,2,2,  // *
				2,2,2,2,0,2,2,  // /
			    0,0,0,0,0,1,3,  // (
			    2,2,2,2,3,2,2,  // )
			    0,0,0,0,0,3,1,  // #
};
void Init_OPTR(OPTR *s,char *TR1)
{
    s->rbase = TR1;
	s->rtop = s->rbase;
}

void PUSH_OPTR(OPTR *s,char elem)
{
	* (s->rtop) = elem;
s->rtop ++;
}
char POP_OPTR(OPTR *s)
{
	char temp;
	s->rtop--;
	temp= *(s->rtop);
	    return temp;
}
void Init_OPND(OPND *s,double *ND1)
{
    s->dbase = ND1;
	s->dtop = s->dbase;
}
void PUSH_OPND(OPND *s,double elem)
{
	* (s->dtop) = elem;
	    s->dtop ++;
}
double POP_OPND(OPND *s)
{
	double temp;
	s->dtop--;
	temp= *(s->dtop);
	return temp;
}
char Precede(char a,char b)
{
	char i,j;
	switch(a)
	{
		    case '+':i=0;break;
		    case '-':i=1;break;
		    case '*':i=2;break;
		    case '/':i=3;break;
		    case '(':i=4;break;
		    case ')':i=5;break;
		    case '#':i=6;break;
		    default :i=0;break;
	}
    switch(b)
	{
		    case '+':j=0;break;
		    case '-':j=1;break;
		    case '*':j=2;break;
		    case '/':j=3;break;
		    case '(':j=4;break;
		    case ')':j=5;break;
		    case '#':j=6;break;
		    default :j=0;break;
	}
	return yxj[i][j];
}

double Operate(double num1,char theta,double num2)
{
    double num3;
    switch(theta)
	{
		    case '+':num3 = num1 + num2;break;
		    case '-':num3 = num1 - num2;break;
		    case '*':num3 = num1 * num2;break;
		    case '/':num3 = num1 / num2;break; 
	}
	return num3;
}
void Pushnum(OPND *sq,double c)
{
    double temp1,temp2;
    temp1 = POP_OPND(sq);
    temp2 = temp1 * 10 + c;
	PUSH_OPND(sq,temp2);
}
void Pushdp(OPND *sq,char flag,double c)
{
    double temp3,temp4;
	    char i;
    double j = 1;
    for(i=0;i<flag;i++)
	{
		    j = j * 0.1;
	}
    temp3 = POP_OPND(sq);
    temp4 = temp3  + c * j;
	PUSH_OPND(sq,temp4);
}

#include "includes.h"

unsigned char code uckey[20] = {0x37,0x38,0x39,0x28,0x29,
                           0x34,0x35,0x36,0x2b,0x2d,
						   0x31,0x32,0x33,0x2a,0x2f,
						   0x30,0x2e,0x64,0xde,0x3d};

char idata TR[20];
double idata ND[20];
void dispdouble(double value);
double AccProcess(char *s);
char getonechar(void);
unsigned char keycount=0;
unsigned char sk=0;
void ErrorProcess(void);
void main(void) 
{
	double value;
	unsigned char keyvalue;
	unsigned char ipos = 0;
	char s[32];
	P2 = 0xff;
	delay_ms(100);
	LCD_init();
	LCD_clear();
	while(1)
    {
		while(1)
		{
			keyvalue = getonechar();
			if(uckey[keyvalue] ==  '=')
			{
				s[ipos++] = '#';
				break;
			}
			else 
			{
				if(uckey[keyvalue] == 'd')                //��ʾ�����˸��
				{
				    s[--ipos] = '0';
				}

				else if(uckey[keyvalue] == 0xde)           //��ʾ�����������Ƽ�
				{
				    sk = !sk;
				    keycount--;
				   	if(sk == 1)
					{
					    LCD_write_char(0,1,0xde);
						LCD_write_com(0x80 + keycount); 
					}
					else
					{
						LCD_write_char(0,1,0x20);
					    LCD_write_com(0x80 + keycount);
					} 
				}				
				else
				{
					s[ipos++] = uckey[keyvalue];
				}	     
			}
		}
		while(keycount >= 16)
	    {
			LCD_write_com(0x1c);
			delay_ms(5);
			keycount--;
	    }
		s[ipos] = '\0';
		ipos = 0;
		keycount = 0;
     	value =  AccProcess(s);
    	dispdouble(value);
	}  
}
void dispdouble(double value)
{
	char text[15];		
    sprintf(text,"%15.3f",value);
    LCD_write_str(1,1,text); 
}

double AccProcess(char *s)
{
	OPTR str;           //����ջ
	OPND snd;           //����ջ
    char flagnum = 0;
	char flagdp = 0;
    char i=0;
	char c,theta;
	double num1,num2,num;
	Init_OPND(&snd,&ND[0]);
	Init_OPTR(&str,&TR[0]);
	PUSH_OPTR(&str,'#');
	flagnum = 0;
    c = *(s++);                                      
 while(c!='#' || (*(str.rtop-1) != '#'))
	{
		if(c>='0' && c<= '9')  
		 {                                                                            
			c = c - 0x30;
			if(flagdp ==0)
			{
				if(flagnum ==0)
				{
					PUSH_OPND(&snd,(double)c); 
					flagnum++;  
				}
                else
				{
					Pushnum(&snd,c);
					flagnum++;				
				}                                                              
			}
			if(flagdp == 1)
			{               			
				Pushdp(&snd,flagnum,c);
				flagnum++;								
			}
			c=*(s++);
		}
		else if(c=='.')
		{
            flagdp = 1;
			if(flagnum ==0 )
			{
				  PUSH_OPND(&snd,0x00);
			}
			flagnum = 1;
			c=*(s++);
		}
		else 
	        switch(Precede(*(str.rtop-1),c))
		    {                                                                                        				case 0:   if(flagnum == 0 && c != '(') ErrorProcess();	
				    PUSH_OPTR(&str,c);c=*(s++);          
	                flagnum = 0;
				    flagdp = 0;					   
				    break;                           
case 1:   POP_OPTR(&str);c=*(s++);      					                 break;      
			case 2:    theta = POP_OPTR(&str);                                  
					 num2 = POP_OPND(&snd);                                                     
	                 num1 = POP_OPND(&snd);                             
                     num =  (double)(Operate(num1,theta,num2));
				     PUSH_OPND(&snd,num);                   
				     break;						 
		    case 3:   ErrorProcess(); break;
				    default:break;
			}
	}
	while(*s)
	{
		*s = '\0';                           //��մ�ű��ʽ������
		s++;
	}
	return (*(snd.dtop - 1));
	
}
char getonechar()
{
	unsigned char key1 = 20;
	keycount++;
	while(key1 == 20)
	{
		key1 = 	KeyProcess();
		if(keycount==1 && key1==17)
		{
			key1=20;
		}
	}
	if(keycount == 1) 
	{
		LCD_clear();
	}
	if(keycount >= 16)
	{
		LCD_write_com(0x18);    //��������
	}
    if(keycount == 33)
	{
		ErrorProcess();	
	}
	if(key1 == 17)
	{
		LCD_write_char(keycount-2,0,0x20);
		delay_ms(2);
	    LCD_write_com(0x80+keycount-2);	
		keycount -= 2;			
	}
	else if(key1 == 18)
	{;}	
	else 
	{
	    LCD_write_Data(uckey[key1]);
	}
	return key1;	
}
void ErrorProcess(void)
{ 
	LCD_clear();
	LCD_write_str(4,1,"ERROR!");
	LCD_write_char(10,1,'!');
	while(KeyProcess() == 20);    
	ISP_CONTR = 0x20;                   //�����λ
}
#include<reg51.h> //����ͷ�ļ��������Ͳ��ö�˵�ˡ��� 
#define uint unsigned int//Ԥ����һ�� 
#define uchar unsigned char 
sbit rs=P2^6;//1602������/ָ��ѡ������� 
sbit rw=P2^5;//1602�Ķ�д������ 
sbit en=P2^7;//1602��ʹ�ܿ����� 
/*P2�ڽ�1602��D0~D7��ע�ⲻҪ�Ӵ���˳������ǰ����������Թ�����*/ 
uchar code table[]="LCD1602 check ok"; //Ҫ��ʾ������1��������tablel 
uchar code table1[]="study up";//Ҫ��ʾ������2��������table1 
void delay(uint n)//��ʱ����
{ 
uint x,y;  
 for(x=n;x>0;x--) 
for(y=110;y>0;y--); 
} 
void lcd_wcom(uchar com)//1602д�����
{ 
 rs=0;//ѡ��ָ��Ĵ���
 rw=0;//ѡ��д
 delay(5);
  en=1;//ʹ���ߵ�ƽ�仯����������1602��8λ���ݿ�
 delay(5); 
 P0=com;//������������P2 
 delay(5);//��ʱһС�������1602׼���������� 
 en=0; 
} 
void lcd_wdat(uchar dat)//1602д���ݺ���
{ 
 rs=1;//ѡ�����ݼĴ��� 
 rw=0;//ѡ��д
 delay(5);
 en=1;//ʹ���ߵ�ƽ�仯����������1602��8λ���ݿ�
 delay(5);  
 P0=dat;//��Ҫ��ʾ����������P2 
 delay(5);//��ʱһС�������1602׼���������� 
 
 en=0; 
} 
void lcd_init()//1602��ʼ������ 
{ 
 lcd_wcom(0x38); //8λ���ݣ�˫�У�5*7����
 lcd_wcom(0x0c);//������ʾ�����ع�꣬��겻��˸ 
 lcd_wcom(0x06); //��ʾ��ַ��������дһ�����ݺ���ʾλ������һλ 
 lcd_wcom(0x01); //���� 
} 
void main()//������ 
{
 uchar n,m=0; 
 lcd_init();//Һ����ʼ��
 lcd_wcom(0x80);//��ʾ��ַ��Ϊ80H����00H�������ŵ�һλ 
 for(m=0;m<16;m++)//��table[]�е���������д��1602��ʾ 
 { 
lcd_wdat(table[m]);
delay(200); 
 } 
 lcd_wcom(0x80+0x44); //�����趨��ʾ��ַΪ0xc4,�����ŵ�5λ 
 for(n=0;n<8;n++)//��table1[]�е���������д��1602��ʾ 
 {
lcd_wdat(table1[n]); 
delay(200); 
 } 
 while(1);//��̬ͣ�� 
} 

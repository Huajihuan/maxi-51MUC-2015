#include<reg51.h>   //ͷ�ļ�
#define uint unsigned int // 
#define uchar unsigned char

sbit lcden=P2^0; //��������
sbit rs=P2^3;
sbit rw=P2^4;
sbit busy=P0^7;

char i,j,temp,num,num_1;
long a,b,c;     //a,��һ���� b,�ڶ����� c,����
float a_c,b_c;
uchar flag,fuhao;//flag��ʾ�Ƿ��з��ż����£�fuhao�������µ����ĸ�����

uchar code table[]={
7,8,9,0,
4,5,6,0,
1,2,3,0,
0,0,0,0};
uchar code table1[]={
7,8,9,0x2f-0x30,
4,5,6,0x2a-0x30,
1,2,3,0x2d-0x30,
0x01-0x30,0,0x3d-0x30,0x2b-0x30};

void delay(uchar z) // �ӳٺ���
{
uchar y;
for(z;z>0;z--)
   for(y=0;y<110;y++);
}

void check() // �ж�æ�����
{
do{
    P0=0xFF;
    rs=0;     //ָ��
    rw=1;     //��
    lcden=0;     //��ֹ��д
    delay(1); //�ȴ���Һ����ʾ����������
    lcden=1;     //�����д
    }while(busy==1); //�ж��Ƿ�Ϊ���У�1Ϊæ��0Ϊ����
}
void write_com(uchar com) // дָ���
{
P0=com;    //comָ���P0��
rs=0;
rw=0;
lcden=0;
check();
lcden=1;
}

void write_date(uchar date) // д���ݺ���
{
    P0=date;
rs=1;
rw=0;
lcden=0;
check();
lcden=1;
}

void init() //��ʼ��
{
    num=-1;
lcden=1; //ʹ���ź�Ϊ�ߵ�ƽ
write_com(0x38); //8λ��2��
write_com(0x0c); //��ʾ�������أ�����˸*/
write_com(0x06); //������ʽ����λ �Ծ����ƶ ��?
write_com(0x80); //���æ�ź�
write_com(0x01); //��ʾ�������أ�����˸
num_1=0;
i=0;
j=0;
a=0;     //��һ�������������
b=0;     //�ڶ��������������
c=0;
flag=0; //flag��ʾ�Ƿ��з��ż����£� 
fuhao=0; // fuhao�������µ����ĸ�����
}
void keyscan() // ����ɨ�����
{

P3=0xfe; 
if(P3!=0xfe)
{
   delay(20); // �ӳ�20ms
   if(P3!=0xfe)
   {
    temp=P3&0xf0;
    switch(temp)
    {
     case 0xe0:num=0;
       break;
     case 0xd0:num=1;
       break; 
     case 0xb0:num=2;
       break;
     case 0x70:num=3;
       break;
    }
   }
   while(P3!=0xfe);
   if(num==0||num==1||num==2)//������µ���'7','8'��'9
   { 
       if(j!=0)
        { 
          write_com(0x01);
          j=0;
         }
       if(flag==0)//û�а������ż�
    {
     a=a*10+table[num]; 
    }
    else//����������ż�
    {
     b=b*10+table[num]; 
    }
   }
   else//������µ���'/'
   {
    flag=1;
    fuhao=4;//4��ʾ�����Ѱ�
   }
   i=table1[num];
   write_date(0x30+i);
}

P3=0xfd;
if(P3!=0xfd)
{
   delay(5);
   if(P3!=0xfd)
   {
    temp=P3&0xf0;
    switch(temp)
    {
     case 0xe0:num=4;
         break;
      
     case 0xd0:num=5;
         break;
      
     case 0xb0:num=6;
         break;
      
     case 0x70:num=7;
         break;
    }
   }
   while(P3!=0xfd);
   if(num==4||num==5||num==6&&num!=7)//������µ���'4','5'��'6'
   { 
    if(j!=0)
        { 
          write_com(0x01);
          j=0;
         }
       if(flag==0)//û�а������ż�
    {
     a=a*10+table[num]; 
    }
    else//����������ż�
    {
     b=b*10+table[num]; 
    }
   }
   else//������µ���'/'
   {
    flag=1;
    fuhao=3;//3��ʾ�˺��Ѱ�
   }
   i=table1[num];
   write_date(0x30+i);
}

P3=0xfb;
if(P3!=0xfb)
{
   delay(5);
   if(P3!=0xfb)
   {
    temp=P3&0xf0;
    switch(temp)
    {
     case 0xe0:num=8;
         break;
      
     case 0xd0:num=9;
         break;
      
     case 0xb0:num=10;
         break;
      
     case 0x70:num=11;
         break;
    }
   }
   while(P3!=0xfb);
   if(num==8||num==9||num==10)//������µ���'1','2'��'3'
   { 
    if(j!=0)
        { 
          write_com(0x01);
          j=0;
         }
      if(flag==0)//û�а������ż�
    {
     a=a*10+table[num]; 
    }
    else//����������ż�
    {
     b=b*10+table[num]; 
    }
   }
   else if(num==11)//������µ���'-'
   {
    flag=1;
    fuhao=2;//2��ʾ�����Ѱ�
   }
   i=table1[num];
   write_date(0x30+i);
}

P3=0xf7;
if(P3!=0xf7)
{
   delay(5);
   if(P3!=0xf7)
   {
    temp=P3&0xf0;
    switch(temp)
    {
     case 0xe0:num=12;
         break;
      
     case 0xd0:num=13;
         break;
      
     case 0xb0:num=14;
         break;
      
     case 0x70:num=15;
         break;
    }
   }
   while(P3!=0xf7);
   switch(num)
   {
    case 12:{write_com(0x01);a=0;b=0;flag=0;fuhao=0;}//���µ���"����"
     break;
    case 13:{                //���µ���"0"
       if(flag==0)//û�а������ż�
       {
        a=a*10;
        write_date(0x30);
        P1=0;
       }
       else if(flag==1)//����������ż�
       {
        b=b*10;
        write_date(0x30);
        }
      }
     break;
    case 14:{j=1;
           if(fuhao==1){write_com(0x80+0x4f);//���µ��ڼ������ǰ�����ڶ������һ����ʾ��
           write_com(0x04);     //���ôӺ�סǰд���ݣ�ÿд��һ�����ݣ�������һ��
           c=a+b;
           while(c!=0)
           { 
             write_date(0x30+c%10);
             c=c/10;
           } 
           write_date(0x3d);     //��д"="
           a=0;b=0;flag=0;fuhao=0;
           }
      else if(fuhao==2){write_com(0x80+0x4f);//���ǰ�����ڶ������һ����ʾ��
            write_com(0x04);     //���ôӺ�סǰд���ݣ�ÿд��һ�����ݣ�������һ��(�������˵˳�򲻶ԣ�����ʾ���϶�һ��)
           if(a-b>0)
             c=a-b;
           else 
             c=b-a;
           while(c!=0)
           { 
             write_date(0x30+c%10);
             c=c/10;
           } 
           if(a-b<0)
             write_date(0x2d);
           write_date(0x3d);     //��д"="           
           a=0;b=0;flag=0;fuhao=0;
          }
      else if(fuhao==3){write_com(0x80+0x4f);
            write_com(0x04);
             c=a*b;
             while(c!=0)
             { 
             write_date(0x30+c%10);
             c=c/10;
             } 
             write_date(0x3d);     
          a=0;b=0;flag=0;fuhao=0;
             }
      else if(fuhao==4){write_com(0x80+0x4f);
            write_com(0x04);
            i=0;
            c=(long)(((float)a/b)*1000);
            while(c!=0)
             { 
               write_date(0x30+c%10);
               c=c/10;
           i++;
           if(i==3)
               write_date(0x2e);
             } 
            if(a/b<=0)
              write_date(0x30);
            write_date(0x3d);                              
            a=0;b=0;flag=0;fuhao=0;
                    }
      }
     break;
     case 15:{write_date(0x30+table1[num]);flag=1;fuhao=1;}
     break;
   }
}
}

main()
{
init();
while(1)
{
   keyscan();
}
}

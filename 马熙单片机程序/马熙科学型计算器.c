#include "reg52.h"
#include <stdlib.h>        //����atof(),�ַ���->ʵ��
#include <stdio.h>         //����sprintf(),ʵ��->�ַ���
#include <string.h>        //����strcpy(),�ַ�������
#include <math.h>		   //��ѧ����ͷ�ļ�
#define uchar unsigned char
#define uint unsigned int
uchar num;
/*************lcd****************/
sbit lcdrs=P2^6; //LCD���ƽ�
sbit lcdrw=P2^5;
sbit lcden=P2^7;
bit  form;            //lcd��ʾ��ʽ�л�
uchar idata state;         //lcd״̬�ִ洢
/************������*************/
sbit reset=P2^0;           //��������λ
sbit back=P2^1;            //�����ϴμ����
sbit save=P2^2;            //�洢�����洢���ϴεĽ��������ĳ�μ���ֵ
bit eqsign;          //���Ⱥű�־
bit press;           //������־
bit savesign;        //�ɴ洢�����־
bit sc;			   //���ñ�־
uchar idata process[30],proc; //���������̣��Ա����ָ��ͳ�������
uchar idata continu=0;        //��������������Ŵ洢
uchar idata pai[2][2];        //�� ǰ�����ݱ�־
uchar idata ferror;        //�������־
uchar idata ywei;		   //��Ļ��λ
uchar idata count=0;       //�������
uchar idata count_num=0;   //��ż���
uchar idata result[15];    //���������棬save
uchar idata saveresult[15];//�洢�������, sc+save
uchar idata jieguo[15];    //����ַ���
uchar idata bdate[2][14];  //�������ַ�����ά��
uchar idata on_symbol;     //�������
uchar idata fsym[2];       //����ǰ����
uchar idata ssym[2];       //�洢��ǰ����
uchar idata bfun[2];       //����ֵ���ú���ѡ��
uchar idata futojiao[2];   //���� to �Ƕȱ任
double idata date[2];      //����ֵ˫���ȱ�����
double idata resultdate;   //˫���Ƚ��ֵ
sbit sfyong=P2^3;           //���������ü�
/******************��������**********************/

/***************��ʱ******************/
void delay(uchar z);
/*************lcdд����***************/
void write_com(uchar com);
/*************lcdд����***************/
void write_date(uchar date);
/*************lcd��״̬***************/
void read_date(void);
/*************lcdд�ַ���*************/
void write_str(uchar *str);
/************Һ����ʼ��***************/
void init(void );

/**********����*******************/
void write();
/**********������ʾ����***************/
void shift(void);
/**************����ɨ��***************/
uchar keyscan(void);
/*************��������λ**************/
void fuwei();
/************error����****************/
void callerror(void);
/***************��������**************/
void huifu(void);
/**********������ǰ���Ŵ���***********/
uchar funqian(void);
/************�����Ԥ����*************/
void  cullars(uchar);
/***********����洢����Ԥ����********/
char  memory(void);
/***********��������������************/
void process_date(uchar press_date);
/***********���������Ӵ���************/
void calculator(uchar press_date);
/************************************************/
void write()
{
   for(num=0;num<16;num++)
      {
       write_com(0x18);
       delay(200);
      }
}
/*************LCD����****************/
/**************��ʱ******************/
void delay(uchar z)			   
{
      uchar  x,y;
      for(x=z;x>0;x--)
      for(y=100;y>0;y--);
}

/**************д����*****************/
void write_com(uchar com)
{
      lcdrs=0;
      lcdrw=0;
      lcden=0;
      P0=com;
      delay(5);
      lcden=1;
      delay(5);
      lcden=0;
}
/*************д����******************/
void write_date(uchar date)
{
      lcdrs=1;
      lcdrw=0;
      lcden=0;
      P0=date;
      delay(5);
      lcden=1;
      delay(5);
      lcden=0;
}
/*************��AC ��ַ*****************/
void read_date(void)
{
      lcdrs=0;
      lcdrw=1;
	  delay(5);
	  P0=0xff;
      lcden=1;
      delay(5);
      state=P0;
      delay(5);
      lcden=0;delay(5);
	  state=state&127;
}
/*************д�ַ���******************/
void write_str(uchar *str)
{
      uchar idata i;
      for(i=0;str[i]!='\0';i++)
         write_date(str[i]);
}
/***********Һ����ʼ��***************/
void init(void )
{
      write_com(0x38);       //ģʽ��8λ���ݣ����У�5*7����
      write_com(0x0c);       //����ʾ���޹��
      write_com(0x06);       //���������ƶ�
      write_com(0x01);       //����
}

/**********������ʾ����***************/
void shift(void)
{
   if(sc==1)
   {
   	  read_date();			//��״̬
      write_com(0xc0);	    //��ʾ������ʾ�����½�'s'
	  write_date('s');
	  write_com(state+0x80);//��껹��ԭ��λ��
   }
  else
  {
      read_date();
      write_com(0xc0);	   //�رո�����ʾ
	  write_date(' ');
	  write_com(state+0x80);
  }
  return;
}

/**************����ɨ��*************/
uchar keyscan(void)          //����ɨ�裬�м������򷵻ؼ����ţ����򷵻�null
{     uchar idata key0,key1,keyment=0;
      P3=0XFe;					   //��1
      key0=P3;
      key0=key0&0xf0;
      key1=key0;
      if(key0!=0xf0)
      {
           delay(5);               //����������
           P3=0XFe;
           key0=P3;
           key0=key0&0xf0;
           if(key0==key1)
           {
                switch(key0)
                {
                  case 0xe0:keyment='7';break;
                  case 0xd0:keyment='8';break;
                  case 0xb0:keyment='9';break;
                  case 0x70:keyment=0xfd;break;  //0xfd������1602Һ���еĴ���
                }
                while(key0!=0xf0)  //���ͷŴ���
                {
                  key0=P3;
                  key0=key0&0xf0;
                }
                press=1;		   //������־��1
                return(keyment);
           }
      }
      P3=0XFd;					  //��2
      key0=P3;
      key0=key0&0xf0;
      key1=key0;
      if(key0!=0xf0)
      {
           delay(5);
           P3=0XFd;
           key0=P3;
           key0=key0&0xf0;
           if(key0==key1)
           {
               switch(key0)
               {
                  case 0xe0:keyment='4';break;
                  case 0xd0:keyment='5';break;
                  case 0xb0:keyment='6';break;
                  case 0x70:keyment='*';break;
               }
               while(key0!=0xf0)
               {
                  key0=P3;
                  key0=key0&0xf0;
               }
               press=1;
               return(keyment);
           }
      }
      P3=0XFb;						 //��3
      key0=P3;
      key0=key0&0xf0;
      key1=key0;
      if(key0!=0xf0)
      {
           delay(5);
           P3=0XFb;
           key0=P3;
           key0=key0&0xf0;
           if(key0==key1)
           {
               switch(key0)
               {
                   case 0xe0:keyment='1';break;
                   case 0xd0:keyment='2';break;
                   case 0xb0:keyment='3';break;
                   case 0x70:keyment='-';break;
               }
               while(key0!=0xf0)
               {
                   key0=P3;
                   key0=key0&0xf0;
               }
               press=1;
               return(keyment) ;
           }
      }
      P3=0XF7;					  //��4
      key0=P3;
      key0=key0&0xf0;
      key1=key0;
      if(key0!=0xf0)
      {
           delay(5);
           P3=0XF7;
           key0=P3;
           key0=key0&0xf0;
           if(key0==key1)
           {
               switch(key0)
               {
                 case 0xe0:keyment='.';break;
                 case 0xd0:keyment='0';break;
                 case 0xb0:keyment='=';break;
                 case 0x70:keyment='+';break;
               }
               while(key0!=0xf0)
               {
                 key0=P3;
                 key0=key0&0xf0;
               }
               press=1;
               return(keyment);
           }
     }
     if(reset==0)          //��λ��
     {
           keyment=' ';
           press=1;
           while(reset==0);//���ͷ�
           return(keyment);
	 }
     else if(back==0)	       //����ǰ������
     {
		   keyment='c';
           press=1;
           while(back==0);
           shift();
           return(keyment);
	 }
     else  if(save==0)		   //�������ݼ�
     {	delay(5);
	    if(save==0)
	    { if(sc==0)	   //���ǰ�μ�������
	       {
		      keyment='m';
              press=1;
              while(save==0);
              return(keyment);
		   }
		   else			   //���´洢�����ݻ�����洢������
		   {
              keyment='n';
              press=1;
			  sc=0;
			  shift();
              while(save==0);
              return(keyment);
		   }
		}
     }
	 else if(sfyong==0)		   //������ʱΪ���ù��ܼ�
     {	 delay(5);
	     if(sfyong==0)
	 	 {  keyment='h';
            press=1;
            while(sfyong==0);
            return(keyment);
		 }return(0);
     }else return(0);	   //�޼����·���null
}

/**************��������λ****************/
void fuwei()
{   uchar idata j,i;
    write_com(0x0f);	    //lcd����
    write_com(0x01);
    write_com(0x80);
    resultdate=0;
    for(i=0;i<2;i++)
	{ date[i]=0;bfun[i]=0;pai[0][i]=0;pai[1][i]=0;fsym[i]=0;futojiao[i]=0; //����־��0
	  for(j=0;j<14;j++)		//�ַ������ʼ��
      {
        bdate[i][j]='\0';
      }
	}
    count=0;				//����־��0
    count_num=0;
	proc=0;
    ferror=0;
    eqsign=0;
	sc=0;
	savesign=0;
	ywei=0;
	press=0;
	on_symbol=0;
}
/**************error����******************/
void callerror(void)
{   uchar idata i;
    write_com(0x01);
    write_com(0x80);
    write_str("     error!     ");
    for(i=0;i<200;i++)delay(25); //������ʾ 1s
}
/*************������ǰ���Ŵ���************/
uchar funqian(void)	   //���뺯��ǰ����Ƿ����
{  if((bdate[ferror][0]=='+'||bdate[ferror][0]=='-')&&count==1)
   {
   		fsym[ferror]=bdate[ferror][0];
   		bdate[ferror][0]='\0';
		bdate[ferror][1]='\0';
		count=0;
   }
   if(bdate[ferror][0]!='\0'||bfun[ferror]!=0)//�������뷽ʽ����
   {    callerror();
        huifu();
		return(1);
   }
   return(0);
}
/****************�����ϴ�����****************/
void huifu(void)
{
     uchar j,pro;	   //pro�������ڻָ�proc
     if(proc!=0)proc--;
	 pro=proc;
	 fuwei();
	 proc=pro;
	 for(j=0;j<proc;j++)calculator(process[j]);	//���λָ�֮ǰ�Ĳ���
	 return;
}
/*****************�����Ԥ����*****************/
void  cullars(uchar csym)
{	read_date();		   //���ڶ����Ƿ�������
	ferror++;              //����־+1
	continu=csym;		   //�洢�������
	if(ferror==2&&state<0x43){callerror();huifu();return;}// �ڶ�����������ferror=2������
	if(ferror==2&&state>0x42)	//�ڶ�����������ferror=2���������������
	{
	   press=1;					//ģ�ⰴ����=���͡�M+���������εļ�������Ϊ��һ�μ���ĵ�һ��
	   process_date('=');
	   press=1;
	   process_date('m');
	   ferror=1;				//�ָ��ֳ�������仯
	   if(continu=='^'||continu=='%'){process[proc]='h';
	        proc++;process[proc]=continu;proc++;}
	   else{process[proc]=continu;proc++;}	  //�ָ������������
	}
	if(continu=='%'){write_str(" f");}else write_date(' ');
	write_date(continu);//����������������������ȡ��
	ywei=0;
	savesign=0;
	count_num=1;     //���־��1
	count=0;		 //�����������
	on_symbol=continu;  //������ŵ���
	write_com(0xc2);
	return;
}
/*************����洢����Ԥ����************/
char  memory(void)
{	if((bdate[count_num][0]=='+'||bdate[count_num][0]=='-')&&count==1)//���Ŵ���
    {
	 	ssym[count_num]=bdate[count_num][0];
	 	bdate[count_num][0]='\0';
		bdate[count_num][1]='\0';
		count=0;
	}
    if(bdate[count_num][0]!='\0'){callerror();huifu();return(1);}	//�������뷽ʽ����
	return(0);
}
/**************��������������****************/
void process_date(uchar press_date)
{
     if(form==0){write_com(0x0f);form=1;}   //��ʾ��ʽ�л� �����˸
     if(eqsign==1&&press==1)fuwei();		//��λ�ٴμ��㣬�����������
	 press=0;
	 if(press_date=='c'){huifu();press_date=0;}
	 if(press_date==0)return;         	//�ް���
	 process[proc]=press_date;
	 proc++;
	 calculator(press_date);
	 return;
}
/***************���������Ӵ���***************/
void calculator(uchar press_date)
{
     uchar idata j=0;
	 /*************************************/
	 if(press_date==('h'))	   //���ü�
	 {
	     sc=~sc;		   //���������л���scΪ1ʱ���ú���
		 shift();		   //��ʾ��رո�����ʾ
	 }
     /*************************************/
     else if((press_date<='9'&&press_date>='0')||(press_date=='.')) //���ּ�����
     {	savesign=0;			  //���ɸ��´洢����
        if(sc==0)			  //�Ƿ�Ϊ����scΪ0��������
        {
           if(count<14-ywei)  //δ���ú���ʱ�������14λ��������С����
           {
			       write_date(press_date);
                   bdate[count_num][count]=press_date; //�����ֵ
                   count++;
           }
           else {callerror();huifu();}  //����14λ����,�ָ�

        }
        else switch(press_date)	  //����ʱ
        {             //	    �Ŵ�			�ú�����־����	��������	 ��λ����ʱ����ֻ��(14-ywei)λ
           case '7': j=funqian();if(j==1)return;bfun[ferror]='s';sc=0;shift();ywei=4;write_str("sin ");break; //����sin
           case '8': j=funqian();if(j==1)return;bfun[ferror]='c';sc=0;shift();ywei=4;write_str("cos ");break; //����cos
           case '9': j=funqian();if(j==1)return;bfun[ferror]='t';sc=0;shift();ywei=4;write_str("tan ");break; //����tan
		   case '4': j=funqian();if(j==1)return;bfun[ferror]='e';sc=0;shift();ywei=4;write_str("exp ");break; //����exp
		   case '5': j=funqian();if(j==1)return;bfun[ferror]='l';sc=0;shift();ywei=3;write_str("ln ");break;  //����ln
		   case '6': j=funqian();if(j==1)return;bfun[ferror]='g';sc=0;shift();ywei=3;write_str("Lg ");break;  //����Lg
		   case '1': j=funqian();if(j==1)return;bfun[ferror]='q';sc=0;shift();ywei=5;write_str("sqrt ");break;//����sqrt
		   case '0': j=funqian();if(j==1)return;bfun[ferror]='d';sc=0;shift();ywei=4;write_str("dao ");break; //����dao(����)
		   case '.': if(count==0){ pai[count_num][0]=1;count=14-ywei; }		 //Բ���� pai����	   ��ǰ���޼�Ȩ
					 else{ pai[count_num][1]=1;count=14;}   //  ��ǰ������м�Ȩ�����治�ܸ�����
					 write_date(247);sc=0;shift();break;
		  /************************2��3��˫�������� �������ʹ��*************************/
		   case '2': 	//x^y x��y�η�
					 cullars('^');		 //����������Ŵ������
					 sc=0;shift();
					 break;
		   case '3':	//A/B��������˫���ȣ�
					 cullars('%');		 //����������Ŵ������
					 sc=0;shift();
					 break;
         }
      }
       /*************************************************/
      else if(press_date=='m')       //�ϴμ��������
      {
           if(memory()==1)return;						  //����洢����Ԥ����
           for(j=0;result[j]!='\0';j++)write_date(result[j]);	        //����洢ֵ
           strcpy(bdate[count_num],result);
		   savesign=1;		  //��ʱ���Ը���saveresult�д洢������
		   count=14;          //count=14���ñ���������ȷ��
	  }
      /*************************************************/
      else if(press_date=='n')       //�洢�����ݸ��»����
      {   if(savesign==1)
          {  strcpy(saveresult,result);
             savesign=0;						 //��־��������
             write_com(0x01);
             write_com(0x80);
             write_str("    success!    ");		 //�洢�ɹ���ʾ
             for(j=0;j<200;j++)delay(25);
             fuwei();
          }
          else
          {
		     if(memory()==1)return;						 //����洢����Ԥ����
             for(j=0;saveresult[j]!='\0';j++)write_date(saveresult[j]);	  //����洢ֵ
             strcpy(bdate[count_num],saveresult);
			 count=14;
          }
      }
      /****************'+','-'����*****************/
       else if((press_date=='+')||(press_date=='-'))
       {
		      if(count==0)      // ��ʾ�������ݵķ��ţ���ʱĬ����ֵΪ0
              {
                write_date(press_date);
                bdate[count_num][0]=press_date;
				bdate[count_num][1]='0';
				read_date();			//��״̬
	            write_date('0');
	            write_com(state);//��껹��ԭ��λ��
                count=1;
              }
              else			   
              {
			    cullars(press_date);//Ϊ�������
              }
       }
       /****************'*','/'����*****************/
       else if(press_date==0xfd) //0xfd������1602Һ���еĴ���
       {
	       if(sc==1)	   //���� to �Ƕ�
		   {  if(count!=0)
		      {futojiao[count_num]=1;sc=0;shift();write_date(0xDF);count=14;}
			  else {callerror();huifu();}
		   }
     	   else cullars(press_date);
       }
	   else if(press_date=='*') //0xfd������1602Һ���еĴ���
       {
     	    cullars(press_date);
       }
       /*******************'='�Ŵ���*****************/
       else if(press_date=='=')
       {
            write_com(0x01);           //����
            write_com(0x80);
            write_date(press_date);    //��ʾ�Ⱥ�
		    for(j=0;j<2;j++)		   //��������ĺ�������
			{
			   	date[j]=atof(bdate[j]);  //�������ݣ��ַ���->ʵ��
			   	if(pai[j][0]==1)
				    {  date[j]=3.1415926535897932384626433832795;}
				if(pai[j][1]==1)
			      	{  date[j]=date[j]*3.1415926535897932384626433832795;}//��ǰ׺��Ȩ����
			   	if(ssym[j]=='-')
			   	  	{  date[j]=-date[j];   }	  //����ǰ����
				if(futojiao[j]==1)
				    {   date[j]=date[j]*3.1415926535897932384626433832795/180;}	 //�����Ƿ�ת�Ƕ�
            	if(bfun[j]!=0)					  //�Ƿ��е��ú����������Ⱥ�������
            	{ 	switch(bfun[j])
              		{
					   	case 's': date[j]=sin(date[j]);break;	   //����sin
               			case 'c': date[j]=cos(date[j]);break;	   //����cos
               			case 't': date[j]=tan(date[j]);break;	   //����tan
			   			case 'e': date[j]=exp(date[j]);break;	   //����exp
			   			case 'l': date[j]=log(date[j]);break;	   //����ln
			   			case 'g': date[j]=log10(date[j]);break;	   //����Lg
			   			case 'q': date[j]=sqrt(date[j]);break;	   //����sqrt
			   			case 'd': date[j]=1/date[j];break;		   //����dao(����)
             		}
            	}
				if(fsym[j]=='-')date[j]=-date[j];	 //����ǰ�ķ��Ŵ���
			}
			if(ferror==0)							 //������������
			   {  resultdate=date[0];}
            else									 //������ż���
			{
			   switch(on_symbol)
               {
                  case '+':resultdate=date[0]+date[1];break;
                  case '-':resultdate=date[0]-date[1];break;
                  case '*':resultdate=date[0]*date[1];break;
                  case 0xfd:resultdate=date[0]/date[1];break;       //0xfd������1602Һ���еĴ���
				  case '^':resultdate=pow(date[0],date[1]);break;	//pow()����	x^y
				  case '%':resultdate=fmod(date[0],date[1]);break;  //fmod()���� ��������˫���ȣ�
               }
			}
            sprintf(jieguo,"%g",resultdate);//���ʵ��->�ַ���,���ø�ʽ�ַ�g,ϵͳѡ��%f��%e�����ʽ����λ��Ч����
	        if((jieguo[0]>'9'||jieguo[0]<'0')&&(jieguo[1]>'9'||jieguo[1]<'0')&&jieguo[1]!='\0'&&jieguo[1]!='.')
			 {   callerror();fuwei();return;  }	 //����������1����2���Ϸ�ʱ����Ǽ���Ӣ����ĸ��ʾ
			else strcpy(result,jieguo);   //û���󣬱�������������� M+��
            for(j=0;jieguo[j]!='\0';j++)               //��ʾ���
                 write_date(jieguo[j]);
			for(;j<15;j++)write_date(' ');	 //�ù�����Ļ
			eqsign=1;						 //���Ⱥż���־��1
	   }
	   /*******************��λ*****************/
       else if(press_date==' ')
       {
            fuwei();
       }
	   return;
}
/*********************������**********************/
void main()
{    
      fuwei();		//��������ʼ��
      init();       //��ʾ��ʼ��
	  form=1;		//��ʾ��ʽ��ʼ��
	  proc=0;		//���㹤�̴洢��ʼ��
      write_com(0x80+0x10);						
      write_str("Name:Maxi");			//���������һ��
      write_com(0x80+0x50);					//ָ������
      write_str("SN:201212268031");			//��������ڶ���
      write();
      while(1)      
      {
	  process_date(keyscan()); //������
      }
}
/*********************end**********************/


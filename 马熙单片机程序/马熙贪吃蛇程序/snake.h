#ifndef __SNAKE_H__
#define __SNAKE_H__

#define uchar unsigned char
#define uint  unsigned int

#define SNAKE_MAX_LONG  20	//�����ߵ���󳤶�

extern unsigned char Over;
extern struct 
{
	uchar X[SNAKE_MAX_LONG];
	uchar Y[SNAKE_MAX_LONG];
	uchar Long;  			//�ߵĳ���
	uchar Life; 			//�ߵ�����
	uchar Score;			//�ߵķ���
	uchar Level;			//�ߵĵȼ�              
}Snake;	//�����߽ṹ��

void Init_time0 (void);
void Init_SNAKE(void) ;
void Run_SNAKE(void)  ;

#endif
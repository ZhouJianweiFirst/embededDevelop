#include "stdio.h"
#include "main.h"

//Ҫʹ�õļĴ�����WTCON��WTDAT��WTCNT��WTCLRINT
#define WTCON		(0xE2700000)
#define WTDAT		(0xE2700004)
#define WTCNT		(0xE2700008)
#define WTCLRINT	(0xE270000C)

#define rWTCON		(*(volatile unsigned int *)WTCON)
#define rWTDAT		(*(volatile unsigned int *)WTDAT)
#define rWTCNT		(*(volatile unsigned int *)WTCNT)
#define rWTCLRINT	(*(volatile unsigned int *)WTCLRINT)

void wdt_init_int(void)
{
	rWTCON &= ~(0xff << 8);	//���ú�Ԥ��Ƶ��Ϊ65�� ���ǳ�����ƵΪ66/(65 + 1) = 1MHz
	rWTCON |= (65 << 8);
	
	rWTCON &= ~(0x03 << 3);	//���÷�Ƶ��Ϊ128�����Ƕ��η�ƵΪ1M/128����ʱ������Ϊ128us
	rWTCON |= (0x03 << 3);
	
	rWTDAT = 10000;
	rWTCNT = 10000;
	
	rWTCON &= ~(1 << 2);		//�жϹر�
	rWTCON |= (1 << 0);		//ʹ�ܸ�λ
	
	
	rWTCON |= (1 << 5);	//�򿪿��Ź���һ��Ҫ��һ�ж����úú��ٴ򿪿��Ź���
}

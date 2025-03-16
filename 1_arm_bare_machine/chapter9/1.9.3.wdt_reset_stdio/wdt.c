#include "stdio.h"
#include "main.h"

//要使用的寄存器：WTCON、WTDAT、WTCNT、WTCLRINT
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
	rWTCON &= ~(0xff << 8);	//设置好预分频器为65， 于是初步分频为66/(65 + 1) = 1MHz
	rWTCON |= (65 << 8);
	
	rWTCON &= ~(0x03 << 3);	//设置分频器为128，于是二次分频为1M/128，即时钟周期为128us
	rWTCON |= (0x03 << 3);
	
	rWTDAT = 10000;
	rWTCNT = 10000;
	
	rWTCON &= ~(1 << 2);		//中断关闭
	rWTCON |= (1 << 0);		//使能复位
	
	
	rWTCON |= (1 << 5);	//打开看门狗，一定要在一切都设置好后再打开看门狗。
}

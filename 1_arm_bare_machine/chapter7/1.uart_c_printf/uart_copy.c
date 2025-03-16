/*
* compony: zhongruanguoji
* author: zhoujianwei
* content: 演示串口的发送和接收功能
*/

#define GPA0CON		0xE0200000
#define ULCON0		0xE2900000
#define UCON0		0xE2900004
#define UFCON0		0xE2900008
#define UMCON0		0xE290000C
#define UTRSTAT0	0xE2900010
#define UTXH0		0xE2900020
#define URXH0		0xE2900024
#define UBRDIV0		0xE2900028
#define UDIVSLOT0	0xE290002C

#define rGPA0CON		*((volatile unsigned int *)GPA0CON)
#define rULCON0			*((volatile unsigned int *)ULCON0)
#define rUCON0			*((volatile unsigned int *)UCON0)
#define rUFCON0			*((volatile unsigned int *)UFCON0)
#define rUMCON0			*((volatile unsigned int *)UMCON0)
#define rUTRSTAT0		*((volatile unsigned int *)UTRSTAT0)
#define rUTXH0			*((volatile unsigned int *)UTXH0)
#define rURXH0			*((volatile unsigned int *)URXH0)
#define rUBRDIV0		*((volatile unsigned int *)UBRDIV0)
#define rUDIVSLOT0		*((volatile unsigned int *)UDIVSLOT0)

void uart_init(void)
{
	//初始化TX RX对应的引脚
	rGPA0CON &= ~(0x0ff << 0);		//寄存器GPA0CON的低八位清零
	rGPA0CON |= 0x00000022;			//设置为串口TX RX
	
	rULCON0 = 0x3;
	rUCON0 = 0x5;
	rUFCON0 = 0x00;
	rUMCON0 = 0x00;
	
	rUBRDIV0 = 35;				//根据PCLK_PSYS频率66.7M计算波特率的两个参数。详见s5pv210数据手册，连接性部分1.6.1.12章节公式。
	rUDIVSLOT0 = 0x0888;
}

void puc(char c)
{
	while(!(rUTRSTAT0 & (1 << 1)));
	
	rUTXH0 = c;
}

char getc(void)
{
	while(!(rUTRSTAT0 & (1 << 0)));
	return (rURXH0 & 0x0f);
}

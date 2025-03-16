#include "main.h"
//相关的寄存器有INTP、RTCCON、BCDSEC、BCDMIN、BCDHOUR、BCDDAYWEEK、BCDDAY、BCDMON、BCDYEAR
#define		RTC_BASE	(0xE2800000)

#define		INTP		(0xE2800030)
#define		RTCCON		(0xE2800040)
#define		BCDSEC		(0xE2800070)
#define		BCDMIN		(0xE2800074)
#define 	BCDHOUR		(0xE2800078)
#define 	BCDDAYWEEK	(0xE280007C)
#define 	BCDDAY		(0xE2800080)
#define 	BCDMON		(0xE2800084)
#define 	BCDYEAR		(0xE2800088)
                                  
#define		rINTP			(*((volatile unsigned int *)(RTC_BASE + 0x30)))
#define		rRTCCON			(*((volatile unsigned int *)(RTC_BASE + 0x40)))
#define		rTICCNT			(*((volatile unsigned int *)(RTC_BASE + 0x44)))
#define		rRTCALM			(*((volatile unsigned int *)(RTC_BASE + 0x50)))
#define		rALMSEC			(*((volatile unsigned int *)(RTC_BASE + 0x54)))
#define		rALMMIN			(*((volatile unsigned int *)(RTC_BASE + 0x58)))
#define		rALMHOUR		(*((volatile unsigned int *)(RTC_BASE + 0x5C)))
#define		rALMDAY			(*((volatile unsigned int *)(RTC_BASE + 0x60)))
#define		rALMMON			(*((volatile unsigned int *)(RTC_BASE + 0x64)))
#define		rALMYEAR		(*((volatile unsigned int *)(RTC_BASE + 0x68)))
#define		rBCDSEC			(*((volatile unsigned int *)(RTC_BASE + 0x70)))
#define		rBCDMIN			(*((volatile unsigned int *)(RTC_BASE + 0x74)))
#define		rBCDHOUR		(*((volatile unsigned int *)(RTC_BASE + 0x78)))
#define		rBCDDAYWEEK		(*((volatile unsigned int *)(RTC_BASE + 0x7C)))
#define		rBCDDAY			(*((volatile unsigned int *)(RTC_BASE + 0x80)))
#define		rBCDMON			(*((volatile unsigned int *)(RTC_BASE + 0x84)))
#define		rBCDYEAR		(*((volatile unsigned int *)(RTC_BASE + 0x88)))
#define		rCURTICCNT		(*((volatile unsigned int *)(RTC_BASE + 0x90)))

//十进制数字(如56)转换为十六进制的数(如0x56)
static unsigned int num_2_bcd(unsigned int num)
{
	return (((num / 10) << 4) |(num %10) << 0);
}

//十六进制的数(如0x56)转换为十进制数字(如56)
static unsigned int bcd_2_num(unsigned int bcd)
{
	return (((bcd & 0xf0) >> 4) * 10 + (bcd & 0x0f));
}
// 设置RTC时间
void rtc_set_time(const struct rtc_time *p)
{
	rRTCCON |= (1 << 0);	//修改寄存器内容前，先设置RTC允许修改寄存器，即0bit设置为1
	
	//十进制数应该按照BCD编码方式转换为十六进制的数
	rBCDYEAR = num_2_bcd(p->year);
	rBCDMON = num_2_bcd(p->month);
	rBCDDAY = num_2_bcd(p->day);
	rBCDHOUR = num_2_bcd(p->hour);
	rBCDMIN = num_2_bcd(p->minute);
	rBCDSEC = num_2_bcd(p->second);
	rBCDDAYWEEK = num_2_bcd(p->dayweek);
	
	rRTCCON &= ~(1 << 0);	//寄存器内容修改好后，要及时关闭，即0bit设置为0
}
//获取RTC时间
void rtc_get_time(struct rtc_time *p)
{
	p->year = bcd_2_num(rBCDYEAR) + 2000;
	p->month = bcd_2_num(rBCDMON);
	p->day = bcd_2_num(rBCDDAY);
	p->hour = bcd_2_num(rBCDHOUR);
	p->minute = bcd_2_num(rBCDMIN);
	p->second = bcd_2_num(rBCDSEC);
	p->dayweek = bcd_2_num(rBCDDAYWEEK);
}

void rtc_set_alam(void)
{
	rALMSEC = num_2_bcd(12);	//时钟走到12秒时会触发ALAM中断
	
	rRTCALM |=(1 << 0);
	rRTCALM |= (1 << 6);
}

void isr_rtc_alam(void)
{
	static int i = 0;
	
	printf("rtc_alam: second is %d.", i++);
	
	rINTP |= (1 << 1);	//清除中断挂起
	intc_clearvectaddr();	//清除中断控制器VICADDR寄存器保存的isr
}


















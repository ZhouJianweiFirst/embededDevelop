#include "stdio.h"
#include "int.h"

void uart_init(void);

#define KEY_INTNUM		NUM_EINT2		// 暂时随便找的，下节课会具体改


/* void key_isr(void)
{
	// 暂时随便写的，下节课正式的会写到key.c中去
} */
void isr_eint2(void);


void wait_delay(int i)
{
	volatile int j = 10000;
	while(i--)
	{
		while(j--);
	}
}
int main(void)
{
	uart_init();
	key_init_int();
	
	// 如果程序中要使用中断，就要调用中断初始化来初步初始化中断控制器
	system_init_exception();		//如果要使用中断，就要调用中断初始化来初始化中断控制器
	
	// 绑定isr到中断控制器硬件(VICnVECADDR)
	//intc_setvectaddr(KEY_INTNUM, key_isr);
	intc_setvectaddr(KEY_INTNUM, isr_eint2);
	
	//使能中断
	intc_enable(KEY_INTNUM);
	
	while(1)
	{
		printf("A ");
		wait_delay(10000);
	}
	
	return 0;
}
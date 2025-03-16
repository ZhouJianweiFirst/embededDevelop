#include "stdio.h"
#include "int.h"
#include "main.h"

#define KEY_INTNUM		NUM_WDT		// 暂时随便找的，下节课会具体改


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
	static int i = 0;
	uart_init();
	wdt_init_int();
	
	printf("------------------WDT INTERRUPUT TEST-------------------------, i=%d", i++);
	
	while(1);
	
	return 0;
}
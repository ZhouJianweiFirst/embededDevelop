//#include "stdio.h"
//#include <stdio.h>
#include "pwm.h"

void uart_init(void);
void putc(char c);

void my_delay(void)
{
	volatile unsigned int j = 1000000;	//volatile unsigned int
		while(j--);		
}
int main(void)
{
	uart_init();
	
	timer2_pwm_init();
	
	while(1)
	{
		putc('a');
		my_delay();
	}
	
	
	return 0;
}
#include "stdio.h"
#include "int.h"
#include "main.h"

#define INT_NUM 	NUM_RTC_ALARM


void my_delay(void)
{
	volatile unsigned int i, j;
	i = j = 1000;
	while (i--)
		while(j--);
}


int main(void)
{
	uart_init();
	//key_init();
	
	
	
	system_init_exception();
	rtc_set_alam();
	
	intc_setvectaddr(INT_NUM, isr_rtc_alam);
	intc_enable(INT_NUM);
	
	struct rtc_time tRead;
	
	while(1)
	{
		rtc_get_time(&tRead);
		printf("rtc_time is second: %d", tRead.second);
		my_delay();
	}
	/* printf("====================set rtc time: 2025/1/5 11:53:50 sunday=======================");
	struct rtc_time wrtc=
	{
		.year = 2025,
		.month = 1,
		.day = 5,
		.hour = 11,
		.minute = 53,
		.second = 50,
		.dayweek = 7,
	};
	rtc_set_time(&wrtc);
	
	my_delay();
	printf("====================get rtc time=======================");
	struct rtc_time rrtc;
	
	//get rtc time pollingly
	while (1)
	{
		rtc_get_time(&rrtc);
		printf("rtctime: %d/%d/%d/ %d:%d:%d %d", rrtc.year, rrtc.month, rrtc.day, rrtc.hour, rrtc.minute, rrtc.second, rrtc.dayweek);
		my_delay();
	}
 */
	return 0;
}
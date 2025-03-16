#include "pwm.h"

void timer2_pwm_init(void)	//蜂鸣器的频率设置为2KHz，即蜂鸣器每隔500us震动一次，也就是说，PWM_TOUT2时钟周期(T) * TCNTB2 = 500us,在这里T=4us，所以，TCNB2=500/4=125,duty在这里设置为50%，即125 * （1/2）=63
{
	//GPD0引脚设为TOUT2
	rGPD0 &= ~(0xf << 8);
	rGPD0 |= (2 << 8);
	
	//预分频器设置为65，初次分频：66M/(65+1) = 1MHz
	rTCFG0 &= ~(0xff << 8);
	rTCFG0 |= (65 << 8);
	
	//二次分频，MUX设为4，二次分频：1MHz/4 = 250KHz,PWM_TOUT2时钟周期为1/250K=4us
	rTCFG1 &= ~(0xf << 8);
	rTCFG1 |= (2 << 8);
	//rTCFG1 |= (1 << 8);
	
	rCON |= (1<< 15);	//打开auto_load，即自动加载，这样蜂鸣器才可以反复震动，从而发出声音。
	
	/* rTCNTB2 =  125;
	rTCMPB2 = 63; */
	rTCNTB2 =  500;
	rTCMPB2 = 250;
	
	rCON |= (1 << 13);	//打开manual_update，把TCNTB2的值手动刷新到TCNT2中去
	rCON &= ~(1 << 13);	//别人是这样写的，手动刷新后，就把它关闭了，不清楚不关闭的话会不会有影响。
	
	rCON |= (1 << 12);	//开启PWM定时器，它会产生一个PWM波形，周期为500us，50%的时间为高电平，另外20%的时间为低电平（或者是反转的，可以通过查看波形来确定，如果是反转的，可以置位Timer 2 Output Inverter on/off 为on，这样不就不用修改TCMPB2的值而实现想要的结果了。）
}
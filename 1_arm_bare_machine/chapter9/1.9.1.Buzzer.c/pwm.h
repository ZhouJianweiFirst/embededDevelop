#ifndef _PWM_H_
#define _PWM_H_

#define GPD0	0xE02000A0	//引脚设为TOUT2 rGPD0 &= ~(0xf << 8);rGPD0 |= (0x10 << 8);
#define TCFG0	0xE2500000	//预分频器
#define TCFG1	0xE2500004	//分频器
#define CON		0xE2500008	//rCON |= 0x1 << 12; rCON |= 0x1 << 13; rCON |= 0x1 << 14; rCON |= 0x1 << 15; 
#define TCNTB2	0xE2500024
#define TCMPB2	0xE2500028
#define TCNTO2	0xE250002C

#define rGPD0	(*(volatile unsigned int *)GPD0)
#define rTCFG0	(*(volatile unsigned int *)TCFG0)
#define rTCFG1	(*(volatile unsigned int *)TCFG1)
#define rCON	(*(volatile unsigned int *)CON)
#define rTCNTB2	(*(volatile unsigned int *)TCNTB2)
#define rTCMPB2	(*(volatile unsigned int *)TCMPB2)
#define rTCNTO2	(*(volatile unsigned int *)TCNTO2)

void timer2_pwm_init(void);


#endif //_PWM_H_
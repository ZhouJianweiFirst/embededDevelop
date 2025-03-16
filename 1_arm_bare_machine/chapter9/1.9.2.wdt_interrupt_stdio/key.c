#include "stdio.h"

// 定义操作寄存器的宏
#define GPH0CON		0xE0200C00
#define GPH0DAT		0xE0200C04
#define GPH2CON		0xE0200C40
#define GPH2DAT		0xE0200C44

#define rGPH0CON	(*(volatile unsigned int *)GPH0CON)
#define rGPH0DAT	(*(volatile unsigned int *)GPH0DAT)
#define rGPH2CON	(*(volatile unsigned int *)GPH2CON)
#define rGPH2DAT	(*(volatile unsigned int *)GPH2DAT)

#define EINT_0_CON	0xE0200E00
#define EINT_2_CON	0xE0200E08
#define EINT_0_PEND	0xE0200F40
#define EINT_2_PEND	0xE0200F48
#define EINT_0_MASK	0xE0200F00
#define EINT_2_MASK	0xE0200F08

#define rEINT_0_CON 	(*(volatile unsigned int *)EINT_0_CON)	//
#define rEINT_2_CON 	(*(volatile unsigned int *)EINT_2_CON)
#define rEINT_0_PEND 	(*(volatile unsigned int *)EINT_0_PEND)
#define rEINT_2_PEND 	(*(volatile unsigned int *)EINT_2_PEND)
#define rEINT_0_MASK 	(*(volatile unsigned int *)EINT_0_MASK)
#define rEINT_2_MASK 	(*(volatile unsigned int *)EINT_2_MASK)

extern void key_init_int(void);
extern void isr_eint2(void);
#if 0
/*********************以轮询方式处理按键*****************************/
// 初始化按键
void key_init(void)
{
	// 设置GPHxCON寄存器，设置为输入模式
	// GPH0CON的bit8～15全部设置为0，即可
	rGPH0CON &= ~(0xFF<<8);
	// GPH2CON的bit0～15全部设置为0，即可
	rGPH2CON &= ~(0xFFFF<<0);
}

void delay20ms(void)
{
	// 这个函数作用是延时20ms
	// 因为我们这里是裸机程序，且重点不是真的要消抖，而是教学
	// 所以我这里这个程序只是象征性的，并没有实体
	// 如果是研发，那就要花时间真的调试出延时20ms的程序
	int i, j;
	
	for (i=0; i<100; i++)
	{
		for (j=0; j<1000; j++)
		{
			i * j;
		}
	}
}


void key_polling(void)
{
	// 依次，挨个去读出每个GPIO的值，判断其值为1还是0.如果为1则按键按下，为0则弹起
	
	// 轮询的意思就是反复循环判断有无按键，隔很短时间
	while (1)
	{
		// 对应开发板上标着LEFT的那个按键
		if (rGPH0DAT & (1<<2))
		{
			// 为1，说明没有按键
			led_off();
		}
		else
		{
			// 添加消抖
			// 第一步，延时
			delay20ms();
			// 第二步，再次检验按键状态
			if (!(rGPH0DAT & (1<<2)))
			{
				// 为0，说明有按键
				led1();
				printf("key left.\n");
			}
		}
		
		// 对应开发板上标着DOWN的那个按键
		if (rGPH0DAT & (1<<3))
		{
			// 为1，说明没有按键
			led_off();
		}
		else
		{
			// 为0，说明有按键
			led2();
			printf("key down.\n");
		}
		
		// 对应开发板上标着UP的那个按键
		if (rGPH2DAT & (1<<0))
		{
			// 为1，说明没有按键
			led_off();
		}
		else
		{
			// 为0，说明有按键
			led3();
		}
	}
}

#elif 1
/*********************以中断方式处理按键*****************************/
void key_init_int(void)	//按键中断处理方式初始化
{
	rGPH0CON |= (0xFF << 8);	//按键的GPIO设置为外部中断模式
	rGPH2CON |= (0xFFFF << 0);
	
	//设置中断触发方式为下降沿触发
	rEINT_0_CON &= ~(0xFF << 8);	//bit8~15全部清零  
	rEINT_2_CON &= ~(0xFFFF << 0);		//bit0~15全部清零
	rEINT_0_CON |= (2 << 8 | 2 << 12);	//EINT_2和EINT_3的触发方式设置为下降沿触发
	rEINT_2_CON |= (2 << 0 | 2 << 4 | 2<< 8 | 2 << 12);		//EINT_16~19的触发方式设置为下降沿触发
	
	//清除中断挂起
	rEINT_0_PEND |= (3 << 2);		//清除是写1，不是写0
	rEINT_2_PEND |= (0x0f << 0);
	
	//允许中断发生
	rEINT_0_MASK &= ~(0x03 << 2);		//bit2 bit3清零,允许EINT2 EINT3中断发生
	rEINT_2_MASK &= ~(0x0f << 0);		//bit0~3清零，允许EINT16~19中断发生
	
}

//外部中断通道2，即EXT_INT_2对应的按键，就是GPH0引脚对应的按键，就是开发板上标LEFT的按键
void isr_eint2(void)
{
	//中断处理代码，就是触发中断后真正干活的代码
	printf("isr_eint2.\n");
	
	//清挂起
	rEINT_0_PEND |= (1 << 2);	//清除挂起的EINT2
	intc_clearvectaddr();		//中断已经处理完毕，需要做好清理工作，清除残留。需要清除VICADDR寄存器中保存的isr地址，为后续保存新的isr地址做准备
}

//外部中断通道2，即EXT_INT_2对应的按键，就是GPH0引脚对应的按键，就是开发板上标   的按键
void isr_eint3(void)
{
	printf("isr_eint3.\n");
	
	//清挂起
	rEINT_0_PEND |= (1 << 3);	//清除挂起的EINT2
	intc_clearvectaddr();		//中断已经处理完毕，需要做好清理工作，清除残留。需要清除VICADDR寄存器中保存的isr地址，为后续保存新的isr地址做准备
}

//外部中断通道16~19，即EXT_INT_16~19对应的按键，就是GPH2引脚对应的按键，就是开发板上标LEFT的按键
void isr_eint16_19(void)
{
	//因为EINT16~19是共享中断，所以需要再次区分，是具体哪一个子中断被触发
	if(rEINT_2_PEND & (1 << 0))				//EINT16被触发
	{
		printf("isr_eint16.\n");
	}
	else if(rEINT_2_PEND & (1 << 1))		//EINT17被触发
	{
		printf("isr_eint17.\n");
	}
	else if(rEINT_2_PEND & (1 << 2))		//EINT18被触发
	{
		printf("isr_eint18.\n");
	}
	else if(rEINT_2_PEND & (1 << 3))		//EINT19被触发
	{
		printf("isr_eint19.\n");
	}
	printf("isr_eint2.\n");
	
	//清挂起
	rEINT_2_PEND |= (0x0F << 0);	//清除挂起的EINT2
	intc_clearvectaddr();		//中断已经处理完毕，需要做好清理工作，清除残留。需要清除VICADDR寄存器中保存的isr地址，为后续保存新的isr地址做准备
}

#endif
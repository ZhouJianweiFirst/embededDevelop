#include "stdio.h"
#include "int.h"
#include "main.h"

#define KEY_INTNUM		NUM_WDT		// 暂时随便找的，下节课会具体改


/* void key_isr(void)
{
	// 暂时随便写的，下节课正式的会写到key.c中去
} */

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
	wdt_init_int();
	
	// 如果程序中要使用中断，就要调用中断初始化来初步初始化中断控制器
	system_init_exception();		//如果要使用中断，就要调用中断初始化来初始化中断控制器。包括绑定异常向量表,清理中断使能（如果不清除中断使能，由于外部或者内部原因，触发了某中断，就会造成程序跑飞，很容易出问题，一般做法是，先关闭所有的中断使能，做好一切准备工作后，用到哪个中断再去开启那个中断。），中断模式选择为IRQ，清理正在运行的中断的isr。
	
	// 绑定isr到中断控制器硬件(VICnVECADDR)
	//intc_setvectaddr(KEY_INTNUM, key_isr);
	intc_setvectaddr(KEY_INTNUM, isr_wdt);		//绑定中断处理程序isr_sdt到看门狗中断对应的中断源上
	
	printf("------------------WDT INTERRUPUT TEST-------------------------");
	//使能中断
	intc_enable(KEY_INTNUM);	//在中断控制器中，把看门狗的中断使能打开
	
	while(1);
	
	return 0;
}
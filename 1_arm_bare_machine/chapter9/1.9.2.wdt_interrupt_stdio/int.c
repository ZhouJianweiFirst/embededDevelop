#include "int.h"
#include "stdio.h"
#include "main.h"


void reset_exception(void)
{
	printf("reset_exception.\n");
}

void undef_exception(void)
{
	printf("undef_exception.\n");
}

void sotf_int_exception(void)
{
	printf("sotf_int_exception.\n");
}

void prefetch_exception(void)
{
	printf("prefetch_exception.\n");
}

void data_exception(void)
{
	printf("data_exception.\n");
}

// 主要功能：绑定第一阶段异常向量表；禁止所有中断；选择所有中断类型为IRQ；
// 清除VICnADDR为0（当前正在处理的中断对应的处理函数地址）
void system_init_exception(void)
{
	// 第一阶段处理，绑定异常向量表到对应的异常处理函数
	r_exception_reset = (unsigned int)reset_exception;		//第一阶段处理，绑定复位异常处理函数
	r_exception_undef = (unsigned int)undef_exception;		//第一阶段处理，绑定未定义指令处理函数
	r_exception_sotf_int = (unsigned int)sotf_int_exception;	//第一阶段处理，绑定软中断异常处理函数
	r_exception_prefetch = (unsigned int)prefetch_exception;	//第一阶段处理，绑定预存取异常处理函数
	r_exception_data = (unsigned int)data_exception;			//第一阶段处理，绑定数据异常处理函数
	r_exception_irq = (unsigned int)IRQ_handle;					//第一阶段处理，绑定普通中断异常处理函数
	r_exception_fiq = (unsigned int)IRQ_handle;					//第一阶段处理，绑定快速中断异常处理函数
	
	// 初始化中断控制器的基本寄存器
	intc_init();		//初始化中断控制器的基本寄存器，包括禁止所有中断、选择所有中断类型为IRQ、清除硬件自动保存的激活isr的地址
}

// 清除需要处理的中断的中断处理函数的地址
void intc_clearvectaddr(void)		//清除需要处理的中断的处理函数地址
{
    // VICxADDR:当前正在处理的中断的中断处理函数的地址
    VIC0ADDR = 0;	//初始化VIC0里触发中断对应的处理函数地址
    VIC1ADDR = 0;	//初始化VIC1里触发中断对应的处理函数地址
    VIC2ADDR = 0;	//初始化VIC2里触发中断对应的处理函数地址
    VIC3ADDR = 0;	//初始化VIC3里触发中断对应的处理函数地址
}

// 初始化中断控制器
void intc_init(void)
{
    // 禁止所有中断
	// 为什么在中断初始化之初要禁止所有中断？
	// 因为中断一旦打开，因为外部或者硬件自己的原因产生中断后一定就会寻找isr
	// 而我们可能认为自己用不到这个中断就没有提供isr，这时它自动拿到的就是乱码
	// 则程序很可能跑飞，所以不用的中断一定要关掉。
	// 一般的做法是先全部关掉，然后再逐一打开自己感兴趣的中断。一旦打开就必须
	// 给这个中断提供相应的isr并绑定好。
    VIC0INTENCLEAR = 0xffffffff;	//关掉VIC0的所有中断
    VIC1INTENCLEAR = 0xffffffff;	//关掉VIC1的所有中断
    VIC2INTENCLEAR = 0xffffffff;	//关掉VIC2的所有中断
    VIC3INTENCLEAR = 0xffffffff;	//关掉VIC3的所有中断

    // 选择中断类型为IRQ
    VIC0INTSELECT = 0x0;		//选择VIC0的中断类型。0：IRQ中断；1：FIQ中断，保证中断触发时进入的是IRQ模式（普通中断模式）。
    VIC1INTSELECT = 0x0;		//选择VIC1的中断类型。0：IRQ中断；1：FIQ中断		
    VIC2INTSELECT = 0x0;		//选择VIC2的中断类型。0：IRQ中断；1：FIQ中断
    VIC3INTSELECT = 0x0;		//选择VIC3的中断类型。0：IRQ中断；1：FIQ中断

    // 清VICxADDR
    intc_clearvectaddr();		//清除所有正在处理的中断的处理函数地址，防止硬件自动放到VICnADDR中的isr没有清理干净，造成无法预期的结果。
}


// 绑定我们写的isr到VICnVECTADDR寄存器
// 绑定过之后我们就把isr地址交给硬件了，剩下的我们不用管了，硬件自己会处理
// 等发生相应中断的时候，我们直接到相应的VICnADDR中去取isr地址即可。
// 参数：intnum是int.h定义的物理中断号，handler是函数指针，就是我们写的isr

// VIC0VECTADDR定义为VIC0VECTADDR0寄存器的地址，就相当于是VIC0VECTADDR0～31这个
// 数组（这个数组就是一个函数指针数组）的首地址，然后具体计算每一个中断的时候
// 只需要首地址+偏移量即可。
void intc_setvectaddr(unsigned long intnum, void (*handler)(void))
{
    //VIC0
    if(intnum<32)
    {
        *( (volatile unsigned long *)(VIC0VECTADDR + 4*(intnum-0)) ) = (unsigned)handler;		//0xF200_0100 + intnum * 字节数(4)
    }
    //VIC1
    else if(intnum<64)
    {
        *( (volatile unsigned long *)(VIC1VECTADDR + 4*(intnum-32)) ) = (unsigned)handler;
    }
    //VIC2
    else if(intnum<96)
    {
        *( (volatile unsigned long *)(VIC2VECTADDR + 4*(intnum-64)) ) = (unsigned)handler;
    }
    //VIC3
    else
    {
        *( (volatile unsigned long *)(VIC3VECTADDR + 4*(intnum-96)) ) = (unsigned)handler;
    }
    return;
}


// 使能中断
// 通过传参的intnum来使能某个具体的中断源，中断号在int.h中定义，是物理中断号
void intc_enable(unsigned long intnum)
{
    unsigned long temp;
	// 确定intnum在哪个寄存器的哪一位
	// <32就是0～31，必然在VIC0
    if(intnum<32)
    {
        temp = VIC0INTENABLE;
        temp |= (1<<intnum);		// 如果是第一种设计则必须位操作，第二种设计可以
									// 直接写。也就是VIC0INTENABLE = 1 << intnum.确定intnum在VIC0INTENABLE~VIC3INTENABLE中哪个寄存器的哪一位
        VIC0INTENABLE = temp;
    }
    else if(intnum<64)
    {
        temp = VIC1INTENABLE;
        temp |= (1<<(intnum-32));
        VIC1INTENABLE = temp;
    }
    else if(intnum<96)
    {
        temp = VIC2INTENABLE;
        temp |= (1<<(intnum-64));
        VIC2INTENABLE = temp;
    }
    else if(intnum<NUM_ALL)
    {
        temp = VIC3INTENABLE;
        temp |= (1<<(intnum-96));
        VIC3INTENABLE = temp;
    }
    // NUM_ALL : enable all interrupt
    else
    {
        VIC0INTENABLE = 0xFFFFFFFF;
        VIC1INTENABLE = 0xFFFFFFFF;
        VIC2INTENABLE = 0xFFFFFFFF;
        VIC3INTENABLE = 0xFFFFFFFF;
    }

}

// 禁止中断
// 通过传参的intnum来禁止某个具体的中断源，中断号在int.h中定义，是物理中断号
void intc_disable(unsigned long intnum)
{
	//确定intnum在VIC0INTENCLEAR~VIC3INTENCLEAR中哪个寄存器的哪一位
    unsigned long temp;

    if(intnum<32)
    {
        temp = VIC0INTENCLEAR;
        temp |= (1<<intnum);
        VIC0INTENCLEAR = temp;
    }
    else if(intnum<64)
    {
        temp = VIC1INTENCLEAR;
        temp |= (1<<(intnum-32));
        VIC1INTENCLEAR = temp;
    }
    else if(intnum<96)
    {
        temp = VIC2INTENCLEAR;
        temp |= (1<<(intnum-64));
        VIC2INTENCLEAR = temp;
    }
    else if(intnum<NUM_ALL)
    {
        temp = VIC3INTENCLEAR;
        temp |= (1<<(intnum-96));
        VIC3INTENCLEAR = temp;
    }
    // NUM_ALL : disable all interrupt
    else
    {
        VIC0INTENCLEAR = 0xFFFFFFFF;
        VIC1INTENCLEAR = 0xFFFFFFFF;
        VIC2INTENCLEAR = 0xFFFFFFFF;
        VIC3INTENCLEAR = 0xFFFFFFFF;
    }

    return;
}


// 通过读取VICnIRQSTATUS寄存器，判断其中哪个有一位为1，来得知哪个VIC发生中断了
unsigned long intc_getvicirqstatus(unsigned long ucontroller)
{
    if(ucontroller == 0)
        return	VIC0IRQSTATUS;
    else if(ucontroller == 1)
        return 	VIC1IRQSTATUS;
    else if(ucontroller == 2)
        return 	VIC2IRQSTATUS;
    else if(ucontroller == 3)
        return 	VIC3IRQSTATUS;
    else
    {}
    return 0;
}


 // 真正的中断处理程序。意思就是说这里只考虑中断处理，不考虑保护/恢复现场
void irq_handler(void)
{
	printf("irq_handler.\n");
	// SoC支持很多个（在低端CPU例如2440中有30多个，在210中有100多个）中断
	// 这么多中断irq在第一个阶段走的是一条路，都会进入到irq_handler来
	// 我们在irq_handler中要去区分究竟是哪个中断发生了，然后再去调用该中断
	// 对应的isr。
	
	
	// 虽然硬件已经自动帮我们把isr放入了VICnADDR中，但是因为有4个，所以我们必须
	// 先去软件的检查出来到底哪个VIC中断了，也就是说isr到底在哪个VICADDR寄存器中
	unsigned long vicaddr[4] = {VIC0ADDR,VIC1ADDR,VIC2ADDR,VIC3ADDR};
    int i=0;
    void (*isr)(void) = NULL;

    for(i=0; i<4; i++)
    {
		// 发生一个中断时，4个VIC中有3个是全0，1个的其中一位不是0
        if(intc_getvicirqstatus(i) != 0)
        {
            isr = (void (*)(void)) vicaddr[i];		//isr地址强行转换为返回类型void，参数也是void的函数指针，指向isr函数，
            break;
        }
    }
    (*isr)();		// 通过函数指针来调用函数
}

/* int getVicIntStatus(int intSelect)		//通过读取VICnIRQSTATUS的状态来判断哪个VIC寄存器触发了中断源isr,也就是，硬件帮忙把中断处理函数isr放到VICn的哪个寄存器里了
{
	if(intSelect == 0)
	{
		return VIC0IRQSTATUS;	//0表示VIC0没有中断被触发；1表示有中断出发VIC0
	}
	else if(intSelect == 1)
	{
		return VIC1IRQSTATUS;	//0表示VIC0没有中断被触发；1表示有中断出发VIC0
	}
	else if(intSelect == 2)
	{
		return VIC2IRQSTATUS;	//0表示VIC0没有中断被触发；1表示有中断出发VIC0
	}
	else if(intSelect == 3)
	{
		return VIC3IRQSTATUS;	//0表示VIC0没有中断被触发；1表示有中断出发VIC0
	}
}
void irq_handler(void)		//查找VIC0~3中哪个具体的VIC触发了中断，然后进入对应的VICADDR中获取isr并通过函数指针调用来执行中断处理函数
{
	int vicNum = 0;
	void (*isr)(void) = NULL;
	unsigned long vicAddrArray[4] = {VIC0ADDR, VIC1ADDR, VIC2ADDR, VIC3ADDR}
	
	for(vicNum = 0; vicNum < 4; vicNum++)
	{
		if(getVicIntStatus(vicNum) != 0)		//通过函数getVicIntStatus（）获取irq状态，轮询查看每个VIC的irq状态
		{
			isr = (void (*)(void)) vicAddrArray[vicNum];		//获取被激活的中断源的处理函数指针
			break;
		}
	}
	
	(*isr)();	//通过函数指针调用执行isr
} */








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

// ��Ҫ���ܣ��󶨵�һ�׶��쳣��������ֹ�����жϣ�ѡ�������ж�����ΪIRQ��
// ���VICnADDRΪ0����ǰ���ڴ�����ж϶�Ӧ�Ĵ�������ַ��
void system_init_exception(void)
{
	// ��һ�׶δ������쳣��������Ӧ���쳣������
	r_exception_reset = (unsigned int)reset_exception;		//��һ�׶δ����󶨸�λ�쳣������
	r_exception_undef = (unsigned int)undef_exception;		//��һ�׶δ�����δ����ָ�����
	r_exception_sotf_int = (unsigned int)sotf_int_exception;	//��һ�׶δ��������ж��쳣������
	r_exception_prefetch = (unsigned int)prefetch_exception;	//��һ�׶δ�����Ԥ��ȡ�쳣������
	r_exception_data = (unsigned int)data_exception;			//��һ�׶δ����������쳣������
	r_exception_irq = (unsigned int)IRQ_handle;					//��һ�׶δ�������ͨ�ж��쳣������
	r_exception_fiq = (unsigned int)IRQ_handle;					//��һ�׶δ����󶨿����ж��쳣������
	
	// ��ʼ���жϿ������Ļ����Ĵ���
	intc_init();		//��ʼ���жϿ������Ļ����Ĵ�����������ֹ�����жϡ�ѡ�������ж�����ΪIRQ�����Ӳ���Զ�����ļ���isr�ĵ�ַ
}

// �����Ҫ������жϵ��жϴ������ĵ�ַ
void intc_clearvectaddr(void)		//�����Ҫ������жϵĴ�������ַ
{
    // VICxADDR:��ǰ���ڴ�����жϵ��жϴ������ĵ�ַ
    VIC0ADDR = 0;	//��ʼ��VIC0�ﴥ���ж϶�Ӧ�Ĵ�������ַ
    VIC1ADDR = 0;	//��ʼ��VIC1�ﴥ���ж϶�Ӧ�Ĵ�������ַ
    VIC2ADDR = 0;	//��ʼ��VIC2�ﴥ���ж϶�Ӧ�Ĵ�������ַ
    VIC3ADDR = 0;	//��ʼ��VIC3�ﴥ���ж϶�Ӧ�Ĵ�������ַ
}

// ��ʼ���жϿ�����
void intc_init(void)
{
    // ��ֹ�����ж�
	// Ϊʲô���жϳ�ʼ��֮��Ҫ��ֹ�����жϣ�
	// ��Ϊ�ж�һ���򿪣���Ϊ�ⲿ����Ӳ���Լ���ԭ������жϺ�һ���ͻ�Ѱ��isr
	// �����ǿ�����Ϊ�Լ��ò�������жϾ�û���ṩisr����ʱ���Զ��õ��ľ�������
	// �����ܿ����ܷɣ����Բ��õ��ж�һ��Ҫ�ص���
	// һ�����������ȫ���ص���Ȼ������һ���Լ�����Ȥ���жϡ�һ���򿪾ͱ���
	// ������ж��ṩ��Ӧ��isr���󶨺á�
    VIC0INTENCLEAR = 0xffffffff;	//�ص�VIC0�������ж�
    VIC1INTENCLEAR = 0xffffffff;	//�ص�VIC1�������ж�
    VIC2INTENCLEAR = 0xffffffff;	//�ص�VIC2�������ж�
    VIC3INTENCLEAR = 0xffffffff;	//�ص�VIC3�������ж�

    // ѡ���ж�����ΪIRQ
    VIC0INTSELECT = 0x0;		//ѡ��VIC0���ж����͡�0��IRQ�жϣ�1��FIQ�ж�
    VIC1INTSELECT = 0x0;		//ѡ��VIC1���ж����͡�0��IRQ�жϣ�1��FIQ�ж�		
    VIC2INTSELECT = 0x0;		//ѡ��VIC2���ж����͡�0��IRQ�жϣ�1��FIQ�ж�
    VIC3INTSELECT = 0x0;		//ѡ��VIC3���ж����͡�0��IRQ�жϣ�1��FIQ�ж�

    // ��VICxADDR
    intc_clearvectaddr();		//����������ڴ�����жϵĴ�������ַ
}


// ������д��isr��VICnVECTADDR�Ĵ���
// �󶨹�֮�����ǾͰ�isr��ַ����Ӳ���ˣ�ʣ�µ����ǲ��ù��ˣ�Ӳ���Լ��ᴦ��
// �ȷ�����Ӧ�жϵ�ʱ������ֱ�ӵ���Ӧ��VICnADDR��ȥȡisr��ַ���ɡ�
// ������intnum��int.h����������жϺţ�handler�Ǻ���ָ�룬��������д��isr

// VIC0VECTADDR����ΪVIC0VECTADDR0�Ĵ����ĵ�ַ�����൱����VIC0VECTADDR0��31���
// ���飨����������һ������ָ�����飩���׵�ַ��Ȼ��������ÿһ���жϵ�ʱ��
// ֻ��Ҫ�׵�ַ+ƫ�������ɡ�
void intc_setvectaddr(unsigned long intnum, void (*handler)(void))
{
    //VIC0
    if(intnum<32)
    {
        *( (volatile unsigned long *)(VIC0VECTADDR + 4*(intnum-0)) ) = (unsigned)handler;		//0xF200_0100 + intnum * �ֽ���(4)
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


// ʹ���ж�
// ͨ�����ε�intnum��ʹ��ĳ��������ж�Դ���жϺ���int.h�ж��壬�������жϺ�
void intc_enable(unsigned long intnum)
{
    unsigned long temp;
	// ȷ��intnum���ĸ��Ĵ�������һλ
	// <32����0��31����Ȼ��VIC0
    if(intnum<32)
    {
        temp = VIC0INTENABLE;
        temp |= (1<<intnum);		// ����ǵ�һ����������λ�������ڶ�����ƿ���
									// ֱ��д��Ҳ����VIC0INTENABLE = 1 << intnum.ȷ��intnum��VIC0INTENABLE~VIC3INTENABLE���ĸ��Ĵ�������һλ
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

// ��ֹ�ж�
// ͨ�����ε�intnum����ֹĳ��������ж�Դ���жϺ���int.h�ж��壬�������жϺ�
void intc_disable(unsigned long intnum)
{
	//ȷ��intnum��VIC0INTENCLEAR~VIC3INTENCLEAR���ĸ��Ĵ�������һλ
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


// ͨ����ȡVICnIRQSTATUS�Ĵ������ж������ĸ���һλΪ1������֪�ĸ�VIC�����ж���
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


 // �������жϴ��������˼����˵����ֻ�����жϴ��������Ǳ���/�ָ��ֳ�
void irq_handler(void)
{
	printf("irq_handler.\n");
	// SoC֧�ֺܶ�����ڵͶ�CPU����2440����30�������210����100������ж�
	// ��ô���ж�irq�ڵ�һ���׶��ߵ���һ��·��������뵽irq_handler��
	// ������irq_handler��Ҫȥ���־������ĸ��жϷ����ˣ�Ȼ����ȥ���ø��ж�
	// ��Ӧ��isr��
	
	
	// ��ȻӲ���Ѿ��Զ������ǰ�isr������VICnADDR�У�������Ϊ��4�����������Ǳ���
	// ��ȥ����ļ����������ĸ�VIC�ж��ˣ�Ҳ����˵isr�������ĸ�VICADDR�Ĵ�����
	unsigned long vicaddr[4] = {VIC0ADDR,VIC1ADDR,VIC2ADDR,VIC3ADDR};
    int i=0;
    void (*isr)(void) = NULL;

    for(i=0; i<4; i++)
    {
		// ����һ���ж�ʱ��4��VIC����3����ȫ0��1��������һλ����0
        if(intc_getvicirqstatus(i) != 0)
        {
            isr = (void (*)(void)) vicaddr[i];		//isr��ַǿ��ת��Ϊ��������void������Ҳ��void�ĺ���ָ�룬ָ��isr������
            break;
        }
    }
    (*isr)();		// ͨ������ָ�������ú���
}

/* int getVicIntStatus(int intSelect)		//ͨ����ȡVICnIRQSTATUS��״̬���ж��ĸ�VIC�Ĵ����������ж�Դisr,Ҳ���ǣ�Ӳ����æ���жϴ�����isr�ŵ�VICn���ĸ��Ĵ�������
{
	if(intSelect == 0)
	{
		return VIC0IRQSTATUS;	//0��ʾVIC0û���жϱ�������1��ʾ���жϳ���VIC0
	}
	else if(intSelect == 1)
	{
		return VIC1IRQSTATUS;	//0��ʾVIC0û���жϱ�������1��ʾ���жϳ���VIC0
	}
	else if(intSelect == 2)
	{
		return VIC2IRQSTATUS;	//0��ʾVIC0û���жϱ�������1��ʾ���жϳ���VIC0
	}
	else if(intSelect == 3)
	{
		return VIC3IRQSTATUS;	//0��ʾVIC0û���жϱ�������1��ʾ���жϳ���VIC0
	}
}
void irq_handler(void)		//����VIC0~3���ĸ������VIC�������жϣ�Ȼ������Ӧ��VICADDR�л�ȡisr��ͨ������ָ�������ִ���жϴ�����
{
	int vicNum = 0;
	void (*isr)(void) = NULL;
	unsigned long vicAddrArray[4] = {VIC0ADDR, VIC1ADDR, VIC2ADDR, VIC3ADDR}
	
	for(vicNum = 0; vicNum < 4; vicNum++)
	{
		if(getVicIntStatus(vicNum) != 0)		//ͨ������getVicIntStatus������ȡirq״̬����ѯ�鿴ÿ��VIC��irq״̬
		{
			isr = (void (*)(void)) vicAddrArray[vicNum];		//��ȡ��������ж�Դ�Ĵ�����ָ��
			break;
		}
	}
	
	(*isr)();	//ͨ������ָ�����ִ��isr
} */








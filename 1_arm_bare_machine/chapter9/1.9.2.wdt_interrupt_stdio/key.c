#include "stdio.h"

// ��������Ĵ����ĺ�
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
/*********************����ѯ��ʽ������*****************************/
// ��ʼ������
void key_init(void)
{
	// ����GPHxCON�Ĵ���������Ϊ����ģʽ
	// GPH0CON��bit8��15ȫ������Ϊ0������
	rGPH0CON &= ~(0xFF<<8);
	// GPH2CON��bit0��15ȫ������Ϊ0������
	rGPH2CON &= ~(0xFFFF<<0);
}

void delay20ms(void)
{
	// ���������������ʱ20ms
	// ��Ϊ��������������������ص㲻�����Ҫ���������ǽ�ѧ
	// �����������������ֻ�������Եģ���û��ʵ��
	// ������з����Ǿ�Ҫ��ʱ����ĵ��Գ���ʱ20ms�ĳ���
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
	// ���Σ�����ȥ����ÿ��GPIO��ֵ���ж���ֵΪ1����0.���Ϊ1�򰴼����£�Ϊ0����
	
	// ��ѯ����˼���Ƿ���ѭ���ж����ް��������ܶ�ʱ��
	while (1)
	{
		// ��Ӧ�������ϱ���LEFT���Ǹ�����
		if (rGPH0DAT & (1<<2))
		{
			// Ϊ1��˵��û�а���
			led_off();
		}
		else
		{
			// �������
			// ��һ������ʱ
			delay20ms();
			// �ڶ������ٴμ��鰴��״̬
			if (!(rGPH0DAT & (1<<2)))
			{
				// Ϊ0��˵���а���
				led1();
				printf("key left.\n");
			}
		}
		
		// ��Ӧ�������ϱ���DOWN���Ǹ�����
		if (rGPH0DAT & (1<<3))
		{
			// Ϊ1��˵��û�а���
			led_off();
		}
		else
		{
			// Ϊ0��˵���а���
			led2();
			printf("key down.\n");
		}
		
		// ��Ӧ�������ϱ���UP���Ǹ�����
		if (rGPH2DAT & (1<<0))
		{
			// Ϊ1��˵��û�а���
			led_off();
		}
		else
		{
			// Ϊ0��˵���а���
			led3();
		}
	}
}

#elif 1
/*********************���жϷ�ʽ������*****************************/
void key_init_int(void)	//�����жϴ���ʽ��ʼ��
{
	rGPH0CON |= (0xFF << 8);	//������GPIO����Ϊ�ⲿ�ж�ģʽ
	rGPH2CON |= (0xFFFF << 0);
	
	//�����жϴ�����ʽΪ�½��ش���
	rEINT_0_CON &= ~(0xFF << 8);	//bit8~15ȫ������  
	rEINT_2_CON &= ~(0xFFFF << 0);		//bit0~15ȫ������
	rEINT_0_CON |= (2 << 8 | 2 << 12);	//EINT_2��EINT_3�Ĵ�����ʽ����Ϊ�½��ش���
	rEINT_2_CON |= (2 << 0 | 2 << 4 | 2<< 8 | 2 << 12);		//EINT_16~19�Ĵ�����ʽ����Ϊ�½��ش���
	
	//����жϹ���
	rEINT_0_PEND |= (3 << 2);		//�����д1������д0
	rEINT_2_PEND |= (0x0f << 0);
	
	//�����жϷ���
	rEINT_0_MASK &= ~(0x03 << 2);		//bit2 bit3����,����EINT2 EINT3�жϷ���
	rEINT_2_MASK &= ~(0x0f << 0);		//bit0~3���㣬����EINT16~19�жϷ���
	
}

//�ⲿ�ж�ͨ��2����EXT_INT_2��Ӧ�İ���������GPH0���Ŷ�Ӧ�İ��������ǿ������ϱ�LEFT�İ���
void isr_eint2(void)
{
	//�жϴ�����룬���Ǵ����жϺ������ɻ�Ĵ���
	printf("isr_eint2.\n");
	
	//�����
	rEINT_0_PEND |= (1 << 2);	//��������EINT2
	intc_clearvectaddr();		//�ж��Ѿ�������ϣ���Ҫ�����������������������Ҫ���VICADDR�Ĵ����б����isr��ַ��Ϊ���������µ�isr��ַ��׼��
}

//�ⲿ�ж�ͨ��2����EXT_INT_2��Ӧ�İ���������GPH0���Ŷ�Ӧ�İ��������ǿ������ϱ�   �İ���
void isr_eint3(void)
{
	printf("isr_eint3.\n");
	
	//�����
	rEINT_0_PEND |= (1 << 3);	//��������EINT2
	intc_clearvectaddr();		//�ж��Ѿ�������ϣ���Ҫ�����������������������Ҫ���VICADDR�Ĵ����б����isr��ַ��Ϊ���������µ�isr��ַ��׼��
}

//�ⲿ�ж�ͨ��16~19����EXT_INT_16~19��Ӧ�İ���������GPH2���Ŷ�Ӧ�İ��������ǿ������ϱ�LEFT�İ���
void isr_eint16_19(void)
{
	//��ΪEINT16~19�ǹ����жϣ�������Ҫ�ٴ����֣��Ǿ�����һ�����жϱ�����
	if(rEINT_2_PEND & (1 << 0))				//EINT16������
	{
		printf("isr_eint16.\n");
	}
	else if(rEINT_2_PEND & (1 << 1))		//EINT17������
	{
		printf("isr_eint17.\n");
	}
	else if(rEINT_2_PEND & (1 << 2))		//EINT18������
	{
		printf("isr_eint18.\n");
	}
	else if(rEINT_2_PEND & (1 << 3))		//EINT19������
	{
		printf("isr_eint19.\n");
	}
	printf("isr_eint2.\n");
	
	//�����
	rEINT_2_PEND |= (0x0F << 0);	//��������EINT2
	intc_clearvectaddr();		//�ж��Ѿ�������ϣ���Ҫ�����������������������Ҫ���VICADDR�Ĵ����б����isr��ַ��Ϊ���������µ�isr��ַ��׼��
}

#endif
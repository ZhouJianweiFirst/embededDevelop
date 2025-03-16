#ifndef __MAIN_H__
#define __MAIN_H__

//int.c
void intc_init(void);
void intc_enable(unsigned long intnum);
void intc_disable(unsigned long intnum);
void intc_setvectaddr(unsigned long intnum, void (*handler)(void));
void intc_clearvectaddr(void);
unsigned long intc_getvicirqstatus(unsigned long ucontroller);
void irq_handler(void);
void system_init_exception(void);
void IRQ_handle(void);

//wdt.c
void wdt_init_int(void);
void isr_wdt(void);

//uart.c
void uart_init(void);
/* void putc(char c);
char getc(void); */







#endif

















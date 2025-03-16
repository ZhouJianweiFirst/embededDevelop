#include "interrupt.h"
#include "stdio.h"

// extern void irq_handler(void);
void exception_init(void)
{
	r_exception_reset = (unsigned int)reset_exception;
	r_exception_undefined_instruction = (unsigned int)exception_undefined_instruction;
	r_exception_software_interrupt = (unsigned int)exception_software_interrupt;
	r_exception_prefetch_abort = (unsigned int)exception_prefetch_abort;
	r_exception_data_abort = (unsigned int)exception_data_abort;
	r_exception_irq = (unsigned int)IRQ_handle;
	r_exception_fiq = (unsigned int)IRQ_handle;
}

void reset_exception(void)
{
	printf("reset_exception.\n");
}

void exception_undefined_instruction(void)
{
	printf("exception_undefined_instruction.\n");
}
void exception_software_interrupt(void)
{
	printf("exception_software_interrupt.\n");
}
void exception_prefetch_abort(void)
{
	printf("exception_prefetch_abort.\n");
}
void exception_data_abort(void)
{
	printf("exception_data_abort.\n");
}
void irq_handler(void)
{
	printf("irq_handler.\n");
}
/* void exception_fiq(void)
{
	printf("exception_fiq.\n");
} */
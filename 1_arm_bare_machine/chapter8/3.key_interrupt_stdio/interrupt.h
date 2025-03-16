#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#define exception_vector_table_base 	0xD0037400 

#define exception_reset 				(exception_vector_table_base + 0x00)
#define exception_undefined_instruction (exception_vector_table_base + 0x04)
#define exception_software_interrupt	(exception_vector_table_base + 0x08)
#define exception_prefetch_abort 		(exception_vector_table_base + 0x0C)
#define exception_data_abort 			(exception_vector_table_base + 0x10)
#define exception_irq 					(exception_vector_table_base + 0x18)
#define exception_fiq 					(exception_vector_table_base + 0x1C)

#define r_exception_reset 					(*(volatile unsigned int*)exception_reset)
#define r_exception_undefined_instruction 	(*(volatile unsigned int*)exception_undefined_instruction)
#define r_exception_software_interrupt		(*(volatile unsigned int*)exception_software_interrupt)
#define r_exception_prefetch_abort 			(*(volatile unsigned int*)exception_prefetch_abort)
#define r_exception_data_abort 				(*(volatile unsigned int*)exception_data_abort)
#define r_exception_irq 					(*(volatile unsigned int*)exception_irq)
#define r_exception_fiq 					(*(volatile unsigned int*)exception_fiq)

#endif //_INTERRUPT_H_
#ifndef __IT_H__
#define __IT_H__

//#define STM8_INTERRUPT_FLAG_UART3	0x0001
//#define STM8_INTERRUPT_FLAG_PC2		0x0002
//#define STM8_INTERRUPT_FLAG_PE1		0x0004
//#define INTERRUPT_HANDLER_TIMER1    0x0008
//#define STM8_INTERRUPT_FLAG_PG3		0x0010
//#define STM8_INTERRUPT_FLAG_PE0		0x0020

#define bsp_it_enable()      enableInterrupts()
#define bsp_it_disable()     disableInterrupts()

extern void bsp_it_init();

//extern void bsp_it_register_isp(void (*isp)(char id, void *arg));
//extern void bsp_it_handler(char id, void *arg);

#endif

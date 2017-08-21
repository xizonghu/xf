#ifndef __UART_H__
#define __UART_H__

#include "xftypedef.h"

#define BSP_UART_BAUDRATE_9600      9600
#define BSP_UART_BAUDRATE_57600     57600
#define BSP_UART_BAUDRATE_115200    115200
#define BSP_UART_DATABITS_8         0x00
#define BSP_UART_STOPBITS_1         0x00
#define BSP_UART_STOPBITS_2         0x20
#define BSP_UART_PARITY_NO          0x00
#define BSP_UART_PARITY_EVEN        0x04
#define BSP_UART_PARITY_ODD         0x06

#define BSP_UART0                   0
#define BSP_UART1                   0
#define BSP_UART2                   0
#define BSP_UART3                   1

typedef unsigned char BSP_UART_PORT;

typedef struct BSP_UART_CONFIG_S {
    uint32 baudRate;
    char *bufRx;
    uint8 sizeBufRx;
    void (*on_fiforx_receiver)(char *buf, uint8 size);
} BSP_UART_CONFIG_T;


//extern const BSP_UART_T BSP_UART0, BSP_UART1, BSP_UART2, BSP_UART3;

extern void bsp_uart_init(BSP_UART_PORT uartno, BSP_UART_CONFIG_T *config);
extern void bsp_uart_enable(BSP_UART_PORT uartno, uint8 on);
extern int bsp_uart_write(BSP_UART_PORT uartno, char *buf, uint16 size);
extern int bsp_uart_read(BSP_UART_PORT uartno, char *buf, uint16 size);
extern uint16 bsp_uart_poll_fifo_rx(BSP_UART_PORT uartno);
extern void bsp_uart_test_main();

#endif

/***************************************************************
 * @Author: weiqiang scuec_weiqiang@qq.com
 * @Date: 2024-10-14 09:14:41
 * @LastEditors: weiqiang scuec_weiqiang@qq.com
 * @LastEditTime: 2024-11-11 16:37:26
 * @FilePath: /my_code/source/uart.c
 * @Description: 
 * @
 * @Copyright (c) 2024 by  weiqiang scuec_weiqiang@qq.com , All Rights Reserved. 
***************************************************************/
#include "types.h"

typedef struct UART_REG
{
   uint8_t RHR_THR_DLL;
   uint8_t IER_DLM;
   uint8_t FCR_ISR;
   uint8_t LCR;
   uint8_t MCR;
   uint8_t LSR;
   uint8_t MSR;
   uint8_t SPR;
}UART_REG_t;

#define UART0     (*(volatile UART_REG_t*)(0x10000000))

#define UART_TX_IDLE (1<<5)
#define UART_RX_IDLE (1<<0)

#define WAIT_FOR_TRANS_READY(uartx)    while(0==(uartx.LSR & UART_TX_IDLE )) 
#define WAIT_FOR_RECEIVE_READY(uartx)  while(0==(uartx.LSR & UART_RX_IDLE))

void uart_init()
{
    UART0.IER_DLM = 0x00;//关闭中断

    UART0.LCR |= (1<<7);//允许访问除数锁寄存器
    UART0.IER_DLM = 0x00;//波特率38.4k
    UART0.RHR_THR_DLL = 0x03;
    UART0.LCR &= ~(1<<7);//禁止访问除数锁寄存器

    UART0.LCR |= (0x03<<0);//设置传输字长为8位
    UART0.LCR &= ~(1<<2);//停止位 1位

    uint32_t a = UART0.IER_DLM;
    a |= 0x01;
    UART0.IER_DLM = a;//打开中断
}


void uart_putc(char c)
{
    WAIT_FOR_TRANS_READY(UART0);
    UART0.RHR_THR_DLL = c;
}

char uart_getc()
{
    WAIT_FOR_RECEIVE_READY(UART0);
    return UART0.RHR_THR_DLL;
    
}

void uart_puts(char *s)
{
    while(*s)
    {
        uart_putc(*s);
        s++;
    }
}

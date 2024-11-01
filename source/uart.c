#include "platform.h"

void uart_init()
{
    UART0.IER_DLM = 0x00;//关闭中断

    UART0.LCR |= (1<<7);//允许访问除数锁寄存器
    UART0.IER_DLM = 0x00;//波特率38.4k
    UART0.RHR_THR_DLL = 0x03;
    UART0.LCR &= ~(1<<7);//禁止访问除数锁寄存器

    UART0.LCR |= (0x03<<0);//设置传输字长为8位
    UART0.LCR &= ~(1<<2);//停止位 1位

}


void uart_putc(char c)
{
    while(0 == (UART0.LSR&(1<<5)))//等待THR空
    {
       
    }
    UART0.RHR_THR_DLL = c;
    
}


void uart_puts(char *s)
{
    while(*s)
    {
        uart_putc(*s);
        s++;
    }
}

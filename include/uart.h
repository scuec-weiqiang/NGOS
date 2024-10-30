/***************************************************************
 * @Author: weiqiang scuec_weiqiang@qq.com
 * @Date: 2024-10-26 16:38:03
 * @LastEditors: weiqiang scuec_weiqiang@qq.com
 * @LastEditTime: 2024-10-26 16:38:56
 * @FilePath: /wei/riscv-operating-system-mooc/code/os/my_code/uart.h
 * @Description: 
 * @
 * @Copyright (c) 2024 by  weiqiang scuec_weiqiang@qq.com , All Rights Reserved. 
***************************************************************/
#ifndef __UART_H
#define __UART_H

extern void uart_init();
extern void uart_putc(char c);
extern void uart_puts(char *s);

#endif
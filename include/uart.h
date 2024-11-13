/***************************************************************
 * @Author: weiqiang scuec_weiqiang@qq.com
 * @Date: 2024-10-26 16:38:03
 * @LastEditors: weiqiang scuec_weiqiang@qq.com
 * @LastEditTime: 2024-11-13 00:22:28
 * @FilePath: /my_code/include/uart.h
 * @Description: 
 * @
 * @Copyright (c) 2024 by  weiqiang scuec_weiqiang@qq.com , All Rights Reserved. 
***************************************************************/
#ifndef UART_H
#define UART_H

extern void uart_init();
extern void uart_putc(char c);
extern void uart_puts(char *s);
extern char uart_getc();

#endif
/***************************************************************
 * @Author: weiqiang scuec_weiqiang@qq.com
 * @Date: 2024-10-12 16:19:16
 * @LastEditors: weiqiang scuec_weiqiang@qq.com
 * @LastEditTime: 2024-11-30 17:17:13
 * @FilePath: /my_code/source/kernel.c
 * @Description:
 * @
 * @Copyright (c) 2024 by  weiqiang scuec_weiqiang@qq.com , All Rights Reserved.
 ***************************************************************/
#include "os.h"
#include "clint.h"

char welcome[] = " \
  ***     **\n \
  ** *    **\n \
  **  *   **\n \
  **   *  **\n \
  **    * **\n \
Welcom To NGOS!\n"; \

extern void os_main();

void start_kernel() 
{
    printf(welcome);

    page_init();

    global_interrupt_enable();

    soft_interrupt_enable();

    extern_interrupt_enable();
    extern_interrupt_setting(HART0,UART0_IRQN,1);
    
    hwtimer_ms(1);
    timer_interrupt_enable();

    os_main();
    
}

//info registers mscratch
//info registers mepc



/***************************************************************
 * @Author: weiqiang scuec_weiqiang@qq.com
 * @Date: 2024-10-12 16:19:16
 * @LastEditors: weiqiang scuec_weiqiang@qq.com
 * @LastEditTime: 2024-11-28 16:40:18
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
    page_init();

    hwtimer_ms(1000);
    timer_interrupt_enable();
    
    // extern_interrupt_enable();
    // extern_interrupt_setting(HART0,UART0_IRQN,1);

    soft_interrupt_enable();
    global_interrupt_enable();

    printf(welcome);
    
    
    os_main();
    task_run();
}

//info registers mscratch
//info registers mepc



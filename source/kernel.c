/***************************************************************
 * @Author: weiqiang scuec_weiqiang@qq.com
 * @Date: 2024-10-12 16:19:16
 * @LastEditors: weiqiang scuec_weiqiang@qq.com
 * @LastEditTime: 2024-11-22 22:06:10
 * @FilePath: /my_code/source/kernel.c
 * @Description:
 * @
 * @Copyright (c) 2024 by  weiqiang scuec_weiqiang@qq.com , All Rights Reserved.
 ***************************************************************/
#include "os.h"

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
    timer_interupt_enable();
    
    extern_interupt_enable();
    extern_interupt_setting(HART0,UART0_IRQN,1);

    global_interrupt_enable();

    printf(welcome);
    
    os_main();
    task_run();
}





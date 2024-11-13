/***************************************************************
 * @Author: weiqiang scuec_weiqiang@qq.com
 * @Date: 2024-10-12 16:19:16
 * @LastEditors: weiqiang scuec_weiqiang@qq.com
 * @LastEditTime: 2024-11-13 20:32:54
 * @FilePath: /my_code/source/kernel.c
 * @Description:
 * @
 * @Copyright (c) 2024 by  weiqiang scuec_weiqiang@qq.com , All Rights Reserved.
 ***************************************************************/
#include "os.h"
void task0()
{
    printf("\ntask0 running\n");
    task_delay(25);

}

void task1()
{
    printf("\ntask1 running....\n");
    task_delay(25);
}


void start_kernel() 
{
    page_init();
    sched_init();
    hwtimer_load(CLINT_TIMEBASE_FREQ);
    timer_interupt_init();
    extern_interupt_init(HART0,UART0_IRQN,1);
    task_create(task0);
    task_create(task1);
    task_run();
}





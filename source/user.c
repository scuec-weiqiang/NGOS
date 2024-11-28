/***************************************************************
 * @Author: weiqiang scuec_weiqiang@qq.com
 * @Date: 2024-11-22 15:34:31
 * @LastEditors: weiqiang scuec_weiqiang@qq.com
 * @LastEditTime: 2024-11-28 16:45:02
 * @FilePath: /my_code/source/user.c
 * @Description: 
 * @
 * @Copyright (c) 2024 by  weiqiang scuec_weiqiang@qq.com , All Rights Reserved. 
***************************************************************/
#include "types.h"
#include "sched.h"
#include "clint.h"

void task0()
{
    uint32_t volatile a;
    a++;        
    printf("task0 running  %d\r",a);
    task_delay(5000);

    // RELEASE_CORE(0);
}

void task1()
{
    uint32_t  volatile a;
    printf("task1 running  %d\r",a);
    a++;
    task_delay(5000);
    // RELEASE_CORE(0);
}

void task2()
{
    printf("task2 running \r");
    task_delay(5000);
    // RELEASE_CORE(0);
}

void task3()
{
    printf("task3 running \r");
    task_delay(5000);
    // RELEASE_CORE(0);
}

void os_main()
{
    task_create(task0);
    task_create(task1);
    task_create(task2);
    task_create(task3);
}
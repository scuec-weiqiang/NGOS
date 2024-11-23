/***************************************************************
 * @Author: weiqiang scuec_weiqiang@qq.com
 * @Date: 2024-11-22 15:34:31
 * @LastEditors: weiqiang scuec_weiqiang@qq.com
 * @LastEditTime: 2024-11-22 22:43:37
 * @FilePath: /my_code/source/user.c
 * @Description: 
 * @
 * @Copyright (c) 2024 by  weiqiang scuec_weiqiang@qq.com , All Rights Reserved. 
***************************************************************/
#include "types.h"
#include "sched.h"

void task0()
{
    uint32_t volatile a;
    a++;        
    printf("task0 running  %d\n",a);
    task_delay(50);

    back2kernel;    
}

void task1()
{
    uint32_t  volatile a;
    printf("task1 running  %d\n",a);
    a++;
    task_delay(50);

    back2kernel;
    
}

void task2()
{
    printf("task2 running....\n");
    task_delay(50);
    back2kernel;
}

void task3()
{
    printf("task3 running....\n");
    task_delay(25);
    back2kernel;
}

void os_main()
{
    task_create(task0);
    task_create(task1);
    task_create(task2);
    task_create(task3);
}
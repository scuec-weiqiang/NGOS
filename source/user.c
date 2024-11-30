/***************************************************************
 * @Author: weiqiang scuec_weiqiang@qq.com
 * @Date: 2024-11-22 15:34:31
 * @LastEditors: weiqiang scuec_weiqiang@qq.com
 * @LastEditTime: 2024-11-30 17:40:43
 * @FilePath: /my_code/source/user.c
 * @Description: 
 * @
 * @Copyright (c) 2024 by  weiqiang scuec_weiqiang@qq.com , All Rights Reserved. 
***************************************************************/
#include "types.h"
#include "sched.h"
#include "clint.h"
#include "printf.h"

void task0()
{
    uint32_t a = 0;
    while (1)
    {
        a++;        
        // task_delay(5000);
        printf("task0 running  %d\r\n",a);
        
    }
    
}

void task1()
{
    uint32_t a = 0;
    while (1)
    {
        a++;   
        // task_delay(5000);    
        printf("task1 running  %d\r\n",a);
    }
}

void task2()
{
    uint32_t a = 0;
    while (1)
    {
        a++;       
        // task_delay(5000); 
        printf("task2 running  %d\r\n",a);
    }
}

void task3()
{
    uint32_t a = 0;
    while (1)
    {
        a++;        
        // task_delay(5000);
        printf("task3 running  %d\r\n",a);
    }
}

void os_main()
{
    task_create(task0,200,0);
    task_create(task1,100,0);
    task_create(task2,100,0);
    task_create(task3,100,0);
    task_run();
}
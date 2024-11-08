/***************************************************************
 * @Author: weiqiang scuec_weiqiang@qq.com
 * @Date: 2024-10-31 12:22:31
 * @LastEditors: weiqiang scuec_weiqiang@qq.com
 * @LastEditTime: 2024-11-07 15:19:15
 * @FilePath: /my_code/source/sched.c
 * @Description: 
 * @
 * @Copyright (c) 2024 by  weiqiang scuec_weiqiang@qq.com , All Rights Reserved. 
***************************************************************/
#include "types.h"
#include "printf.h"

#define TASK_STACK_SIZE 1024 //每个任务分配1k的栈大小
#define TASK_SIZE 1

//reg context struct
typedef struct reg_context
{
    reg_t zero;
    reg_t ra ;
    reg_t sp ;
    reg_t gp ;
    reg_t tp ;
    reg_t t0 ;
    reg_t t1 ;
    reg_t t2 ;
    reg_t s0 ;
    reg_t s1 ;
    reg_t a0 ;
    reg_t a1 ;
    reg_t a2 ;
    reg_t a3 ;
    reg_t a4 ;
    reg_t a5 ;
    reg_t a6 ;
    reg_t a7 ;
    reg_t s2 ;
    reg_t s3 ;
    reg_t s4 ;
    reg_t s5 ;
    reg_t s6 ;
    reg_t s7 ;
    reg_t s8 ;
    reg_t s9 ;
    reg_t s10;
    reg_t s11;
    reg_t t3 ;
    reg_t t4 ;
    reg_t t5 ;
    reg_t t6 ;
}reg_context_t;

typedef struct task_crt_block
{
    void (*task[TASK_SIZE])();
    reg_context_t reg_context[TASK_SIZE];
    uint8_t  __attribute__((aligned(16))) task_stack[TASK_SIZE][TASK_STACK_SIZE];
    uint32_t count;
}tcb_t;

tcb_t tcb = {0};

//此函数定义在entry.S文件中
extern void _switch_to(reg_context_t* next);


void delay(uint32_t a)
{   uint32_t i=a;
    uint32_t j=a;
    uint32_t k=a;
    for(;a>0;a--)
    {
        for(;i>0;i--)
        {
            for(;j>0;j--)
            {
                for(;k>0;k--)
                {

                }
            }
        }
    }
    
}

void task_create(void (*task)(void))
{   
    tcb.task[tcb.count] = task;
    tcb.reg_context[tcb.count].sp = (uint8_t*)&(tcb.task_stack[tcb.count]) + TASK_STACK_SIZE;
    tcb.reg_context[tcb.count].ra = task;
    tcb.count++;
}
uint32_t current = 0;
void task_run()
{   
    asm volatile("csrw mscratch, %0" : : "r" (0));
    while(1)
    {
        tcb.task[current]();
    }
    
}

void task0()
{
    printf("task0 running\n");
    current =(current+1) % tcb.count;
    _switch_to(&tcb.reg_context[current]);
}

void task1()
{
    printf("task1 running....\n");
    current =(current+1) % tcb.count;
    _switch_to(&tcb.reg_context[current]);
}


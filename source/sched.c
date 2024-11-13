/***************************************************************
 * @Author: weiqiang scuec_weiqiang@qq.com
 * @Date: 2024-10-31 12:22:31
 * @LastEditors: weiqiang scuec_weiqiang@qq.com
 * @LastEditTime: 2024-11-13 16:07:33
 * @FilePath: /my_code/source/sched.c
 * @Description: 
 * @
 * @Copyright (c) 2024 by  weiqiang scuec_weiqiang@qq.com , All Rights Reserved. 
***************************************************************/
#include "types.h"
#include "printf.h"
#include "list.h"
#include "page.h"

#define TASK_STACK_SIZE 1024 //每个任务分配1k的栈大小

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

//此函数定义在switch.S文件中
extern void __switch_to(reg_context_t* next);

typedef struct task_ctrl_block
{
    void (*task)();
    reg_context_t reg_context;
    uint8_t  __attribute__((aligned(16))) task_stack[TASK_STACK_SIZE];
    list_t task_node;
}tcb_t;

void task_delay(volatile int count)
{
	count *= 50000;
	while (count--);
}

void task_default()
{
	
}

tcb_t task_head;

void sched_init()
{
    task_head.task = task_default;
    // task_head.reg_context.ra = task_default;
    task_head.reg_context.sp = task_head.task_stack;
    INIT_LIST_HEAD(&task_head.task_node);
}

void task_create(void (*task)(void))
{   
    tcb_t* task_ctrl_block = page_alloc(1);
    task_ctrl_block->task = task;
    // task_ctrl_block->reg_context.ra = task;
    task_ctrl_block->reg_context.sp = task_ctrl_block->task_stack;
    
    list_add_tail(&task_head.task_node,&task_ctrl_block->task_node);
}

void task_run()
{   
    tcb_t* pos = &task_head;
    asm volatile("csrw mscratch,%0": :"r"(&(pos->reg_context)));
    while(1)
    {
        pos->task();
        // __switch_to(&((list_entry(pos->task_node.next,tcb_t,task_node))->reg_context));
        pos = list_entry(pos->task_node.next,tcb_t,task_node);
    }
    
}




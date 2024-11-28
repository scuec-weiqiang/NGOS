/***************************************************************
 * @Author: weiqiang scuec_weiqiang@qq.com
 * @Date: 2024-10-31 12:22:31
 * @LastEditors: weiqiang scuec_weiqiang@qq.com
 * @LastEditTime: 2024-11-28 16:36:19
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
    reg_t mepc ;
}reg_context_t;

typedef struct task_ctrl_block
{   
    uint32_t id;
    void (*task)();
    reg_context_t reg_context;
    uint8_t  __attribute__((aligned(16))) task_stack[TASK_STACK_SIZE];
    list_t task_node;
}tcb_t;
tcb_t* task_head = NULL_PTR;
tcb_t* task_current = NULL_PTR;

reg_context_t sched_context;
uint8_t  __attribute__((aligned(16))) sched_stack[32];

//此函数定义在switch.S文件中
extern void __sw_save(reg_context_t* next);
extern void __sw_without_save(reg_context_t* next);
/***************************************************************
 * @description: 
 * @param {volatile int} count [in/out]:  
 * @return {*}
***************************************************************/
void task_delay(volatile int count)
{
	count *= 50000;
	while (count--);
}

/***************************************************************
 * @description: 
 * @return {*}
***************************************************************/
void sched()
{
    task_current = list_entry(task_current->task_node.next,tcb_t,task_node); 
    __sw_save(&task_current->reg_context); 
}

/***************************************************************
 * @description: 
 * @return {*}
***************************************************************/
void task_create(void (*task)(void))
{   
    tcb_t* task_ctrl_block = page_alloc(1);

    switch ((uint32_t)task_head)
    {
        case (uint32_t)NULL_PTR://第一次创建任务，将其作为头节点
            static uint32_t id = 0;

            sched_context.ra = sched;//初始化调度器
            sched_context.mepc = sched_context.ra;
            sched_context.sp = &sched_stack[31];

            task_head = task_ctrl_block;
            INIT_LIST_HEAD(&task_head->task_node);

        default:
            task_ctrl_block->id = id;
            task_ctrl_block->task = task;
            task_ctrl_block->reg_context.ra = (uint32_t)task;
            task_ctrl_block->reg_context.mepc = task_ctrl_block->reg_context.ra;
            task_ctrl_block->reg_context.sp = (uint32_t)&task_ctrl_block->task_stack[TASK_STACK_SIZE-1];
            list_add_tail(&task_head->task_node,&task_ctrl_block->task_node);
            id++;
        break;
    }

}

void task_distory(void (*task)(void))
{
    tcb_t* node = list_entry(task,tcb_t,task);
    list_del(&node->task_node);
    page_free(node);
}

void task_run()
{   
    if(NULL_PTR != task_head)
    {
        task_current = task_head;
        __sw_without_save(&task_current->reg_context);
    }
    panic("\n  no task to exec!");
}
        


// p /x *task_ctrl_block

// t0 0x8000c000
// t1 0x8000d000

// x /1xw 0x8000c07c
//x /1xw 0x8000c07c





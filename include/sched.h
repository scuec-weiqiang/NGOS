/***************************************************************
 * @Author: weiqiang scuec_weiqiang@qq.com
 * @Date: 2024-10-31 16:30:19
 * @LastEditors: weiqiang scuec_weiqiang@qq.com
 * @LastEditTime: 2024-11-30 16:14:08
 * @FilePath: /my_code/include/sched.h
 * @Description: 
 * @
 * @Copyright (c) 2024 by  weiqiang scuec_weiqiang@qq.com , All Rights Reserved. 
***************************************************************/
#ifndef SCHED_H
#define SCHED_H

#include "types.h"

typedef struct task_ctrl_block tcb_t;

extern tcb_t* task_head ;
extern tcb_t* task_current;

typedef struct reg_context reg_context_t;
extern reg_context_t sched_context;
extern uint8_t sched_stack[1];

extern void task_create(void (*task)(void),uint64_t time_slice,uint8_t priority);
extern void task_distory(void (*task)(void));
extern void task_run();
extern void task_delay(volatile int count);

#endif
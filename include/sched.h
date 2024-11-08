/***************************************************************
 * @Author: weiqiang scuec_weiqiang@qq.com
 * @Date: 2024-10-31 16:30:19
 * @LastEditors: weiqiang scuec_weiqiang@qq.com
 * @LastEditTime: 2024-11-03 23:19:15
 * @FilePath: /my_code/include/sched.h
 * @Description: 
 * @
 * @Copyright (c) 2024 by  weiqiang scuec_weiqiang@qq.com , All Rights Reserved. 
***************************************************************/
#ifndef SCHED_H
#define SCHED_H

#include "types.h"

extern void task_create(void (*task)(void));
extern void task_run();
extern uint32_t current;
#endif
/***************************************************************
 * @Author: weiqiang scuec_weiqiang@qq.com
 * @Date: 2024-10-31 16:30:19
 * @LastEditors: weiqiang scuec_weiqiang@qq.com
 * @LastEditTime: 2024-11-13 16:05:37
 * @FilePath: /my_code/include/sched.h
 * @Description: 
 * @
 * @Copyright (c) 2024 by  weiqiang scuec_weiqiang@qq.com , All Rights Reserved. 
***************************************************************/
#ifndef SCHED_H
#define SCHED_H

#include "types.h"

extern void sched_init();
extern void task_create(void (*task)(void));
extern void task_run();
extern void task_delay(volatile int count);
#endif
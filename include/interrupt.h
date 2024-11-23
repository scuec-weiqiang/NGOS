/***************************************************************
 * @Author: weiqiang scuec_weiqiang@qq.com
 * @Date: 2024-11-12 23:46:59
 * @LastEditors: weiqiang scuec_weiqiang@qq.com
 * @LastEditTime: 2024-11-13 23:41:42
 * @FilePath: /my_code/include/interrupt.h
 * @Description: 
 * @
 * @Copyright (c) 2024 by  weiqiang scuec_weiqiang@qq.com , All Rights Reserved. 
***************************************************************/
#ifndef __INTERRUPT_H
#define __INTERRUPT_H

#include "types.h"

extern void global_interrupt_enable();
extern void global_interrupt_disable();

extern void timer_interupt_enable();
extern void timer_interupt_disable();

extern void extern_interupt_enable();
extern void extern_interupt_disable();

extern void extern_interupt_setting(uint32_t hart,uint32_t iqrn,uint32_t priority);

#endif

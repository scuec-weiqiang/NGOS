/***************************************************************
 * @Author: weiqiang scuec_weiqiang@qq.com
 * @Date: 2024-11-13 19:54:21
 * @LastEditors: weiqiang scuec_weiqiang@qq.com
 * @LastEditTime: 2024-11-15 17:29:19
 * @FilePath: /my_code/include/hwtimer.h
 * @Description: 
 * @
 * @Copyright (c) 2024 by  weiqiang scuec_weiqiang@qq.com , All Rights Reserved. 
***************************************************************/
#ifndef __HWTIMER_H
#define __HWTIMER_H

#include "types.h"
#include "platform.h"

extern void hwtimer_load(uint64_t value);
#define hwtimer_ms(x) hwtimer_load(10000*x)

#endif 
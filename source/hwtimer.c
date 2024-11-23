/***************************************************************
 * @Author: weiqiang scuec_weiqiang@qq.com
 * @Date: 2024-11-13 19:49:17
 * @LastEditors: weiqiang scuec_weiqiang@qq.com
 * @LastEditTime: 2024-11-13 23:32:27
 * @FilePath: /my_code/source/hwtimer.c
 * @Description: 
 * @
 * @Copyright (c) 2024 by  weiqiang scuec_weiqiang@qq.com , All Rights Reserved. 
***************************************************************/
#include "types.h"
#include "clint.h"

void hwtimer_load(uint64_t value)
{   
    uint64_t temp = __clint_mtime_get();
    temp += value;
    __clint_mtimecmp_set(0,temp);
}
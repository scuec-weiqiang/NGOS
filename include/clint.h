/***************************************************************
 * @Author: weiqiang scuec_weiqiang@qq.com
 * @Date: 2024-11-13 18:42:21
 * @LastEditors: weiqiang scuec_weiqiang@qq.com
 * @LastEditTime: 2024-11-13 23:39:45
 * @FilePath: /my_code/include/clint.h
 * @Description: 
 * @
 * @Copyright (c) 2024 by  weiqiang scuec_weiqiang@qq.com , All Rights Reserved. 
***************************************************************/
#ifndef __CLINT_H
#define __CLINT_H

#include "types.h"

#define CLINT_BASE          0x02000000

#define CLINT_MTIME                 (CLINT_BASE + (0xbff8))
#define CLINT_MTIMECMP(hartid)      (CLINT_BASE + (0x4000)+ 8*(hartid))

__SELF __INLINE uint64_t __clint_mtime_get()
{
    return *(uint64_t*)CLINT_MTIME;
}

__SELF __INLINE void __clint_mtimecmp_set(uint32_t hartid,uint64_t value)
{
    *(uint64_t*)CLINT_MTIMECMP(hartid) = value;
}

#endif 
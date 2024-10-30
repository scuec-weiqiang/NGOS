/***************************************************************
 * @Author: weiqiang scuec_weiqiang@qq.com
 * @Date: 2024-10-26 16:38:14
 * @LastEditors: weiqiang scuec_weiqiang@qq.com
 * @LastEditTime: 2024-10-26 16:41:34
 * @FilePath: /wei/riscv-operating-system-mooc/code/os/my_code/page.h
 * @Description: 
 * @
 * @Copyright (c) 2024 by  weiqiang scuec_weiqiang@qq.com , All Rights Reserved. 
***************************************************************/
#ifndef __PAGE_H
#define __PAGE_H

#include "types.h"

extern void page_init();
extern void* page_alloc(uint32_t npages);
extern void page_free(void* p);

#endif

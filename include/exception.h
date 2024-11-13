/***************************************************************
 * @Author: weiqiang scuec_weiqiang@qq.com
 * @Date: 2024-11-12 23:46:59
 * @LastEditors: weiqiang scuec_weiqiang@qq.com
 * @LastEditTime: 2024-11-13 19:57:40
 * @FilePath: /my_code/include/exception.h
 * @Description: 
 * @
 * @Copyright (c) 2024 by  weiqiang scuec_weiqiang@qq.com , All Rights Reserved. 
***************************************************************/
#ifndef __EXCEPTION_H
#define __EXCEPTION_H

extern void extern_interupt_init(uint32_t hart,uint32_t iqrn,uint32_t priority);
extern void timer_interupt_init();
#endif

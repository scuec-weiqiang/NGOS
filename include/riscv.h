/***************************************************************
 * @Author: weiqiang scuec_weiqiang@qq.com
 * @Date: 2024-11-11 18:41:39
 * @LastEditors: weiqiang scuec_weiqiang@qq.com
 * @LastEditTime: 2024-11-13 19:39:17
 * @FilePath: /my_code/include/riscv.h
 * @Description: 
 * 
 * @
 * @Copyright (c) 2024 by  weiqiang scuec_weiqiang@qq.com , All Rights Reserved. 
***************************************************************/
#ifndef _RISCV_H
#define _RISCV_H

#include "types.h"

/***************************************************************
 * @description: 
 * @return {*}
***************************************************************/
__SELF __INLINE reg_t mip_r()
{
    reg_t a;
    asm volatile("csrr a0,mip");
    asm volatile("mv %0,a0":"=r"(a));
    return a;
}

/***************************************************************
 * @description: 
 * @param {reg_t} a [in/out]:  
 * @return {*}
***************************************************************/
__SELF __INLINE void mip_w(reg_t a)
{
    asm volatile("csrw mip,%0"::"r"(a));
}

/***************************************************************
 * @description: 
 * @return {*}
***************************************************************/
__SELF __INLINE reg_t mie_r()
{   
    reg_t a;
    asm volatile("csrr a0,mie");
    asm volatile("mv %0,a0":"=r"(a));
    return a;
}

/***************************************************************
 * @description: 
 * @param {reg_t} a [in/out]:  
 * @return {*}
***************************************************************/
__SELF __INLINE void mie_w(reg_t a)
{   
    asm volatile("csrw mie,%0"::"r"(a));
}

/***************************************************************
 * @description: 
 * @return {*}
***************************************************************/
__SELF __INLINE reg_t mcause_r()
{   
    reg_t a;
    asm volatile("csrr a0,mcause");
    asm volatile("mv %0,a0":"=r"(a));
    return a;
}

/***************************************************************
 * @description: 
 * @return {*}
***************************************************************/
__SELF __INLINE reg_t mepc_r()
{   
    reg_t a;
    asm volatile("csrr a0,mepc");
    asm volatile("mv %0,a0":"=r"(a));
    return a;
}

__SELF __INLINE void mepc_w(reg_t a)
{   
    asm volatile("csrw mepc,%0"::"r"(a));
}

/***************************************************************
 * @description: 
 * @return {*}
***************************************************************/
__SELF __INLINE reg_t mstatus_r()
{   
    reg_t a;
    asm volatile("csrr a0,mstatus");
    asm volatile("mv %0,a0":"=r"(a));
    return a;
}

/***************************************************************
 * @description: 
 * @param {reg_t} a [in/out]:  
 * @return {*}
***************************************************************/
__SELF __INLINE void mstatus_w(reg_t a)
{   
    asm volatile("csrw mstatus,%0"::"r"(a));
}


#endif
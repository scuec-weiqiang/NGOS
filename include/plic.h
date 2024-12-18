/***************************************************************
 * @Author: weiqiang scuec_weiqiang@qq.com
 * @Date: 2024-11-09 19:42:48
 * @LastEditors: weiqiang scuec_weiqiang@qq.com
 * @LastEditTime: 2024-11-13 00:23:21
 * @FilePath: /my_code/include/plic.h
 * @Description: 
 * @
 * @Copyright (c) 2024 by  weiqiang scuec_weiqiang@qq.com , All Rights Reserved. 
***************************************************************/
#ifndef PLIC_H
#define PLIC_H

#include "types.h"
#include "platform.h"

#define PLIC_BASE                    0x0c000000
#define PLIC_PRIORITY_BASE            (PLIC_BASE + (0x0000))
#define PLIC_PENDING_BASE             (PLIC_BASE + (0x1000))
#define PLIC_INT_EN_BASE              (PLIC_BASE + (0x2000))
#define PLIC_INT_THRSHOLD_BASE        (PLIC_BASE + (0x200000))
#define PLIC_CLAIM_BASE               (PLIC_BASE + (0x200004))
#define PLIC_COMPLETE_BASE            (PLIC_BASE + (0x200004))

/***************************************************************
 * @description: 
 * @param {uint32_t} irqn [in/out]:  
 * @param {uint32_t} priority [in/out]:  
 * @return {*}
***************************************************************/
__SELF __INLINE void __plic_priority_set(uint32_t irqn,uint32_t priority)
{
    *(uint32_t*)(PLIC_PRIORITY_BASE  + irqn*4) = priority;
}

/***************************************************************
 * @description: 
 * @param {uint32_t} irqn [in/out]:  
 * @return {*}
***************************************************************/
__SELF __INLINE uint32_t __plic_priority_get(uint32_t irqn)
{
    return *(uint32_t*)(PLIC_PRIORITY_BASE  + irqn*4);
}

/***************************************************************
 * @description: 
 * @param {uint32_t} irqn [in/out]:  
 * @return {*}
***************************************************************/
__SELF __INLINE uint32_t __plic_pending_get(uint32_t irqn)
{
    return ( (*(uint32_t*)(PLIC_PENDING_BASE  + irqn/32)) & (1<<(irqn%32)) )?1:0;
}

/***************************************************************
 * @description: 
 * @param {uint32_t} hart [in/out]:  
 * @param {uint32_t} irqn [in/out]:  
 * @return {*}
***************************************************************/
__SELF __INLINE void __plic_interrupt_enable(uint32_t hart,uint32_t irqn)
{
    (*(uint32_t*)(PLIC_INT_EN_BASE + hart*0x80 + 4*(irqn/32))) |= (1<<(irqn%32));
}

/***************************************************************
 * @description: 
 * @param {uint32_t} hart [in/out]:  
 * @param {uint32_t} irqn [in/out]:  
 * @return {*}
***************************************************************/
__SELF __INLINE void __plic_interrupt_disable(uint32_t hart,uint32_t irqn)
{
    (*(uint32_t*)(PLIC_INT_EN_BASE + hart*0x80 +  4*(irqn/32))) &= ~(1<<(irqn%32));
}

/***************************************************************
 * @description: 
 * @param {uint32_t} hart [in/out]:  
 * @param {uint32_t} threshold [in/out]:  
 * @return {*}
***************************************************************/
__SELF __INLINE void __plic_threshold_set(uint32_t hart,uint32_t threshold)
{
    (*(uint32_t*)(PLIC_INT_THRSHOLD_BASE + hart*0x1000 )) = threshold;
}

/***************************************************************
 * @description: 
 * @param {uint32_t} hart [in/out]:  
 * @return {*}
***************************************************************/
__SELF __INLINE uint32_t __plic_claim(uint32_t hart)
{
    return (*(uint32_t*)(PLIC_CLAIM_BASE  + hart*0x1000 ));
}

/***************************************************************
 * @description: 
 * @param {uint32_t} hart [in/out]:  
 * @param {uint32_t} irqn [in/out]:  
 * @return {*}
***************************************************************/
__SELF __INLINE void __plic_complete(uint32_t hart,uint32_t irqn)
{
    (*(uint32_t*)(PLIC_CLAIM_BASE  + hart*0x1000)) = irqn;
}


#endif
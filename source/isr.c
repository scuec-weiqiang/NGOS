/***************************************************************
 * @Author: weiqiang scuec_weiqiang@qq.com
 * @Date: 2024-11-13 23:13:53
 * @LastEditors: weiqiang scuec_weiqiang@qq.com
 * @LastEditTime: 2024-11-28 16:40:05
 * @FilePath: /my_code/source/isr.c
 * @Description: 
 * @
 * @Copyright (c) 2024 by  weiqiang scuec_weiqiang@qq.com , All Rights Reserved. 
***************************************************************/
#include "sched.h"
#include "uart.h"
#include "printf.h"
#include "hwtimer.h"

#include "plic.h"
#include "clint.h"

#include "types.h"
#include "riscv.h"

extern void __sw_without_save(reg_context_t* next);

/***************************************************************
 * @description: 
 * @return {*}
***************************************************************/
void uart0_iqr()
{   
    char a = uart_getc();
    printf("%c",a);
    if('\r'==a)
        printf("\n");     
}


/***************************************************************
 * @description: 
 * @param {uint32_t} mcause [in/out]:  
 * @param {uint32_t} mtval [in/out]:  
 * @param {uint32_t} mepc [in/out]:  
 * @return {*}
***************************************************************/
void trap_handler(uint32_t mcause,uint32_t mtval,uint32_t mepc)
{
    uint32_t code = mcause & 0x7fffffff;
   
    if(!(mcause & 0x80000000))//异常
    {
        printf("casue code is %d\n",code);
        printf("mtval is %d\n",mtval);
        panic("trap!\n"); 
    }
}

/***************************************************************
 * @description: 
 * @param {uint32_t} mepc [in/out]:  
 * @return {*}
***************************************************************/
uint32_t extern_interrupt_handler(uint32_t mepc)
{
    uint32_t irqn = __plic_claim(0);
    switch (irqn)
    {
        case 10:
            uart0_iqr();
        break;

        default:
            printf("unexpected extern interrupt!");
        break;
    }
    __plic_complete(0,irqn);
    return mepc+4;

}

uint32_t __tick = 0;
/***************************************************************
 * @description: 
 * @param {uint32_t} mepc [in/out]:  
 * @return {*}
***************************************************************/
uint32_t timer_interrupt_handler(uint32_t mepc)
{
    __tick++;
    hwtimer_ms(1000);
    printf("\n");
    printf("%l\r\n",__tick);
    __sw_without_save(&sched_context);
    return mepc+4;
}

void  soft_interrupt_handler()
{
    *(uint32_t*)CLINT_MSIP(0)=0;
    __sw_without_save(&sched_context);
}


/***************************************************************
 * @Author: weiqiang scuec_weiqiang@qq.com
 * @Date: 2024-11-12 23:18:55
 * @LastEditors: weiqiang scuec_weiqiang@qq.com
 * @LastEditTime: 2024-11-13 20:10:43
 * @FilePath: /my_code/source/exception.c
 * @Description: 
 * @
 * @Copyright (c) 2024 by  weiqiang scuec_weiqiang@qq.com , All Rights Reserved. 
***************************************************************/
#include "types.h"
#include "riscv.h"
#include "plic.h"
#include "clint.h"

#include "uart.h"
#include "printf.h"
#include "hwtimer.h"
/***************************************************************
 * @description: 
 * @param {uint32_t} mcause [in/out]:  
 * @param {uint32_t} mtval [in/out]:  
 * @param {uint32_t} mepc [in/out]:  
 * @return {*}
***************************************************************/
uint32_t trap_handler(uint32_t mcause,uint32_t mtval,uint32_t mepc)
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
uint64_t __tick = 0;

uint32_t timer_interrupt_handler(uint32_t mepc)
{
    __tick++;
    hwtimer_load(CLINT_TIMEBASE_FREQ);
    printf("%l\n",__tick);
    return mepc+4;
}

void timer_interupt_init()
{
    mie_w(mie_r()|0x80);
    
}


/***************************************************************
 * @description: 
 * @param {uint32_t} hart [in/out]:  
 * @param {uint32_t} iqrn [in/out]:  
 * @param {uint32_t} priority [in/out]:  
 * @return {*}
***************************************************************/
void extern_interupt_init(uint32_t hart,uint32_t iqrn,uint32_t priority)
{ 
    mie_w(mie_r()|0x800);
    __plic_priority_set(iqrn,priority);
    __plic_threshold_set(hart,0);
    __plic_interrupt_enable(hart,iqrn);
} 

void uart0_iqr()
{   
    char a = uart_getc();
    printf("%c",a);
    if('\r'==a)
        printf("\n");     
}


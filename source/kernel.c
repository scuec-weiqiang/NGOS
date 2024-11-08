/***************************************************************
 * @Author: weiqiang scuec_weiqiang@qq.com
 * @Date: 2024-10-12 16:19:16
 * @LastEditors: weiqiang scuec_weiqiang@qq.com
 * @LastEditTime: 2024-11-08 17:57:08
 * @FilePath: /my_code/source/kernel.c
 * @Description:
 * @
 * @Copyright (c) 2024 by  weiqiang scuec_weiqiang@qq.com , All Rights Reserved.
 ***************************************************************/
#include "os.h"
#include "list.h"

int a = 1;

void __attribute__((aligned(4))) start_kernel() 
{
    uart_init();
    page_init();
    printf("System initial success!\n");

    if(a!=1)
    {
        panic("out of trap!\n");       
    }
    else
    {
        // *(uint32_t *)2 = 0x12345678;
        asm volatile("li a0,0x1234");
        int b = *(int *)0x00000000;
        // *(int *)0x00000000 = 100;
        // printf("b is %d\n",b);
    }
    while (1)
    {
        /* code */
    }
    
}

void trap_handler(uint32_t cause,uint32_t mtval)
{
    // panic("trap!\n");
    printf("trap!");
    uint32_t code = cause & 0x7fffffff;
    if(!(cause & 0x80000000))
    {
        printf("     casue code is %d\n",code);
        printf("     mtval is %d\n",mtval);
    }
    a=0;
}


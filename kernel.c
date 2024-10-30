/***************************************************************
 * @Author: weiqiang scuec_weiqiang@qq.com
 * @Date: 2024-10-12 16:19:16
 * @LastEditors: weiqiang scuec_weiqiang@qq.com
 * @LastEditTime: 2024-10-26 19:43:35
 * @FilePath: /wei/riscv-operating-system-mooc/code/os/my_code/kernel.c
 * @Description:
 * @
 * @Copyright (c) 2024 by  weiqiang scuec_weiqiang@qq.com , All Rights Reserved.
 ***************************************************************/
#include "os.h"
char a[] = {"hello world!\n"};
void start_kernel()
{
    uart_init();
    printf("%s",a);
    page_init();
    char *p1 = page_alloc(3);
    char *p2 = page_alloc(3);
    char *p3 = page_alloc(5);
    page_free(p2);
    page_free(p1);
    char *p4 = page_alloc(6);
    char *p5 = page_alloc(8);
    // while (1)
    // {
    //     // display pagem_i
    //     //  display num_blank
    // }
}

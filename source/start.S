#include "save_reg.S" 

#注意，这里在预处理.S文件时，指定参数“-c”,强制把.S文件当作.c文件，#include 命令就会强制展开
.equ STACK_SIZE,1024

.section .text.entry
.global _start
_start:
    csrr t0, mhartid #读取hart id
    mv tp,t0
    bnez t0,park #hart id 不为0的将休眠

    la a0 , _bss_start
    la a1 , _bss_end
    bgeu a0, a1, 2f

    #将bss段数据清0
    1:
    sw zero, (a0)
    addi a0, a0, 4
    bltu a0,a1,1b

    #设置栈指针
    2:   #hart0将执行下面的代码
    la sp,stacks + STACK_SIZE #将sp指向hart0的栈底

    # 设置向量表
    la a0,_trap_vector
    andi a0,a0,0xfffffffc
    ori a0,a0,0x01
    csrw mtvec,a0

    li a0,0
    csrw mscratch,a0

    call uart_init#基本输入输出初始化

    li a0,0x1880
    csrw mstatus,a0
    la a0,start_kernel
    csrw mepc,a0
    mret
park:   #hart id 不为0的将休眠
    wfi
    j park 


# ################### 异常与中断向量表 #########################
.balign 4 #四字节对齐
.global _trap_vector
_trap_vector:
    j _trap_handler
    .skip  4
    .skip  4
    j _soft_interrupt_handler
    .skip  4
    .skip  4
    .skip  4
    j _timer_interrupt_handler
    .skip  4
    .skip  4
    .skip  4
    j _extern_interrupt_handler

.global _trap_handler
_trap_handler:
    interrupt_save
    csrr a0,mepc
    call trap_handler 
    csrw mepc,a0
    interrupt_load
    mret


.global _extern_interrupt_handler
_extern_interrupt_handler:
    interrupt_save
    csrr a0,mepc
    call extern_interrupt_handler 
    csrw mepc,a0
    interrupt_load
    mret

.global _timer_interrupt_handler
_timer_interrupt_handler:
    interrupt_save
    csrr a0,mepc
    call timer_interrupt_handler
    csrw mepc,a0
    interrupt_load
    mret

.global _soft_interrupt_handler
_soft_interrupt_handler:
    interrupt_save
    csrr a0,mepc
    call soft_interrupt_handler
    csrw mepc,a0
    interrupt_load
    mret
######################################################

.balign 16
stacks:#分配hart0的栈
    .skip STACK_SIZE

.end

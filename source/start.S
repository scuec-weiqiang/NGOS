.global _start
.equ STACK_SIZE,1024

.section .text.entry
_start:
    csrr t0, mhartid #读取hart id
    mv tp,t0
    bnez t0,park #hart id 不为0的将休眠

    la a0 , _bss_start
    la a1 , _bss_end
    bgeu a0, a1, 2f

//将bss段数据清0
1:
    sw zero, (a0)
    addi a0, a0, 4
    bltu a0,a1,1b

//设置栈指针
2:   #hart0将执行下面的代码
    la sp,stacks + STACK_SIZE #将sp指向hart0的栈底

// 设置向量表
    la a0,_trap_vector
    andi a0,a0,0xfffffffd
    csrw mtvec,a0

// 开启全局中断
    li a0,0x01808
    csrw mstatus,a0

    li a0,0#0x80009000
    csrw mscratch,a0

    la t0,start_kernel
    csrw mepc,t0
    mret

park:   #hart id 不为0的将休眠
    wfi
    j park 

.balign 4 #四字节对齐
.global _trap_vector
_trap_vector:
    j _trap_handler
    # .skip 4
    # .skip 4
    # .skip 4
    # .skip 4
    # .skip 4
    # .skip 4
    # .skip 4
    # .skip 4
    # .skip 4
    # j uart0_iqr
    # j NMI_Handler                /* NMI */
    # j HardFault_Handler          /* Hard Fault */
    # .skip 4
    # j Ecall_M_Mode_Handler       /* Ecall M Mode */
    # .skip 4
    # .skip 4
    # j Ecall_U_Mode_Handler       /* Ecall U Mode */
    # j Break_Point_Handler        /* Break Point */
    # .skip 4
    # .skip 4
    # j SysTick_Handler            /* SysTick */
    # .skip 4
    # j SW_Handler                 /* SW */
    # .skip 4



.balign 16
stacks:#分配hart0的栈
    .skip STACK_SIZE

.end

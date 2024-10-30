.global _start
.equ STACK_SIZE,1024

.text
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
    j start_kernel
park:   #hart id 不为0的将休眠
    wfi
    j park 
    
.balign 16
stacks:#分配hart0的栈
    .skip STACK_SIZE

.end
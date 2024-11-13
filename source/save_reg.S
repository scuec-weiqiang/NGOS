
#ifndef __SAVE_REG_H
#define __SAVE_REG_H

#define LOAD        lw
#define STORE       sw
#define REG_SIZE    4

.macro store_reg addr
#   STORE zero,0*REG_SIZE(\addr)   zero值不会变，存储没有意义
    STORE ra , 1*REG_SIZE(\addr)
    STORE sp , 2*REG_SIZE(\addr)
#   STORE gp , 3*REG_SIZE(\addr)
#   STORE tp , 4*REG_SIZE(\addr)   tp里存储着mhartid，也不会变化
    STORE t0 , 5*REG_SIZE(\addr)
    STORE t1 , 6*REG_SIZE(\addr)
    STORE t2 , 7*REG_SIZE(\addr)
    STORE s0 , 8*REG_SIZE(\addr)
    STORE s1 , 9*REG_SIZE(\addr)
    STORE a0 ,10*REG_SIZE(\addr)
    STORE a1 ,11*REG_SIZE(\addr)
    STORE a2 ,12*REG_SIZE(\addr)
    STORE a3 ,13*REG_SIZE(\addr)
    STORE a4 ,14*REG_SIZE(\addr)
    STORE a5 ,15*REG_SIZE(\addr)
    STORE a6 ,16*REG_SIZE(\addr)
    STORE a7 ,17*REG_SIZE(\addr)
    STORE s2 ,18*REG_SIZE(\addr)
    STORE s3 ,19*REG_SIZE(\addr)
    STORE s4 ,20*REG_SIZE(\addr)
    STORE s5 ,21*REG_SIZE(\addr)
    STORE s6 ,22*REG_SIZE(\addr)
    STORE s7 ,23*REG_SIZE(\addr)
    STORE s8 ,24*REG_SIZE(\addr)
    STORE s9 ,25*REG_SIZE(\addr)
    STORE s10,26*REG_SIZE(\addr)
    STORE s11,27*REG_SIZE(\addr)
    STORE t3 ,28*REG_SIZE(\addr)
    STORE t4 ,29*REG_SIZE(\addr)
    STORE t5 ,30*REG_SIZE(\addr)
#   STORE t6 ,31*REG_SIZE(\addr)
#   t6要用来暂时存储addr，因此后面会手动保存
.endm
#
.macro load_reg addr
#   LOAD zero,0*REG_SIZE(\addr)   zero值不会变
    LOAD ra , 1*REG_SIZE(\addr)
    LOAD sp , 2*REG_SIZE(\addr)
#   LOAD gp , 3*REG_SIZE(\addr)
#   LOAD tp , 4*REG_SIZE(\addr)   tp里存储着mhartid，也不会变化
    LOAD t0 , 5*REG_SIZE(\addr)
    LOAD t1 , 6*REG_SIZE(\addr)
    LOAD t2 , 7*REG_SIZE(\addr)
    LOAD s0 , 8*REG_SIZE(\addr)
    LOAD s1 , 9*REG_SIZE(\addr)
    LOAD a0 ,10*REG_SIZE(\addr)
    LOAD a1 ,11*REG_SIZE(\addr)
    LOAD a2 ,12*REG_SIZE(\addr)
    LOAD a3 ,13*REG_SIZE(\addr)
    LOAD a4 ,14*REG_SIZE(\addr)
    LOAD a5 ,15*REG_SIZE(\addr)
    LOAD a6 ,16*REG_SIZE(\addr)
    LOAD a7 ,17*REG_SIZE(\addr)
    LOAD s2 ,18*REG_SIZE(\addr)
    LOAD s3 ,19*REG_SIZE(\addr)
    LOAD s4 ,20*REG_SIZE(\addr)
    LOAD s5 ,21*REG_SIZE(\addr)
    LOAD s6 ,22*REG_SIZE(\addr)
    LOAD s7 ,23*REG_SIZE(\addr)
    LOAD s8 ,24*REG_SIZE(\addr)
    LOAD s9 ,25*REG_SIZE(\addr)
    LOAD s10,26*REG_SIZE(\addr)
    LOAD s11,27*REG_SIZE(\addr)
    LOAD t3 ,28*REG_SIZE(\addr)
    LOAD t4 ,29*REG_SIZE(\addr)
    LOAD t5 ,30*REG_SIZE(\addr)
    LOAD t6 ,31*REG_SIZE(\addr)
.endm



.macro interrupt_save
    csrrw t6,mscratch,t6
    bne t6, zero, 1f //mscratch值是正常的，直接跳转到保存上下文的地方
 
    addi sp,sp,-4
    sw a0,(sp)//暂时先将a0压栈，他要用来传参

    li a0,1
    call page_alloc
    csrw mscratch,a0//当mscratch=0，给它分配一片内存用来存上下文
    mv t6,a0

    lw a0,(sp)//将a0出栈
    addi sp,sp,4

    1:
    store_reg t6
    csrr t5,mscratch
    STORE t5,31*REG_SIZE(t6)#保存t6的值
    csrw mscratch,t6    #保持mscratch值不变

.endm

.macro interrupt_load
    csrr t6,mscratch
    load_reg t6
.endm


#endif
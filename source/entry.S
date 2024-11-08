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

.text
.global _switch_to 
_switch_to:
# 存储当前任务上下文内容的结构体的地址 保存在mscratch里
# 交换mscratch与t6的值（因为mscratch属于csr寄存器，无法直接用来寻址，必须用通用寄存器作为中介，这里我们选t6作为中介）
    csrrw t6,mscratch,t6 
    beq t6, zero, 1f # 如果mscratch值为0，则代表当前没有任务上下文需要保存（例如：第一个任务还没开始执行）
    store_reg t6
    csrr t5,mscratch #把原来t6的值放入t5
    STORE t5,31*REG_SIZE(t6)#再把原来t6的值存入结构体中
# 至此保存当前任务上下文完成，下面恢复下一个任务的上下文

# _switch_to会在sched.c文件中声明为一个函数 void _switch_to(reg_context_t* next)
# 参数reg_context_t* next指向保存着下个任务上下文内容的地址，它通过寄存器a0传递
1:   
    csrw mscratch ,a0 #下个任务上下文内容的地址保存进mscratch
    mv t6,a0 
    load_reg t6 
    #注意：这里如果不用t6（比如直接用a0）,那么在执行宏 load_reg a0 时会执行 LOAD a0 ,18*REG_SIZE(a0)，
    #从此之后a0值会被覆盖掉，后面的操作都是从错误的地址加载值到寄存器，因此要保证宏load_reg的参数对应的寄存器最后被覆盖
    ret
  
.global _trap_handler
_trap_handler:
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

    csrr a0,mcause
    csrr a1,mtval
    call trap_handler 
    csrr t6,mepc
    # la t6,start_kernel
    la t6,_start
    # addi t6,t6,4# 退出trap执行下一条指令
    csrw mepc ,t6

    csrr t6,mscratch
    load_reg t6
    mret

.end
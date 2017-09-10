/******************************************************************************
 *
 * @ File Name  : abnormal.S
 * @ Date       : 2012-03-24
 * @ Author     : gaofeilong <gaofeilonglcu@163.com>
 *
 * @ Description: set interrupt sub program
 * @ History    : 2012-04-27：添加简单中断处理代码，1>调整返回值；
 *                      2> 保存程序上下文环境；3> 调用通用中断处理
 *                      函数；4> 堆栈恢复，调整的返回值赋值给pc，
 *                      SPSR恢复到CPSR
 *                2012-04-28：改为更简单的中断处理办法
 *                2012-04-29：还是先使用普通的中断处理办法处理吧
 *                2012-05-05：全部注释掉中断相关代码，中断无法使能，先做动态
 *                      内存分配
 *
 * ***************************************************************************/

.equ    DISABLE_IRQ,    0x80
.equ    DISABLE_FIQ,    0x40
.equ    SVC_MOD,        0x13
.macro  CHANGE_TO_SVC   
        msr cpsr_c, #(DISABLE_IRQ|DISABLE_FIQ|SVC_MOD) 
.endm

.global _undefined
.global _swi
.global _prefetch_abort 
.global _data_abort 
.global _reserved 
.global _irq 
.global _fiq 

.text

_undefined:
        nop

_swi:
        nop

_prefetch_abort:
        nop

_data_abort: 
        nop

_reserved: 
        nop

_irq: 
/*
        sub     r14, r14, #4
        str     r14, [r13, #-0x4]
        mrs     r14, spsr
        str     r14, [r13, #-0x8]
        str     r0,  [r13, #-0xc]
        mov     r0,  r13
        CHANGE_TO_SVC
        str     r14, [r13, #-0x8]!
        ldr     r14, [r0,  #-0x4]
        str     r14, [r13, #-0x4]
        ldr     r14, [r0,  #-0x8]
        ldr     r0,  [r0,  #-0xc]
        stmdb   r13!,{r0-r3, r14}
        bl      common_irq_handler
        ldmia   r13!,{r0-r3, r14}
        msr     spsr, r14
        ldmfd   r13!,{r14, pc}^

        sub     r14, r14, #4
        stmfd   r13!, {r0-r3, r14}
        bl      common_irq_handler
        ldmfd   r13!, {r0-r3, pc}^;
        */
        nop

_fiq: 
        nop

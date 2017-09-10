/******************************************************************************
 *
 * @ File Name  : init.S
 * @ Date       : 2012-03-24
 * @ Author     : gaofeilong <gaofeilonglcu@163.com>
 *
 * @ Description: bootloader file, init hardware resource and set 
 *                all resource can be used, and then jump to ram
 * @ History    : 2012-04-30：初始化栈完毕后返回svc模式
 *                2012-05-05：将拷贝长度从4K改为8K，解决了函数过多不执行的问题，
 *                      代码没有从nand中拷贝到内存；内存刷新率由0x008e07a3(用于
 *                      12M的HCLK)改为0x008e04f5(用于100M的HCLK)，但是目前没发现
 *                      由该问题引起的程序异常
 * ****************************************************************************/

#include "2440addr.S.h"

.extern kernel_test
.extern __bss_start
.extern __bss_end

.global _reset

.text

_reset:
        bl      _init_gpb
        bl      _off_watchdog
        bl      _off_int
        bl      _init_clock
        bl      _init_sdram
        bl      _init_stack
        bl      _clear_bss
        bl      _init_uart
        bl      _copy_code
        bl      _jump_ram

_init_gpb:
        @ set gpb5, gpb6, gpb8, gpb10 output, other remain
        ldr     r0, =GPB_CON
        ldr     r1, [r0]
        ldr     r2, =(0b11<<20|0b11<<16|0b11<<12|0b11<<10)
        bic     r1, r1, r2
        ldr     r2, =(0b01<<20|0b01<<16|0b01<<12|0b01<<10)
        orr     r1, r1, r2
        str     r1, [r0]

        @ mask gpb5, gpb6, gpb8, gpb10 pull-up registers 
        ldr     r0, =GPB_UP
        ldr     r1, =0x560
        str     r1, [r0]

        mov     pc, lr


_off_watchdog:
        ldr     r0, =WT_CON
        mov     r1, #0x0
        str     r1, [r0]

        mov     pc, lr


_off_int:
        @ off interrupt
        ldr     r0, =INT_MASK
        ldr     r1, =0xffffffff
        str     r1, [r0]

        @ off sub interrupt
        ldr     r0, =INT_SUB_MASK
        ldr     r1, =0x7fff
        str     r1, [r0]

        mov     pc, lr


_init_clock:
        @ set lock time 
        ldr     r0, =LOCK_TIME
        ldr     r1, =0x00ffffff
        str     r1, [r0]

        @ set FCLK:HCLK:PCLK = 1:4:8 
        ldr     r0, =CLK_DIVN
        ldr     r1, =0x05
        str     r1, [r0]

        @ set cpu bus mode
        mrc     p15, 0, r1, c1, c0, 0   @ read control register
        orr     r1, r1, #0xc0000000     @ Asynchronous
        mcr     p15, 0, r1, c1, c0, 0   @ write control register

         
        @ set FCLK to 400MHz
        @ MPLL(FCLK) = (2*(MDIV+8) * Fin) / ((PDIV+2) * 2^(SDIV))
        @ MDIV=92(0x5c), PDIV=1, SDIV=1
        ldr     r0, =MPLL_CON
        ldr     r1, =0x5c011
        str     r1, [r0]

        mov     pc, lr

        
_init_sdram:
        ldr     r0, =MEM_CTL_BASE
        ldr     r1, =MEM_CTL_END
        adr     r2, __mem_ctl_val
_init_loop:
        ldr     r3, [r2], #0x4        
        str     r3, [r0], #0x4
        cmp     r0, r1
        bne     _init_loop

        mov     pc, lr

@ memory configuration value
.align 4
__mem_ctl_val:
        .long   0x22000000      @ vBWSCON
        .long   0x00000700      @ vBANKCON0
        .long   0x00000700      @ vBANKCON1
        .long   0x00000700      @ vBANKCON2
        .long   0x00000700      @ vBANKCON3
        .long   0x00000700      @ vBANKCON4
        .long   0x00000700      @ vBANKCON5
        .long   0x00018005      @ vBANKCON6
        .long   0x00018005      @ vBANKCON7
        .long   0x008e04f5      @ vREFRESH
        .long   0x000000b1      @ vBANKSIZE
        .long   0x00000030      @ vMRSRB6
        .long   0x00000030      @ vMRSRB7


_init_stack:
        msr     cpsr_c, #(DISABLE_IRQ | DISABLE_FIQ | SVC_MOD)
        ldr     sp, =SVC_STACK

        msr     cpsr_c, #(DISABLE_IRQ | DISABLE_FIQ | IRQ_MOD)
        ldr     sp, =IRQ_STACK

        msr     cpsr_c, #(DISABLE_IRQ | DISABLE_FIQ | FIQ_MOD)
        ldr     sp, =FIQ_STACK

        msr     cpsr_c, #(DISABLE_IRQ | DISABLE_FIQ | ABT_MOD)
        ldr     sp, =ABT_STACK

        msr     cpsr_c, #(DISABLE_IRQ | DISABLE_FIQ | UND_MOD)
        ldr     sp, =UND_STACK

        msr     cpsr_c, #(DISABLE_IRQ | DISABLE_FIQ | SYS_MOD)
        ldr     sp, =SYS_STACK

        msr     cpsr_c, #(DISABLE_IRQ | DISABLE_FIQ | SVC_MOD)
                
        mov     pc, lr


_clear_bss:
        ldr     r0, _bss_start
        ldr     r1, _bss_end
        mov     r2, #0x0
_clear_loop:
        str     r2, [r0], #0x4
        cmp     r0, r1
        ble     _clear_loop

        mov     pc, lr


_init_uart:
        mov     r10, lr
        bl      init_uart
        @ bl      test_uart

        mov     pc, r10


_copy_code:
        @ init nand and copy code to ram
        mov     r10, lr
        bl      nand_init_ll
        ldr     r0, =0x30000000         
        ldr     r1, =0x1000             @ why cannot be 0?
        ldr     r2, =0x2000             
        bl      nand_read_ll

        mov     pc, r10

        
_jump_ram:
        ldr     lr, =_led_loop;
        ldr     pc, =kernel_start

_led_loop:
        ldr     r2, =GPB_DAT
        ldr     r3, [r2]
        bic     r3, r3, #0x560
        orr     r3, r3, #0x540
        str     r3, [r2]
        ldr     r0, =DELAY_VAL
        bl      _delay0

        ldr     r3, [r2]
        bic     r3, r3, #0x560
        orr     r3, r3, #0x520
        str     r3, [r2]
        ldr     r0, =DELAY_VAL
        bl      _delay0

        ldr     r3, [r2]
        bic     r3, r3, #0x560
        orr     r3, r3, #0x460
        str     r3, [r2]
        ldr     r0, =DELAY_VAL
        bl      _delay0

        ldr     r3, [r2]
        bic     r3, r3, #0x560
        orr     r3, r3, #0x160
        str     r3, [r2]
        ldr     r0, =DELAY_VAL
        bl      _delay0

        b       _led_loop

_delay0:
        sub     r0, r0, #1   
        cmp     r0, #0x0
        bne     _delay0
        mov     pc, lr


_bss_start:     .word __bss_start
_bss_end:       .word __bss_end


.end

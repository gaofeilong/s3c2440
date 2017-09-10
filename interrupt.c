/*******************************************************************************
 *
 * @ File Name  : interrupt.c
 * @ Date       : 2012-04-27
 * @ Author     : gaofeilong <gaofeilonglcu@163.com>
 *
 * @ Description: common interrupt handler function
 * @ History    : 2012-04-27：实现该文件，关键点：1> cpsr[7]置位，全局使能中断
 *                      2> 写 INTMASK ，清除相应硬件的中断屏蔽位。3> 中断处理
 *                      清除悬挂位 SRCPND 和 INTPND。通过写1
 *                2012-04-29：加入清 CPSR[7] 位前后的CPSR模式位输出
 *
 * ****************************************************************************/

#include "2440bsp.h"
extern  void printk(const char *fmt, ...);

void umask_int(unsigned int offset)
{
        _debug();
        INT_MASK &= ~(1<<offset);
        _debug();
}

void enable_irq(void)
{
        _debug();
        unsigned int tmp = 0;
        unsigned int tmp1 = 0;
        asm volatile (
                "stmfd sp!, {r0}\n"
                "ldr r8, =0xd6000014\n" // leds data address
                "ldr r9, =0x400\n"      
                "str r9, [r8]\n"        // light 3 leds
                "mrs r0, cpsr\n"        // read cpsr
                "mov %0, r0\n"          // tmp = r0, for debug
                "ldr r9, =0x500\n"      
                "str r9, [r8]\n"        // light 2 leds
                "bic r0, r0, #0x80\n"   // clear cpsr[7], enable irq
                "mov %1, r0\n"          // tmp = r0, for debug
                "ldr r9, =0x540\n"      
                "str r9, [r8]\n"        // light 1 led
                //"msr cpsr, r0\n"        // write cpsr
                "ldr r9, =0x560\n"      
                "str r9, [r8]\n"        // light 0 led
                "ldmfd sp!, {r0}\n"
                :"+r"(tmp), "+r"(tmp1)
                :
                :"r0"

                /*
                "mrs r4, cpsr\n"        // read cpsr
                "mov %0, r4\n"          // tmp = r4, for debug
                "bic r4, r4, #0x80\n"   // clear cpsr[7], enable irq
                "mov %1, r4\n"          // tmp = r4, for debug
                "msr cpsr_c, r4\n"      // write cpsr
                :"+r"(tmp), "+r"(tmp1)
                :
                :"r4"
                */

                );
        printk("%b\r\n", tmp);
        printk("%b\r\n", tmp1);

        _debug();
}

void common_irq_handler(void)
{
        _debug();
        GPB_DAT = 0x0;
        SRC_PND |= (1<<INT_OFFSET);
        INT_PND |= (1<<INT_OFFSET);
        _debug();
}

/********************************************************************
 *
 * @ File Name  : 2440addr.S.h
 * @ Date       : 2012-03-24
 * @ Author     : gaofeilong <gaofeilonglcu@163.com>
 *
 * @ Description: defile FL2440 register address, used for *.S
 * @ History    : 2012-04-29：修正写错得 irq 和 fiq 模式定义
 *
 * *****************************************************************/

#ifndef         _FL_2440_ADDR_S_
#define         _FL_2440_ADDR_S_

// sdram
#define         MEM_CTL_BASE    0x48000000                              
#define         MEM_CTL_END     0x48000034
// interrupt
#define         INT_CON_BASE    0x4a000000                              
#define         INT_MASK        0x4a000008
#define         INT_SUB_MASK    0x4a00001c 
// clock
#define         LOCK_TIME       0x4c000000                              
#define         CLK_DIVN        0x4c000014
#define         MPLL_CON        0x4c000004
// nand flash
#define         NFCONF          0x4e000000
#define         NFCONT          0x4e000004
#define         NFCMD           0x4e000008
#define         NFADDR          0x4e00000c
#define         NFDATA          0x4e000010
#define         NFSTAT          0x4e000020
// watch dog timer
#define         WT_CON          0x53000000                              
// gpio----for led
#define         GPB_CON         0x56000010                              
#define         GPB_DAT         0x56000014
#define         GPB_UP          0x56000018
// gpio----for serial port
#define         GPH_CON         0x56000070  
#define         GPH_DAT         0x56000074
#define         GPH_UP          0x56000078
// UART0 registers
#define         ULCON0          0x50000000  
#define         UCON0           0x50000004
#define         UFCON0          0x50000008
#define         UMCON0          0x5000000c
#define         UTRSTAT0        0x50000010
#define         UTXH0           0x50000020
#define         URXH0           0x50000024
#define         UBRDIV0         0x50000028

// for each mode to set stack
#define         DISABLE_IRQ     0x80                    // 0b10000000
#define         DISABLE_FIQ     0x40                    // 0b01000000
#define         USR_MOD         0x10                    // 0b00010000
#define         FIQ_MOD         0x11                    // 0b00010001
#define         IRQ_MOD         0x12                    // 0b00010010
#define         SVC_MOD         0x13                    // 0b00010011 
#define         ABT_MOD         0x17                    // 0b00010111
#define         UND_MOD         0x1b                    // 0b00011011
#define         SYS_MOD         0x1f                    // 0b00011111
// each stack top
#define         MEM_SIZE        0x04000000              // 64M
#define         TEXT_BASE       0x30000000              // base mem addr
#define         SVC_STACK       (TEXT_BASE + MEM_SIZE-4)// svc stack base
#define         IRQ_STACK       (SVC_STACK - 0x400)     // irq stack base
#define         FIQ_STACK       (IRQ_STACK - 0x400)     // fiq stack base
#define         ABT_STACK       (FIQ_STACK - 0x400)     // abt stack base
#define         UND_STACK       (ABT_STACK - 0x400)     // udf stack base
#define         SYS_STACK       (UND_STACK - 0x400)     // sys/usr stack base

#define         DELAY_VAL       0x4ffff

#endif          //_FL_2440_ADDR_S_

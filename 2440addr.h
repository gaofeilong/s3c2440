/********************************************************************
 *
 * @ File Name  : 2440addr.h
 * @ Date       : 2012-03-24
 * @ Author     : gaofeilong <gaofeilonglcu@163.com>
 *
 * @ Description: defile FL2440 register address, used for *.c
 * @ History    : 2012-04-01：添加接收端口虚拟地址
 *                2012-04-27：添加中断控制器寄存器的虚拟地址，添加
 *                      gpio虚拟地址，用于测试中断，添加定时器控制
 *                      器虚拟地址，用于产生中断
 *                2012-07-11：添加 nandflash 地址相关定义
 * *****************************************************************/

#ifndef         _FL_2440_ADDR
#define         _FL_2440_ADDR

// nand flash 
#define         NFCONF          (*(volatile unsigned int *)0x4e000000)
#define         NFCONT          (*(volatile unsigned int *)0x4e000004)
#define         NFCMD           (*(volatile unsigned int *)0x4e000008)
#define         NFADDR          (*(volatile unsigned int *)0x4e00000c)
#define         NFDATA8         (*(volatile unsigned char*)0x4e000010)
#define         NFDATA32        (*(volatile unsigned int *)0x4e000010)
#define         NFMECCD0        (*(volatile unsigned int *)0x4e000014)
#define         NFMECCD1        (*(volatile unsigned int *)0x4e000018)
#define         NFSECCD         (*(volatile unsigned int *)0x4e00001c)
#define         NFSTAT          (*(volatile unsigned int *)0x4e000020)
#define         NFESTAT0        (*(volatile unsigned int *)0x4e000024)
#define         NFESTAT1        (*(volatile unsigned int *)0x4e000028)
#define         NFMECC0         (*(volatile unsigned int *)0x4e00002c)
#define         NFMECC1         (*(volatile unsigned int *)0x4e000030)
#define         NFSECC          (*(volatile unsigned int *)0x4e000034)
#define         NFSBLK          (*(volatile unsigned int *)0x4e000038)
#define         NFEBLK          (*(volatile unsigned int *)0x4e00003c)

// gpio----for led
#define         GPB_CON         (*(volatile unsigned int *)0x56000010)
#define         GPB_DAT         (*(volatile unsigned int *)0x56000014)
#define         GPB_UP          (*(volatile unsigned int *)0x56000018)

// gpio----for serial port
#define         GPH_CON         (*(volatile unsigned int *)0x56000070)  
#define         GPH_DAT         (*(volatile unsigned int *)0x56000074)
#define         GPH_UP          (*(volatile unsigned int *)0x56000078)

// UART0 registers
#define         ULCON0          (*(volatile unsigned int *)0x50000000)  
#define         UCON0           (*(volatile unsigned int *)0x50000004)
#define         UFCON0          (*(volatile unsigned int *)0x50000008)
#define         UMCON0          (*(volatile unsigned int *)0x5000000c)
#define         UTRSTAT0        (*(volatile unsigned int *)0x50000010)
#define         UTXH0           (*(volatile unsigned char*)0x50000020)
#define         URXH0           (*(volatile unsigned char*)0x50000024)
#define         UBRDIV0         (*(volatile unsigned int *)0x50000028)

//interrupt registers virtual address
#define         SRC_PND         (*(volatile unsigned int *)0x4a000000)
#define         INT_MASK        (*(volatile unsigned int *)0x4a000008)
#define         INT_PND         (*(volatile unsigned int *)0x4a000010)
#define         INT_OFFSET      (*(volatile unsigned int *)0x4a000014)

//pwm timer virtual address
#define         TCFG0           (*(volatile unsigned int *)0x51000000)
#define         TCON            (*(volatile unsigned int *)0x51000008)
#define         TCNTB4          (*(volatile unsigned int *)0x5100003c)

#if 0
// virtual address
#define         VIR_GPB_CON     (*(volatile unsigned int *)0xd6000010)
#define         VIR_GPB_DAT     (*(volatile unsigned int *)0xd6000014)
#define         VIR_GPB_UP      (*(volatile unsigned int *)0xd6000018)

// UART0 registers virtual address
#define         VIR_UTRSTAT0    (*(volatile unsigned int *)0xd0000010)
#define         VIR_UTXH0       (*(volatile unsigned int *)0xd0000020)
#define         VIR_URXH0       (*(volatile unsigned char*)0xd0000024)

//interrupt registers virtual address
#define         VIR_SRCPND      (*(volatile unsigned int *)0xca000000)
#define         VIR_INTMASK     (*(volatile unsigned int *)0xca000008)
#define         VIR_INTPND      (*(volatile unsigned int *)0xca000010)
#define         VIR_INTOFFSET   (*(volatile unsigned int *)0xca000014)

//pwm timer virtual address
#define         VIR_TCFG0       (*(volatile unsigned int *)0xd1000000)
#define         VIR_TCON        (*(volatile unsigned int *)0xd1000008)
#define         VIR_TCNTB4      (*(volatile unsigned int *)0xd100003c)
#endif

#define         UTXD0READY      (1<<2)          // ready to send
#define         URXD0READY      (1)             // ready to receive

#endif          //_FL_2440_ADDR

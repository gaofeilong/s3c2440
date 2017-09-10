/*******************************************************************************
 *
 * @ File Name  : nand.c
 * @ Date       : 2012-03-24
 * @ Author     : gaofeilong <gaofeilonglcu@163.com>
 *
 * @ Description: nand flash init and driver
 * @ History    : 
 * @ History    : 2012-04-30：修改nand初始化NFCONF配置，TACLS/TWRPH0/TWRPH1 = 
 *                      0/3/0改为 TACLS/TWRPH0/TWRPH1 = 1/4/1，修改NFCONT配置
 *                2012-07-11：修改 *buf = NFDATA 为 *buf = NFDATA8
 *                2012-08-05：对外函数 nand_init() 和 nand_read() 改为
 *                      nand_init_ll() 和 nand_read_ll()
 * ****************************************************************************/

#include "2440addr.h"

// HCLK=100Mhz
#define IDLE                    1         
#define TACLS                   1
#define TWRPH0                  4
#define TWRPH1                  1
#define NAND_PAGE_SIZE          2048
#define NAND_PAGE_MASK          (NAND_PAGE_SIZE-1)

static void nand_select_chip(void)
{
        NFCONT &= ~(1<<1);
}

static void nand_deselect_chip(void)
{
        NFCONT |= (1<<1);
}

static void nand_write_cmd(int cmd)
{
        NFCMD = cmd;
}

static void nand_wait_idle(void)
{
        while (!(NFSTAT & IDLE));
}

static void nand_write_addr(unsigned int addr)
{
        int i;

        NFADDR = 0;
        for (i = 0; i < 10; i++);
        NFADDR = 0;
        for (i = 0; i < 10; i++);
        NFADDR = (addr>>11) & 0xff;
        for (i = 0; i < 10; i++);
        NFADDR = (addr>>19) & 0xff;
        for (i = 0; i < 10; i++);
}

static void nand_reset(void)
{
        nand_select_chip();
        nand_write_cmd(0xff);
        nand_wait_idle();
        nand_deselect_chip();
}

void nand_init_ll(void)
{
        NFCONF = (TACLS<<12) | (TWRPH0<<8) | (TWRPH1<<4);
        NFCONT = (0<<13) | (0<<12) | (0<<10) | (0<<9) | (0<<8) | (1<<6) | (1<<5) 
                | (1<<4) | (1<<1) | (1<<0);
        // Lock-tight   [13]            0:Disable lock, 1:Enable lock.
        // Soft Lock    [12]            0:Disable lock, 1:Enable lock.
        // EnablillegalAcINT[10]        Illegal access interupt control. 0:Disable, 1:Enable
        // EnbRnBINT    [9]             RnB interrupt. 0:Disable, 1:Enable
        // RnB_TrandMode[8]             RnB transition detection config. 0:Low to High, 1:High to Low
        // SpareECCLock [6]             0:Unlock, 1:Lock
        // MainECCLock  [5]             0:Unlock, 1:Lock
        // InitECC(W)   [4]             1:Init ECC decoder/encoder.
        // Reg_nCE      [1]             0:nFCE=0, 1:nFCE=1.
        // NANDC Enable [0]             operating mode. 0:Disable, 1:Enable.
        nand_reset();
}

void nand_read_ll(unsigned char *buf, unsigned long start_addr, int size)
{
        int i, j;

        // start address or size not align
        if ((start_addr & NAND_PAGE_MASK) || (size & NAND_PAGE_MASK)) 
                return ;                // start addr or size not align

        nand_select_chip();
        for (i = start_addr; i < start_addr + size; ) {
                nand_write_cmd(0x00);   // write read start cmd
                nand_write_addr(i);     // write address
                nand_write_cmd(0x30);   // write read end cmd
                nand_wait_idle();       // wait for ready to operate

                for (j = 0; j < NAND_PAGE_SIZE; j++, i++, buf++)
                        *buf = NFDATA8; 
        }
        nand_deselect_chip();

        return ;
}

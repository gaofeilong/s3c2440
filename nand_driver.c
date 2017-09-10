/*******************************************************************************
 *
 * @ File Name  : nand_driver.c
 * @ Date       : 2012-05-13, 2012-08-05
 * @ Author     : gaofeilong <gaofeilonglcu@163.com>
 *
 * @ Description: nand flash driver
 * @ History    : 2012-05-13：创建文件
 *                2012-07-11：添加页读写函数
 *                2012-07-26：添加驱动读写函数
 *                2012-07-29：添加地址转换到页号的宏，驱动测试通过
 *                2012-08-04：修改文件名为小写+下划线风格；添加初始化函数、nand
 *                      驱动结构体和设备列表数组
 *                2012-08-08：将 storage.* 拆分为 driver_framework.* 和
 *                      nand_driver.*，分为框架和具体设备驱动
 *
 * ****************************************************************************/
#include "nand_driver.h"
#include "2440bsp.h"
#include "2440string.h"

int wait_idle()
{
        U8 status;
        WriteCmd(READSTATUSCMD);
        do {
                status = ReadData8();
        } while (!(status & 0x40));     /* IO[6] == 1: idle */
        WriteCmd(READCMD0);

        return status & 0x1;            /* IO[0] == 1: error */
}

/* addr is page addr, which is the number of page */
void read_page(U32 addr, U8 *buf)
{
        int i;

        ChipEnable();
        WriteCmd(READCMD0);
        WriteAddr(0);
        WriteAddr(0);
        WriteAddr(addr);
        WriteAddr(addr>>8);
        WriteCmd(READCMD1);
        wait_idle();

        for (i = 0; i < 2048; i++) {
                buf[i] = ReadData8(); 
        }
        ChipDisable(); 
}

/* addr is page addr, which is the number of page */
int write_page(U32 addr, U8 *buf)
{
        int i;
        U32 mecc;
        U8  isError;

        ChipEnable();
        WriteCmd(WRITECMD0);
        WriteAddr(0);
        WriteAddr(0);
        WriteAddr(addr);
        WriteAddr(addr>>8);

        ResetEcc();
        MainEccUnlock();
        for(i = 0; i < 2048; i++) {
                WriteData8(buf[i]);
        }
        MainEccLock();
        mecc = ReadMainEcc();
        WriteData8(0xff);
        WriteData8(mecc & 0xff);
        WriteData8((mecc>>8) & 0xff);
        WriteData8((mecc>>16) & 0xff);
        WriteData8((mecc>>24) & 0xff);
        WriteCmd(WRITECMD1);

        isError = wait_idle();
        if (!isError) {
                U8 readBuf[2048];
                read_page(addr, readBuf);
                for (i = 0; i < 2048; i++) {
                        if (readBuf[i] != buf[i]) {
                                return -1; 
                        } 
                }
        }

        return 0;
}

void read(U32 start_addr, U8 *buf, U32 size)
{
        U32 i;
        unsigned char page_buf[NAND_PAGE_SIZE];

        /* address not aligned */
        if (start_addr & NAND_PAGE_MASK) {
                return;
        }

        /* read data to buffer */
        for (i = 0; i < size; i += NAND_PAGE_SIZE) {
                memset(page_buf, 0, NAND_PAGE_SIZE);
                read_page(NAND_ADDR_TO_PAGE(start_addr + i), page_buf);
                if (size > NAND_PAGE_SIZE) {
                        memcpy(buf, page_buf, NAND_PAGE_SIZE);
                        size -= NAND_PAGE_SIZE;
                } else {
                        memcpy(buf, page_buf, size);
                }
        }
}

void write(U32 start_addr, U8 *buf, U32 size)
{
        U32 i;

        /* address not aligned */
        if (start_addr & NAND_PAGE_MASK) {
                return;
        }

        /* write data to buffer */
        for (i = 0; i < size; i += NAND_PAGE_SIZE) {
                write_page(NAND_ADDR_TO_PAGE(start_addr + i), buf + i);
        }
}

struct storage_device nand_flash = {
        .start_pos = 0x0,
        .device_size = 1024*1024*128,
        .sector_size = NAND_PAGE_SIZE,
        .read = read,
        .write = write
};

void nand_driver_init()
{
        if (!storage_devices[NAND_STORAGE_INDEX]) {
                storage_devices[NAND_STORAGE_INDEX] = &nand_flash;
        }
        return;
}

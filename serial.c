/********************************************************************
 *
 * @ File Name  : serial.c
 * @ Date       : 2012-03-24
 * @ Author     : gaofeilong <gaofeilonglcu@163.com>
 *
 * @ Description: serial port init and serial port driver
 * @ History    : 2012-04-01：将put_*，get_*放到bsp中
 *
 * *****************************************************************/

#include "2440addr.h"

inline void delay(int msec)
{
        int i, j;
        for (i = 1000; i > 0; --i) {
                for (j = msec; j > 0; --j) {
                        // do nothing
                } 
        }
}

void init_uart()
{
        volatile int i;
        GPH_CON= 0x00faaa;
        GPH_UP = 0x7ff;
        //GPH_CON = (GPH_CON & (~(0xf<<4)) | 0xa0);       // set gph2 txd, gph3 rxd
        //GPH_UP |= 0x0;                                  // pull-up gph2, gph3

        UCON0   = 0x05;         // 时钟选择为PCLK，查询方式为轮询或中断
        ULCON0  = 0x03;         // 8数据位，1停止位
        UFCON0  = 0x00;         // no FIFO
        UMCON0  = 0x00;         // no modem control 
        UBRDIV0 = 0x1a;         // baud=115200, PCLK=50MHz

        for (i = 0; i < 100; ++i);
}

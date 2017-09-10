/*******************************************************************************
 *
 * @ File Name  : 2440bsp.c
 * @ Date       : 2012-04-01
 * @ Author     : gaofeilong <gaofeilonglcu@163.com>
 *
 * @ Description: board support package for fl2440, implementation of put_s(),
 *                      put_c() and get_c()
 * @ History    : 2012-04-01：添加文件
 *
 * ****************************************************************************/

#include "2440bsp.h"

void put_c(unsigned int c)
{
        while ( !(UTRSTAT0 & UTXD0READY) );
        UTXH0 = c;
}

unsigned char get_c()
{
        while ( !(UTRSTAT0 & URXD0READY) );
        return URXH0;
}

int put_s(const char *str)
{
        int i = 0;
        while (str[i]) {
                put_c((unsigned int)str[i++]);
        }
        return i;
}

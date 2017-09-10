/*******************************************************************************
 *
 * @ File Name  : 2440bsp.h
 * @ Date       : 2012-04-01
 * @ Author     : gaofeilong <gaofeilonglcu@163.com>
 *
 * @ Description: board support package for fl2440, declaration of  put_s(),
 *                      put_c() and get_c()
 * @ History    : 2012-04-01：添加文件
 *                2012-04-27：添加重复包含保护和_func_debug宏
 *                2012-05-05：修改调试宏_func_debug()为_debug，调试信息格式改变
 *                      为输出日期、时间、文件、行号，而不输出函数名；将printk
 *                      声明在该头文件中
 *                2012-05-09：添加 NULL 宏定义
 *                2012-05-10：修改 NULL 宏定义
 *
 * ****************************************************************************/

#ifndef _2440ADDR_H_
#define _2440ADDR_H_
#include "2440addr.h"

#define NULL    (void *)0

#define _FUNC_DEBUG_
#ifdef  _FUNC_DEBUG_
        #define _debug() printk("[%s %s] -- @ %s(%d)\r\n", \
                                __DATE__, __TIME__, __FILE__, __LINE__);
#else
        #define _debug()
#endif

// put a character to uart0 with mmu support
void put_c(unsigned int c);

// get a character from uart0 with mmu support
unsigned char get_c();

// put a string to uart0 with mmu support
int put_s(const char *str);

// printk(), support %b, %o, %u, %d, %x, %c, %s
void printk(const char *fmt, ...);
#endif //_2440ADDR_H_

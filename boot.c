/*******************************************************************************
 *
 * @ File Name  : boot.c
 * @ Date       : 2012-03-24
 * @ Author     : gaofeilong <gaofeilonglcu@163.com>
 *
 * @ Description: This file is first kernel start file, generally 
 *                used to init low level operation system source.
 *
 * @ History    : 2012-03-31：添加测试 mmu 和 printk 的代码
 *                2012-04-01：删除static void put_s()， 使用bsp
 *                2012-04-04：去掉对GPB赋值前对值得unsigned转换，没必要
 *                2012-04-27：添加中断和定时器相关，定时器用于产生中断
 *                2012-04-29：去掉 printk 的大量测试输出，添加进入 kernel_start 
 *                      函数的提示信息，显示编译时间方便连续启动系统的输出信息的
 *                      查看
 *                2012-05-05：中断无法使能，先做动态内存分配，添加动态内存分配
 *                      测试代码，使用新版的调试宏_debug()
 *                2012-05-06：添加申请和释放 buddy 的测试代码
 *                2012-05-10：相同阶的 buddy 的反复申请和释放的测试代码
 *                2012-05-12：添加测试 cache 和 kmalloc 的代码，动态内存分配测试
 *                      通过
 *                2012-07-29：添加 nand 驱动测试，通过
 *                2012-08-04：nand读写不同地址、读不够字节数、正确读写测试用例
 *
 * ****************************************************************************/

#include "mem.h"                        /* for kmalloc() and kfree() */
#include "2440bsp.h"                    /* for put_* */
#include "2440string.h"                 /* for mem* and str* */
#include "nand_driver.h"                /* for nand_driver_init() */
#include "driver_framework.h"           /* for struct storage_device */

typedef void (*init_func)(void);
extern  void printk(const char *fmt, ...);

static void uart_test(void)
{
        put_s("test uart.............[ok]!\r\n\r\n");
        return;
}

static void led_test(void)
{
        GPB_CON = 0x00111400;
        GPB_DAT = 0x420;
        return;
}

static void mmu_test(void)
{
#if 0
        extern void start_mmu(void); 
        extern void init_mmu(void); 

        init_mmu();
        start_mmu();
        put_s("test mmu..............[ok]!\r\n");
        return;
#endif
}

static void printk_test(void)
{
#define _WINDOWS_
#ifdef  _LINUX_
        int d1    = 40;
        int d2    = -2;
        int d3    = 0;
        char c    = 'h';
        const char *str = "This is for %s testing";
        printk("\ttest string     [%s]\n",  str);
        printk("\ttest char       [%c]\n",  c);
        printk("\ttest int        [%d]\n",  d1);
        printk("\ttest int        [%d]\n",  d3);
        printk("\ttest long       [%ld]\n", d1);
        printk("\ttest int        [%d]\n",  d2);
        printk("\ttest unsigned   [%u]\n",  d2);
        printk("\ttest binary     [%b]\n",  d2);
        printk("\ttest octal      [%o]\n",  d2);
        printk("\ttest hex        [%x]\n",  d2);
        printk("test printk...........[ok]!\n\n");
#endif

#ifdef  _WINDOWS_
        int d1    = 40;
        int d2    = -2;
        int d3    = 0;
        char c    = 'h';
        const char *str = "This is for %s testing";
        printk("\ttest string     [%s]\r\n",  str);
        printk("\ttest char       [%c]\r\n",  c);
        printk("\ttest int        [%d]\r\n",  d1);
        printk("\ttest int        [%d]\r\n",  d3);
        printk("\ttest long       [%ld]\r\n", d1);
        printk("\ttest int        [%d]\r\n",  d2);
        printk("\ttest unsigned   [%u]\r\n",  d2);
        printk("\ttest binary     [%b]\r\n",  d2);
        printk("\ttest octal      [%o]\r\n",  d2);
        printk("\ttest hex        [%x]\r\n",  d2);
        printk("test printk...........[ok]!\r\n\r\n");
#endif
        return;
}

void irq_test(void)
{
#if 0
        /* init timer */
        TCFG0 |= 0x800;             // 一级分频[15:8]八位数
        TCON  &= ~(7<<20);          // 清位[22:20]用于配置 timer4
        TCON  |= (1<<22);           // autoreload
        TCON  |= (1<<21);           // TCNTB4->TCNT4
        TCNTB4 = 10000;             // timer4的初始值 
        TCON  |= (1<<20);           // start timer4
        TCON  &= ~(1<<21);          // 清位

        extern void enable_irq(void);
        extern void umask_int(unsigned int);
        umask_int(14);
        enable_irq();
        return;
#endif
}

void malloc_test(void)
{
        init_buddy_page();
#if 0
        /********** for buddy test ***********/
        char *str1, *str2, *str3;
        str1 = (char *)alloc_buddy(0);
        printk("address of str1: [%x]\r\n", str1);
        str2 = (char *)alloc_buddy(5);
        printk("address of str2: [%x]\r\n", str2);
        free_buddy(str1);
        printk("free str1\r\n");
        free_buddy(str2);
        printk("free str2\r\n");
        str3 = (char *)alloc_buddy(5);
        printk("address of str3: [%x]\r\n", str3);
        free_buddy(str3);
        printk("free str3\r\n");
#endif

#if 0
        /********** for cache test ***********/
        struct kmem_cache cache;
        char *str1, *str2, *str3;

        if (create_cache(&cache, 100) == NULL) {
                printk("create cache error\r\n");  
                return;
        }
        if ((str1 = alloc_cache(&cache)) == NULL) {
                printk("alloc cache for str1 error\r\n"); 
                return;
        } else {
                printk("str1 = %x\r\n", str1); 
        }
        if ((str2 = alloc_cache(&cache)) == NULL) {
                printk("alloc cache for str2 error\r\n"); 
                return;
        } else {
                printk("str2 = %x\r\n", str2); 
        }
        free_cache(&cache, str1);
        free_cache(&cache, str2);

        if ((str3 = alloc_cache(&cache)) == NULL) {
                printk("alloc cache for str3 error\r\n"); 
                return;
        } else {
                printk("str3 = %x\r\n", str3); 
        }
        free_cache(&cache, str3);
#endif

#if 1
        int ret;
        ret = kmalloc_init();
        if (ret != 0) {
                printk("init error\r\n"); 
        }

        char *str1, *str2, *str3, *str4;
        str1 = (char *)kmalloc(100);
        if (str1) {
                printk("address of str1: [%x]\r\n", str1);
        }
        str2 = (char *)kmalloc(5);
        if (str2) {
                printk("address of str2: [%x]\r\n", str2);
        }
        str3 = (char *)kmalloc(4000);
        if (str3) {
                printk("address of str3: [%x]\r\n", str3);
        }
        str4 = (char *)kmalloc(10000);
        if (str4) {
                printk("address of str4: [%x]\r\n", str4);
        } else {
                printk("kmalloc str4 error\r\n");
        }
        kfree(str1);
        printk("str1 free\r\n");
        kfree(str2);
        printk("str2 free\r\n");
        kfree(str3);
        printk("str3 free\r\n");
        kfree(str4);
        printk("str4 free\r\n");
        kfree((void *)0x0400000);
        printk("0x04000000 free\r\n");
        str1 = (char *)kmalloc(1);
        if (str1) {
                printk("address of str1: [%x]\r\n", str1);
        }
        kfree(str1);
#endif
        printk("test malloc...........[ok]!\r\n\r\n");

        return;
}

static void storage_test(void)
{
#if 1
        char *write_buf = "gaofeilonggaofeilonggaofeilong\r\n\
                           gaofeilonggaofeilonggaofeilong\r\n\
                           gaofeilonggaofeilonggaofeilong\r\n\
                           gaofeilonggaofeilonggaofeilong\r\n\
                           gaofeilonggaofeilonggaofeilong\r\n\
                           gaofeilonggaofeilonggaofeilong\r\n\
                           gaofeilonggaofeilonggaofeilong\r\n\
                           gaofeilonggaofeilonggaofeilong\r\n\
                           gaofeilonggaofeilonggaofeilong";
#else
        char *write_buf = "gaofeilong";
#endif
#define BUFSIZE 2048
         
        nand_driver_init();

        U32 wr_addr = 0x00200000;
        char read_buf[BUFSIZE];
        struct storage_device *sd = storage_devices[NAND_STORAGE_INDEX];

        memset(read_buf, 0, BUFSIZE);
        sd->write(wr_addr, (U8 *)write_buf, strlen(write_buf));
        printk("written 1 accomplished\r\n");
        sd->read(0x00500000, (U8 *)read_buf, BUFSIZE);
        printk("read 1 accomplished\r\n");
        /* should be error, because of write and read address is different */
        if (strcmp(write_buf, read_buf) == 0) { 
                printk("first w&r succeed\r\n");
        } else {
                printk("first w&r error:\r\n\twrite=%s\r\n\tread=%s\r\n", 
                                                        write_buf, read_buf);
        }

        wr_addr = 0x00300000;
        memset(read_buf, 0, BUFSIZE);
        sd->write(wr_addr, (U8 *)write_buf, strlen(write_buf));
        printk("written 2 accomplished\r\n");
        sd->read(wr_addr, (U8 *)read_buf, 100);
        printk("read 2 accomplished\r\n");
        /* should be error, because of only read 100 bytes */
        if (strcmp(write_buf, read_buf) == 0) {
                printk("second w&r succeed\r\n");
        } else {
                printk("secondw&r error:\r\n\twrite=%s\r\n\tread=%s\r\n", 
                                                        write_buf, read_buf);
        }

        wr_addr = 0x00250000;
        memset(read_buf, 0, BUFSIZE);
        sd->write(wr_addr, (U8 *)write_buf, strlen(write_buf));
        printk("written 3 accomplished\r\n");
        sd->read(wr_addr, (U8 *)read_buf, BUFSIZE);
        printk("read 3 accomplished\r\n");
        /* should be ok */
        if (strcmp(write_buf, read_buf) == 0) {
                printk("third w&r succeed\r\n");
        } else {
                printk("third w&r error:\r\n\twrite=%s\r\n\tread=%s\r\n", 
                                                        write_buf, read_buf);
        }

        printk("test nand driver......[ok]!\r\n\r\n");
}

static init_func init[] = {
        led_test,
        uart_test,
        mmu_test,
        printk_test,
        malloc_test,
        irq_test,
        storage_test,
        0
};

void kernel_start(void)
{
        int i;
        for (i = 0; init[i]; ++i) {
                init[i](); 
        }
        
        printk("\r\nkernel starting......, compiled at [%s]\r\n", __TIME__);
        while (1);
        return;
}

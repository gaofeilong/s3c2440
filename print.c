/*******************************************************************************
 *
 * @ File Name  : print.c
 * @ Date       : 2012-03-25
 * @ Author     : gaofeilong <gaofeilonglcu@163.com>
 *
 * @ Description: implement of printf()
 * @ History    : 2012-03-30：实现该文件，关键点：1> va系列宏定义的技巧; 2> 进制
 *                      宏定义，该宏不仅用作flag，同时也用作取余的基数; 3> 类型
 *                      宏定义，有符号的 INT 和 CHAR 中包含了 SIGN。
 *                2012-04-01：删除static void put_s()， 使用bsp
 *                2012-04-05：用自己实现的 mem* 替换掉 my_mem*
 *                2012-07-29：修改用于 vsprintk 的宏 BUFSIZE 为4096，用于容纳
 *                      nand 驱动测试中的长字符串，但是此处仍有限制，即printk
 *                      输出的 buffer 长度最大不能超过 4K
 *
 * ****************************************************************************/

#include "2440bsp.h"
#include "2440string.h"
typedef char*                   va_list;
#define INTSIZEOF(x)            ( (sizeof(x)+sizeof(int)-1) & ~(sizeof(int)-1) )
#define va_start(args, fmt)     ( args = (va_list)&fmt + INTSIZEOF(fmt) )
#define va_arg(arg, type)       ( *(type *)((arg += INTSIZEOF(type)) - INTSIZEOF(type)) )
#define va_end(arg)             ( arg = (va_list)0)
#define BUFSIZE                 4096

#define FORMAT_BASE_MASK        0xff
#define FORMAT_BASE_B           0x02
#define FORMAT_BASE_O           0x08
#define FORMAT_BASE_D           0x0a
#define FORMAT_BASE_X           0x10
#define FORMAT_TYPE_MASK        0xff00        
#define FORMAT_TYPE_NONE        0x0000
#define FORMAT_TYPE_SIGN        0x0100
#define FORMAT_TYPE_UINT        0x0200
#define FORMAT_TYPE_INT         0x0300
#define FORMAT_TYPE_STR         0x0400
#define FORMAT_TYPE_CHAR        0x0500
#define FORMAT_BASE(x)          ((x) & FORMAT_BASE_MASK)
#define FORMAT_TYPE(x)          ((x) & FORMAT_TYPE_MASK)

#ifdef  _DEBUG_
        #define debug(x)        put_s(x)
#else
        #define debug(x)        {}
#endif

static inline void set_type(unsigned int *flag, unsigned int type)
{
        debug("enter set_type\n");
        *flag &= ~FORMAT_TYPE_MASK;
        *flag |= type;
        debug("leave set_type\n");
}

static inline void set_base(unsigned int *flag, unsigned int base)
{
        debug("enter set_base\n");
        *flag &= ~FORMAT_BASE_MASK;
        *flag |= base;
        debug("leave set_base\n");
}

char *number(char *str, int num, unsigned int base, unsigned int flag)
{
        debug("enter number\n");
        int r, neg = 0, i = 0;
        char num_buf[36];
        const char *digits = "0123456789abcdef";

        memset(num_buf, '\0', 36);
        if (num < 0 && flag&FORMAT_TYPE_SIGN) {
                num = -num;  
                neg = -1;
        }

        do {
                r = num % base;
                num /= base;
                num_buf[i++] = digits[r];
        } while (num); 
        if (base == FORMAT_BASE_B) {
                num_buf[i++] = 'b'; 
                num_buf[i++] = '0'; 
        } else if (base == FORMAT_BASE_O) {
                num_buf[i++] = '0'; 
        } else if (base == FORMAT_BASE_X) {
                num_buf[i++] = 'x'; 
                num_buf[i++] = '0'; 
        }

        if (neg) {
                num_buf[i++] = '-';
        }
        while (i--) {
                *str++ = num_buf[i]; 
        }

        debug("leave number\n");
        return str;
}

int decode(const char *fmt, unsigned int *flag)
{
        debug("enter decode\n");
        const char *start = fmt;

        set_type(flag, FORMAT_TYPE_NONE);
        for (; *fmt; fmt++) {
                if (*fmt == '%') {
                        break; 
                }
        }
        if (fmt != start || !*fmt) {
                return fmt - start; 
        }

        switch (*++fmt) {
                case 'b':
                        set_base(flag, FORMAT_BASE_B);
                        set_type(flag, FORMAT_TYPE_UINT);
                        break;
                case 'o':
                        set_base(flag, FORMAT_BASE_O);
                        set_type(flag, FORMAT_TYPE_UINT);
                        break;
                case 'u':
                        set_base(flag, FORMAT_BASE_D);
                        set_type(flag, FORMAT_TYPE_UINT);
                        break;
                case 'd':
                        set_base(flag, FORMAT_BASE_D);
                        set_type(flag, FORMAT_TYPE_INT);
                        break;
                case 'x':
                        set_base(flag, FORMAT_BASE_X);
                        set_type(flag, FORMAT_TYPE_UINT);
                        break;
                case 'c':
                        set_type(flag, FORMAT_TYPE_CHAR);
                        break;
                case 's':
                        set_type(flag, FORMAT_TYPE_STR);
                        break;
                default:
                        break;
        }
        debug("leave decode\n");
        return ++fmt - start;
}

void vsprintk(char *buf, int size, const char *fmt, va_list args)
{
        debug("enter vsprintk\n");
        int num = 0;
        unsigned int flag;
        const char *old_fmt;
        char *str, *end;

        str = buf;
        end = str + size;

        while (*fmt) {
                old_fmt = fmt;
                int read = decode(fmt, &flag); 
                fmt += read;

                if (FORMAT_TYPE(flag) == FORMAT_TYPE_NONE) {
                        int copy = read;
                        if (str < end) {
                                copy = end-str> copy? copy: end-str; 
                                memcpy(str, old_fmt, copy);
                        }
                        str += read; 
                } else if (FORMAT_TYPE(flag) == FORMAT_TYPE_CHAR) {
                        char c = va_arg(args, char);
                        if (str < end) {
                                *str++ = c;
                        } 
                } else if (FORMAT_TYPE(flag) == FORMAT_TYPE_STR) {
                        char *s = va_arg(args, char *); 
                        while (str < end && *s) {
                                *str++ = *s++; 
                        }
                } else {
                        if (FORMAT_TYPE(flag) == FORMAT_TYPE_INT) {
                                num = va_arg(args, int); 
                        } else if (FORMAT_TYPE(flag) == FORMAT_TYPE_UINT) {
                                num = va_arg(args, unsigned int); 
                        } 
                        str = number(str, num, flag&FORMAT_BASE_MASK, flag);
                }
        }
        put_s(buf);
        debug("leave vsprintk\n");
}

void printk(const char *fmt, ...)
{
        va_list args;
        char print_buf[BUFSIZE];
        memset(print_buf, '\0', BUFSIZE);

        va_start(args, fmt);
        vsprintk(print_buf, BUFSIZE, fmt, args);
        va_end(args);
}

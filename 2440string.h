/*******************************************************************************
 *
 * @ File Name  : 2440string.h
 * @ Date       : 2012-04-05
 * @ Author     : gaofeilong <gaofeilonglcu@163.com>
 *
 * @ Description: string and memory operations for my os
 * @ History    : 2012-04-05：添加文件
 * @            : 2012-08-07：删除 C 文件，改为 static inline 函数
 *
 * ****************************************************************************/

// memcpy
static inline void *memcpy(void *dest, const void *src, unsigned int count)
{
        char *tmp = dest;
        const char *s = src;
        while (count--) {
                *tmp++ = *s++; 
        }

        return dest;
}

// memset
static inline void *memset(void *dest, int c, unsigned int count)
{
        char *tmp = dest;
        while (count--) {
                *tmp++ = c; 
        }
        return dest;
}

// strcpy
static inline char *strcpy(char *dest, const char *src)
{
        char *tmp = dest;

        while ((*dest++ = *src++) != '\0') {
        }
        return tmp;
}

// strcat 
static inline char *strcat(char *dest, const char *src)
{
        char *tmp = dest;

        while (*dest) {
                dest++; 
        }
        while ((*dest++ = *src++) != '\0') {
        }
        return tmp;
}

// strcmp 
static inline int strcmp(const char *s1, const char *s2)
{
        unsigned char c1, c2;

        while (1) {
                c1 = *s1++; 
                c2 = *s2++;
                if (c1 != c2) {
                        return c1 - c2; 
                }
                if (!c1) {
                        break; 
                }
        }
        return 0;
}

// strlen 
static inline unsigned int strlen(const char *s)
{
        const char *sc;
        for (sc = s; *sc != '\0'; ++sc) {
                // nothing  
        }
        return sc - s;
}

// strchr
static inline char *strchr(const char *s, int c)
{
        for (; *s != c; s++) {
                if (*s == '\0') {
                        return (void *)0; 
                }
        }
        return (char *)s;
}

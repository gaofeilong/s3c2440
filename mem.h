/*******************************************************************************
 *
 * @ File Name  : mem.h
 * @ Date       : 2012-05-10
 * @ Author     : gaofeilong <gaofeilonglcu@163.com>
 *
 * @ Description: head file of mem.c, general purpose macro defination and 
 *                      function declarations.
 * @ History    : 2012-05-10: 创建文件，修改 kmalloc 函数声明，没有参数，修改
 *                      宏定义中的小bug
 *                2012-05-12: free ---> kfree
 *
 * ****************************************************************************/
#ifndef  _MEM_H_
#define  _MEM_H_
#include "list.h"

/* for memory management */
#define PAGE_SHIFT              12
#define MEM_END                 0x33f00000
#define MEM_START               0x30100000
#define PAGE_SIZE               0x00001000
#define PAGE_NUM                ( (MEM_END - MEM_START) / (PAGE_SIZE + \
                                                        sizeof(struct page)) )
#define PAGE_START              MEM_START 
#define PAGE_END                (PAGE_START + PAGE_NUM * PAGE_SIZE)
#define CONTROL_END             MEM_END
#define CONTROL_START           (CONTROL_END - PAGE_NUM * sizeof(struct page))

/* for buddy */
#define PAGE_AVAILABLE                  0x00
#define PAGE_DIRTY                      0x01
#define PAGE_BUDDY_BUSY                 0x04
#define ORDER_NUM                       9       /* 4K*2^0 ~ 4K*2^8 */
#define MAX_BUDDY_PAGE_NUM_MASK         ((1 << (ORDER_NUM - 1)) - 1)
#define BUDDY_END(x, order)             ((x) + (1 << order) - 1)
#define NEXT_BUDDY_START(x, order)      ((x) + (1 << order))
#define PREV_BUDDY_START(x, order)      ((x) - (1 << order))

/* for slab */
#define CACHE_MAX_ORDER                 5
#define CACHE_MAX_WAST                  (PAGE_SIZE - 90 * PAGE_SIZE / 100)

/* for malloc */
#define KMALLOC_SIZE_STEP               32
#define KMALLOC_CACHE_NUM               128
#define kmalloc_size_to_index(size)     ((size) >> 5)

/************************** data structs **************************************/
struct page {
        unsigned int vaddr;             /* page addr */
        unsigned int flags;             /* PAGE_BUDDY_BUSY or PAGE_DIRTY ...*/
        int order;                      /* 1 page = 4k * 2^order */
        struct kmem_cache *cachep;      /* flowing */
        struct list_head list;          /* list the all 4k pages of memory */
};

struct kmem_cache {
        unsigned int obj_size;          /* sub memory block size */
        unsigned int obj_nr;            /* number of sub memory block */
        unsigned int page_order;        /* order of the page */
        unsigned int flags;             /* not used */
        struct page *head_page;         /* first page of slab */
        struct page *end_page;          /* last page of slab */
        void *nf_block;                 /* most important, pointed to address 
                                           that of the first useable block */
};

/* for buddy */
extern void init_buddy_page(void);
extern void *alloc_buddy(int order);
extern void free_buddy(void *addr);

/* for cache */
extern struct kmem_cache *create_cache(struct kmem_cache *cache, 
                        unsigned int size);
extern void *alloc_cache(struct kmem_cache *cache);
extern void free_cache(struct kmem_cache *cache, void *paddr);
extern void destroy_cache(struct kmem_cache *cache);

/* for malloc */
extern int  kmalloc_init();
extern void *kmalloc(unsigned int size);
extern void kfree(void *addr);

#endif  //_MEM_H_

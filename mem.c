/*******************************************************************************
 *
 * @ File Name  : mem.c
 * @ Date       : 2012-04-30
 * @ Author     : gaofeilong <gaofeilonglcu@163.com>
 *
 * @ Description: Use for dynamic memory management, buddy algorithm and slab
 *                      and kmalloc & kfree
 *                Memory layout:
 *                              64M: ================= 0x34000000
 *                                   |  stack: 6K    |
 *                                   ----------------- 0x33ffe800
 *                                   |  page table   |
 *                              63M: ----------------- 0x33f00000
 *                                   |               |
 *                                   |               |
 *                                   |               |
 *                                   |               |
 *                                   |               |
 *                                   ----------------- some address
 *                                   | struct page   |
 *                               1M: ----------------- 0x30100000
 *                                   |  kernel code  |
 *                                0: ================= 0x30000000
 *
 * @ History    : 2012-04-30：将链表操作拿出去，实现 buddy 的申请和释放
 *                2012-05-05：实现对申请、释放buddy的封装，申请返回地址，释放
 *                      传入地址，修改主要函数的函数名
 *                2012-05-06：释放 buddy 的循环体最大合并到最大阶数-1
 *                2012-05-09：添加 slab 内存分配相关代码，未测
 *                2012-05-10：创建 mem.h 头文件，将函数声明和数据结构放到头文件
 *                      中；修改函数名，一致使用 alloc_** 和 free_**风格；新增
 *                      kmalloc 相关代码；修改数组初始化，修改kmalloc初始化函数
 *                      定义，没有参数
 *                2012-05-12：1> 将所有函数添加返回语句，返回指针类型的函数出错
 *                      后返回 NULL; 2> kmalloc, kfree, virt_to_page 添加错误处
 *                      理; 3> 添加 alloc_pages 函数和 free_pages 函数，用于返
 *                      回一个申请到的 buddy 的管理页的指针，解决了不能序列化
 *                      申请到的 cache 内存的问题，因为使用 alloc_buddy 返回的
 *                      是一个申请到的内存地址，而不是 struct page 的地址; 4>
 *                      将所有内部函数定义为 static; 5> free -> kfree
 *
 * ****************************************************************************/
#include "list.h"
#include "2440bsp.h"
#include "mem.h"

struct list_head page_buddy[ORDER_NUM];
struct kmem_cache kmalloc_cache[KMALLOC_CACHE_NUM] 
                                = { {0, 0, 0, 0, NULL, NULL, NULL}, };

/************************** kernel buddy *************************************/
/**
 *  init_buddy_list() -初始化链表头数组中的链表头。在 buddy 中，把相同阶数的
 *      buddy 链接成双向链表进行管理。数组元素即为不同阶数buddy的双向链表的
 *      链表头。可以通过索引找到对应的链表头，而索引值正是 buddy 的阶数，如 
 *      pabe_buddy[4]这个链表头所代表的双向链表就是阶数为5的 buddy，即每个 
 *      buddy 中有2^4个page
 * @return: void
 */ 
static void init_buddy_list(void)
{
        int i;
        for (i = 0; i < ORDER_NUM; ++i) {
                INIT_LIST_HEAD(&page_buddy[i]); 
        }

        return;
}

/**
 * virt_to_page() -将虚拟内存地址转换为管理结构体 page 的指针
 * @addr: 要转换的虚拟地址
 * @return: 管理结构体 page 的指针或0
 */
static struct page *virt_to_page(unsigned int addr)
{
        /* 第几个内存页 */
        unsigned int i;

        if (addr - PAGE_START < 0) {
                return NULL; 
        }
        i = ((addr) - PAGE_START) >> PAGE_SHIFT;
        if (i > PAGE_NUM) {
                return NULL; 
        }
        return (struct page *)CONTROL_START + i;
}

/**
 * page_address() -获取管理结构体所管理内存的地址
 * @pg: 管理结构体指针
 * @return: 被管理的内存首地址或0
 */
static void *page_address(struct page *pg)
{
        return (void *)(pg->vaddr);
}

/**
 *  init_buddy_page() -将内存分成最小单位的页，将页尽可能的分给最大的 buddy，
 *      当最后剩余的页不足以构成一个最大的 buddy 时，将这些页分成一个个最小
 *      阶数的 buddy，不管是大 buddy 还是小 buddy，分配完成后都链入 buddy
 *      链表中去，初始化完毕之后，系统中只存在最大阶数的 buddy 和最小阶数的
 *      buddy
 * @return: void
 */
void init_buddy_page(void)
{
        int i;
        struct page *pg = (struct page *)CONTROL_START;
        init_buddy_list();

        for (i = 0; i < PAGE_NUM; ++i, ++pg) {
                pg->vaddr = PAGE_START + i * PAGE_SIZE; 
                pg->flags = PAGE_AVAILABLE;
                INIT_LIST_HEAD(&(pg->list));
                /* 最多有 (PAGE_NUM & ~MAX_BUDDY_PAGE_NUM_MASK) 个页应该分进
                 * 最大buddy中，当 page 索引是最大 buddy 所含 page 数的整数
                 * 被时，该 page 即为本阶的 buddy 的头 page
                 */
                if ( i < (PAGE_NUM & (~MAX_BUDDY_PAGE_NUM_MASK)) ) {
                        if ((i & MAX_BUDDY_PAGE_NUM_MASK) == 0) {
                                pg->order = ORDER_NUM - 1;
                        } else {
                                pg->order = -1; 
                        }
                        list_add_tail(&(pg->list), &page_buddy[ORDER_NUM - 1]);
                } else {
                        pg->order = 0; 
                        list_add_tail(&(pg->list), &page_buddy[0]);
                }
        }

        return;
}

/**
 * get_buddy_from_list() -从系统中分配一个指定阶数的 buddy 出来，当链表头数组
 *      相应的阶数（索引）下正好有空闲的 buddy 时，直接从链表中取下，当没有
 *      时，逐层想高阶 buddy 寻找，直到找到空闲的 buddy，然后拆分，逐层向下
 *      ，直到拆分出需要阶数的 buddy，将其他拆掉的 buddy 挂到相应阶数索引的
 *      链表头下。
 * @order: 指定的阶数
 * @return: 找到的 buddy 的管理结构体指针或者0
 */
struct page *get_buddy_from_list(int order)
{
        int neworder;
        struct page *pg;
        struct list_head *tlist, *tlist1;

        for (neworder = order; neworder < ORDER_NUM; ++neworder) {
                if (list_empty(&page_buddy[neworder])) {
                        continue; 
                } else {
                        /* 从链表中取出第一个 buddy */
                        pg = list_entry(page_buddy[neworder].next, 
                                                struct page, list);
                        tlist = &(BUDDY_END(pg, neworder)->list);
                        tlist->next->prev = &page_buddy[neworder];
                        page_buddy[neworder].next = tlist->next;
                        goto OUT_OK;
                }
        }

        return NULL;

OUT_OK:
        /* 分割大阶的 buddy，一分为二，直到分出需要阶数的 buddy，将大阶 buddy
         * 的前半部分链到对应阶数的空闲 buddy 链表中，后半部分继续分
         */
        for (--neworder; neworder >= order; --neworder) {
                tlist1 = &(pg->list);
                tlist = &(BUDDY_END(pg, neworder)->list);
                pg->order = neworder;
                pg = NEXT_BUDDY_START(pg, neworder);
                list_add_chain_tail(tlist1, tlist, &page_buddy[neworder]);
        }
        pg->flags |= PAGE_BUDDY_BUSY;
        pg->order  = order;

        return pg;
}

/**
 * put_buddy_to_list() -将指定的 buddy 释放回系统，如果释放的 buddy 前后相连的
 *      内存空间不能合并，直接挂到相对应阶数的链表头下，如果存在相同阶数的空闲
 *      buddy，则可合并，先检查合并，再挂到相应阶数的链表头下。
 * @pg:    要释放的 buddy 的管理结构体指针。     
 * @return: 无
 */
void put_buddy_to_list(struct page *pg)
{
        struct page *pprev, *pnext = 0;

        /* if not a buddy alloced by get_buddy_from_list() */
        if (!(pg->flags & PAGE_BUDDY_BUSY)) {
                return; 
        }

        pg->flags &= ~(PAGE_BUDDY_BUSY);
        /* 最大阶为8，则最大合并阶数为7的buddy */
        while (pg->order < ORDER_NUM - 1) {
                pprev = PREV_BUDDY_START(pg, pg->order);
                pnext = NEXT_BUDDY_START(pg, pg->order); 
                /* 在从链表中分配 buddy 时，分配出的 buddy 头和尾的两个 page
                 * 中的 list 指针还是指向链表中的下一个元素的，使用时并没有
                 * 破坏这两个指针，所以在释放时，如果在当初分配时该 buddy 两
                 * 边的 buddy 有空闲的话，那么合并这两个 buddy 为一个，循环
                 * 向上合并，最后将释放的 buddy 存入相应的可用链表中
                 */
                if (!(pnext->flags & PAGE_BUDDY_BUSY) && 
                                        (pnext->order == pg->order)) {
                        list_remove_chain(&(pnext->list), 
                                        &(BUDDY_END(pnext, pg->order)->list));
                        BUDDY_END(pg, pg->order)->list.next = &(pnext->list);
                        pnext->list.prev = &(BUDDY_END(pg, pg->order)->list);
                        pnext->order = -1;
                        pg->order++;
                        continue;
                } else if (!(pprev->flags & PAGE_BUDDY_BUSY) && 
                                        (pprev->order == pg->order)) {
                        list_remove_chain(&(pprev->list), 
                                        &(BUDDY_END(pprev, pg->order)->list));
                        BUDDY_END(pprev, pg->order)->list.next = &(pg->list);
                        pg->list.prev = &(BUDDY_END(pprev, pg->order)->list);
                        pg->order = -1;
                        pprev->order++;
                        pg = pprev;
                        continue;
                } else {
                        break; 
                }
        }
        list_add_chain(&(pg->list), &((pnext - 1)->list), &page_buddy[pg->order]);

        return;
}

/**
 * alloc_pages() -分配指定阶数的 buddy，设置分配的 buddy 的每个页的 DIRTY 位，
 *      返回管理该 buddy 的 struct page 的地址
 * @order: 需要的 buddy 的阶数
 * @return: page 指针或者 NULL
 */
struct page *alloc_pages(int order)
{
        int i;
        struct page *pg;

        pg = get_buddy_from_list(order);
        if (pg == NULL) {
                return NULL;
        }
        for (i = 0; i < (1<<order); ++i) {
                (pg + i)->flags |= PAGE_DIRTY;
        }

        return pg;
}

/**
 * free_pages() -释放 buddy，清空分配的 buddy 的每个页的 DIRTY 位
 * @pg: 要是放的 buddy 的管理 page 的地址
 * @return: void
 */
void free_pages(struct page *pg)
{
        int i;
        for (i = 0; i < (1<<pg->order); ++i) {
                (pg + i)->flags &= ~PAGE_DIRTY;
        }
        put_buddy_to_list(pg);

        return;
}

/**
 * alloc_buddy() -用get_buddy_from_list 分配一个指定阶数的 buddy，成功后设置 
 *      buddy 中每页的 DIRTY 位，返回分配的内存的首地址
 * @order: 需要的 buddy 的阶数
 * @return: 分配成功的内存首地址或者0
 */
void *alloc_buddy(int order)
{
        struct page *pg;
        pg = alloc_pages(order);
        if (pg == NULL) {
                return NULL; 
        }
        return page_address(pg);
}

/**
 * free_buddy() 
 * @addr: 需要释放的 buddy 的首个页的内存地址
 * @return: void
 */
void free_buddy(void *addr)
{
        return free_pages(virt_to_page((unsigned int)addr));
}

/****************************** kernel memory cache **************************/
/**
 * find_order() -找到一个合适的阶数，该阶数的 buddy 必须要大于10倍的请求大小
 * @size: 将会频繁请求的内存大小      
 * @return: 找到的符合要求的 buddy 的阶数或-1
 */
static int find_order(unsigned int size)
{
        int order;
        for (order = 0; order < CACHE_MAX_ORDER; order++) {
                if (CACHE_MAX_WAST * (1<<order) >= size) {
                        return order; 
                }
        }
        return -1;
}

/**
 * cache_line_object() -将一个 order 阶的 buddy 分割成 size 大小的内存块，
 *      每个内存块的块首保存下一个块首的位置。返回分割出的内存块个数
 * @head: 被分割的 buddy 的首地址
 * @size: 要分割出的子内存块的大小
 * @order: 被分割的 buddy 的阶数
 * @return: 分割完成的子内存快的个数
 */

static int cache_line_object(void *head, unsigned int size, int order)
{
        void **pl;
        void *p;
        pl = (void **)head;
        p = (char *)head + size;
        int i, s = PAGE_SIZE * (1<<order);
        for (i = 0; s > size; i++, s -= size) {
                *pl = p;
                pl = (void **)p;
                p += size;
        }
        if (s == size) {
                return i++; 
        }
        return i;
}

/**
 * create_cache() -构造内存缓冲区，填充一个 kmem_cache 结构体，初始化其所有成员
 * @cache: 传入被填充的结构体
 * @size: 将会频繁请求的内存大小      
 * @return: 填充好的 kmem_cache 结构体指针
 */
struct kmem_cache *create_cache(struct kmem_cache *cache, unsigned int size)
{
        void **nf_blk = &(cache->nf_block);
        int order = find_order(size);
        if (order == -1) {
                return NULL; 
        }
        if ((cache->head_page=alloc_pages(order)) == NULL) {
                return NULL; 
        }
        *nf_blk = page_address(cache->head_page);
        cache->obj_nr = cache_line_object(*nf_blk, size, order);
        cache->obj_size = size;
        cache->page_order = order;
        cache->end_page = BUDDY_END(cache->head_page, order);
        cache->end_page->list.next = NULL;

        return cache;
}

/**
 * destroy_cache() -销毁内存缓冲区，逐个销毁所有的 buddy
 * @cache: kmem_cache 结构体指针
 * @return: void
 */
void destroy_cache(struct kmem_cache *cache)
{
        int order = cache->page_order;
        struct page *pg = cache->head_page;
        struct list_head *list; 
        while (1) {
                list = BUDDY_END(pg, order)->list.next; 
                free_pages(pg);
                if (list) {
                        pg = list_entry(list, struct page, list); 
                } else {
                        return; 
                }
        }
}

/**
 * alloc_cache() -分配预先指定大小的内存，传入初始化好的 kmem_cache 指针
 * @cache: 已经初始化过的 kmem_cache 指针，根据该结构体中的信息进行分配
 * @return: 分配到的内存块的首地址，或者NULL
 */
void *alloc_cache(struct kmem_cache *cache)
{
        void *p;
        struct page *pg;
        if (cache == NULL) {
                return NULL;
        }

        void **nf_block = &(cache->nf_block);
        unsigned int *nr = &(cache->obj_nr);
        int order = cache->page_order;

        /* 如果该现有 cache 中没有可用的的内存块了，分配一个新的 cache */
        if (!*nr) {
                if ((pg = alloc_pages(order)) == NULL) {
                        return NULL; 
                }
                *nf_block = page_address(pg);
                cache->end_page->list.next = &pg->list;
                cache->end_page = BUDDY_END(pg, order);
                cache->end_page->list.next = NULL;
                *nr += cache_line_object(*nf_block, cache->obj_size, order);
        }
        (*nr)--;
        p = *nf_block;
        *nf_block = *(void **)p;
        pg = virt_to_page((unsigned int)p);
        pg->cachep = cache;
        return p;
}

/**
 * free_cache() -释放内存块
 * @cache: kmem_cache 结构体指针
 * @paddr: 释放的内存块首地址
 * @return: void
 */
void free_cache(struct kmem_cache *cache, void *paddr)
{
        *(void **)paddr = cache->nf_block;
        cache->nf_block = paddr;
        cache->obj_nr++;

        return;
}

/****************************** kernel malloc *********************************/
/**
 * kmalloc_init() -将 kmalloc_cache 数组中的每个元素用 create_cache 初始化
 * @return: 0 或者 -1
 */
int kmalloc_init(void)
{
        int i;
        for (i = 0; i < KMALLOC_CACHE_NUM; i++) {
                if (create_cache(&kmalloc_cache[i], 
                                (i + 1) * KMALLOC_SIZE_STEP) == NULL) {
                        return -1; 
                }
        }
        return 0;
}

/**
 * kmalloc() -向系统请求内存，从已经初始化好的 cache 数组中的 某个合适的 cache
 *              中取得一个可用地址，返回给用户
 * @size: 要请求的内存大小      
 * @return: 请求到的内存首地址或者NULL
 */
void *kmalloc(unsigned int size)
{
        int index = kmalloc_size_to_index(size);
        if (index >= KMALLOC_CACHE_NUM) {
                return NULL;
        }
        return alloc_cache(&kmalloc_cache[index]);
}

/**
 * kfree() -释放从系统请求到的内存
 * @addr: 要释放的内存首地址      
 * @return: void
 */
void kfree(void *addr)
{
        if ((unsigned int)addr <= 0x1000) {
                return; 
        }
        struct page *pg;
        pg = virt_to_page((unsigned int)addr);
        if (!pg) {
                return; 
        }
        free_cache(pg->cachep, addr);

        return;
}

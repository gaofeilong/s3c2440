/*******************************************************************************
 *
 * @ File Name  : list.h
 * @ Date       : 2012-04-30
 * @ Author     : gaofeilong <gaofeilonglcu@163.com>
 *
 * @ Description: list operation
 * @ History    : 2012-04-30：将链表操作从 mem.c 中拿出来单独使用头文件list.h
 *                2012-04-30：去掉宏定义结尾的空格，在使用宏时一般宏后边加分号，
 *                      不应该在宏和分号之间有空格
 *                2012-05-10：添加避免重复包含的预编译指令
 *
 * ****************************************************************************/

#ifndef _LIST_H_
#define _LIST_H_

struct list_head {
        struct list_head *next, *prev;
};

static inline void INIT_LIST_HEAD(struct list_head *list)
{
        list->next = list;
        list->prev = list;
}

static inline void __list_add(struct list_head *new, struct list_head *prev,
                        struct list_head *next)
{
        prev->next = new; 
        next->prev = new;
        new->prev  = prev;
        new->next  = next;
}

static inline void list_add(struct list_head *new, struct list_head *list)
{
        __list_add(new, list, list->next);
}

static inline void list_add_tail(struct list_head *new, struct list_head *list)
{
        __list_add(new, list->prev, list);
}

static inline void __list_del(struct list_head *prev, struct list_head *next)
{
        prev->next = next;
        next->prev = prev;
}

static inline void list_del(struct list_head *entry)
{
        __list_del(entry->prev, entry->next);
}

static inline void list_remove_chain(struct list_head *ch, struct list_head *ct)
{
        __list_del(ch->prev, ct->next);
}

static inline void list_add_chain(struct list_head *ch, struct list_head *ct,
                        struct list_head *list)
{
        ch->prev = list;
        ct->next = list->next;
        list->next->prev = ct;
        list->next = ch;
}

static inline void list_add_chain_tail(struct list_head *ch, 
                        struct list_head *ct,
                        struct list_head *list)
{
        ch->prev = list->prev;
        ct->next = list;
        list->prev->next = ch;
        list->prev = ct;
}

static inline int list_empty(const struct list_head *list)
{
        return list->next == list;
}

#define offsetof(type, mem)             ( (unsigned int)&(((type *)0)->mem) )
#define list_entry(ptr, type, mem)      container_of(ptr, type, mem)
#define container_of(ptr, type, mem)    ({ \
                        const typeof (((type *)0)->mem) *__ptr = (ptr); \
                        (type *)((char *)__ptr - offsetof(type, mem));})
#define list_for_each(pos, head) \
                        for (pos = (head)->next; pos != (head); pos = pos->next)
#endif  //_LIST_H_

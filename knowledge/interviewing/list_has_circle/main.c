#include <stdio.h>      // for printf
#include <stdlib.h>     // for malloc
#define  LEN     10

struct list_head {
        int val;
        struct list_head *next;
};

void show_list(struct list_head *head)
{
        struct list_head *pnode;
        for (pnode = head; pnode != NULL; pnode = pnode->next) {
                printf("%d ", pnode->val);
        }
        printf("\n");
}

/* 判断单向链表是否有环，如果有，返回入环点，没有返回 NULL */
struct list_head *list_has_circle(struct list_head *head)
{
        struct list_head *p1 = head;
        struct list_head *p2 = head;
        while (p1 != NULL && p2 != NULL) {
                p1 = p1->next;
                p2 = p2->next->next;
                if (p1 == p2) {
                        break; 
                }
        }

        /* find circle */
        if (p1 != NULL && p2 != NULL) {
                p1 = head;
                while (p1 != p2) {
                        p1 = p1->next; 
                        p2 = p2->next;
                }
                return p1;
        }
        return NULL;
        
}

int main()
{
        int ret, i;
        struct list_head *head, *tail, *pnode;

        for (i = 0; i < LEN; ++i) {
                pnode = (struct list_head *)malloc(sizeof(struct list_head));
                pnode->val = i;
                pnode->next = NULL;
                if (i == 0) {
                        head = pnode;
                        tail = pnode;
                } else {
                        tail->next = pnode; 
                        tail = pnode;
                }
        }
        tail->next = tail;
#if 0
        show_list(head);
#endif
        printf("%d\n", list_has_circle(head)->val);
#if 0
        /* show_list(head); */
#endif

        return 0;
}

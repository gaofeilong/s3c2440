#include <stdio.h>      // for printf
#include <stdlib.h>     // for malloc
#define         LEN     10

struct list_node {
        int val;
        struct list_node *next;
};

void show_list(struct list_node *head)
{
        struct list_node *pnode;
        for (pnode = head; pnode != NULL; pnode = pnode->next) {
                printf("%d ", pnode->val);
        }
        printf("\n");
}

struct list_node *reverse_list(struct list_node **head)
{
        struct list_node *p1, *p2, *p3;
        
        if (!(*head) || !((*head)->next)) {
                return *head; 
        }

        p1 = *head;
        p2 = p1->next;
        p1->next = NULL;
        while (p2) {
                p3 = p2->next;
                p2->next = p1;
                p1 = p2;
                p2 = p3;
        }
        *head = p1;
        return *head;
}

int main()
{
        int i;
        struct list_node *head, *tail, *pnode;
        for (i = 0; i < LEN; ++i) {
                pnode = (struct list_node *)malloc(sizeof(struct list_node));
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
        show_list(head);
        reverse_list(&head);
        show_list(head);

        return 0;
}

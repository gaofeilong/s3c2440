#include <unistd.h>     // for sbrk
#include <stdio.h>      // for printf

void *managed_addr;
int inited = 0;
void *last_valid_addr;
struct memory_control_block {
        int size;
        int used;
};

void *my_malloc(long size)
{
        void *ret_addr = 0;
        void *current_addr;
        struct memory_control_block *mcb;

        if (!inited) {
                last_valid_addr = sbrk(0); 
                managed_addr = last_valid_addr;
                inited = 1;
        }

        current_addr = managed_addr;
        size += sizeof(struct memory_control_block);
        while (current_addr != last_valid_addr) {
                mcb = (struct memory_control_block *)current_addr;
                if (!mcb->used && mcb->size >= size) {
                        ret_addr = current_addr; 
                        mcb->used = 1;
                        break;
                }
                current_addr += mcb->size;
        }
        if (!ret_addr) {
                sbrk(size);
                ret_addr = last_valid_addr;
                last_valid_addr += size;
                mcb = (struct memory_control_block *)ret_addr;
                mcb->used = 1;
                mcb->size = size;
        }

        return ret_addr + sizeof(struct memory_control_block);
}

void my_free(void *addr)
{
        struct memory_control_block *mcb = (struct memory_control_block*)addr;
        mcb->used = 0;
}

int main()
{
        char *str1 = (char *)my_malloc(10);
        printf("%016x\n", str1);
        char *str2 = (char *)my_malloc(10);
        printf("%016x\n", str2);
        return 0;
}

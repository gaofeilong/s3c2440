/*******************************************************************************
 *
 * @ File Name  : mmu.c
 * @ Date       : 2012-03-30
 * @ Author     : gaofeilong <gaofeilonglcu@163.com>
 *
 * @ Description: initialize mmu and memory map.
 * @ History    : 2012-03-30：功能实现，重点：1> 定义宏；2> 分别对内存映射、IO
 *                      端口映射进行初始化；3> 启动MMU的协处理器操作。
 *
 * ****************************************************************************/

#define PT_BASE_ADDR            0x33f00000
#define PHY_MEM_ADDR            0x30000000       
#define VIR_MEM_ADDR            0x30000000
#define MEM_MAP_SIZE            0x04000000
#define PHY_IO_ADDR             0x48000000
#define VIR_IO_ADDR             0xc8000000
#define IO_MAP_SIZE             0x20000000
#define VIR_TO_PTE_INDEX        0xfff00000
#define PTE_TO_MEM_BASE_MASK    0xfff00000
#define PTE_AP_DEFAULT          (0x1<<0xa)
#define PTE_DOMAIN_DEFAULT      (0x0<<0x5)
#define PTE_NO_CACHE_BUFFER     (0x0<<0x2)
#define PTE_PAGE_TYPE           (0x1<<0x1)
#define get_pte_addr(x)         ( PT_BASE_ADDR | (((x)&VIR_TO_PTE_INDEX)>>18) )

void init_mmu()
{
        int i;
        unsigned pte, pte_addr;
        for (i = 0; i < MEM_MAP_SIZE>>20; ++i) {
                pte  = (PHY_MEM_ADDR + (i<<20)) & PTE_TO_MEM_BASE_MASK;
                pte |= PTE_PAGE_TYPE;
                pte |= PTE_AP_DEFAULT;
                pte |= PTE_DOMAIN_DEFAULT;
                pte |= PTE_NO_CACHE_BUFFER;
                pte_addr = get_pte_addr(VIR_MEM_ADDR + (i<<20));
                *(volatile unsigned int *)pte_addr = pte;
        }
        for (i = 0; i < IO_MAP_SIZE>>20; ++i) {
                pte  = (PHY_IO_ADDR + (i<<20)) & PTE_TO_MEM_BASE_MASK;
                pte |= PTE_PAGE_TYPE;
                pte |= PTE_AP_DEFAULT;
                pte |= PTE_DOMAIN_DEFAULT;
                pte |= PTE_NO_CACHE_BUFFER;
                pte_addr = get_pte_addr(VIR_IO_ADDR + (i<<20));
                *(volatile unsigned int *)pte_addr = pte;
        }
}

void start_mmu()
{
        unsigned int pt = PT_BASE_ADDR;

        asm (
                "mcr p15, 0, %0, c2, c0, 0\n"
                "mvn r0, #0x0\n"
                "mcr p15, 0, r0, c3, c0, 0\n"
                "mov r0, #0x1\n"
                "mcr p15, 0, r0, c1, c0, 0\n"
                "nop\n"
                "nop\n"
                "nop\n"
                :
                : "r" (pt)
                : "r0"
            );
}


/******************************************************************************
 *
 * @ File Name  : link.lds
 * @ Date       : 2012-03-24
 * @ Author     : gaofeilong <gaofeilonglcu@163.com>
 *
 * @ Description: link scripts, determin all section layout
 * @ History    : 2012-05-06：将__bss_start从.kernel上边拿到下边，删除.kernel
 *                      中的bss信息删掉                       
 *
 * ****************************************************************************/

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)

SECTIONS
{
        . = 0x00000000;
        . = ALIGN(4);
        .bootloader     : 
        { 
                start.o(.text .rodata* .data) 
                init.o(.text .rodata* .data) 
                serial.o(.text .rodata* .data) 
                nand.o(.text .rodata* .data) 
        }

        . = ALIGN(4);
        .kernel 0x30000000 : AT(0x1000) { *(.text .rodata* .data) }

        . = ALIGN(4);
        __bss_start = .;
        .bss            : { *(.bss) }
        . = ALIGN(4);
        __bss_end = .;


}

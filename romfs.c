/*******************************************************************************
 *
 * @ File Name  : romfs.c
 * @ Date       : 2012-08-06
 * @ Author     : gaofeilong <gaofeilonglcu@163.com>
 *
 * @ Description: romfs implement
 * @ History    : 2012-08-06: 创建文件，添加 init_romfs() 函数和其他函数框架
 *
 * ****************************************************************************/
#include "driver_framework.h"
#include "nand_driver.h"
#include "fs.h"

/* 根据inode地址和文件名长度取得存储文件数据的地址 */
#define get_file_offset(pnode, len)     (0)

struct inode *romfs_namei(struct super_block *super, char *p)
{
        return NULL;
}

unsigned int romfs_get_file_addr(struct inode *node)
{
        return get_file_offset(node->node_addr, strlen(node->name));
}


struct super_block romfs_super_block = {
        .namei = romfs_namei,
        .get_file_addr = romfs_get_file_addr,
        .name = "romfs"
};

void init_romfs(void)
{
        nand_driver_init();
        romfs_super_block.dev = storage_devices[NAND_STORAGE_INDEX];
        register_filesystem(&romfs_super_block, ROMFS_INDEX);
}

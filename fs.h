/*******************************************************************************
 *
 * @ File Name  : fs.h
 * @ Date       : 2012-08-05
 * @ Author     : gaofeilong <gaofeilonglcu@163.com>
 *
 * @ Description: file system framework
 * @ History    : 2012-08-05: 创建文件
 *              : 2012-08-06: 添加注册和注销文件系统函
 *
 * ****************************************************************************/

#ifndef _FILE_SYSTEM_H_
#define _FILE_SYSTEM_H_

#define MAX_SUPERBLOCK  2 
#define ROMFS_INDEX     0

#include "driver_framework.h"

struct super_block;

struct inode {
        char *name;
        unsigned int flags;
        unsigned int file_size;
        unsigned int node_addr;
        struct super_block *super;
};

struct super_block {
        struct inode *(*namei)(struct super_block *super, char *p);
        unsigned int (*get_file_addr)(struct inode *);

        struct storage_device *dev;
        char *name;
};

extern struct super_block *fs_type[];

void register_filesystem(struct super_block *fs, unsigned int index);
void unregister_filesystem(struct super_block *fs, unsigned int index);

#endif  //_FILE_SYSTEM_H_

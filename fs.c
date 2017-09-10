/*******************************************************************************
 *
 * @ File Name  : fs.c
 * @ Date       : 2012-08-05
 * @ Author     : gaofeilong <gaofeilonglcu@163.com>
 *
 * @ Description: file system framework
 * @ History    : 2012-08-05: 创建文件
 *              : 2012-08-06: 添加注册和注销文件系统函数，将init放在具体类型的
 *                      文件实现文件中
 *
 * ****************************************************************************/

#include "fs.h"

struct super_block *fs_type[MAX_SUPERBLOCK] = {0};

void register_filesystem(struct super_block *fs, unsigned int index)
{
        if (!fs_type[index]) {
                fs_type[index] = fs;
        }
        return;
}

void unregister_filesystem(struct super_block *fs, unsigned int index)
{
        fs_type[index] = NULL;
        return;
}

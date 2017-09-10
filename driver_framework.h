/*******************************************************************************
 *
 * @ File Name  : driver_framework.h
 * @ Date       : 2012-05-13, 2012-08-05
 * @ Author     : gaofeilong <gaofeilonglcu@163.com>
 *
 * @ Description: storage driver framework
 * @ History    : 2012-08-05: 创建文件
 *
 * ****************************************************************************/
#ifndef _DRIVER_FRAMEWORK_H_
#define _DRIVER_FRAMEWORK_H_

typedef unsigned char           U8;
typedef unsigned short          U16;
typedef unsigned long           U32;

#define MAX_STORAGE_DEVICE      2
#define NULL                    (void *)0

struct storage_device {
        U32 start_pos;
        U32 device_size;
        U32 sector_size;
        void (*read)(U32 start_addr, U8 *dest, U32 size);
        void (*write)(U32 start_addr, U8 *dest, U32 size);
};

extern struct storage_device *storage_devices[MAX_STORAGE_DEVICE];

void register_storage_device(struct storage_device *dev, unsigned int index);
void unregister_storage_device(struct storage_device *dev, unsigned int index);

#endif  //_DRIVER_FRAMEWORK_H_

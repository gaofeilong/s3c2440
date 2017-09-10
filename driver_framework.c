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

#include "driver_framework.h"

struct storage_device *storage_devices[MAX_STORAGE_DEVICE] = {0};

void register_storage_device(struct storage_device *dev, unsigned int index)
{
        if (!storage_devices[index]) {
                storage_devices[index] = dev;
        }
        return;
}

void unregister_storage_device(struct storage_device *dev, unsigned int index)
{
        storage_devices[index] = NULL;
        return;
}

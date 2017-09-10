/*******************************************************************************
 *
 * @ File Name  : nand_driver.h
 * @ Date       : 2012-05-13, 2012-08-05
 * @ Author     : gaofeilong <gaofeilonglcu@163.com>
 *
 * @ Description: nand flash driver
 * @ History    : 2012-05-13: 创建文件
 *                2012-07-11：添加CHIPID=0xECF1
 *                2012-07-29：添加地址转换到页号的宏，驱动测试通过
 *                2012-08-04：添加驱动结构体和设备列表数组
 *                2012-08-08：将 storage.* 拆分为 driver_framework.* 和
 *                      nand_driver.*，分为框架和具体设备驱动
 *
 * ****************************************************************************/
#ifndef _STORAGE_H_
#define _STORAGE_H_
#include "2440addr.h"
#include "driver_framework.h"

/* control */
#define ControlEnable()         (NFCONT |= 1)
#define ControlDisable()        (NFCONT &= ~1)
#define ChipEnable()            (NFCONT &= ~(1<<1))
#define ChipDisable()           (NFCONT |= (1<<1))
#define ResetEcc()              (NFCONT |= (1<<4))      /* reset ECC */
#define MainEccLock()           (NFCONT |= (1<<5))      /* lock main array ECC */
#define MainEccUnlock()         (NFCONT &= ~(1<<5))     /* unlock main array ECC */
#define SpareEccLock()          (NFCONT |= (1<<6))      /* lock spare array ECC */
#define SpareEccUnlock()        (NFCONT &= ~(1<<6))     /* unlock spare array ECC */

/* data, cmd and addr operation */
#define WriteCmd(c)             (NFCMD = (c))
#define WriteAddr(a)            (NFADDR = (a))

/* #define WaitIdle()               while ( !(NFSTAT & 1) ) */
#define ClearRb()               (NFSTAT |= (1<<2))
#define DetectRb()               while ( !(NFSTAT & (1<<2)) )
#define ReadData8()             (NFDATA8)               /* byte */
#define ReadData32()            (NFDATA32)              /* word */
#define WriteData8(x)           (NFDATA8 = (x) )        /* byte */ 
#define WriteData32(x)          (NFDATA32 = (x) )       /* word */
#define ReadMainEcc()           (NFMECC0)               /* for 8 bit nand flash,  only use NFMECC0 */
#define ReadSpareEcc()          (NFSECC)                /* for 8 bit nand flash,  only use low 16 bits */

/* nand flash command set */
#define READCMD0                0x00
#define READCMD1                0x30
#define WRITECMD0               0x80
#define WRITECMD1               0x10
#define ERASECMD0               0x60
#define ERASECMD1               0xd0
#define READSTATUSCMD           0x70
#define READIDCMD               0x90
#define RESETCMD                0xff
#define RANDOMREADCMD0          0x05
#define RANDOMREADCMD1          0xe0
#define RANDOMWRITECMD          0x85

/* nand flash k9f1g08 info */
#define NAND_BLOCK_PER_DEVICE   1024
#define NAND_PAGE_PER_BLOCK     64
#define NAND_PAGE_SIZE          2048
#define NAND_PAGE_MASK          ((NAND_PAGE_SIZE) - 1)

/* others */
#define NAND_CHIPID             0xecf1
#define NAND_ADDR_TO_PAGE(x)    ((x)>>16)
#define NAND_STORAGE_INDEX      0

void nand_driver_init(void);

#endif  //_STORAGE_H_

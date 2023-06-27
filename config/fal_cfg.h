/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-5      SummerGift   first version
 */

#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

#include <rtthread.h>
#include <board.h>
#include "appconfig.h"

#ifdef AT32

extern const struct fal_flash_dev at32_onchip_flash;

#define FAL_FLASH_DEV_TABLE                                          \
{                                                                    \
    &at32_onchip_flash                                                \
}

/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG

#define FAL_PART_TABLE                                                                  \
{                                                                                       \
    {FAL_PART_MAGIC_WROD, APP_PART_NAME,"onchip_flash", APP_ADDR, APP_SIZE, 0}, \
}

#endif

#endif /* FAL_PART_HAS_TABLE_CFG */
#endif /* _FAL_CFG_H_ */

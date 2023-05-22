/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-18     tcjia       the first version
 * 2022-11-4      tcjia       first startup auto format flash
 */

#include "appconfig.h"

#ifdef QSPI_FLASH
#include <rtthread.h>
#include <rtdevice.h>
#include "dfs_fs.h"
#include "sfud.h"
#include "drv_spi.h"
#include "spi_flash.h"

/**
 * attach flash device in spi1 bus
 * @return
 */
static int rt_hw_spi_flash_init()
{
    extern rt_err_t at32_qspi_bus_attach_device(const char *bus_name, const char *device_name, rt_uint32_t pin, rt_uint8_t data_line_width, void (*enter_qspi_mode)(), void (*exit_qspi_mode)());
    extern rt_spi_flash_device_t rt_sfud_flash_probe(const char *spi_flash_dev_name, const char *spi_dev_name);
    at32_qspi_bus_attach_device(QSPI_FLASH_BUS, QSPI_FLASH_ATTACH, QSPI_FLASH_CS, 4, RT_NULL, RT_NULL);
    if (rt_sfud_flash_probe(QSPI_FLASH_DEVICE, QSPI_FLASH_ATTACH) == RT_NULL)
    {
        rt_kprintf("spi flash probe failed!\n");
    }
    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_spi_flash_init);




/**
 * mount flash block device
 * @return
 */
static int mnt_init()
{
    if (dfs_mount(QSPI_FLASH_DEVICE, QSPI_FLASH_PATH, QSPI_FLASH_FS, 0, 0) == 0)
    {
        rt_kprintf("dfs mount ok\n");
    }
    else
    {
        rt_kprintf("dfs mount failed\n");
        extern void mkfs(const char *fs_name, const char *device_name);
        mkfs(QSPI_FLASH_FS, QSPI_FLASH_DEVICE);
        rt_kprintf("tried format flash device\n");
        rt_kprintf("reset device!\n");
        rt_thread_mdelay(3000);
        rt_hw_cpu_reset();
    }
    return 0;
}
INIT_ENV_EXPORT(mnt_init);

#endif

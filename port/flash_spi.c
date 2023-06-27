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

#if defined FLASH_SPI || defined FLASH_QSPI
#include <rtdevice.h>
#include "dfs_fs.h"
#include "sfud.h"
#include "drv_spi.h"
#include "spi_flash.h"
#include "common.h"

// spi bus name
#ifdef FLASH_SPI
#define FLASH_SPI_BUS          "spi"FLASH_SPI_PORT
#else
#define FLASH_SPI_BUS          "qspi"FLASH_SPI_PORT
#endif

#define FLASH_SPI_ATTACH        FLASH_SPI_BUS"0"
#define FLASH_SPI_CS            GET_PIN(FLASH_SPI_CS_GPIO, FLASH_SPI_CS_PIN)


/**
 * attach flash device in spi1 bus
 * @return
 */
static int rt_hw_spi_flash_init()
{
#ifdef FLASH_SPI
    extern rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, gpio_type *cs_gpiox, uint16_t cs_gpio_pin);
    rt_hw_spi_device_attach(FLASH_SPI_BUS, FLASH_SPI_ATTACH, GPIOx(FLASH_SPI_CS_GPIO), PINx(FLASH_SPI_CS_PIN));
#else
    extern rt_err_t at32_qspi_bus_attach_device(const char *bus_name, const char *device_name, rt_uint32_t pin, rt_uint8_t data_line_width, void (*enter_qspi_mode)(), void (*exit_qspi_mode)());
    at32_qspi_bus_attach_device(FLASH_SPI_BUS, FLASH_SPI_ATTACH, FLASH_SPI_CS, 4, RT_NULL, RT_NULL);
#endif

    extern rt_spi_flash_device_t rt_sfud_flash_probe(const char *spi_flash_dev_name, const char *spi_dev_name);
    if (rt_sfud_flash_probe(FLASH_OC_DEVICE, FLASH_SPI_ATTACH) == RT_NULL)
    {
        kprintf("spi flash probe failed!\n");
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
    if (dfs_mount(FLASH_OC_DEVICE, FLASH_OC_PATH, FLASH_OC_FS, 0, 0) == 0)
    {
        kprintf("dfs mount ok\n");
    }
    else
    {
        kprintf("dfs mount failed\n");
        extern void mkfs(const char *fs_name, const char *device_name);
        mkfs(FLASH_OC_FS, FLASH_OC_DEVICE);
        kprintf("tried format flash device\n");
        kprintf("reset device!\n");
        mdelay(10000);
        reboot();
    }
    return 0;
}
INIT_ENV_EXPORT(mnt_init);

#endif

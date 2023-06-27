/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-25     RT-Thread    first version
 */

#include "appconfig.h"
#include <rtthread.h>
#include <rtdevice.h>
#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>
#include <fal.h>
#include "common.h"

int main(void)
{
#ifdef BOOTLOADER
    fal_init();
#else

    int pin = rt_pin_get("PB.5");
    rt_pin_mode(pin, PIN_MODE_OUTPUT_OD);
    u8 data0[8] = {0};
    u8 data1[8] = {0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00};
    static rt_device_t hidd;
    hidd = rt_device_find("hidd");
    rt_device_open(hidd, RT_DEVICE_OFLAG_RDWR);
    rt_thread_mdelay(5000);
#endif
    while (1)
    {
#ifdef BOOTLOADER
        rt_thread_mdelay(10000);
#else
//        LOG_D("Hello RT-Thread!");
//        rt_pin_write(pin, 1);
        rt_device_write(hidd, 1, data0, 8);
        rt_thread_mdelay(1000);
//        rt_pin_write(pin, 0);
        rt_device_write(hidd, 1, data1, 8);
        rt_thread_mdelay(1000);
#endif
    }

    return RT_EOK;
}

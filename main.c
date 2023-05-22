/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-25     RT-Thread    first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

int main(void)
{
    int count = 1;
    int pin = rt_pin_get("PB.5");
    rt_pin_mode(pin, PIN_MODE_OUTPUT_OD);
    while (count++)
    {
//        LOG_D("Hello RT-Thread!");
        rt_pin_write(pin, 1);
        rt_thread_mdelay(1000);
        rt_pin_write(pin, 0);
        rt_thread_mdelay(1000);
    }

    return RT_EOK;
}

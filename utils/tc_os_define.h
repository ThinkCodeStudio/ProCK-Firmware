/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-22     tcjia       the first version
 */
#ifndef APPLICATIONS_UTILS_TC_OS_DEFINE_H_
#define APPLICATIONS_UTILS_TC_OS_DEFINE_H_

#include <rtthread.h>

#define mdelay(m)               rt_thread_mdelay(m)
#define reboot()                rt_hw_cpu_reset()
#define kprintf(fmt, ...)       rt_kprintf(fmt, ##__VA_ARGS__)

#endif /* APPLICATIONS_UTILS_TC_OS_DEFINE_H_ */

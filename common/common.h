/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-22     tcjia       the first version
 */
#ifndef APPLICATIONS_COMMON_COMMON_H_
#define APPLICATIONS_COMMON_COMMON_H_

#include "appconfig.h"
#include "tc_type.h"
#include "tc_os_define.h"

//*******Do not change****//
#ifdef STM32
#define XXX_GPIOx(x)            GPIO##x
#define XXX_PINx(x)             GPIO_PIN_##x
#endif
#ifdef AT32
#define XXX_GPIOx(x)            GPIO##x
#define XXX_PINx(x)             GPIO_PINS_##x
#endif

#define GPIOx(x)                XXX_GPIOx(x)
#define PINx(x)                 XXX_PINx(x)

#endif /* APPLICATIONS_COMMON_COMMON_H_ */

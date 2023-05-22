/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-19     tcjia       the first version
 */
#ifndef APPLICATIONS_APPCONFIG_H_
#define APPLICATIONS_APPCONFIG_H_

// flash
#define QSPI_FLASH
#ifdef QSPI_FLASH

// spi bus name
#define QSPI_FLASH_BUS          "qspi1"
// attach device name to spi bus
#define QSPI_FLASH_ATTACH       "qspi10"
// device name
#define QSPI_FLASH_DEVICE       "W25"
// file system
#define QSPI_FLASH_FS           "elm"
// mount dir
#define QSPI_FLASH_PATH         "/"
// chip select pin
#define QSPI_FLASH_CS      GET_PIN(G, 6)

#endif

#endif /* APPLICATIONS_APPCONFIG_H_ */

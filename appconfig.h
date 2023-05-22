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

/**     chip        **/
#define AT32F435

/**     app         **/
#define BOOTLOADER
#define BOOT_APP_ADDR      0x08010000UL
#define BOOT_BKP           ERTC_DT15

/**     module      **/


/**     device      **/
#ifndef BOOTLOADER
//#define FLASH_SPI
#define FLASH_QSPI
#define FLASH_SPI_PORT          "1"
#define FLASH_SPI_CS_GPIO       G
#define FLASH_SPI_CS_PIN        6
#define FLASH_OC_DEVICE         "ecf"
#define FLASH_OC_FS             "elm"
#define FLASH_OC_PATH           "/"
#endif


#endif /* APPLICATIONS_APPCONFIG_H_ */

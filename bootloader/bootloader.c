/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-22     tcjia       the first version
 */

#include "appconfig.h"

#if defined BOOTLOADER && defined AT32F435
#include "common.h"
#include <stdio.h>
#include "drv_common.h"
#define AT32_SRAM_SIZE                  512
#define AT32_SRAM_END                   (0x20000000 + AT32_SRAM_SIZE * 1024)
#define ENTER_BOOT_TIMEOUT 500
#define APP_PART_NAME      "app"
#define DOWNLOAD_PART_NAME "download"

typedef void (*boot_app_func)(void);
void boot_start_application(void) {
    crm_periph_clock_enable(CRM_PWC_PERIPH_CLOCK, TRUE);
    pwc_battery_powered_domain_access(TRUE);

    __disable_irq();
    uint32_t bkp_data = ertc_bpr_data_read(BOOT_BKP);
    ertc_bpr_data_write(BOOT_BKP, 0);

    if (bkp_data != 0xA5A5) return;

    boot_app_func app_func = NULL;
    uint32_t app_addr = BOOT_APP_ADDR;
    if (((*(__IO uint32_t *)(app_addr + 4)) & 0xff000000) != 0x08000000) return;

    /* 栈顶地址在 512K RAM 间 */
    if (((*(__IO uint32_t *)app_addr) - 0x20000000) >= (AT32_SRAM_SIZE * 1024)) return;

    app_func = (boot_app_func) * (__IO uint32_t *)(app_addr + 4);
    /* Configure main stack */
    __set_MSP(*(__IO uint32_t *)app_addr);
    /* jump to application */
    app_func();
}

#endif

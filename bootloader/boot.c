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

#if defined BOOTLOADER && defined AT32
#include "common.h"
#include <stdio.h>
#include "drv_common.h"
#include <agile_upgrade.h>

extern const struct agile_upgrade_ops agile_upgrade_file_ops;
extern const struct agile_upgrade_ops agile_upgrade_fal_ops;

void boot_app_enable(void)
{
    __disable_irq();
    ertc_bpr_data_write(BOOT_BKP, 0xA5A5);
    NVIC_SystemReset();
}

typedef void (*boot_app_func)(void);
void boot_start_application(void)
{
    crm_periph_clock_enable(CRM_PWC_PERIPH_CLOCK, TRUE);
    pwc_battery_powered_domain_access(TRUE);

    __disable_irq();
    uint32_t bkp_data = ertc_bpr_data_read(BOOT_BKP);
    ertc_bpr_data_write(BOOT_BKP, 0);

    if (bkp_data != 0xA5A5)
        return;

    boot_app_func app_func = NULL;
    uint32_t app_addr = ROM_START + APP_ADDR;
    if (((*(__IO uint32_t *) (app_addr + 4)) & 0xff000000) != 0x08000000)
        return;

    /* 栈顶地址在 512K RAM 间 */
    if (((*(__IO uint32_t *) app_addr) - 0x20000000) >= RAM_SIZE)
        return;

    app_func = (boot_app_func) *(__IO uint32_t *) (app_addr + 4);
    /* Configure main stack */
    __set_MSP(*(__IO uint32_t *) app_addr);
    /* jump to application */
    app_func();
}

void boot_upgrade(const char *src_path)
{
    agile_upgrade_t src_agu = { 0 };
    src_agu.name = "src";
    src_agu.user_data = src_path;
    src_agu.ops = &agile_upgrade_file_ops;

    agile_upgrade_t dst_agu = { 0 };
    dst_agu.name = "app";
    dst_agu.user_data = APP_PART_NAME;
    dst_agu.ops = &agile_upgrade_fal_ops;

    agile_upgrade_release(&src_agu, &dst_agu, 0);

    boot_app_enable();
}

#ifdef BOOTLOADER_CMD
#include <string.h>
static int boot(int argc, char **argv)
{
    if(argc > 1 && (!strcmp(argv[1],"-g") || !strcmp(argv[1],"upgrade"))){
        if(argc > 2)
        {
            boot_upgrade(argv[2]);
        }
        else{
            boot_upgrade("/sec.rbl");
        }
    }
    else{
        kprintf("-g\t upgrade [p]\t upgrade app, p is path of rbl file, default sec.rbl");
    }

    return 0;
}
MSH_CMD_EXPORT(boot, the tool for upgrade firmware);
#endif

#else
void boot_start_application(void)
{}
#endif

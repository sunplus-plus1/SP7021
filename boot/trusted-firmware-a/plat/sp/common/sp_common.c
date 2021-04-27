/*
 * Copyright (c) 2017-2019, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <errno.h>

#include <platform_def.h>

#include <arch_helpers.h>
#include <common/debug.h>
#include <lib/mmio.h>
#include <lib/xlat_tables/xlat_tables_v2.h>
#include <plat/common/platform.h>

#include <sp_def.h>
#include <sp_mmap.h>
#include <sp_private.h>

static const mmap_region_t sp_mmap[PLATFORM_MMAP_REGIONS + 1] = {
	MAP_REGION_FLAT(SP_DRAM_SEC_ADDR, SP_DRAM_SEC_SIZE,    MT_MEMORY | MT_RW | MT_SECURE),
	MAP_REGION_FLAT(SP_DRAM_NS_ADDR,  SP_DRAM_NS_SIZE,     MT_MEMORY | MT_RW | MT_NS),
	MAP_REGION_FLAT(SP_RGST_BASE,     SP_RGST_SIZE,        MT_DEVICE | MT_RW | MT_SECURE | MT_EXECUTE_NEVER),
	MAP_REGION_FLAT(SP_CBSRAM_BASE,   SP_CBSRAM_SIZE,      MT_MEMORY | MT_RW | MT_NS),
	{},
};

unsigned int plat_get_syscnt_freq2(void)
{
	return SP_ARM_COUNTER_CLK_IN;
}

void sp_configure_mmu_el3(int flags)
{
	
	mmap_add_region(BL31_BASE, BL31_BASE, (BL31_LIMIT - BL31_BASE),
			MT_MEMORY | MT_RW | MT_SECURE);
	mmap_add_region(BL_CODE_BASE, BL_CODE_BASE, (BL_CODE_END - BL_CODE_BASE),
			MT_CODE | MT_SECURE);
	mmap_add_region(BL_RO_DATA_BASE, BL_RO_DATA_BASE, BL_RO_DATA_END - BL_RO_DATA_BASE,
			MT_RO_DATA | MT_SECURE);

	mmap_add(sp_mmap);
	init_xlat_tables();

	enable_mmu_el3(0);
}

uint16_t sp_read_soc_id(void)
{
	uint32_t reg = mmio_read_32(SP_RGST_BASE);
	return reg;
}

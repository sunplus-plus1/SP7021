/*
 * Copyright (c) 2017-2019, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_DEF_H
#define PLATFORM_DEF_H

#include <common/tbbr/tbbr_img_def.h>
#include <lib/utils_def.h>
#include <plat/common/common_def.h>

#include <sp_mmap.h>

#define CPU_WAIT_INIT_VAL			0xffffffff
#define CORE_CPU_START_POS(core_id)	(CORE0_CPU_START_POS - ((core_id) * 8))
#define CORE3_CPU_START_POS     	(0xfa240000 - 0x28)  // core3 wait fa23_ffd8
#define CORE2_CPU_START_POS    	 	(0xfa240000 - 0x20)  // core2 wait fa23_ffe0
#define CORE1_CPU_START_POS    	 	(0xfa240000 - 0x18)  // core1 wait fa23_ffe8
#define CORE0_CPU_START_POS     	(0xfa240000 - 0x10)  // core0 wait fa23_fff0


/*
 * DRAM
 *   Secure :   0 ~   4MB
 *   NS     :   4 ~  64MB
 *
 * Software :
 *   BL31   @ 2MB
 *   uboot  @ 3MB
 */
#define SP_DRAM_SEC_ADDR		(SP_DRAM_BASE)
#define SP_DRAM_SEC_SIZE		(4U << 20)
#define SP_DRAM_NS_ADDR			(SP_DRAM_SEC_ADDR + SP_DRAM_SEC_SIZE)
#define SP_DRAM_NS_SIZE			((64U << 20) - SP_DRAM_NS_ADDR)

#define BL31_BASE				0x200000 /* @ 2MB */
#define BL31_LIMIT				(BL31_BASE + 0x100000)

#define SP_LINUX_DTB_OFFSET		(SP_DRAM_BASE + 0x400000)  /* dtb @ 4MB */
#define PLAT_SP_NS_IMAGE_OFFSET	(SP_DRAM_BASE + 0x300040) /* uboot @ 3MB+64 */


/* stack */
#define PLATFORM_STACK_SIZE		(0x2000 / PLATFORM_CORE_COUNT)  /* in case that verbose string is long */



/* max cacheline size = 64 bytes */
#define CACHE_WRITEBACK_SHIFT		6
#define CACHE_WRITEBACK_GRANULE		(1 << CACHE_WRITEBACK_SHIFT)

/* map regions */
#define PLATFORM_MMAP_REGIONS		4
#define MAX_MMAP_REGIONS			(3 + PLATFORM_MMAP_REGIONS)
#define MAX_XLAT_TABLES				8

#define PLAT_PHY_ADDR_SPACE_SIZE	(1ULL << 32)
#define PLAT_VIRT_ADDR_SPACE_SIZE	(1ULL << 32)


/* PWR */
#define PLAT_MAX_PWR_LVL_STATES		U(2)
#define PLAT_MAX_RET_STATE			U(1)
#define PLAT_MAX_OFF_STATE			U(2)
#define PLAT_MAX_PWR_LVL			U(2) /* See plat/sp/common/sp_topology.c */
#define PLAT_NUM_PWR_DOMAINS		(U(1) + PLATFORM_CLUSTER_COUNT + PLATFORM_CORE_COUNT)

/* cores */
#define PLATFORM_CLUSTER_COUNT			U(1)
#define PLATFORM_MAX_CPUS_PER_CLUSTER	U(4)
#define PLATFORM_CORE_COUNT				(PLATFORM_CLUSTER_COUNT * PLATFORM_MAX_CPUS_PER_CLUSTER)

#endif /* PLATFORM_DEF_H */

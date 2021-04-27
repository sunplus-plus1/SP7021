/*
 * Copyright (c) 2017-2020, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>

#include <platform_def.h>

#include <arch_helpers.h>
#include <common/debug.h>
#include <drivers/arm/gicv2.h>
#include <drivers/delay_timer.h>
#include <lib/mmio.h>
#include <lib/psci/psci.h>
#include <plat/common/platform.h>

#include <sp_private.h>
#include <lib/libc/errno.h>
#include <lib/el3_runtime/context_mgmt.h>

static entry_point_info_t next_ep_info[PLATFORM_CORE_COUNT];

static void sp_pwr_domain_on_finish(const psci_power_state_t *target_state)
{
	int coreid;
	entry_point_info_t *ep;
	uint32_t next_pc; /* phy addr < 4GB in this IC */

	coreid = plat_my_core_pos();

	mmio_write_32(SP_RGST_BASE, (uint32_t)0xb131ca00);
	mmio_write_32(SP_RGST_BASE, coreid);

	if (coreid >= PLATFORM_CORE_COUNT) {
		return ; /* not support */
	}

	mmio_write_32(SP_RGST_BASE, (uint32_t)0xb131ca01);
	next_pc = mmio_read_32(CORE_CPU_START_POS(coreid)); // =secondary_holding_pen
	mmio_write_32(SP_RGST_BASE, (uint32_t)next_pc);

	ep = &next_ep_info[coreid];

	/* setup for NS gic. Refer to optee gic_cpu_init() */
	/* per-CPU interrupts config:
	 * ID0-ID7(SGI)   for Non-secure interrupts
	 * ID8-ID15(SGI)  for Secure interrupts.
	 * All PPI config as Non-secure interrupts.
	 */
	mmio_write_32(SP_GICD_BASE + GICD_IGROUPR, 0xffff00ff);

	mmio_write_32(SP_GICC_BASE + GICC_PMR, 0x80);

	/* enable G0 and G1 */
	mmio_write_32(SP_GICC_BASE + GICC_CTLR, FIQ_EN_BIT | CTLR_ENABLE_G0_BIT | CTLR_ENABLE_G1_BIT);

	/* Populate entry point information for this core */
	SET_PARAM_HEAD(ep, PARAM_EP, VERSION_1, 0);
	ep->pc = next_pc;
	ep->spsr = SPSR_64(MODE_EL2, MODE_SP_ELX, DISABLE_ALL_EXCEPTIONS);
	ep->args.arg0 = (u_register_t)SP_LINUX_DTB_OFFSET;
	ep->args.arg1 = 0ULL;
	ep->args.arg2 = 0ULL;
	ep->args.arg3 = 0ULL;
	SET_SECURITY_STATE(ep->h.attr, NON_SECURE);

	mmio_write_32(SP_RGST_BASE, (uint32_t)0xb131ca02);
	cm_init_my_context(ep);

	mmio_write_32(SP_RGST_BASE, (uint32_t)0xb131ca09);
	mmio_write_32(SP_RGST_BASE, (uint32_t)coreid);
}

static void __dead2 sp_pwr_down_wfi(const psci_power_state_t *target_state)
{
	sp_cpu_off(read_mpidr());

	/* coverity[no_escape] */
	while (1) {
		wfi();
	}
}

static void __dead2 sp_system_off(void)
{
	gicv2_cpuif_disable();

	NOTICE("%s: L#%d\n", __func__, __LINE__);

	/* Turn off all secondary CPUs */
	sp_disable_secondary_cpus(read_mpidr());

	NOTICE("%s: halt\n", __func__);

	/* coverity[no_escape] */
	while (1) {
		wfi();
	}
}

static void __dead2 sp_system_reset(void)
{
	gicv2_cpuif_disable();

	NOTICE("%s: L#%d\n", __func__, __LINE__);

	mmio_write_32(SP_RGST_BASE + 0x100, RF_MASK_V_SET(1 << 0)); /* G2.0[0] */

	/* Wait before panicking */
	mdelay(1000);

	ERROR("%s: reset failed\n", __func__);

	/* coverity[no_escape] */
	while (1) {
		wfi();
	}
}


static plat_psci_ops_t sp_psci_ops = {
	.system_off			= sp_system_off,
	.system_reset			= sp_system_reset,
	.pwr_domain_on_finish		= sp_pwr_domain_on_finish,
	.pwr_domain_pwr_down_wfi	= sp_pwr_down_wfi,
};

int plat_setup_psci_ops(uintptr_t sec_entrypoint,
			const plat_psci_ops_t **psci_ops)
{
	assert(psci_ops);

	NOTICE("PSCI: %s\n", __func__);

	*psci_ops = &sp_psci_ops;

	return 0;
}

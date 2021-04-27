/*
 * Copyright (c) 2017-2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>

#include <libfdt.h>

#include <platform_def.h>

#include <arch.h>
#include <arch_helpers.h>
#include <common/debug.h>
#include <drivers/arm/gicv2.h>
#include <drivers/console.h>
#include <drivers/generic_delay_timer.h>
#include <lib/mmio.h>
#include <lib/el3_runtime/cpu_data.h>
#include <plat/common/platform.h>
#include <sp_def.h>
#include <sp_mmap.h>
#include <sp_private.h>


static entry_point_info_t bl32_image_ep_info;
static entry_point_info_t bl33_image_ep_info;

static const gicv2_driver_data_t sp_gic_data = {
	.gicd_base = SP_GICD_BASE,
	.gicc_base = SP_GICC_BASE,
};

uintptr_t plat_get_ns_image_entrypoint(void)
{
	volatile unsigned int *pass;
	uintptr_t ap_addr;

	/* See xboot go_a32_to_a64(ap_addr) */
	pass = (void *)CORE0_CPU_START_POS + 4; // =fa23_fff4
	ap_addr = (uintptr_t)*pass;

	if (ap_addr)
		return ap_addr;

	return PLAT_SP_NS_IMAGE_OFFSET;
}

void bl31_early_platform_setup2(u_register_t arg0, u_register_t arg1,
				u_register_t arg2, u_register_t arg3)
{
	/* Initialize the debug console as soon as possible */
	sp_console_setup();

#ifdef BL32_BASE
	/* Populate entry point information for BL32 */
	SET_PARAM_HEAD(&bl32_image_ep_info, PARAM_EP, VERSION_1, 0);
	SET_SECURITY_STATE(bl32_image_ep_info.h.attr, SECURE);
	bl32_image_ep_info.pc = BL32_BASE;
#endif
	/* Populate entry point information for BL33 */
	SET_PARAM_HEAD(&bl33_image_ep_info, PARAM_EP, VERSION_1, 0);

	/* Tell BL31 where the non-trusted software image
	 * is located and the entry state information
	 */

	bl33_image_ep_info.spsr = SPSR_64(MODE_EL2, MODE_SP_ELX, DISABLE_ALL_EXCEPTIONS);

	bl33_image_ep_info.pc = plat_get_ns_image_entrypoint();
	bl33_image_ep_info.args.arg0 = SP_LINUX_DTB_OFFSET;
	bl33_image_ep_info.args.arg1 = 0ULL;
	bl33_image_ep_info.args.arg2 = 0ULL;
	bl33_image_ep_info.args.arg3 = 0ULL;
	SET_SECURITY_STATE(bl33_image_ep_info.h.attr, NON_SECURE);
}

void bl31_plat_arch_setup(void)
{
	sp_configure_mmu_el3(0);
}

void bl31_platform_setup(void)
{
	uint32_t val;
	const char *soc_name;
	uint32_t soc_id = sp_read_soc_id();
	switch (soc_id) {
	case SP_Q645:
	default:
		soc_name = "Q645";
	}

	NOTICE("BL31: Detected %s SoC (%04x)\n", soc_name, soc_id);

	generic_delay_timer_init();

	/* Configure the interrupt controller */
	gicv2_driver_init(&sp_gic_data);
	gicv2_distif_init();
	gicv2_pcpu_distif_init();
	gicv2_cpuif_enable();

	/* setup for NS gic. Refer to optee gic_init(). */

	/* per-CPU inerrupts config:
	 * ID0-ID7(SGI)   for Non-secure interrupts
	 * ID8-ID15(SGI)  for Secure interrupts.
	 * All PPI config as Non-secure interrupts.
	 */
	mmio_write_32(SP_GICD_BASE + GICD_IGROUPR, 0xffff00ff);
	mmio_write_32(SP_GICC_BASE + GICC_PMR, 0x80);

	/* gicc: enable G0 and G1 */
	mmio_write_32(SP_GICC_BASE + GICC_CTLR, FIQ_EN_BIT | CTLR_ENABLE_G0_BIT | CTLR_ENABLE_G1_BIT);

	/* gicd: enable G0 and G1 */
	val = mmio_read_32(SP_GICD_BASE + GICD_CTLR);
	mmio_write_32(SP_GICD_BASE + GICD_CTLR, val | CTLR_ENABLE_G0_BIT | CTLR_ENABLE_G1_BIT);

	// verify
	VERBOSE("gicd typer = 0x%08x\n", mmio_read_32(SP_GICD_BASE + GICD_TYPER));
	VERBOSE("gicd igrp = 0x%08x\n", mmio_read_32(SP_GICD_BASE + GICD_IGROUPR));
	VERBOSE("gicc pmr  = 0x%08x\n", mmio_read_32(SP_GICC_BASE + GICC_PMR));
	VERBOSE("gicc ctrl = 0x%08x\n", mmio_read_32(SP_GICC_BASE + GICC_CTLR));
	VERBOSE("gicd ctrl = 0x%08x\n", mmio_read_32(SP_GICD_BASE + GICD_CTLR));

	INFO("BL31: Platform setup done\n");
}

void bl31_plat_runtime_setup(void)
{
	int i;

	VERBOSE("BL31: RT setup\n");

	/* Init smp states.
	 * Refer to psci_set_aff_info_state_by_idx(i, AFF_STATE_ON);
	 */
	for (i = 1; i < PLATFORM_CORE_COUNT; i++) {
		set_cpu_data_by_index(i, psci_svc_cpu_data.aff_info_state, AFF_STATE_ON_PENDING);
		flush_cpu_data_by_index(i, psci_svc_cpu_data.aff_info_state);
	}
}

entry_point_info_t *bl31_plat_get_next_image_ep_info(uint32_t type)
{
	VERBOSE("BL31: get next img type=%u\n", type);

	assert(sec_state_is_valid(type) != 0);

	if (type == NON_SECURE)
		return &bl33_image_ep_info;

	if ((type == SECURE) && bl32_image_ep_info.pc)
		return &bl32_image_ep_info;

	return NULL;
}

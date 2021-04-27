/*
 * Copyright (c) 2020, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <arch.h>
#include <asm_macros.S>
#include <common/bl_common.h>
#include <platform_def.h>

	.globl  plat_my_core_pos
	.globl	plat_get_my_entrypoint
	.globl	plat_secondary_cold_boot_setup
	.globl	plat_is_my_cpu_primary

func plat_my_core_pos /* MPIDR : 8100_0x00, x=0~3 */
	mrs     x0, mpidr_el1
	lsr	x0, x0, #MPIDR_AFF1_SHIFT
	and	x0, x0, #MPIDR_AFFLVL_MASK
	ret
endfunc plat_my_core_pos

/* -----------------------------------------------------------------------
 * Indicate a cold boot for every CPU
 * -----------------------------------------------------------------------
 */
func plat_get_my_entrypoint
	mov	x0, #0
	ret
endfunc plat_get_my_entrypoint

/* -----------------------------------------------------------------------
 * void plat_secondary_cold_boot_setup (void);
 * -----------------------------------------------------------------------
 */
func plat_secondary_cold_boot_setup
	/*
	 * Poll the CPU's hold entry until it indicates to jump
	 * to the entrypoint address.
	 */
	bl	plat_my_core_pos

	/* x0 = 0~3 (core #) */
	mov	x1, #CPU_WAIT_INIT_VAL
	mov	x2, #0
	mov	x3, #0
	mov	x4, #0

	ldr	w2, =CORE0_CPU_START_POS
	sub	x2, x2, x0, LSL #3	/* core wait address = x2 - (core * 8) */
	str	w1, [x2]		/* w2 = init */
	dsb	sy
poll_hold_entry:
	ldr	w3, [x2]		/* wait until x2 is changed */
	cmp	w3, w1
	b.eq	1f
	ldr	w4, =bl31_warm_entrypoint
#if 1 // stamp given pc
	mov     x21, #0
	ldr     w21, =0xf8000000
	ldr	w22, =0x12345001
	str     w22, [x21]
	str     w3, [x21]
#endif
	br	x4
1:
	wfe
	b	poll_hold_entry
endfunc plat_secondary_cold_boot_setup

/* -----------------------------------------------------------------------
 * unsigned int plat_is_my_cpu_primary (void);
 *
 * Find out whether the current cpu is the primary cpu
 * -----------------------------------------------------------------------
 */
func plat_is_my_cpu_primary
	mov	x9, x30
	bl	plat_my_core_pos
	cmp	x0, #0
	cset	x0, eq		/* set 1 for primary, and set 0 for others */
	ret	x9
endfunc plat_is_my_cpu_primary

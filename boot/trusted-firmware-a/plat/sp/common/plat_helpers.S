/*
 * Copyright (c) 2017-2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <arch.h>
#include <asm_macros.S>
#include <sp_def.h>
#include <sp_mmap.h>

	.globl	plat_reset_handler
	.globl	platform_mem_init
	.globl	plat_report_exception

func plat_reset_handler
	ret
endfunc plat_reset_handler

func platform_mem_init
	ret
endfunc platform_mem_init

func plat_report_exception
	ret
endfunc plat_report_exception

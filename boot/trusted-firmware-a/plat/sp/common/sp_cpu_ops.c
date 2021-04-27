/*
 * Copyright (c) 2017-2019, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <common/debug.h>

void sp_cpu_off(u_register_t mpidr)
{
	INFO("%s: L#%d 0x%lx\n", __func__, __LINE__, mpidr);
}

void sp_cpu_on(u_register_t mpidr)
{
	INFO("%s: L#%d 0x%lx\n", __func__, __LINE__, mpidr);
}

void sp_disable_secondary_cpus(u_register_t primary_mpidr)
{
	INFO("%s: L#%d 0x%lx\n", __func__, __LINE__, primary_mpidr);
}

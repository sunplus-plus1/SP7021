/*
 * Copyright (c) 2017-2019, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SP_PRIVATE_H
#define SP_PRIVATE_H

void sp_configure_mmu_el3(int flags);

void sp_cpu_on(u_register_t mpidr);
void sp_cpu_off(u_register_t mpidr);
void sp_disable_secondary_cpus(u_register_t primary_mpidr);
void sp_power_down(void);

uint16_t sp_read_soc_id(void);

void sp_console_setup(void);


#endif /* SP_PRIVATE_H */

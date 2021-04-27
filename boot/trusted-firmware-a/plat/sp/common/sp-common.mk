#
# Copyright (c) 2017-2019, ARM Limited and Contributors. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

include lib/xlat_tables_v2/xlat_tables.mk

SP_PLAT			:=	plat/sp

PLAT_INCLUDES		:=	-Iinclude/plat/arm/common/aarch64	\
				-I${SP_PLAT}/common/include		\
				-I${SP_PLAT}/${PLAT}/include

include lib/libfdt/libfdt.mk

PLAT_BL_COMMON_SOURCES	:= \
				${XLAT_TABLES_LIB_SRCS}			\
				plat/common/aarch64/crash_console_helpers.S \
				${SP_PLAT}/common/sp_console.S		\
				${SP_PLAT}/common/sp_console_setup.c	\
				${SP_PLAT}/common/plat_helpers.S	\
				${SP_PLAT}/common/sp_common.c

BL31_SOURCES		+=	\
				drivers/arm/gic/common/gic_common.c	\
				drivers/arm/gic/v2/gicv2_helpers.c	\
				drivers/arm/gic/v2/gicv2_main.c		\
				drivers/delay_timer/delay_timer.c	\
				drivers/delay_timer/generic_delay_timer.c \
				lib/cpus/${ARCH}/cortex_a55.S		\
				plat/common/plat_gicv2.c		\
				plat/common/plat_psci_common.c		\
				${SP_PLAT}/common/sp_bl31_setup.c	\
				${SP_PLAT}/common/sp_cpu_ops.c		\
				${SP_PLAT}/common/sp_topology.c

# Have core0~3
COLD_BOOT_SINGLE_CPU		:=	0

# Do not enable SPE (not supported on ARM v8.0).
ENABLE_SPE_FOR_LOWER_ELS	:=	0

# Do not enable SVE (not supported on ARM v8.0).
ENABLE_SVE_FOR_NS		:=	0

# Enable workarounds for Cortex-A55 errata
# See lib/cpus/cpu-ops.mk

# The reset vector can be changed for each CPU.
PROGRAMMABLE_RESET_ADDRESS	:=	0

# Allow mapping read-only data as execute-never.
SEPARATE_CODE_AND_RODATA	:=	1

# Put NOBITS memory in a separate region
SEPARATE_NOBITS_REGION		:=	0

# BL31 gets loaded alongside BL33 (U-Boot) by xBoot
RESET_TO_BL31			:=	1

# This platform is single-cluster and does not require coherency setup.
WARMBOOT_ENABLE_DCACHE_EARLY	:=	1


####################3333
# CA55

# System coherency is managed in hardware
HW_ASSISTED_COHERENCY	:=	1

# When building for systems with hardware-assisted coherency, there's no need to
# use USE_COHERENT_MEM. Require that USE_COHERENT_MEM must be set to 0 too.
USE_COHERENT_MEM	:=	0

# Q642 CA55 : r2p0
ERRATA_A55_1530923	?=	1

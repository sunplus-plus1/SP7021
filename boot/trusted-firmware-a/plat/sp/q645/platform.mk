#
# Copyright (c) 2017-2019, ARM Limited and Contributors. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

# The differences between the platform are covered by the include files.
include plat/sp/common/sp-common.mk

BL31_SOURCES += plat/sp/q645/sp_helpers.S
BL31_SOURCES += plat/sp/q645/sp_pm.c

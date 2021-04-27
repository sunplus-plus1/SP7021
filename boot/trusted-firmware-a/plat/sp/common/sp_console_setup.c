/*
 * Copyright (c) 2019-2020, Socionext Inc. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>

#include <drivers/console.h>
#include <errno.h>
#include <lib/mmio.h>
#include <plat/common/platform.h>

#include <sp_def.h>
#include <sp_uart.h>

/* These callbacks are implemented in assembly to use crash_console_helpers.S */
int sp_console_putc(int character, struct console *console);
int sp_console_getc(struct console *console);
void sp_console_flush(struct console *console);

static console_t sp_console = {
	.flags = CONSOLE_FLAG_BOOT |
		 CONSOLE_FLAG_RUNTIME |
		 CONSOLE_FLAG_CRASH,
	.putc = sp_console_putc,
	.getc = sp_console_getc,
	.flush = sp_console_flush,
};

void sp_uart_init(unsigned long base, unsigned int src_clk_in, unsigned int baud)
{
	/* this uart is likely shared -- don't change its baud */
#if 0
	mmio_write_32(base + SP_UA_DIVL, SP_UART_BAUD_DIV_L(src_clk_in, baud));
	mmio_write_32(base + SP_UA_DIVH, SP_UART_BAUD_DIV_H(src_clk_in, baud));
#endif
}

void sp_console_setup(void)
{
	sp_console.base = SP_UART0_BASE;

	sp_uart_init(sp_console.base, SP_UART0_CLK_IN_HZ, SP_UART0_BAUDRATE);

	console_register(&sp_console);
}

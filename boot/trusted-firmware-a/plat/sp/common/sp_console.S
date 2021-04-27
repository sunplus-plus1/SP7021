/*
 * Copyright (c) 2017-2019, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <asm_macros.S>
#include <drivers/console.h>

#include <sp_uart.h>


/*
 * In: w0 - character to be printed
 *     x1 - pointer to console structure
 * Out: return the character written (always succeeds)
 * Clobber: x2
 */
	.globl	sp_console_putc
func sp_console_putc
	ldr	x1, [x1, #CONSOLE_T_BASE]

	/* Wait until tx fifo not full */
0:	ldr	w2, [x1, #SP_UA_LSR_OFF]
	tbz	w2, #SP_UART_LSR_TX_SHIFT, 0b

	str	w0, [x1, #SP_UA_DR_OFF]

	ret
endfunc sp_console_putc

/*
 * In: x0 - pointer to console structure
 * Out: return the character read, or ERROR_NO_PENDING_CHAR if no character
	is available
 * Clobber: x1
 */
	.globl	sp_console_getc
func sp_console_getc
	ldr	x0, [x0, #CONSOLE_T_BASE]

	ldr	w1, [x0, #SP_UA_LSR_OFF]
	tbz	w1, #SP_UART_LSR_RX_SHIFT, 0f

	ldr	w0, [x0, #SP_UA_DR_OFF]
	ret

0:	mov	w0, #ERROR_NO_PENDING_CHAR
	ret
endfunc sp_console_getc

/*
 * In: x0 - pointer to console structure
 * Out: return 0 (always succeeds)
 * Clobber: x1
 */
	.global sp_console_flush
func sp_console_flush
	ldr	x0, [x0, #CONSOLE_T_BASE]

	/* wait until the transmitter gets empty */
0:	ldr	w1, [x0, #SP_UA_LSR_OFF]
	tbz	w1, #SP_UART_LSR_TXE_SHIFT, 0b

	mov	w0, #0
	ret
endfunc sp_console_flush

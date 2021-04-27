/*
 * Copyright (c) 2017-2019, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SP_UART_H
#define SP_UART_H

#define SP_UA_DR_OFF   0x00
#define SP_UA_LSR_OFF  0x04
#define SP_UA_MSR_OFF  0x08
#define SP_UA_LCR_OFF  0x0c
#define SP_UA_MCR_OFF  0x10
#define SP_UA_DIVL_OFF 0x14
#define SP_UA_DIVH_OFF 0x18
#define SP_UA_ISC_OFF  0x1c
#define SP_UA_TXR_OFF  0x20
#define SP_UA_RXR_OFF  0x24
#define SP_UA_THR_OFF  0x28


/* LSR bit define */
#define SP_UART_LSR_TX_SHIFT       0
#define SP_UART_LSR_RX_SHIFT       1
#define SP_UART_LSR_TXE_SHIFT      6

/*
#define SP_UART_LSR_TX             (1 << SP_UART_LSR_TX_SHIFT)
#define SP_UART_LSR_RX             (1 << SP_UART_LSR_RX_SHIFT)
#define SP_UART_LSR_TXE            (1 << SP_UART_LSR_TXE_SHIFT)
*/

#define SP_UART_BAUD_DIV_H(baud, sclk)     ((((sclk) + ((baud) / 2)) / (baud)) >> 12)
#define SP_UART_BAUD_DIV_L(baud, sclk)     ((((((sclk) + ((baud) / 2)) / (baud)) & 0xf) << 12) | \
                                         ((((((sclk) + ((baud) / 2)) / (baud)) >> 4) & 0xff) - 1))


#if 0
struct uart_regs {
        unsigned int dr;  /* data register */
        unsigned int lsr; /* line status register */
        unsigned int msr; /* modem status register */
        unsigned int lcr; /* line control register */
        unsigned int mcr; /* modem control register */
        unsigned int div_l;
        unsigned int div_h;
        unsigned int isc; /* interrupt status/control */
        unsigned int txr; /* tx residue */
        unsigned int rxr; /* rx residue */
        unsigned int thr; /* rx threshold */
};

#define UART_RX_READY()        (UART_REG->lsr & UART_LSR_RX)
#define UART_TX_END()          (UART_REG->lsr & UART_LSR_TXE)
#define UART_TX_NOT_FULL()     (UART_REG->lsr & UART_LSR_TX)
#endif


#endif /* SP_UART_H */

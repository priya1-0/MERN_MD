
/* ************************************************************************* */
/*
 *	serial.c
 *
 *	(C) 1994 - 2006 VOCAL Technologies, Ltd.
 *
 *	ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *	VOCAL Technologies, Ltd.
 *	90A John Muir Drive.
 *	Buffalo, NY  14228
 *
 *	Product:	MODEM 101
 *
 *	Module:		SUPPORT
 *
 *	This file contains generic serial port buffering routines.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.4.4.2  2009/04/28 20:44:27  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#include "system/system.h"

#include "support/local.h"

#include "dteif/dteif.h"

#include "pump/pump.h"
#include "v24/v24.h"

/* ************************************************************************* */

#define UART_TX_BUF_SIZE	8192
#define UART_RX_BUF_SIZE	128
uint8 far uart_tx_buf[UART_TX_BUF_SIZE];
int uart_tx_char_count  = 0;
int uart_tx_read_index  = 0;
int uart_tx_write_index = 0;

uint8 far uart_rx_buf[UART_RX_BUF_SIZE];
int uart_rx_char_count  = 0;
int uart_rx_read_index  = 0;
int uart_rx_write_index = 0;

int console_tx_active = TRUE;

/* ************************************************************************* */
ENTRY void
support_serial_module_reset (void)
{
	sys_nested_interrupt_disable ();
	uart_tx_char_count = 0;
	uart_tx_read_index = 0;
	uart_tx_write_index = 0;

	uart_rx_char_count = 0;
	uart_rx_read_index = 0;
	uart_rx_write_index = 0;
	console_tx_active = FALSE;
	sys_nested_interrupt_restore ();
}

/* ************************************************************************* */

ENTRY uint16
sys_putc (char c)
{
	int ret = 0;
extern struct proc *csc_proc;
extern struct proc *csc_txproc;
	if (csc_proc) {
		return 1;
	}

	sys_nested_interrupt_disable ();

	if (uart_tx_char_count >= (UART_TX_BUF_SIZE -1)) {
		c = '^';
		if (uart_tx_write_index == 0) {
			uart_tx_buf[UART_TX_BUF_SIZE - 1] = c;
		} else {
			uart_tx_buf[uart_tx_write_index - 1] = c;
		}

		sys_nested_interrupt_restore ();
		return 1;
	}

	uart_tx_buf[uart_tx_write_index++] = c;
	if (uart_tx_write_index == UART_TX_BUF_SIZE) {
		uart_tx_write_index = 0;
	}
	uart_tx_char_count++;

	sys_nested_interrupt_restore ();
	return ret;
}

ENTRY int
sys_puts (const char *buf)
{
	int count;

	count = 0;
	while (*buf != 0) {
		if (sys_putc(*buf++)) break;
		count++;
	}

	if (*buf == 0) {
		return -1;
	}
	return count;
}

ENTRY int
sys_putb (const char *buf, int len)
{
	int count;

	count = 0;
	while (count < len) {
		if (sys_putc(*buf++)) break;
		count++;
	}

	if (count == len) {
		return -1;
	}
	return count;
}

/* ************************************************************************* */

ENTRY int
kbread (void)
{
	int c;

	while (uart_rx_char_count == 0) {
		pwait (keyboard);
	}

	sys_nested_interrupt_disable ();
	c =	uart_rx_buf[uart_rx_read_index++];
	if (uart_rx_read_index == UART_RX_BUF_SIZE) {
		uart_rx_read_index = 0;
	}
	uart_rx_char_count--;
	sys_nested_interrupt_restore ();
	return c;
}

/* ************************************************************************* */
/* INTERRUPT HANDLER - CALLED ONLY FROM INTERRUPT STATE */
/* when the uart receives a char this is called */

ENTRY void
serial_console_rx (uint16 du)
{
	int temp;
	sys_nested_interrupt_disable ();

	temp = uart_rx_write_index;
	uart_rx_buf[temp] = du;

	temp++;
	if (temp >= UART_RX_BUF_SIZE) {
		temp = 0;
	}
	uart_rx_write_index = temp;
	uart_rx_char_count++;

	nested_interrupt_increment();
	psignal (keyboard, 1);
	nested_interrupt_decrement();
	sys_nested_interrupt_restore ();
}

/* ************************************************************************* */
/* INTERRUPT HANDLER - CALLED ONLY FROM INTERRUPT STATE */
/* the uart will call this looking for available chars to send */

ENTRY uint16
serial_console_tx (void)
{
	uint8 c;
	int temp;

	sys_nested_interrupt_disable ();

	if (uart_tx_char_count == 0) {
		sys_nested_interrupt_restore ();
		return V24_DU__NO_DATA_AVAILABLE;
	}

	temp = uart_tx_read_index;
	c = uart_tx_buf[temp];
	temp++;
	if (temp >= UART_TX_BUF_SIZE) {
		temp = 0;
	}
	uart_tx_read_index = temp;

	uart_tx_char_count--;
	if (uart_tx_char_count == 0) {
		console_tx_active = FALSE;
	}

	sys_nested_interrupt_restore ();
	return c;
}

ENTRY uint16
console_tx_pending (void)
{
	if (uart_tx_char_count == 0) {
		return V24_DU__NO_DATA_AVAILABLE;
	}

	return 0;
}

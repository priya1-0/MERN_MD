
/* ************************************************************************* */
/*
 *	pump.h
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
 *	Module:		PUMP
 *
 *	This file contains the public declations/definitions for the PUMP module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:42:19  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _PUMP_PUMP_H
#define _PUMP_PUMP_H

/* ************************************************************************* */

#define INT_STATE_TX_DATA					0
#define INT_STATE_TX_DATA_WITH_CONTROL_FLAG	1
#define INT_STATE_TX_CONTROL				2
#define INT_STATE_RX_CONTROL_WAIT_2			3
#define INT_STATE_RX_CONTROL_WAIT			4
#define INT_STATE_RX_CONTROL				5
#define INT_STATE_RX_READ					6

/* ************************************************************************* */

#define V54_SYNC_PAT_LENGTH	0x00C0

/* ************************************************************************* */

/* ************************************************************************* */
/*
 *	Entry Routine:	execute_thread
 *
 *	This inline function allows for high speed thread execution in both
 *	fgmain and v34 tx parser preload.
 *
 */

INLINE void
execute_thread (int block)
{
	thread_routine_t *func;
	func = &(fg_thread_table [fg_thread_offsets[block]]);
	while(*func != NULL) {
		(*func)();
		func++;
	}
}

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Global Routines: */

/* cleanup.c */
void cleanup (void);
void cleanup_modulation (void);

/* fgmain.c */
sint15 fg_process_sample(sint15 rx_data);
uint16 fg_process (void);

/* hwinit.c */
void hardware_initialization (void);

/* init.c */
void pump_module_reset (void);
void pump_startup (void);

/* interrpt.c */
void hardware_interrupt_mask_set (uint32 mask);
void hardware_interrupt_mask_clear (uint32 mask);
void nested_interrupt_forced_enable (void);
void nested_interrupt_restore (void);
void nested_interrupt_disable (void);
void nested_interrupt_increment(void);
void nested_interrupt_decrement(void);
uint16 nested_interrupt_read_depth (void);
void nested_interrupt_force_depth (uint16 depth);

/* mgmain.c */
void reset_mg_processing (void);
void mg_process (void);
void bg_process (void);

/* ti55xdrv.c */
void processor_initialization (void);
void codec_hardware_initialization (void);
void hardware_off_hook (void);
void hardware_on_hook (void);
int hardware_ringing (void);
void hardware_host_interrupt_set (void);
uint16 codec_process_control_word (uint16 control);
uint16 hardware_gpiodat0_write (uint16 mask, uint16 pattern);
uint16 hardware_gpiodat0_read ();
uint16 hardware_gpiodir0_write (uint16 mask, uint16 pattern);
uint16 hardware_gpiodir0_read ();
uint16 hardware_gpiodat1_write (uint16 mask, uint16 pattern);
uint16 hardware_gpiodir1_write (uint16 mask, uint16 pattern);
uint16 hardware_gpiodat1_read ();
uint16 hardware_gpiodir1_read ();
uint16 hardware_gpiodat2_write (uint16 mask, uint16 pattern);
uint16 hardware_gpiodir2_write (uint16 mask, uint16 pattern);
uint16 hardware_gpiodir2_read ();
uint16 hardware_gpiodat2_read ();
uint16 hardware_pgpiodat0_write (uint16 mask, uint16 pattern);
uint16 hardware_pgpiodat0_read ();
uint16 hardware_pgpiodir0_write (uint16 mask, uint16 pattern);
uint16 hardware_pgpiodir0_read ();
uint16 hardware_pgpiodat1_write (uint16 mask, uint16 pattern);
uint16 hardware_pgpiodat1_read ();
uint16 hardware_pgpiodir1_write (uint16 mask, uint16 pattern);
uint16 hardware_pgpiodir1_read ();
uint16 hardware_pgpiodat2_write (uint16 mask, uint16 pattern);
uint16 hardware_pgpiodat2_read ();
uint16 hardware_pgpiodir2_write (uint16 mask, uint16 pattern);
uint16 hardware_pgpiodir2_read ();

/* tiint.c */
void sport_tx_interrupt(void);
void sport_rx_interrupt(void);

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _PUMP_PUMP_H */

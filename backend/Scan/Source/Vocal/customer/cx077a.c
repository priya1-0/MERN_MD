
/* ************************************************************************* */
/*
 *	cx077a.c
 *
 *	(C) 2003 - 2006 VOCAL Technologies, Ltd.
 *
 *	ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *	VOCAL Technologies, Ltd.
 *
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.8  2010/02/17 23:16:48  heiand1
 *	Revision History:	SCR 186226. Add nwm_Get_Modem_Response() for network debugging.
 *	Revision History:	
 *	Revision History:	Revision 1.1.24.7  2010/02/17 21:27:54  zhangn1
 *	Revision History:	SCR #186864. Prevent system lock-up
 *	Revision History:	
 *	Revision History:	Revision 1.1.24.6  2010/02/17 21:16:03  zhangn1
 *	Revision History:	SCR #186863. Implement blind dialing
 *	Revision History:	
 *	Revision History:	Revision 1.1.24.5  2010/02/17 00:14:32  heiand1
 *	Revision History:	SCR 186226. Chap Login and Network initialization Timing.
 *	Revision History:	
 *	Revision History:	Revision 1.1.24.4  2010/02/16 22:11:21  zhangn1
 *	Revision History:	SCR #186247. Incorporate South Africa Tx Tone
 *	Revision History:	
 *	Revision History:	Revision 1.1.24.3  2010/02/16 21:13:34  heiand1
 *	Revision History:	SCR 182239. Increase network stack buffer size to 15.
 *	Revision History:	
 *	Revision History:	Revision 1.1.24.2  2009/04/28 19:09:22  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *	Revision History:	Revision 1.1  2004/04/21 15:17:38  shermt1
 *	Revision History:	SCR #82010:
 *	Revision History:	Added Vocal Source code and build process
 *	Revision History:
 *
 */
/* ************************************************************************* */

#include "system/system.h"
#include "v24/v24.h"
#include "dteif/dteifd.h"
#include "dteif/dteif.h"
#include "mdm/mdm.h"
#include "v24/locald.h"
#include "include/pump.h"
#include "pump/pump.h"

#define _CSL_TIME
#define _CSL_RTC_DATA_H_

#include "csl.h"
#include "csl_mcbsp.h"
#include <std.h>
#include <clk.h>
#include <hwi.h>
#include <mem.h>

#include "system/system.h"
#include "lansend/global.h"

#include "net/net.h"
#include "sys/sys.h"
#include "dev/dev.h"
#include "dev/devmdm.h"

#include "ip/ip.h"

#include "lansend/lansend.h"

#include "wan/wan.h"
#include "utils/utils.h"

#include "customer/local.h"
#ifdef DSP_2490
#include "../bsm/bsm_DAA.h"
#else /* DSP_2490 */
#include "customer/cx077b.h"
#endif /* DSP_2490 */
#include "include/callprog.h"
#include "include/silabs.h"
#include "csc/csc.h"
#include "csc/dte.h"

#include "../bsm/bsm_SerialPort.h"

#pragma DATA_SECTION(data_store,".vocal_data_store");
uint16 data_store [0x4800];

/* the following externs are for symbols defined by the linker */
extern const unsigned long isr_code_run_addr;
extern const unsigned long isr_code_load_addr;
extern const unsigned long isr_code_size;

extern const unsigned long trellis_code_run_addr;
extern const unsigned long trellis_code_load_addr;
extern const unsigned long trellis_code_size;

extern const unsigned long vocal_uninit_int_load_start;
extern const unsigned long vocal_uninit_int_size;

extern const unsigned long vocal_const_int_load_start;
extern const unsigned long vocal_const_int_run_start;
extern const unsigned long vocal_const_int_size;

/* global variables */
int mdm_cancel_command;
int network_process_return = MDM_ERRORCODE__NO_ERROR;

/* Flag to enable network enable */
int parm__network_debug_enable = 0;

volatile int testGlobal;

/* local variables */

#define MODEM_CONNECTED() (csc_mode == CSC_MODE__DATA)

/******************************************************************************/
/* Local functions */
/******************************************************************************/
/* ************************************************************************* */
/*
 *	Module Routine: check_for_timeout
 *
 *	Parameters:
 *
 *	Returns:
 *		TRUE - timeout occured
 *		FALSE - not timeout
 *
 */
static void timeout_init(unsigned long * lastltime)
{
	*lastltime = CLK_getltime();
}

static int timeout_check(unsigned long * lastltime, unsigned int * timer, unsigned int timeout)
{
	unsigned long ltime = CLK_getltime();
	/* increment our local timer if necessary */
	if ( ltime != *lastltime ) {
		if ( ltime < *lastltime ) {
			/* timer wrapped */
			*timer += 0xffffffffUL - *lastltime + 1;
			*timer += ltime;
		}
		else {
			*timer += ltime - *lastltime;
		}
		*lastltime = ltime;
	}
	/* check for timeout */
	if ( *timer >= timeout )
		return TRUE;
	else
		return FALSE;
}

void wait (unsigned int nwaitms)
{
	unsigned long lastt;
	unsigned int timer = 0;
	timeout_init(&lastt);
	while (!timeout_check(&lastt,&timer,nwaitms));
}

static void load_data (void)
{
	/* move data from External to DARAM */
	/* mdm_Store_Data (below) fills the data_store initially */
	memcpy(
	   (void *)((unsigned long)&vocal_const_int_run_start / 2),
	   (void *)((unsigned long)&vocal_const_int_load_start / 2),
	   (unsigned int)((unsigned long)&vocal_const_int_size / 2)
	);

	/* Copy the DAA isr code into DARAM, convert addresses from byte to word */
	memcpy((void *)((unsigned long)&isr_code_run_addr / 2),
		   (void *)((unsigned long)&isr_code_load_addr / 2),
		   (unsigned int)((unsigned long)&isr_code_size / 2));

	/* Copy the trellis code into DARAM, convert addresses from byte to word */
	memcpy((void *)((unsigned long)&trellis_code_run_addr / 2),
		   (void *)((unsigned long)&trellis_code_load_addr / 2),
		   (unsigned int)((unsigned long)&trellis_code_size / 2));
}

/******************************************************************************/
/******************************************************************************/
/* Modem API */
/******************************************************************************/
/******************************************************************************/

/* ************************************************************************* */
/*
 *	Module Routine: mdm_Send_Control_String
 *
 *	This routine sends a control string to the modem and returns the response.
 *
 *	Parameters:
 *		char * command - pointer to AT command as a null terminated string
 *
 *	Returns:
 *		int - number of character returned in respbuf
 *
 *  Notes:
 *		function blocks until a complete reponse string is available
 *		Must be called from IDL function
 */
ENTRY int
mdm_Send_Control_String (char* command, char* respbuf, int buflen)
{
	char * pCmd = command;
	unsigned int chr;
	int len = 0;
	long timeout = 0;
	int found_char = 0;
	int immediate_return = FALSE;
	int i;
	int retry = 1;

	mdm_cancel_command = FALSE;

	/* flush the response buffer */
	for ( i = 0 ; i < 20 ; i++ ) {
		while ( dteif_tx() != V24_DU__NO_DATA_AVAILABLE );
		wait(2);
	}

	if (strstr(pCmd,"+++") != NULL) {
		immediate_return = TRUE;
	}

	/* send the control string */
	while (*pCmd != 0) {
		sys_putc(*pCmd);
		dteif_rx(*pCmd++);
		wait(2);
	}

	if (buflen == 0 || respbuf == NULL)
		return 0;

	pCmd = respbuf;
	*pCmd = 0;

	if (immediate_return) {
		wait(100);
		for ( i = 0 ; i < 20 ; i++ ) {
			while ( dteif_tx() != V24_DU__NO_DATA_AVAILABLE );
			wait(2);
		}
		strcpy(pCmd,"\r\nOK\r\n");
		return 6;
	}

carrier_jump:
	timeout = 100000;

	/* Wait for command response */
	while ( timeout-- ) {
		chr = dteif_tx();
		if (chr == V24_DU__NO_DATA_AVAILABLE ) {
			wait(5);
			if (mdm_cancel_command)
				break;
			continue;
		}
		timeout = 500;
		found_char = 1;
		sys_putc(chr);

		*pCmd++ = chr;
		*pCmd = 0;
		len++;
		if (len == (buflen - 1)) {
			break;
		}

		if (mdm_cancel_command) {
			break;
		}
	}
	if(!found_char) {
		sys_putc('$');
		sys_putc('*');
		sys_putc('*');
		sys_putc('*');
		sys_putc('*');
		sys_putc('*');
		sys_putc('$');
	}

	if (retry && (strstr(respbuf,"CARRIER ") != NULL)){
		if (strstr(respbuf,"CONNECT") == NULL) {
			retry = 0;
			sys_putc('&');
			sys_putc('*');
			sys_putc('*');
			sys_putc('&');
			goto carrier_jump;
		}
	}

	return len;
}

/* ************************************************************************* */
/*
 *	Module Routine: mdm_Init
 *
 *	This routine initializes the modem.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		One of MDM_ERRORCODE__xxx.
 */

ENTRY int
mdm_Init (void)
{
	extern int network_task_state;
	int errorcode, i, port;
	int daa_init_count;

	MCBSP_Config daa_config = {
		0x0000, /* spcr1 */
		0x0200, /* spcr2 */
		0x0040, /* rcr1 */
		0x0045, /* rcr2 */
		0x0040, /* xcr1 */
		0x0045, /* xcr2 */
		0x0000, /* srgr1 */
		0x2000, /* srgr2 */
		0x0000, /* mcr1 */
		0x0000, /* mcr2 */
		0x0080, /* pcr */
		0x0000, /* rcera */
		0x0000, /* rcerb */
		0x0000, /* rcerc */
		0x0000, /* rcerd */
		0x0000, /* rcere */
		0x0000, /* rcerf */
		0x0000, /* rcerg */
		0x0000, /* rcerh */
		0x0000, /* xcera */
		0x0000, /* xcerb */
		0x0000, /* xcerc */
		0x0000, /* xcerd */
		0x0000, /* xcere */
		0x0000, /* xcerf */
		0x0000, /* xcerg */
		0x0000  /* xcerh */
	};

	sys_nested_interrupt_disable();

	/* Plexus had already setup the DSP */
	/* Plexus has already setup the McBSP (hDAA_mcbsp) */

	mdm_cancel_command = FALSE;

	load_data();

	/* Clear host variables */
	clear_structures();

	/* Initialize modules */
	/* Clear the background run active flag */
	v34b_mg_run_active_flag = 0;
	errorcode = application_startup ();

	// Turn off reporting events
    parm__report_event_mask = 0;

	/* Mask the LSB of tx samples */
	codec_tx_mask = 0xffff;
	interrupt_sample_count = 1;
	sample_overflow_count = 0;
	codec_int_state = INT_STATE_TX_DATA;
	/*
	 *	Configure McBSP for CODEC
	 */
	port = MCBSP_getPort(hDAA_mcbsp);
	MCBSP_close(hDAA_mcbsp);
	hDAA_mcbsp = MCBSP_open(port, MCBSP_OPEN_RESET);
	MCBSP_config(hDAA_mcbsp, &daa_config);

	MCBSP_write16(hDAA_mcbsp,0);

	/*
	 *	Configure the registers internal to the codec by prefilling sample buffer
	 *
	 */
	/* initialization for CX077 TI 5501/5502 board w/ SiLabs 3056 CODEC */
	daa_init_count = 0;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x1;
	sample_buffer[daa_init_count++] = (DAA_Control1 << 8) | 0x80;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x1;
	sample_buffer[daa_init_count++] = (DAA_PLLdivN << 8) | 0;
	sample_buffer[daa_init_count++] = 0x1;
	sample_buffer[daa_init_count++] = (DAA_PLLdivM << 8) | 7;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x1;
	sample_buffer[daa_init_count++] = (DAA_SampleRate << 8) | 1;
	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x1;
	sample_buffer[daa_init_count++] = (DAA_DAAControl2 << 8) | 0;

	sample_buffer[daa_init_count++] = 0x1;
	sample_buffer[daa_init_count++] = (DAA_DCtermCtl << 8) | 0xc0;

	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x1;
	sample_buffer[daa_init_count++] = (DAA_DAAControl1 << 8) | 2;

	sample_buffer[daa_init_count++] = 0x0;
	sample_buffer[daa_init_count++] = 0x1;
	sample_buffer[daa_init_count++] = (DAA_Control1 << 8) | 0x18;

	sample_buffer[daa_init_count++] = 0x1;
	sample_buffer[daa_init_count++] = (DAA_CPRxAtten << 8) | 0xff;
	sample_buffer[daa_init_count++] = 0x1;
	sample_buffer[daa_init_count++] = (DAA_CPTxAtten << 8) | 0xff;

	if (daa_init_count > SAMPLE_BUFFER_SIZE) {
		while(1);
	}

	/* Initialize the heap */
	{
		extern unsigned int network_heap;
		volatile Ptr base = MEM_memtab[network_heap].base;
		volatile Uns length;
		struct MEM_Stat mem;
		MEM_stat(network_heap,&mem);
		length = mem.size;
		MEM_redefine(network_heap,base,length);
	}

	MCBSP_start(hDAA_mcbsp, MCBSP_XMIT_START|MCBSP_RCV_START, MCBSP_SRGR_DEFAULT_DELAY);

	sys_nested_interrupt_restore();

	if (errorcode != MDM_ERRORCODE__NO_ERROR) {
		return errorcode;
	}

	/* enable MCBSP Tx & Rx interrupts */
	switch(MCBSP_getPort(hDAA_mcbsp))
	{
	case 0:
		IRQ_enable(IRQ_EVT_RINT0);
		IRQ_enable(IRQ_EVT_XINT0);
		break;
	case 1:
		IRQ_enable(IRQ_EVT_RINT1);
		IRQ_enable(IRQ_EVT_XINT1);
		break;
	case 2:
		IRQ_enable(IRQ_EVT_RINT2);
		IRQ_enable(IRQ_EVT_XINT2);
		break;
	}

	/* Wait for indication that foreground is running and DAA is okay */
	/* check that foreground interrupt pointer has consumed DAA init */
	for ( i = 1000 ; i > 0 ; i-- ) {
		wait(5);
		if (codec_tx_mask == 0xfffe)
			break;
	}

	if ( i == 0 ) {
		return MDM_ERRORCODE__HARDWARE_TIMEOUT;
	}
	wait(2000);

	{
		extern void SYS_sprintf(char *buf, char * fmt, ...);
		static int count = 0;
		char cmdstr[80];
		SYS_sprintf(cmdstr,"\r\nRUN # %d\r\n",count++);
		sys_puts(cmdstr);

	}

	//Hold off negotiating for better rate and let PPP connection complete	
	V34S_RUN_HOLDOFF_TIME =60;	

	/* Initialize the network kernel and stack */
	errorcode = dspbios_network_start();
	if (errorcode != MDM_ERRORCODE__NO_ERROR) {
		return errorcode;
	}
	/* Wait for indication that the network kernel is running */
	for ( i = 100 ; i > 0 ; i-- ) {
		wait(10);
		if (network_task_state != 0)
			break;
	}

	if ( i == 0 ) {
		return MDM_ERRORCODE__NETWORK_INIT_FAILED;
	}

    /* Configure flags so that printf() function calls are disabled */ 
    parm__net_debug_level_omc = 0;
    print_disable = 1;
        
	return errorcode;
}

/* ************************************************************************* */
/*
 *	Module Routine: mdm_Shut_Off
 *
 *	This routine shuts off the DAA and deinitializes the modem.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 */

ENTRY void
mdm_Shut_Off (void)
{
	mdm_cancel_command = TRUE;

	/* Disable the DAA interrupts */
	switch (MCBSP_getPort(hDAA_mcbsp)) {
	case 0:
		IRQ_disable(IRQ_EVT_RINT0);
		IRQ_disable(IRQ_EVT_XINT0);
		break;
	case 1:
		IRQ_disable(IRQ_EVT_RINT1);
		IRQ_disable(IRQ_EVT_XINT1);
		break;
	case 2:
		IRQ_disable(IRQ_EVT_RINT2);
		IRQ_disable(IRQ_EVT_XINT2);
		break;
	}


	network_process_return = MDM_ERRORCODE__SHUTDOWN;
	dspbios_network_shutdown();

	application_shutdown();

	/*  Power down line-side device */
	while ( MCBSP_xrdy(hDAA_mcbsp) == 0 );
	MCBSP_write16(hDAA_mcbsp,0x01);
	while ( MCBSP_xrdy(hDAA_mcbsp) == 0 );
	MCBSP_write16(hDAA_mcbsp,(DAA_DAAControl2 << 8) | 0x10);

	/* Set PLL2 to zero */
	while ( MCBSP_xrdy(hDAA_mcbsp) == 0 );
	MCBSP_write16(hDAA_mcbsp,0x01);
	while ( MCBSP_xrdy(hDAA_mcbsp) == 0 );
	MCBSP_write16(hDAA_mcbsp,(DAA_PLLdivM << 8) | 0x00);

	/* Power down the system-side device. */
	/* A pulse on /RESET is required to restore normal operation. */
	while ( MCBSP_xrdy(hDAA_mcbsp) == 0 );
	MCBSP_write16(hDAA_mcbsp,0x01);
	while ( MCBSP_xrdy(hDAA_mcbsp) == 0 );
	MCBSP_write16(hDAA_mcbsp,(DAA_DAAControl2 << 8) | 0x18);

	/* Initialize and clear heap to prevent any stale pointers from being
	   inadvertantly used, (For example, if printf() is used by the main application,
	   the stdout file handle would still contain a valid pointer, if not cleared here.)*/
	/* Initialize the heap */
	{
		extern unsigned int network_heap;
		volatile Ptr base = MEM_memtab[network_heap].base;
		volatile Uns length;
		struct MEM_Stat mem;
		MEM_stat(network_heap,&mem);
		length = mem.size;
		MEM_redefine(network_heap,base,length);
	}
}

/* ************************************************************************* */
/*
 *	Module Routine: mdm_Get_Connect_Speed
 *
 *	This routine returns the connect speed if modem is connected.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		long integer connect speed
 *
 *	Notes:
 *		A call to this function is valid only after a connect response(from AT
 *		command) and before hangup or disconnect.
 */

long mdm_Get_Connect_Speed(void)
{
	if(!MODEM_CONNECTED()) {
		return 0L;
	}

	switch ( stat__dm_tx_data_rate & 0x00ff ) {
	case 0x00:
		return 75L;
	case 0x01:
		return 300L;
	case 0x02:
		return 600L;
	case 0x03:
		return 1200L;
	case 0x04:
		return 2400L;
	case 0x05:
		return 4800L;
	case 0x06:
		return 7200L;
	case 0x07:
		return 9600L;
	case 0x08:
		return 12000L;
	case 0x09:
		return 14400L;
	case 0x0a:
		return 16800L;
	case 0x0b:
		return 19200L;
	case 0x0c:
		return 21600L;
	case 0x0d:
		return 24000L;
	case 0x0e:
		return 26400L;
	case 0x0f:
		return 28800L;
	case 0x10:
		return 31200L;
	case 0x11:
		return 33600L;
	}
	return 0L;
}

/* ************************************************************************* */
/*
 *	Module Routine: mdm_Check_Dialtone
 *
 *	This routine check if there is a dial tone.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		0 - no dial tone found.
 *		1 - dial tone found
 *
 *	Notes:
 *		You must wait 1 second after going off hook to check for initial
 *		dialtone and 3 seconds after dialing for second dialtone.
 */

int mdm_Check_Dialtone(void)
{
	access_omc_pump_dm_wr_direct (parm__call_progress_cadence_detect_mask, parm__itel_cp_predial_mask);
	set_event (EVENT__DETECT_CALL_PROGRESS);
	wait(3000);

	if (stat__call_progress_cadence_detect_mask & ( CP_STATUS__INITIAL_DIALTONE |
											CP_STATUS__SECOND_DIALTONE |
											CP_STATUS__OTHER_DIALTONE |
											CP_STATUS__BROKEN_DIALTONE) ) {
		return TRUE;
	}
	return FALSE;
}

/******************************************************************************/
/******************************************************************************/
/* Terminal Mode API */
/******************************************************************************/
/******************************************************************************/

/* ************************************************************************* */
/*
 *	Module Routine: mdm_Init_Term_Mode
 *
 *	This routine switches modem to terminal mode for scripted login.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 */

void mdm_Init_Term_Mode(void)
{
	mdm_Purge_Input_Buffer();
}

/* ************************************************************************* */
/*
 *	Module Routine: mdm_Get_Char
 *
 *	This routine gets a character from the modem buffer.
 *
 *	Parameters:
 *		int max - size of buffer passed
 *		char * buffer - pointer to buffer to receive characters
 *
 *	Returns:
 *		int - number of characters placed in buffer
 *
 */

int mdm_Get_Char(int max, char* buffer)
{
	uint16 i;
	uint16 chr;

	for ( i = 0 ; i < max ; i++ ) {
		chr = dteif_tx();
		if ( chr != V24_DU__NO_DATA_AVAILABLE ) {
			chr &= 0x00ff;
			buffer[i] = chr;
		}
		else {
			break;
		}
	}
	return i;
}

/* ************************************************************************* */
/*
 *	Module Routine: mdm_Purge_Input_Buffer
 *
 *	This routine clears the input buffer.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 *
 */

ENTRY void
mdm_Purge_Input_Buffer (void)
{
	while ( dteif_tx() != V24_DU__NO_DATA_AVAILABLE );
}

/* ************************************************************************* */
/*
 *	Module Routine: mdm_Send_String
 *
 *	This routine sends a string via terminal mode.
 *
 *	Parameters:
 *		int length - length of string to send
 *		char * buffer - pointer to buffer containing string to send
 *
 *	Returns:
 *		int - number of characters sent
 *
 *	Notes:
 *		String to send should be terminated with a carriage return.
 */

ENTRY int
mdm_Send_String (int length, char* buffer)
{
	uint16 i;
	for ( i = 0 ; i < length ;) {
		if(!MODEM_CONNECTED()) {
			break;
		}
		if (dte_tx_cnt < DTE_TX_BUFFER_SIZE) {
			dteif_rx(buffer[i++]);
		}
		else {
			wait(10);
		}
	}
	return i;
}

/* ************************************************************************* */
/* ************************************************************************* */
/* Network API */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/*
 *	LocalRoutine: network_send_cmd
 *
 *
 *	Returns:
 *		int -
 *
 *	Notes:
 *		Blocking, call from IDL function
 */

MODULE void
network_send_cmd (int iarge, void * cmdstr, void * p2)
{
	fflush(stdout);
	cmdparse (Cmds, cmdstr, NULL);
	fflush(stdout);
}

MODULE void
network_send_cmd_proc (int iarge, void * cmdstr, void * p2)
{
	fflush(stdout);
	cmdparse (Cmds, cmdstr, NULL);
	fflush(stdout);

	network_process_return = MDM_ERRORCODE__NO_ERROR;
}

ENTRY int
network_Send_Cmd (char * cmdstr)
{
	if (!dspbios_network_kernel_running()) {
		return MDM_ERRORCODE__NETWORK_NOT_STARTED;
	}

	while (network_process_return == 0xffff) {
		wait(10);
	}

	/* Start network process */
	network_process_return = 0xffff;
	dspbios_network_start_process(512,network_send_cmd_proc,0,cmdstr,NULL,FALSE);

	/* wait for process to complete */
	while (network_process_return == 0xffff) {
		wait(10);
	}

	return network_process_return;
}

/* ************************************************************************* */
/*
 *	Entry Routine: network_Init
 *
 *	This routine stops terminal mode and makes a network connection via PPP.
 *
 *	Parameters:
 *		int do_auth - if 1 username/password are used to authenticate
 *			via PAP/CHAP
 *		char * username - null terminated string containing username
 *		char * password - null terminated string containing password
 *
 *	Returns:
 *		int -
 *
 *	Notes:
 *		Blocking, call from IDL function
 */

ENTRY void
network_init_proc (int do_auth, void * username, void * password)
{
	char cmdstr[150];
#if 0
	/* Check memory usage */
	generic_sprintf(cmdstr,"mem s\r\n");
	network_send_cmd(0,cmdstr,NULL);
	pwait(NULL);
#endif

	/* attach mdm device */
	generic_sprintf(cmdstr,"device mdm0 attach mdm ppp\r\n");
	network_send_cmd(0,cmdstr,NULL);
	pwait(NULL);

   /* Setup PPP authentication */
	if (do_auth) {
		generic_sprintf(cmdstr,"ppp mdm0 pap user %s %s\r\n",username,password);
		network_send_cmd(0,cmdstr,NULL);
		pwait(NULL);
		generic_sprintf(cmdstr,"ppp mdm0 chap user %s %s\r\n",username,password);
		network_send_cmd(0,cmdstr,NULL);
		pwait(NULL);
	}

	if (parm__network_debug_enable) {
		generic_sprintf(cmdstr,"trace mdm0 in\r\n");
		network_send_cmd(0,cmdstr,NULL);
		pwait(NULL);

		generic_sprintf(cmdstr,"trace mdm0 out\r\n");
		network_send_cmd(0,cmdstr,NULL);
		pwait(NULL);

		generic_sprintf(cmdstr,"trace mdm0 hex\r\n");
		network_send_cmd(0,cmdstr,NULL);
		pwait(NULL);
	}

	/* add routes */
	generic_sprintf(cmdstr,"ip route add default mdm0\r\n");
	network_send_cmd(0,cmdstr,NULL);
	pwait(NULL);

	/* accept server assigned ip address */
	generic_sprintf(cmdstr,"ip address mdm0 on\r\n");
	network_send_cmd(0,cmdstr,NULL);
	pwait(NULL);

#ifndef DSP_2490
	/* set mss */
	generic_sprintf(cmdstr,"ip tcp mss 1400\r\n");
	network_send_cmd(0,cmdstr,NULL);
	pwait(NULL);

	/* set mtu */
	generic_sprintf(cmdstr,"device mdm0 mtu 1500\r\n");
	network_send_cmd(0,cmdstr,NULL);
	pwait(NULL);

	/* set window */
	generic_sprintf(cmdstr,"ip tcp window 5600\r\n");
	network_send_cmd(0,cmdstr,NULL);
	pwait(NULL);
#endif /* DSP_2490 */

	/* enable DNS */
	generic_sprintf(cmdstr,"ppp mdm0 ipcp local dns on\n");
	network_send_cmd(0,cmdstr,NULL);
	pwait(NULL);

	/* set modem output buffer size */
	generic_sprintf (cmdstr, "device mdm0 outbuf 15\n");
	network_send_cmd(0,cmdstr,NULL);
	pwait(NULL);

	/* set modem input buffer size */
	generic_sprintf (cmdstr, "device mdm0 inbuf 15\n");
	network_send_cmd(0,cmdstr,NULL);
	pwait(NULL);


	/* start PPP negotiation */
	generic_sprintf(cmdstr,"mdm mdm0 ioctl blind 1\r\n");
	network_send_cmd(0,cmdstr,NULL);
	pwait(NULL);

	network_process_return = MDM_ERRORCODE__NO_ERROR;
}

ENTRY int
network_Init (int do_auth, char* username, char* password)
{
	int i;

	if (!dspbios_network_kernel_running()) {
		return MDM_ERRORCODE__NETWORK_NOT_STARTED;
	}

	while (network_process_return == 0xffff) {
		wait(10);
	}

	/* Setup PPP authentication */
	network_process_return = 0xffff;

	dspbios_network_start_process(512,network_init_proc,do_auth,username,password,FALSE);

	/* wait for process to complete */
	while ((network_process_return == 0xffff) && MODEM_CONNECTED()) {
		wait(10);
	}

	if ( network_process_return != MDM_ERRORCODE__NO_ERROR ) {
		return network_process_return;
	}

	/* wait for PPP connection to complete */
	for ( i = 6000 ; i > 0 ; i-- ) {
		if (Mdm[0]) {
			if ( ((struct ppp_s *)(Mdm[0]->iface->pppedv))->fsm[IPcp].state == fsmOPENED ) {
				return MDM_ERRORCODE__NO_ERROR;
			}
		}
		if(!MODEM_CONNECTED()) {
			return MDM_ERRORCODE__SHUTDOWN;
		}
		wait(10);
	}

	return MDM_ERRORCODE__NETWORK_INIT_FAILED;
}

/* ************************************************************************* */
/*
 *	Module Routine: mdm_Get_PPP_Auth_Type
 *
 *	This routine returns the type of authentication that succeeded durring
 *		PPP negotiation.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		int - NET_PPP_AUTH_*
 *
 */

MODULE int
network_Get_PPP_Auth_Type (void)
{
	if (!dspbios_network_kernel_running()) {
		return MDM_ERRORCODE__NETWORK_NOT_STARTED;
	}

	if ( ((struct ppp_s *)(Mdm[0]->iface->pppedv))->fsm[IPcp].state == fsmOPENED ) {
		if ( ((struct ppp_s *)(Mdm[0]->iface->pppedv))->fsm[Pap].pdc != NULL )
			return NET_PPP_AUTH_PAP;
		if ( ((struct ppp_s *)(Mdm[0]->iface->pppedv))->fsm[CHap].pdc != NULL )
			return NET_PPP_AUTH_CHAP;
	}
	return NET_PPP_AUTH_NONE;
}

/* ************************************************************************* */
/*
 *	Entry Routine: http_Process_Request
 *
 *	This routine processes an HTTP request, found in http_request_data, and
 *		fills in the response field of http_request_data.
 *
 *	Parameters:
 *		http_request_data req_data - http request data structure
 *
 *	Returns:
 *		int - HTTP_STATUS_*
 *
 *	Notes:
 *		Blocking, must be called from IDL function
 */

ENTRY void
http_process (int iarg, void * p1, void * p2)
{
	network_process_return = http_process_request ((http_request_data *)p1);
}

int http_Process_Request (http_request_data * req_data) {
	if (!dspbios_network_kernel_running()) {
		return MDM_ERRORCODE__NETWORK_NOT_STARTED;
	}

	while ((network_process_return == 0xffff) && MODEM_CONNECTED()) {
		wait(10);
	}

	/* Setup http client process */
	network_process_return = 0xffff;

	dspbios_network_start_process(1024,http_process,0,(void*)req_data,NULL,FALSE);

	/* wait for process to complete */
	while ((network_process_return == 0xffff) && MODEM_CONNECTED()) {
		wait(10);
	}

	if (network_process_return == 0xffff) {
		printf("\r\ncsc_mode = %d\r\n",csc_mode);
	}
	return network_process_return;
}

/* ************************************************************************* */
/*
 *	Module Routine: speaker_monitor_on
 *
 *	This routine turns on the speaker.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 *
 */
ENTRY void
speaker_monitor_on (void)
{
	uint16 local_rx_gain = 0x40;
	uint16 local_tx_gain = 0x40;
	uint16 temp_uint16;
	switch(parm__spk_monitor_rx_gain) {
			case 0x0: /* OFF */
				local_rx_gain = 0x0;
				break;

			case 0x2000: /* LOW VOLUME */
				local_rx_gain = 0x40;
				break;

			case 0x4000: /* MED VOLUME */
				local_rx_gain = 0x7f;
				break;

			case 0x8000: /* HIGH VOLUME */
				local_rx_gain = 0xff;
				break;

			case 0x1000: /* LOWEST/DEFAULT VOLUME */
			default:
				local_rx_gain = 0x40;
				break;
			}

	switch(parm__spk_monitor_tx_gain) {

			case 0x0: /* OFF */
				local_tx_gain = 0x0;
				break;

			case 0x2000: /* LOW VOLUME */
				local_tx_gain = 0x40;
				break;

			case 0x4000: /* MED VOLUME */
				local_tx_gain = 0x7f;
				break;

			case 0x8000: /* HIGH VOLUME */
				local_tx_gain = 0xff;
				break;

			case 0x1000: /* LOWEST/DEFAULT VOLUME */
			default:
				local_tx_gain = 0x40;
				break;
	}

	codec_process_control_word((DAA_CPRxAtten << 8) | local_rx_gain);
	codec_process_control_word((DAA_CPTxAtten << 8) | local_tx_gain);

	/* ENABLE OUTPUT*/
	temp_uint16 = codec_process_control_word (0x8000 | (DAA_Control1 << 8));
	temp_uint16 &= ~0x08;
	temp_uint16 |=  0x08;
	codec_process_control_word ((DAA_Control1 << 8) | temp_uint16);

}

/* ************************************************************************* */
/*
 *	Entry Routine: speaker_monitor_off
 *
 *	This routine turns off the speaker.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 *
 */

ENTRY void
speaker_monitor_off (void)
{
	uint16 temp_uint16;

	/* NO VOLUME */
   temp_uint16 = codec_process_control_word (0x8000 | (DAA_Control1 << 8));
   temp_uint16 &= ~0x08;
   codec_process_control_word ((DAA_Control1 << 8) | temp_uint16);

}

/* ************************************************************************* */
/*
 *	Entry Routine:
 *
 *	This routine stores all data that is initialized in DARAM into a data store
 *		for later retrieval by mdm_Init
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 *
 */
ENTRY void
mdm_Store_Data (void)
{

	/* move data that is filled by cinit at startup from DARAM to External */
	/* load_data routine (above) moves in the other direction */

}

/* ************************************************************************* */
/*
 *	Module Routine: set_num_fg_states()
 *
 *	Sets the number of ForeGround processing states.
 *  Note: Setting this value to zero causes all modem events to be ignored
 *        (in particular retraining and carrier loss detection).
 *
 *	Parameters:
 *		(int): Desired value
 *
 *	Returns:
 *		<none>
 */

ENTRY void
set_num_fg_states (int desired)
{
	volatile int testLocal;
	testGlobal += 1;
	testLocal = testGlobal;
	number_fg_states = desired;
}

/* ************************************************************************* */
/*
 *	Module Routine: read_num_fg_states()
 *
 *	Reads the number of ForeGround processing states
 *
 *	Parameters:
 *		<none>
 *
 *	Returns:
 *		(int):  Current number_fg_states
 */
ENTRY int
read_num_fg_states (void)
{
	return number_fg_states;
}

/******************************************************************

FUNCTION: mdm_setModemDTMFStrength

DESCRIPTION: This function sets the DTMF signal strength. By default
             the values the modem code uses are low. This function
             overides the modem's configuration to increase the DTMF
             signal strength.
CONSTRAINT:  This function should be called AFTER all country code
             commands have taken place (AT*NCn where n is the
             country code). A subsequent country code assignment
             will nullify this setting.

ARGS:
	<none>

RETURNS:
    <none>
******************************************************************/
ENTRY void
mdm_setModemDTMFStrength (void)
{
     parm__itel_dtmf_low_tone_level  = 7;
     parm__itel_dtmf_high_tone_level = 4;

	/*
     * parm__hw_tx_gain_correction Gain Table
     *
    
    dBm    10^(dBm/20)   Corresponding Hex Setting
    ----   -----------   -------------------------
    -20    0.1            0199
    -19    0.112201845    01CB
    -18    0.125892541    0203
    -17    0.141253754    0242
    -16    0.158489319    0288
    -15    0.177827941    02d8
    -14    0.199526231    0331
    -13    0.223872114    0394
    -12    0.251188643    0404
    -11    0.281838293    0482
    -10    0.316227766    050F
    -9     0.354813389    05ad
    -8     0.398107171    065e
    -7     0.446683592    0725
    -6     0.501187234    0804
    -5     0.562341325    08FD
    -4     0.630957344    0A18
    -3     0.707945784    0B53
    -2     0.794328235    0CB5
    -1     0.891250938    0E42
     0     1.000000000    1000
     1     1.122018454    11f3
     2     1.258925412    1424
     3     1.412537545    1699
     4     1.584893192    195b
     5     1.77827941     1c72
     6     1.995262315    1fEC
     7     2.238          23CE
     8     2.511          282D
*/

    parm__hw_tx_gain_correction = 0x11F3;  // by default we add +1 db to the output

    /* override for south africa */
    if (parm__itel_country_code == 79)
    {
    	  // Increase gain by +7db, which means gain is actually set to 8db
        parm__hw_tx_gain_correction = 0x282D;  //add +7db to the default

        // Since the gain is increased by +7db, the dtmf tone level's
        // need to be reduced by 7db to keep their levels unaffected

        //These numbers are really the negative of the number its set to,
        // so 14 is really -14 db */
        parm__itel_dtmf_low_tone_level = 14;   //normally -7, subtract 7
        parm__itel_dtmf_high_tone_level = 11;  //normally -4, subtract 7
}

}
/******************************************************************

FUNCTION: mdm_setModemCadenceDialDetect

DESCRIPTION: This function overides the modem country code to support
             the detection of cadenced dialtones.
CONSTRAINT:  This function should be called AFTER all country code
             commands (AT*NCn where n is the country code). A
             subsequent country code assignment will nullify this
             setting.
NOTE:        Enabling this for some countries can cause problems, as
             an example the unit may detect a busy done as a
             dialtone because if the simularity between the busy tone
             and a cadenced dialtone.
ARGS:
	<none>

RETURNS:
    <none>
******************************************************************/
ENTRY void
mdm_setModemCadenceDialDetect (void)
{
	parm__itel_cp_predial_mask  |=  0x0004;
}

/******************************************************************

FUNCTION: mdm_setNetworkDebugEnable

DESCRIPTION: This function enables/disables network debug functionality.

			 If the parameter is enabled prior to network startup, network
             debug printing will start automatically. Please note that it
			 is disabled by default.

			 This function may be called dynamically.

Paramters:
	int mode - 1 enables network debug, 0 disables network debug

RETURNS:
    <none>
******************************************************************/
ENTRY void
mdm_setNetworkDebugEnable (int mode)
{
	if (mode != parm__network_debug_enable) {
		char cmdstr[150];

		parm__network_debug_enable = mode;

		if (!dspbios_network_kernel_running()) {
			return;
		}

		if (parm__network_debug_enable == FALSE) {
			generic_sprintf (cmdstr,"trace mdm0 off\r\n");
			network_send_cmd (0,cmdstr,NULL);
			pwait (NULL);
		}
		else {
			/* Display incoming packets */
			generic_sprintf(cmdstr,"trace mdm0 in\r\n");
			network_send_cmd(0,cmdstr,NULL);
			pwait(NULL);

			/* Display outgoing packets */
			generic_sprintf(cmdstr,"trace mdm0 out\r\n");
			network_send_cmd(0,cmdstr,NULL);
			pwait(NULL);

			/* Set packet data display mode to hexidecimal format */
			generic_sprintf(cmdstr,"trace mdm0 hex\r\n");
			network_send_cmd(0,cmdstr,NULL);
			pwait(NULL);
		}
	}
}

/* ************************************************************************* 
	Module Routine: get_disconnect_reason()

	Returns the modem disconnect reason

	Parameters:
		<none>

	Returns:
		(unit16):  Modem disconnect reason
**************************************************************************** */
ENTRY uint16
get_disconnect_reason(void)
{
	return stat__omc_disconnect_reason;
}

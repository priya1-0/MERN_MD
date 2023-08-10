 /*********************************************************************
 *          (C) COPYRIGHT TEXAS INSTRUMENTS, INC. 2000, 2001
 * FBTC55.c -- Main Loop and global utility funcs for
 *             55x FlashBurn FBTC
 ********************************************************************/

/* Change Log:
 */
/*
 * $Log$
 * Revision 1.1  2004/01/19 21:58:33  perkig2
 * SCR 79555 - Initlal Flashburn code
 *
 * Revision 1.1.1.1  2003/11/20 18:05:30  robert.deml
 * no message
 *
 * Revision 1.5  2001/06/27 17:55:14  heeschen
 * v00.32 Beta Prep
 * Capturing all files to prepare for Beta Release
 *
 * Revision 1.4  2001/04/19 18:56:50  heeschen
 * v00.30 Alpha - Updated comments
 *
 *
 */

#include <stdio.h>
#include "fbtc55.h"
#include "fbcmd.h"
#include "flash.h"


/* Local Prototypes
 */


/* -------------
 * Globals
 * -------------
 */
/* The message must be global; Host will use
 * its address for sending and receiving
 * messages.
 * This program reads what's in the message block
 * and processes it. When done processing,
 * this program will store any response data back
 * into the same block.
 */
u16 theMessage[1+ARGSIZEWORDS+MAXDATAWORDS] = {0}; // the latest message from Host

/* This function must be global; Host will
 * set a breakpoint on it.
 * When this program hits the breakpoint,
 * host will detect the halt and process
 * any response info that may be in the message
 * block. When Host wants to send a message
 * to this FBTC, it will store
 * the message into the global message block
 * and start this FBTC running.
 */
void doMessageProc();  // Message Exchange routine

/* -------------
 * Local Variables & funcs
 * -------------
 */

/* This is the Status Word described
 * in the Comm. Protocol Spec.
 */	
static u16 m_ProtocolStatusWord = 0;


void main()
{

	flash_reset();
	
    /* User comfort message. Runs much
     * faster and leaner if no printf is
     * used anywhere.
     */
//	printf("Target FBTC Running\n");

	InitFlash();
		
	/* Runs forever: I expect Host component
	 * to halt me by closing CCS.
	 */
	for(;;)
	{
		doMessageProc();   // when this returns, I have a message.
		
    	doCommand(theMessage); // Process the new message
	}

}


/* Global Utility Functions
 */


/* This do-nothing function is here to
 * define a global symbol. The Host app.
 * will set a breakpoint at this loc.
 * When this program steps off the
 * breakpoint (returns from this func),
 * that means that the Host has filled
 * the global message block (at theMessage)
 * with a command and data to process.
 * This prog. will process the message,
 * write any response data back into
 * the message block, and then come back
 * here and hit the breakpoint.
 */
void doMessageProc()
{
	/* Optimizer will want to delete
	 * this function, since it doesn't
	 * appear to do anything useful.
	 * Assigning a value to a volatile
	 * forces optimizer to keep this code. 
	 */ 
	volatile int FoolTheOptimizer = 0;
}


u16 GetProtocolVersionID(void)
{
	return (u16)COMMPROTOCOLVERSION;
}

u16 GetProtocolStatusWord(void)
{
	return m_ProtocolStatusWord;
}


void SendI4ToHost(u16 cmd, long val)
{
	StoreCmd(cmd);
	StoreArg(0, (u16)(val >> 16));
	StoreArg(1, (u16)(val & 0x0000ffff));

}


void SendI2ToHost(u16 cmd, u16 val)
{
	StoreCmd(cmd);
	StoreArg(0, val);
}


/* Utility Status Word funcs
 */

	/* Set the 4 status bits
	 */
void SetErrorBits(u16 x)
{
    m_ProtocolStatusWord &= ~(0x000f);
    m_ProtocolStatusWord |= ((x) & 0x000f);
}



/* Stores val into the message command bytes
 */
void StoreCmd(u16 val)
{
	theMessage[CMDINDEX] = val;
}

u16 GetCmd(void)
{
	return theMessage[CMDINDEX];
}

/* Stores val into the message argument bytes
 * at argindex.
 * Argindex is 0-15.
 */
void StoreArg(int argindex, u16 val)
{
	int myindex = ARGINDEX + argindex;
	theMessage[myindex] = val;
}

/* Returns an arg value from arg index 0-15
 */
u16  GetArgVal(int index)
{
	return theMessage[ARGINDEX + index];
}

u16 *GetMessage(void)
{
	return &theMessage[0];
}

u16 *GetData(void)
{
	return &theMessage[DATAINDEX];
}

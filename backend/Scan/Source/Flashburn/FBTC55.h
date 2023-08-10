/*********************************************************************
 *          (C) COPYRIGHT TEXAS INSTRUMENTS, INC. 2000, 2001
 * FlashBurn 55x Target Code header
 * for main module. Includes the
 * Host/Target protocol interfaces.
 */

/* Change Log:
 */
/*
 *$Log$
 *Revision 1.1  2004/01/19 21:58:33  perkig2
 *SCR 79555 - Initlal Flashburn code
 *
 *Revision 1.1.1.1  2003/11/20 18:05:31  robert.deml
 *no message
 *
 *Revision 1.6  2001/05/11 14:28:40  heeschen
 *v00.30 Alpha -- Completed unit and system testing. Ready for release.
 *
 *Revision 1.5  2001/04/19 18:56:50  heeschen
 *v00.30 Alpha - Updated comments
 *
 *
 */

#include "type.h"   /* Mainly for u16 type */


	/* Comm. Protocol Version in force when this
	 * FBTC was created. Add 1 if the protocol
	 * changes, even if this software did not change.
	 * For Protocol Version ID, see the Exchange
	 * Communications Protocol document.
	 * This is in the C file instead of the header
	 * file 'cause the header file is used by other
	 * C files, which could compromise encapsulation.
	 * v1 - original version
	 * v2 - added the Query Edit Flash Permission command
	 *      and expanded msg data buffer to 768 8-bit bytes.
	 * v3 - added the Query Max Data Buffer Bytes command.
	 */
#define COMMPROTOCOLVERSION  3

    /*********************
     * Version ID of this FBTC.
	 * Major.Minor 0.0 to 65535.65535
	 * (thus if major = 1, minor = 20, then
	 * version is 00001.00001
	 *
	 * MUST BE EDITED FOR ANY NEW RELEASE!
     *********************
     */
#define FBTCVersionMajor   00001
#define FBTCVersionMinor   00000

	/* This is the response to send when
	 * host queries for Edit Flash Permission.
	 * Set this to 0 or 1 to indicate whether
	 * this FBTC allows editing individual flash
	 * memory locations.
	 */
#define EDITFLASHPERMIT  0


	/* Message data block length, in bytes.
	 * Use BYTESPERMAU to convert from bytes to
	 * Memory address units.
	 * On a 54x DSP, BYTESPERMAU is 2
	 * On a 62x DSP, BYTESPERMAU is 1
	 */
#define BYTESPERMAU		   2
#define ARGSIZEBYTES	  30
#define ARGSIZEWORDS	  (ARGSIZEBYTES / 2)
#define MAXDATABYTES	2048
#define MAXDATAWORDS	  (MAXDATABYTES / 2)

#define CMDINDEX           0
#define ARGINDEX           1
#define DATAINDEX          (ARGINDEX+ARGSIZEWORDS)

	/* Predefined Status Codes for returning to
	 * Host processor.
	 */
#define CMDOK              0x0
#define UNEXP_DATA_LENGTH  0x1
#define ILL_DATA_VAL       0x2       
#define CMD_NOT_DONE       0x3

/* Prototypes
 */

	/* Returns the current Communications
	 * Protocol status word.
	 */
u16 GetProtocolStatusWord(void);

	/* Returns the Host Communications Protocol
	 * Version ID (0 to 65535) which this FBTC
	 * was designed for. Host uses this to determine
	 * backward compatibility.
	 */
u16 GetProtocolVersionID(void);

	/* Handy func to set the 4 status bits
	 * of the Program Status Word
	 */
void SetErrorBits(u16 x);


/* Send a long value to Host
 * Formats a response message and sends it
 */
void SendI4ToHost(u16 cmd, long val); 

/* Send a u16 value to Host
 * Formats a response message and sends it
 */
void SendI2ToHost(u16 cmd, u16 val); 

/* Message Store/fetch accessors
 */
/* Store a command value into the message buffer
 */
void StoreCmd(u16 val);
u16 GetCmd(void);

/* Store an arg (parameter) into the message buffer
 * Index is 0, 1..., 14  for arg0, arg1, ... arg14
 */
void StoreArg(int argindex, u16 val);
u16  GetArgVal(int index);

/* Get a pointer to the message buffer.
 */
u16 *GetData(void);

u16 *GetMessage(void);

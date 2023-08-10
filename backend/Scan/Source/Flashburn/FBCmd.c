/**********************************************************************
 *		 (C) COPYRIGHT TEXAS INSTRUMENTS, INC. 2000, 2001			  *
 *																	  *
 * FBCmd.c -- Process FlashBurn Target Component commands             *
 *				for FBTC55.                                           *
 **********************************************************************
 */
/* Change Log:
 */
/*
 * $Log$
 * Revision 1.1  2004/01/19 21:58:33  perkig2
 * SCR 79555 - Initlal Flashburn code
 *
 * Revision 1.1.1.1  2003/11/20 18:05:28  robert.deml
 * no message
 *
 * Revision 1.4  2001/04/19 18:56:50  heeschen
 * v00.30 Alpha - Updated comments
 *
 *
 */

#include "fbtc55.h"
#include "fbcmd.h"
#include "flash.h"
#include <stdio.h>


#define DBPRINT  0

/* -------------
 * Globals
 * -------------
 */



/* -------------
 * Local statics
 * -------------
 */

/* ----------------
 * Local prototypes
 * ----------------
 */
static void SendVersionID(void);


u16 doCommand(u16 *msg)
{
	u16 cmd = GetCmd();
	
			#if DBPRINT == 1
			printf("CMD: %x", cmd);
			#endif
	
	/* Dispatch to a processor for the current message.
	*/
	switch(cmd)
	{
	case 0x0000:      /* NOP */
		break;
	case 0x0001:      /* QUERY PROTOCOL VERSION */
		SetErrorBits(CMDOK);
		SendI2ToHost(cmd, GetProtocolVersionID());
		break;
	case 0x0002:      /* QUERY STATUS */
			#if DBPRINT == 1
			printf("  Status: %x", GetProtocolStatusWord());
			#endif
		SendI2ToHost(cmd, GetProtocolStatusWord());
		break;
	case 0x0003:      /* ERASE FLASH */
		SetErrorBits(CMDOK);
		EraseFlash();
		SendI2ToHost(cmd, 0);
		break;
	case 0x0004:      /* QUERY FLASH BASE ADDRESS VALUE */
		SetErrorBits(CMDOK);
			// Send byte addr back to host,
			// not word addr.
		SendI4ToHost(cmd, FLASH_BASE_ADDR * 2);
		break;
	case 0x0005:      /* READ 1 VALUE FROM FLASH LOGICAL ADDR */	
			#if DBPRINT == 1
			printf(" ARGS: %x %x", GetArgVal(0), GetArgVal(1));
			#endif
		SetErrorBits(CMDOK);
			// Note that address from host is byte addr,
			// but I use word addr.
		SendI2ToHost(cmd, GetFlashVal(GetFlashBase() + ShortsToULong(GetArgVal(0), GetArgVal(1)) / 2));
		break;
	case 0x0006: /* READ A BLOCK OF FLASH DATA */
			#if DBPRINT == 1
			printf(" ARGS: %x %x %x", GetArgVal(0), GetArgVal(1), GetArgVal(2));
			#endif
		SetErrorBits(CMDOK);
		SendFlashBufToHost(cmd, GetFlashBase() + ShortsToULong(GetArgVal(0), GetArgVal(1)) / 2, GetArgVal(2));
		break;
	case 0x0007:   /* WRITE DATA TO FLASH  */
			#if DBPRINT == 1
			printf(" ARGS: %x %x %x",  GetArgVal(0), GetArgVal(1), GetArgVal(2));
			#endif
			// Note that address from host is byte addr,
			// but I use word addr.
		SetErrorBits(CMDOK);
		BurnFlash(ShortsToULong(GetArgVal(0), GetArgVal(1)), GetData(), GetArgVal(2));
		break;
	case 0x0008:    /* WRITE MORE DATA TO FLASH */
			#if DBPRINT == 1
			printf(" ARG: %x",  GetArgVal(0));
			#endif
		SetErrorBits(CMDOK);
		BurnFlash((unsigned long)GetNextFlashAddr() * 2, GetData(), GetArgVal(0));
		break;
	case 0x0009:   /* RESPOND WITH FLASH DATA CHECKSUM */
			#if DBPRINT == 1
			printf(" ARGS: %x %x %x %x",  GetArgVal(0), GetArgVal(1), GetArgVal(2), GetArgVal(3));
			#endif
		SetErrorBits(CMDOK);

		CKSSet(0);
			// Note that address from host is logical byte addr.
		SendI2ToHost(cmd,
		            (u16)CKSAccumBuf(ShortsToULong(GetArgVal(0), GetArgVal(1)),
					                 ShortsToULong(GetArgVal(2), GetArgVal(3))));
		break;
    case 0x000a:   /* ACCEPT USER DATA
	                * Simply accept & toss data.
                    * I use this for timing tests.
                    * It could contain your own proprietary
                    * commands or data, sort of an escape
                    * sequence.
                    */
			#if DBPRINT == 1
			printf(" ARG: %x",  GetArgVal(0));
			#endif
		SetErrorBits(CMDOK);		/* This implementation doesn't do anything
		 * with the data)
		 */
		SendI2ToHost(cmd, 0);
		break;

    case 0x000b:      /* QUERY FLASHSIZE VALUE */
		SetErrorBits(CMDOK);
		SendI4ToHost(cmd, GetFlashSize());
		break;

	case 0x000c:      /* CHANGE FLASHSTART ADDRESS */
			#if DBPRINT == 1
			printf(" ARGS: %x %x", GetArgVal(0), GetArgVal(1));
			#endif
		SetErrorBits(CMDOK);
			// Change to word address from byte address for Host.
		SetFlashBase(ShortsToULong(GetArgVal(0), GetArgVal(1)) / 2);
		break;

	case 0x000d:      /* CHANGE FLASH SIZE */
			#if DBPRINT == 1
			printf(" ARGS: %x %x\n", GetArgVal(0), GetArgVal(1));
			#endif
		SetErrorBits(CMDOK);
		SetFlashSize(ShortsToULong(GetArgVal(0), GetArgVal(1)));
		break;

	case 0x000e:      /* QUERY FBTC VERSION ID */
		SetErrorBits(CMDOK);
		SendVersionID();
		break;

	case 0x000f:      /* QUERY EDIT FLASH PERMISSION */
		SetErrorBits(CMDOK);
		SendI2ToHost(cmd, EDITFLASHPERMIT);
		break;

	case 0x0010:      /* QUERY MAX DATA BLOCK SIZE IN BYTES */
		SetErrorBits(CMDOK);
		SendI2ToHost(cmd, MAXDATABYTES);
		break;

	default:
			#if DBPRINT == 1
			printf(" *** UNKNOWN! ***");
			#endif
		break;
	}
	
	#if DBPRINT == 1
	printf("\n");
	#endif
	
	return 0;
}



/* Send my version ID back to the Host.
 */
static void SendVersionID(void)
{	
	StoreCmd(0x000e);  /* response to this command */	
	StoreArg(0, FBTCVersionMajor); /* Arg0 */
	StoreArg(1, FBTCVersionMinor); /* Arg1 */
}




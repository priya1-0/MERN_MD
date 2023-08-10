/************************************************************************
*
* MODULE: bsm_CrcValue.c
*
* OWNER:
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION:
*    This file is a place holder for the CRC value of the program.
*    There are two ways to create the CRC:
*
*    1.) The CRC is calculated after all files are compiled and linked.
*
*        This is done by running the command line utility 2490Gcrc.exe
*        which will calculate crc and overwrite the CRC-values defined
*        here and located in the Motorola S-Record file and create a
*        binary file.
*
*    2.) The CRC is calculated after one compile/link operation, this
*        bsm_CrcValue.c file is overwritten, and a second compile/link
*        is done to compile the new CRC vlaue into the program.
*
*        The utility WinCRC found in c:\2490G\WinCrc is used to read
*        the firmware file, calculate crc, and write a new bsm_CrcValue.c
*        file which is used after a second compile/link. The WinCRC utility
*        also creates a binary file containing the firmware.
*
*    How the crc value is setup:
*
*    1.) The firmware that is executing references the crc by using the
*        variables defined in this file.
*
*    2.) Defining where the crc is located.
*
*        This file uses the pragma-option to locate the crc-parameters in
*        the ".crc" section of memory.
*
*        The flash boot loader command file (each TI CC Studio config can
*        use a different command file) contains the location of the ".crc"
*        section. See the TI CCStudio Project/Build Options General-tab for
*        the specific flash boot loader command file run after compile/linking
*        the program.
*
*    3.) Both the utilities listed above WinCRC.exe and 2490Gcrc.exe read
*        and calculate crc for all memory up to and not including the crc values.
*        The calculated crc values are then written over the old crc values.
*
*************************************************************************/

/////////////
// Includes
/////////////
#include "global.h"

////////////
// Globals
////////////
#ifndef SKIP_CRC
#pragma DATA_SECTION(StoredCrcL, ".crc");
#pragma DATA_SECTION(StoredCrcH, ".crc");

// These values are calculated and set at build time.
UINT16 StoredCrcH;
UINT16 StoredCrcL;

#endif

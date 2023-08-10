/*
************************************************************************
 2490 In-home Remote Monitor
 Copyright (c) Medtronic, Inc. 2001

 MODULE: Application File System Encryption Routine.

 OWNER: Medtronic

 $Revision$

 $Date$

 $RCSfile$

 FUNCTIONS:
      --Public--
void fsm_Encrypt(void)

 DESCRIPTION:
This module contains the C implementation of the Blowfish algorithm

This module contains the routines used to manage the RAM file which contains
the following sections:
     - Header
     - Asset Data
     - Save-To-Disk (Tachy Format)
     - Presenting Waveform Data



 GLOBAL MODULE DATA:
 fsv_connectTimeIndex - Marks where connect time will be placed in the file

 STATIC MODULE DATA:

 ENDPURPOSE

************************************************************************
*/

void fsm_Encrypt (unsigned char *data, unsigned long dataLength);
void fsm_Decrypt (unsigned char *data, unsigned long dataLength);

#ifdef DSP_2490

void fsm_EncryptFile (void);

void fsm_DecryptFile (void);

unsigned long  fsm_BlowfishForPackedData (      unsigned char *data,
                                                unsigned long dataLengthInBytes,
                                                bool          isEncryption);
#endif


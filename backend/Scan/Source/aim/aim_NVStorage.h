/*
************************************************************************
 2490 In-home Remote Monitor
 Copyright (c) Medtronic, Inc. 2004

 MODULE: Interface for EEPROM storage.

 OWNER: Medtronic

 $Revision$

 $Date$

 $RCSfile$

 DESCRIPTION:

 These functions allow for easier accessing of the bsm_EERead and
 bsm_EEWrite functions for 16 and 32 bit values.


 ENDPURPOSE

************************************************************************
*/


#ifndef aim_nvstorage_h
#define aim_nvstorage_h




/*
************************************************************************

        Functions

************************************************************************
*/


/*
***********************************************************************

 FUNCTION: aim_EEReadUINT32

 DESCRIPTION:

        Reads 32-bit long from NV storage at Addr.

 FUNCTION PARAMETERS:

        unsigned int Addr - NV storage address.


 FUNCTION RETURN:

   UINT32 value from NV storage.

***********************************************************************
*/


UINT32 aim_EEReadUINT32(unsigned int Addr);



/*
***********************************************************************

 FUNCTION: aim_EEReadUINT16

 DESCRIPTION:

        Reads 16-bit long from NV storage at Addr.

 FUNCTION PARAMETERS:

        unsigned int Addr - NV storage address.


 FUNCTION RETURN:

   UINT16 value from NV storage.

***********************************************************************
*/

UINT16 aim_EEReadUINT16(unsigned int Addr);


/*
***********************************************************************

 FUNCTION: aim_EEWriteUINT32

 DESCRIPTION:

        Writes 32-bit long to NV storage at Addr.

 FUNCTION PARAMETERS:

        UINT32 ulongValue - value to write.
        unsigned int Addr - NV storage address.


 FUNCTION RETURN:

   None.

***********************************************************************
*/


void  aim_EEWriteUINT32(UINT32 ulongValue, unsigned int Addr);


/*
***********************************************************************

 FUNCTION: aim_EEWriteUINT16

 DESCRIPTION:

        Writes 16-bit integer to NV storage at Addr.

 FUNCTION PARAMETERS:

        UINT16 uintValue - value to write.
        unsigned int Addr - NV storage address.


 FUNCTION RETURN:

   None.

***********************************************************************
*/


void aim_EEWriteUINT16(UINT16 uintValue, unsigned int Addr);

#endif

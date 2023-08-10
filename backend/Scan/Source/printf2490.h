/* Copyright (c) 2005 by Medtronic Inc.  All Rights Reserved */
/********************************************************************

MODULE:  2490W


$Revision$

$Date$

$Workfile$

FUNCTIONS:

DESCRIPTION:

    Functions to replicate the simplicity of printf for the 2490
    platforms.


ENDPURPOSE
********************************************************************/

#ifndef PRINTF2490_H
#define PRINTF2490_H


void printf2490(char* _formatString, ...);
void asciiHex(char* ptrIn, unsigned int ptrInLength, char* ptrOut);


#ifdef UNIT_TEST_CCM

void UTestPrintf2490(void);

#endif



#endif

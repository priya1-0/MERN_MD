/************************************************************************
*
* MODULE: itoa.h
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION:
*
*************************************************************************/
#ifndef ITOA_H
#define ITOA_H

// Voacl has a itoa() function. To avoid linker confusion, we will rename ours.
// from char *itoa(int value, char *string, int radix) to:

char *aim_itoa(int value, char *string, int radix);

#endif

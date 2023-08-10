/************************************************************************
*
* MODULE: itoa.c
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
#include "itoa.h"
#include <stdio.h>

// See itoa.h file for why function name is not itoa()

char *aim_itoa(int integer, char* output, int radix)
{
    // Let sprintf do the formatting.
    (void)sprintf(output,"%d",integer);

    // Return point to buffer
    return(output);
}



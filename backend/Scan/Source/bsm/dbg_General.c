/************************************************************************
*
* MODULE: dbg_General.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions for debugging general
*              system items.
*
*************************************************************************/

/////////////
// Includes
/////////////
#include "bsm_serialport.h"
#include "dbg_General.h"
#include "string.h"

#ifdef __DEV_VT__
/******************************************************************

FUNCTION: ReadSystemID

DESCRIPTION: This function reads the battery threshold pin and
                         writes the value to the ResultsBuffer

ARGS:
        <none>

RETURNS:
        <none>

******************************************************************/
void ReadSystemID(void)
{
    char systemType[20];
    strcpy(systemType, "Model: ");

    //Determine Model
        #if   defined __BRADYA__ //Kappa
    strcat(systemType, DBG_MODEL_2490H);
        #elif defined __TACHYA__ //GEM
    strcat(systemType, DBG_MODEL_2490J);
        #elif defined __TACHYB__ //Marquis
    strcat(systemType, DBG_MODEL_2490G);
        #else
                #warn "WARNING: No System type selected."
    strcat(systemType, DBG_MODEL_UNKNOWN);
        #endif

    //Print output
    bsm_SDPrint(systemType);
}
#endif // __DEV_VT__
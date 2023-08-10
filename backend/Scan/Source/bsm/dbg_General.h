/************************************************************************
*
* MODULE: dbg_General.h
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the function to debug general system
*              items
*
*************************************************************************/
#ifndef DBG_GENERAL_H
#define DBG_GENERAL_H

//System Types
#define DBG_MODEL_2490G   "G" //TachyB - Marquis
#define DBG_MODEL_2490H   "H" //BradyA - Kappa
#define DBG_MODEL_2490J   "J" //TachyA - GEM
#define DBG_MODEL_UNKNOWN "*Unknown*" //TachyA - GEM

/////////////
// Prototypes
/////////////
void ReadSystemID(void);

#endif

/*
************************************************************************
 2490 In-home Remote Monitor
 Copyright (c) Medtronic, Inc. 2001

 MODULE: Application Interrogation Module for the Kappa Family.

 OWNER: Medtronic

 $Revision$

 $Date$

 $RCSfile$

*/

#include <string.h>
#include "aim_kappa.h"
#include "aim_enpulse.h"
#include "fsm_file.h"
#include "fsm_kappa.h"


extern char aiv_workingKappaDevice;
extern char aiv_workingKappaSubModelId;

ait_KappaDeviceMemoryRange aim_Enpulse_Table[] =
{
//
//segment, firstPage,numPages,offset, size, data ptr
//
    {0,         0,       32,      0,    1056,  NULL},
    {1,         0,      128,      0,    4224,  NULL},
    {2,         0,      256,      0,    8448,  NULL},
    {0,         0,        0,      0,       0,  NULL}, // numpages=0 means end of table
};



/*
***********************************************************************

 FUNCTION:   aim_EnpulsePreInterrogate

 DESCRIPTION:
Any tasks that need to be done before the full interrogation phase
begins are done here. This allows the caller/user to do any desired
pre-interrogation work, free up control back to the user, and
call back later to do the full interrogation.

 FUNCTION CONSTANTS:

 FUNCTION PARAMETERS:

   NONE

***********************************************************************
*/
void aim_EnpulsePreInterrogate(void)
{
    // Initialize the version number in the file section headers
    strcpy(fsv_SaveToDiskSectionHeader.version, "2.0");
    strcpy(fsv_AssetSectionHeader.version, "2.0");
    strcpy(fsv_WaveformSectionHeader.version, "2.0");

    aim_KappaResumeTelemetryA();
}

/*
***********************************************************************

 FUNCTION:   aim_EnpulseInterrogate

 DESCRIPTION:
Interrogate an Enpulse Device.

***********************************************************************
*/
void aim_EnpulseInterrogate(void)
{
    fsm_OpenMemoryDumpFileSection(aiv_workingKappaDevice, aiv_workingKappaSubModelId);

    aim_KappaRead(aim_Enpulse_Table);

    fsm_CloseMemoryDumpFileSection();
}

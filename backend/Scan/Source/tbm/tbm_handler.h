/* Copyright (c) 2001 by Medtronic Inc.  All Rights Reserved */
/********************************************************************
DOCUMENT

$Revision$

$Date$

$RCSfile$

NAME:
  tbm_handler.h  area = telemetry B (tb) which encompasses all telemetry B
    functionality.

PURPOSE:
  This file contains prototypes for functions which are available to
  the 2490B Application modules, to perform Telemetry B functions.

ENDDOCUMENT
*************************************************************************/
#ifndef tbm_handler_h
#define tbm_handler_h

#include "..\types.h"
#include "tbt_handler.h"

#ifdef DEFINED_HERE
        #define SCOPE
#else
        #define SCOPE extern
#endif

/*
*******************************************************************
  tbm_telemBAutoID is called by the Application to request the Device ID's
  from all Telemetry B type devices in range of the RF Head.

  CONSTRAINTS:
  1.  This function may be called after a power-up has occurred and
  tbm_telemBInitialize has been called.
  2.  It must be called and it's return buffer must contain a valid device ID
  before either tbm_telemBData or tbm_telemBUplinks can be called.
  3.  After either tbm_telemBData or tbm_telemBUplinks has been called, a call to
  tbm_telemBClose must be made before this function may be called again.

  INPUTS:
  tbv_deviceIDRespPtr : a pointer to a response buffer.
  tbv_ProgrammerID : the 2490B Programmer ID.

  OUTPUTS:
  "return value" : status which indicate the success or failure of this function.
  Note that a return status of tbc_successful only indicates that the downlinks
  were transmitted without failure.  The contents of the returned buffer
  (tbv_DeviceIDRespPtr) must be examined to determine whether or not any device
  successfully responded to the downlink.

  *tbv_DeviceIDRespPtr : The device ID's are returned in the response buffer.

*******************************************************************
*/
SCOPE tbt_reqStatus tbm_telemBAutoID(tbt_autoIDRespType * tbv_DeviceIDRespPtr,
                                     UINT16             tbv_ProgrammerID);

/*
*******************************************************************
  tbm_telemBClose is called by the Application to request that the
  telemetry session with the device be terminated.  This would normally
  be called only after all device data had been accumulated.   The
  Application supplies no parameters.  This function returns a status
  to indicate the success or failure of this function.

  CONSTRAINTS:
  A tbm_telemBClose session is useful, but not required after either a successful
  call to tbm_telemBData or tbm_telemBUplinks if the application determines it has
  completed all telemetry tasks and wishes to shut off the telemetry portion of the
  system.

  INPUTS:  none

  OUTPUTS:
  "return value" : status which indicate the success or failure of this function.
  Note: The return value is always successful unless the caller has used this
  function incorrectly.  Therefor no retry should be used if a failure status is
  returned as that would indicate a coding problem and not a telemetry problem.

*******************************************************************
*/
SCOPE tbt_reqStatus tbm_telemBClose(void);

/*
*******************************************************************
  tbm_telemBData is called by the Application to request that a Telemetry B
  session be established with a specific device and to send that device
  an Application Downlink request.  This function must also store all of the
  responses to the Application Downlink request and provide these at the
  specific memory location defined by the calling function.

  CONSTRAINTS:
  1.  This function may be called after a power-up has occurred,
  tbm_telemBInitialize has been called, and a call to tbm_telemBAutoID
  has successfully returned a buffer containing a valid device ID.
  2.  After the initial steps in Constraint #1 have occurred, this function
  can be called repeatedly back-to-back any number of times.

  INPUTS:
  v_appDataReqInfoPtr :  a pointer to a set of required parameters.
  The details of the contents is defined by the type: tbt_appDataReqEntry.

  OUTPUTS:
  "return value" : status which indicate the success or failure of this function.

  *v_appDataReqInfoPtr : The response information is stored in one or more of the
  parameters. The details of the contents is defined by the type: tbt_appDataReqEntry.

*******************************************************************
*/
SCOPE tbt_reqStatus tbm_telemBData(tbt_appDataReqEntry * v_appDataReqInfoPtr);

/*
*******************************************************************
  tbm_telemBInitialize initializes the Telemetry system.

  CONSTRAINTS:  This function must be the first Telemetry function called. And it
  must be called only once per power on.

  INPUTS:  none

  OUTPUTS:
  "return value" : status which indicate the success or failure of this function.

*******************************************************************
*/
SCOPE tbt_reqStatus tbm_telemBInitialize(void);
/********************************************************************

FUNCTION:
  tbm_telemBDeactivate

DESCRIPTION:
  This function deactivates the Telemetry B system.

  This function must be called by the application when Telemetry
  B activities have been completed. Failure to call this function
  can have adverse affects on other modules that utilize the
  shared DARAM space that the tbm module utilizes.

INPUT:
  none

OUTPUT:
  none


********************************************************************/
SCOPE void tbm_telemBDeactivate(void);

/*
*******************************************************************
  tbm_telemBUplinks is called by the Application to request that a Telemetry B
  session be established with a specific device.  This function must also
  store all of the valid uplink frames and provide these at the
  specific memory location defined by the calling function.  The details
  of the parameters in the tbt_uplinksReqEntry type are found in
  tbt_handler.h.  This function returns a status to indicate the success
  or failure of this function.

  CONSTRAINTS:
  1.  This function may be called after a power-up has occurred,
  tbm_telemBInitialize has been called, and a call to tbm_telemBAutoID
  has successfully returned a buffer containing a valid device ID.
  2.  After the initial steps in Constraint #1 have occurred, this function
  can be called repeatedly back-to-back any number of times.

  INPUTS:
  v_uplinksReqInfoPtr :  a pointer to a set of required parameters.
  The details of the contents is defined by the type: tbt_uplinksReqEntry.

  OUTPUTS:
  "return value" : status which indicate the success or failure of this function.

  *v_uplinksReqInfoPtr : The response information is stored in one or more of the
  parameters. The details of the contents is defined by the type: tbt_uplinksReqEntry.

*******************************************************************
*/
SCOPE tbt_reqStatus tbm_telemBUplinks(tbt_uplinksReqEntry * v_uplinksReqInfoPtr);


// Global Variables.

/* Declare the global variable to track all Telemetry Channel Items. */
SCOPE tbt_sessionType tbv_session;

/* Declare the tag used in Downlink Application Requests. */
SCOPE BYTE tbv_tag;  /* Valid values are 0 through 7. */


#undef SCOPE

#endif //tbm_handler_h

/*
***********************************************************************
 2490 In-home Remote Monitor
 Copyright (c) Medtronic,0x Inc. 2001

 MODULE: CSPY File Used for debugging with CSPY Simulator

 OWNER: Medtronic

 $Revision$

 $Date$

 $RCSfile$

 FUNCTIONS:

 DESCRIPTION:

 This file contains the CSPY simulator functions which are used to
 reference the data in the file cspy_pdd.c.  In the aim_cspy.c file
 both the CSPY and CSPY_PDD compiler options should be defined (uncommented)
 to run this file.

 ENDPURPOSE

***********************************************************************
*/




#ifdef CSPY_PDD

#include <string.h>

#ifdef __2490TELEMB__
#include "aim_tlmb.h"
#include "tbt_handler.h"
#endif


// These are redundant and must not be defined unless CSPY_PDD is defined.

#define AIC_RESUME_DETECTION 0x21

ait_DeviceMemory simulatorDeviceMemory =
{
   0,                                           // timeOfLastInterrogate
   sizeof(simulatorRange)/sizeof(ait_Range),    // numberOfRanges
   (ait_Range*)simulatorRange                               // ranges
};


#ifdef __2490TELEMA__

/*
***********************************************************************

 FUNCTION:   aim_RetrieveModelAccessCodeA()

 DESCRIPTION:
This function returns the model access code for the current model.

 FUNCTION PARAMETERS:.

***********************************************************************
*/
BYTE aim_RetrieveModelAccessCodeA(void)
{
  BYTE returnAccessCode = 0;
  
  if (0 == strncmp("7273", simulatorModelIdName, 4))
     returnAccessCode = 0xC3;
  else if (0 == strncmp("7271", simulatorModelIdName, 4))
     returnAccessCode = 0x4F;
  else if (0 == strncmp("7275", simulatorModelIdName, 4))
     returnAccessCode = 0xCC;  
  else if (0 == strncmp("7227", simulatorModelIdName, 4))
     returnAccessCode = 0x4B;  
  else if (0 == strncmp("7229", simulatorModelIdName, 4))
     returnAccessCode = 0x65;
  else if (0 == strncmp("7231", simulatorModelIdName, 4))
     returnAccessCode = 0xC6;        
     
  return(returnAccessCode);
}

/*
***********************************************************************

 FUNCTION:   aim_RetrieveModelIdCodeA()

 DESCRIPTION:
This function returns the model Id code for the current model.

 FUNCTION PARAMETERS:.

***********************************************************************
*/
BYTE aim_RetrieveModelIdCodeA(void)
{
  BYTE returnIdCode = 0;
  
  if (0 == strncmp("7273", simulatorModelIdName, 4))
     returnIdCode = 0xC3;
  else if (0 == strncmp("7271", simulatorModelIdName, 4))
     returnIdCode = 0x4F;
  else if (0 == strncmp("7275", simulatorModelIdName, 4))
     returnIdCode = 0xCC;  
  else if (0 == strncmp("7227", simulatorModelIdName, 4))
     returnIdCode = 0x4B;  
  else if (0 == strncmp("7229", simulatorModelIdName, 4))
     returnIdCode = 0x65;
  else if (0 == strncmp("7231", simulatorModelIdName, 4))
     returnIdCode = 0xC6; 
     
  return(returnIdCode);
}
#endif
#ifdef __2490TELEMB__
/*
***********************************************************************

 FUNCTION:   aim_SimulatedAutoIdB()

 DESCRIPTION:
This function returns the model Id code for the current model.
Telemetry B.

 FUNCTION PARAMETERS:.

***********************************************************************
*/
bool aim_SimulatedAutoIdB(unsigned long *p_deviceId)
{
  bool returnStatus=false;
  
  if (0 == strncmp("7274", simulatorModelIdName, 4))
  {
     *p_deviceId = 0x000201;
     returnStatus = true;
  }
  else if (0 == strncmp("7230", simulatorModelIdName, 4))
  {
     *p_deviceId = 0x000202;
     returnStatus = true;
  }
  else if (0 == strncmp("7277", simulatorModelIdName, 4))
  {
     *p_deviceId = 0x000205;
     returnStatus = true;
  }
  else if (0 == strncmp("9520", simulatorModelIdName, 4))
  {
     *p_deviceId = 0x000601;
     returnStatus = true;
  }
  else if (0 == strncmp("7278", simulatorModelIdName, 4))
  {
     *p_deviceId = 0x000206;
     returnStatus = true;
  }
  else if (0 == strncmp("7232", simulatorModelIdName, 4))
  {
     *p_deviceId = 0x000207;
     returnStatus = true;
  }
  // 7279 and 7289 both have an application ID of 7279
  else if (0 == strncmp("7279", simulatorModelIdName, 4))
  {
     *p_deviceId = 0x000701;
     returnStatus = true;
  }
  if (returnStatus)
    returnStatus = aim_IsKnownDevice(*p_deviceId, aic_TelemetryTypeB);
  return(returnStatus);
     
}
#endif // __2490TELEMB__

/*
***********************************************************************

 FUNCTION:   aim_PointerToSimulatedMemory

 DESCRIPTION:
This function returns a pointer to the simulated data at the passed address. 
It is up to the caller to decode the data from the returned pointer or in 
some cases change the data pointed to.

 FUNCTION PARAMETERS:
   address
      The physicalAddress of the parameter.

   len
      The length of data the user wishes to have access to.

***********************************************************************
*/
char *aim_PointerToSimulatedMemory(unsigned long address, unsigned int len)
{
   ait_Address a;

   a.bank = aic_noBank;
   a.physicalAddress = address;
   a.mask = 0;

   return(aim_PointerToDeviceMemory(&simulatorDeviceMemory, a, len));
}

#ifdef __2490TELEMA__
/*
***********************************************************************

 FUNCTION:   aim_SimulatedRepeatDownlink

 DESCRIPTION:
Simulate the Telemetry Application Module (TAM) Repeat Downlink 
function by returning a successful status.

 FUNCTION CONSTANTS:

 FUNCTION PARAMETERS:

 FUNCTION RETURN:
   

***********************************************************************
*/
tat_status aim_SimulatedRepeatDownlink(BYTE *p_downlinkMsg,
                                       USHORT v_downlinkSize,
                                       BYTE v_repeatInterval)
{

  p_downlinkMsg = p_downlinkMsg;
  v_downlinkSize = v_downlinkSize;
  v_repeatInterval = v_repeatInterval;
  
  return(tac_successful);
}

/*
***********************************************************************

 FUNCTION:   aim_SimulatedCancelRepeatDownlink

 DESCRIPTION:
Simulate the Telemetry Application Module (TAM) Cancel Repeat Downlink 
function by returning a successful status.

 FUNCTION CONSTANTS:

 FUNCTION PARAMETERS:

 FUNCTION RETURN:
   

***********************************************************************
*/
tat_status aim_SimulatedCancelRepeatDownlink(void)
{
  return(tac_successful);
}
/*
***********************************************************************

 FUNCTION:   aim_SimulatedSendTelemetryA

 DESCRIPTION:
Simulate the Telemetry Application Module (TAM) send telemetry function.

 FUNCTION CONSTANTS:

 FUNCTION PARAMETERS:
   p_downlink
      Pointer to the downlink message.
   
   downlinkSize
      Size of the downlink message. Includes the header and CRC.

   p_uplink
      Pointer to the uplink.

   uplinkSize
      Expected size of the uplink message.  Includes the header and CRC.

   timeOut
      Not used here.

 FUNCTION RETURN:
   Index of next element to be written.

***********************************************************************
*/
tat_status aim_SimulatedSendTelemetryA(BYTE *p_downlink, USHORT downlinkSize, 
                                      BYTE *p_uplink,   USHORT uplinkSize, 
                                      USHORT timeOut)

{
   BYTE controlByte;
   BYTE hi;
   BYTE lo;
   BYTE bank;
   unsigned int i, j;
   unsigned int record;
   USHORT address;
   ait_Address a;
   char *ptr;
   BYTE modelAccessCode;
   BYTE modelIdCode;
   tat_status status = tac_successful;
   
   timeOut = timeOut;

   modelAccessCode = aim_RetrieveModelAccessCodeA();
   modelIdCode = aim_RetrieveModelIdCodeA();
   
   // check for auto id & resume
   if (downlinkSize == 4)
   {
      if (p_downlink[1] == AIC_RESUME_DETECTION)
      {  // resume detection
         i=0;
         p_uplink[i++] = modelIdCode;
         p_uplink[i++] = 0x00;
         p_uplink[i++] = 0x00;
         aim_AddCRC(p_uplink, i);
      }
      else
      {  // auto id
         i=0;
         p_uplink[i++] = modelIdCode;
         p_uplink[i++] = 0x00;
         p_uplink[i++] = 0x05;
         aim_AddCRC(p_uplink, i);
      }
   }
   else
   {
     // all other downlinks are > 4
      if (p_downlink[0] == modelAccessCode)
      {
         i=0;
         j=0;
         p_uplink[j++] = p_downlink[i++]; // model id.
         p_uplink[j++] = p_downlink[i++];
         record = 0;
         do{
            controlByte = p_downlink[i++] + 1;   // requested sizes are -1
            hi = p_downlink[i++];
            lo = p_downlink[i++];
            address = (hi<<8) + lo;

            bank = aic_noBank;

            // if address is in bank area then the next byte is bank.
            if ((address>=0x2000) && (address<=0x5fff))
            {
               bank = p_downlink[i++];
            }

            a.bank = bank;
            a.physicalAddress = address;

            // get a pointer to simulated device memory.
            // controlByte = # of bytes.
            ptr = aim_PointerToDeviceMemory(&simulatorDeviceMemory,
                                             a, 
                                             controlByte);

            // The address is in the simulated area.
            if (ptr!=NULL)
            {
               memcpy(&p_uplink[j], ptr, controlByte);
               // add to uplink accumulator.
               j+=controlByte;
            }
            else
            {
	       // add "filler" bytes, if the user doesn't care about content.
               memset(&p_uplink[j], '1'+record, controlByte);
               j+=controlByte;
            }

            ++record;
         } while(i < downlinkSize - 2);   // -2 for the CRC


         j = aim_AddCRC(p_uplink, j);

         // compared actual uplinksize to expected.
         if (j != uplinkSize)
            status = 1; // This just has to be non-successful.

      }
      else
      {
         // actually wrong device
         status = 1;  // This just has to be non-successful.
      }

   }

   return(status);
}
#endif
#ifdef __2490TELEMB__
/*
***********************************************************************

 FUNCTION:   aim_SimulatedSendTelemetryB

 DESCRIPTION:
Simulate the Telemetry Application Module (TBM) send telemetry function.

 FUNCTION CONSTANTS:

 FUNCTION PARAMETERS:
   p_downlink
      Pointer to the downlink message.
   
   downlinkSize
      Size of the downlink message. Includes the header and CRC.

   p_uplink
      Pointer to the uplink.

   uplinkSize
      Expected size of the uplink message.  Includes the header and CRC.

   timeOut
      Not used here.

 FUNCTION RETURN:
   Index of next element to be written.

***********************************************************************
*/
void  aim_SimulatedSendTelemetryB(char *p_downlink, int downlinkSize,
                                  char *p_uplink,   int uplinkSize,
                                  bool updateProgress)

{
   BYTE hi;
   BYTE med;
   BYTE lo;
   unsigned int i, j;
   unsigned int record;
   unsigned long address;
   ait_Address a;
   char *ptr;
   int length;
   
   updateProgress = updateProgress;
   uplinkSize = uplinkSize;

   // Unlike the telemetry A simulated send-telemetry,
   // telemetry B send-telemetry does not care about the
   // model id.
   
   i=2;  // The downlink reference is set to first records command code.
   j=0;
   // This 3 byte header is discarded by caller.
   p_uplink[j++] = 0x00;  // Command Code
   p_uplink[j++] = 0x00;  // Command Code
   p_uplink[j++] = 0x00;  // Status
   record = 0;
   do{
     i++;  // step past the command code.
     hi = p_downlink[i++];
     med = p_downlink[i++];
     lo = p_downlink[i++];
     address = ((long)hi<<16) + ((long)med<<8) + lo;
     hi = p_downlink[i++];
     lo = p_downlink[i++];
     length = (hi<<8) + lo;
     
     a.bank = aic_noBank;
     a.physicalAddress = address;

     // get a pointer to simulated device memory.
     // controlByte = # of bytes.
     ptr = aim_PointerToDeviceMemory(&simulatorDeviceMemory,
                                     a, 
                                     length);

     // The address is in the simulated area.
     if (ptr!=NULL)
     {
        memcpy(&p_uplink[j], ptr, length);
        // add to uplink accumulator.
        j+=length;
     }
     else
     {
        // add "filler" bytes, if the user doesn't care about content.
        memset(&p_uplink[j], '1'+record, length);
        j+=length;
     }
     ++record;
   } while(i < downlinkSize - 4);   // -2 for the Command Code/# Records and -2 for the CRC


   j = aim_AddCRC(&p_uplink[AIC_B_UPLINK_HEADER_SIZE], (j - AIC_B_UPLINK_HEADER_SIZE));

}
#endif // __2490TELEMB__

#endif
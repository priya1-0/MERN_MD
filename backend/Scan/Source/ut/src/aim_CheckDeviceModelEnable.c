#include "aim_CheckDeviceModelEnable.h"
#include "bsm_EEReadBuf.h"
#include "com_eepromapp.h"

// #include <stdio.h>




/*
***********************************************************************

 FUNCTION: aim_CheckDeviceModelEnable

 DESCRIPTION:

        Determines if the particular device model has been enabled via the
        Phone4 parameter.  This routine relies on a particular format for
        the model ids listed in the Phone4 parameter.
        1. The very first character must be a '#'
        2. The entire string must be terminated with a ';'
        3. A ',' must separate the individual model id information 
        4. Hexidecimal entries should be upper case
        5. NULL termination is not required. 

        Example format: #0019,0017,002A;

        For extensibility, submodel information checking may be easily
        added provided it directly follows the corresponding model id.

 FUNCTION PARAMETERS:

        unsigned long deviceId - a valid device ID determined via AutoID.

 FUNCTION RETURN:

   boolean true if device is enabled. If the device
   has not been enabled, false is returned.

***********************************************************************
*/

bool aim_CheckDeviceModelEnable(unsigned long deviceId)
{
    char        DeviceEnableList[coc_ISPPhone4_SIZE];
    char        model_id_str[4];
    char        HexToAscii[] = "0123456789ABCDEF";
    int         loop_cnt;
    bool        ret_val = false;
    bool        model_found = false;

//     if ( NULL == aiv_KappaDeviceTableA[aiv_workingKappaDeviceTableIndex].deviceId)
//     if ( false == aiv_KappaDeviceTableA[aiv_workingKappaDeviceTableIndex].checkPhone4 )
//     {
//         return true;
//     }

    
    // Read in the device enable data from the Phone4 parameter
    bsm_EEReadBuf((UINT8*)DeviceEnableList, coc_ISPPhone4_SIZE, coc_ISPPhone4_ADDR);

    // Check the first character for validity
    if (DeviceEnableList[0] == '#')
    {
        // Initial character found, replace with a comma to optimize the loop below
        DeviceEnableList[0] = ',';

        // Convert the deviceId passed in, into a 4 byte character string
        // for comparison
        model_id_str[0] = HexToAscii[(deviceId & 0x0000F000) >> 12];
        model_id_str[1] = HexToAscii[(deviceId & 0x00000F00) >>  8];
        model_id_str[2] = HexToAscii[(deviceId & 0x000000F0) >>  4];
        model_id_str[3] = HexToAscii[(deviceId & 0x0000000F)      ];

        // The initial character has been located
        // now parse the data for the model id and terminating character
        for(loop_cnt = 0; loop_cnt < coc_ISPPhone4_SIZE; loop_cnt++)
        {
            // Look for the start of the next entry
            if(DeviceEnableList[loop_cnt] == ',')
            {
                // If we haven't already found a matching id,
                // Read 4 bytes of model data and compare to the interrogated Device Id
                if(model_found == false &&
                   DeviceEnableList[loop_cnt+1] == model_id_str[0] &&
                   DeviceEnableList[loop_cnt+2] == model_id_str[1] &&
                   DeviceEnableList[loop_cnt+3] == model_id_str[2] &&
                   DeviceEnableList[loop_cnt+4] == model_id_str[3])
                {
                   // model id located
                   model_found = true;
                   // extensibility - Extra code could be added here to support submodel id
                }
            }
            else if(DeviceEnableList[loop_cnt] == ';')
            {
                // This is the terminating character, if a model id match was found,
                // set the return value to true
                if (model_found == true)
                {
                    ret_val = true;
                }
                break; // Exit - terminating character found
            }
        }
     }
     // return the status of the string search
     return(ret_val);
}

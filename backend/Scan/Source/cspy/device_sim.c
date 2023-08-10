
#include <file.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "types.h"

#ifdef __2490TELEMA__

#include "tam_global.h"

#endif

#include "device_sim.h"
#include "bsm_global.h"
#include "aim_gem.h"
#include "uim_ui.h"
#include "fsm_pbfr.h"
#include "fsm_encrypt.h"
#include "fsm_file.h"

#ifdef __2490TELEMB__
#include "aim_tlmb.h"
#endif


#define NO_DEV_SIM_ERROR	// steam ahead on range errors


#define DEV_MEMORY_FILE	((char*)"device.dm")
#define DEV_LOG_FILE	((char*)"2490G_TestRun.log")
#define PACKAGE_FILE	((char*)"upload.bin")
#define WAVEFORM_FILE	((char*)"device.wvf")


typedef struct {
    u32 bank;			// A given range's bank (info from PC file).
    u32 address;		// A given range's device address (info from PC file).
    u32 mask;			// A given range's mask (info from PC file).
    u32 length;			// A given range's data length (info from PC file).
    u32 fileOffset;  	// Starting offset of data in PC file
    bool hasBeenRead; 	// Bank has been read accessed
} RangeInfo;

//  Range/file info table
static RangeInfo RangesOfDiskFile[256];


#define AUTO_ID_7227 (0x4B)     /* Model 7227 */
#define AUTO_ID_7273 (0xC3)     /* Model 7273 */
#define AUTO_ID_7229 (0x65)     /* Model 7229 */
#define AUTO_ID_7271 (0x4F)     /* Model 7271 */
#define AUTO_ID_7272 (0xC5)     /* Model 7272 (HF) */
#define AUTO_ID_7275 (0xCC)     /* Model 7275 */
#define AUTO_ID_7231 (0xC6)     /* Model 7231 */
  
#define AUTO_ID_7274 (0x000201)
#define AUTO_ID_7230 (0x000202)
#define AUTO_ID_7277 (0x000205)
#define AUTO_ID_9520 (0x000601)
#define AUTO_ID_7278 (0x000206)
#define AUTO_ID_7232 (0x000207)
#define AUTO_ID_7279 (0x000701)  // 7279/7289 HAVE SAME AUTO-ID
#define AUTO_ID_7289 (0x000701)
#define AIC_RESUME_DETECTION 0x21


#define MAX_MATCHES 100

#define NO_BANK_FLAG = ((u32)0x000000ff)

#define FILENAME_BFR_SZ 256
#define FILE_BYTES_PER_LONG	4

// DM file offset
#define FILENAME_OFFSET         ((u32) 0)
#define AUTO_ID_OFFSET          ((u32) FILENAME_OFFSET + FILENAME_BFR_SZ)
#define NUM_RANGES_OFFSET       ((u32) AUTO_ID_OFFSET + FILE_BYTES_PER_LONG)
#define TIME_OF_SAVE_OFFSET     ((u32) NUM_RANGES_OFFSET + FILE_BYTES_PER_LONG)
#define LAST_SESSION_OFFSET     ((u32) TIME_OF_SAVE_OFFSET + FILE_BYTES_PER_LONG)
#define START_OF_RANGES_OFFSET  ((u32) LAST_SESSION_OFFSET + FILE_BYTES_PER_LONG)

//
// Since PC file I/O hogs CPU/interrupt time, this helps the LEDs and tones stay reasonably
// useful.
#define SLEEP_A_LITTLE NU_Sleep(2)


// Full path of PDD on PC used to create the DEVICE.DM file
static char Source_PDD_Filename[FILENAME_MAX];




// Values retrieved from DEVICE.DM 

static u32 TimeOfSave = 0;
static u32 NumberOfRanges = 0;
static u32 TimeOfLastSession = 0;
static u32 AutoId = 0;
 
// Used in DevSimMemory and set/reset via DeviceSimRescan, DeviceSimNormalScan
static bool rescanPdd = false;

///#define DEBUG_DEVSIM_MEMORY

//
// Convert from "network" order to "host"
//
u32 NToHL(char *bytes)
{
	int x;
    u32 aLong = 0;
    for (x = 0; x < 4; x++)
    {
        aLong <<= 8;
        aLong = aLong + (bytes[x] & 0xff);
    }
    return(aLong);
}



//
// Set flag for more detailed scanning in DeviceSimMemory
//
void DeviceSimRescan()
{
	rescanPdd = true;	
}

//
// Reset flag for DeviceSimMemory to use 1st match
//
void DeviceSimNormalScan()
{
	rescanPdd = false;	
}



//
// This function reads the "DEVICE.DM" file on the PC and 
// initializes the entries in the table RangesOfDiskFile[].
// 
void DeviceSimInit()
{


    int fileId, range;
    u32 runningOffset;       
    int errs = 0;
    char longBytes[4];
    
    DeviceSimNormalScan();

    // Clear file path/file names
    
    DeviceSimLogInit();
    
    DeviceSimLog("Started DeviceInit");

    memset(Source_PDD_Filename,0,sizeof(Source_PDD_Filename));

    if (-1 == (fileId = open(DEV_MEMORY_FILE, O_RDONLY|O_BINARY, 0)))
        DeviceSimError("Can't open device memory file.");

    // Seek to start of file

	if (FILENAME_OFFSET != lseek(fileId, (off_t)FILENAME_OFFSET, SEEK_SET))
        DeviceSimError("Error seeking to start of device memory file.");

    
	if (FILENAME_BFR_SZ  != read(fileId, Source_PDD_Filename, FILENAME_BFR_SZ))
        DeviceSimError("Error reading source PDD path in device memory file.");

	// Document where the PDD came from
	
	DeviceSimLog(Source_PDD_Filename);
	
    // Read AutoId

	if (FILE_BYTES_PER_LONG  != read(fileId, (char *)longBytes, FILE_BYTES_PER_LONG))
        DeviceSimError("Error reading Auto ID in device memory file.");

    AutoId = NToHL(longBytes);


    // Read number of ranges

	if (FILE_BYTES_PER_LONG  != read(fileId, (char *)longBytes, FILE_BYTES_PER_LONG))
        DeviceSimError("Error reading number of ranges in device memory file.");

    NumberOfRanges = NToHL(longBytes);


    // Read time-of-save 

	if (FILE_BYTES_PER_LONG  != read(fileId, (char *)longBytes, FILE_BYTES_PER_LONG))
        DeviceSimError("Error reading time-of-save in device memory file.");

    TimeOfSave = NToHL(longBytes);

    // Read time-of-last-session 

	if (FILE_BYTES_PER_LONG  != read(fileId, (char *)longBytes, FILE_BYTES_PER_LONG))
        DeviceSimError("Error reading time-of-last-session in device memory file.");

    TimeOfLastSession = NToHL(longBytes);



    // Read all range definitions in the file and set up 
    // the list of both actual device info and the device memory file offsets

    runningOffset = START_OF_RANGES_OFFSET;

	SLEEP_A_LITTLE; // Let others have some CPU cycles

    for (range = 0; range < NumberOfRanges; range++)
    {
		SLEEP_A_LITTLE; // Let others have some CPU cycles

	    if (runningOffset != lseek(fileId, (off_t)runningOffset, SEEK_SET))
            errs++;

        // Bank
	    if (FILE_BYTES_PER_LONG != read(fileId, longBytes, FILE_BYTES_PER_LONG))
            errs++;
            
        RangesOfDiskFile[range].bank = NToHL(longBytes);

        // Address
	    if (FILE_BYTES_PER_LONG  != read(fileId, longBytes, FILE_BYTES_PER_LONG))
            errs++;
        RangesOfDiskFile[range].address = NToHL(longBytes);
        
        // Mask
	    if (FILE_BYTES_PER_LONG  !=  read(fileId, longBytes, FILE_BYTES_PER_LONG))
            errs++;
        RangesOfDiskFile[range].mask = NToHL(longBytes);

        // Length
	    if (FILE_BYTES_PER_LONG  !=  read(fileId, longBytes, FILE_BYTES_PER_LONG))
            errs++;
        RangesOfDiskFile[range].length = NToHL(longBytes);
        
        // Init read flag of this range.
        RangesOfDiskFile[range].hasBeenRead = false;

        // Save start position of data in the file
        RangesOfDiskFile[range].fileOffset = runningOffset += 16;

        // Point to next range section
        runningOffset += RangesOfDiskFile[range].length;

    }

    //  Close files

    close(fileId);
    
#ifdef DEBUG_DEVSIM_MEMORY

	NumberOfRanges = 2;
	
	RangesOfDiskFile[0].bank = 0xff;
	RangesOfDiskFile[0].address = 7;	
	RangesOfDiskFile[0].length = 3;
	RangesOfDiskFile[0].fileOffset = 100 + 12;


	RangesOfDiskFile[1].bank = 0xff;
	RangesOfDiskFile[1].address = 90;	
	RangesOfDiskFile[1].length = 1;
	RangesOfDiskFile[1].fileOffset = RangesOfDiskFile[0].fileOffset + RangesOfDiskFile[0].length + 12;

	DeviceSimLog("*** Start of DeviceSimMemory test");
		
	DeviceSimMemory(&longBytes[0],4,0xff,92,0xff); // range 1, 2 bytes in, 4 bytes requested (two not there)
	DeviceSimMemory(&longBytes[0],1,0xff,92,0xff); // range 1, 2 bytes in, 1 byte requested
	DeviceSimMemory(&longBytes[0],1,0xff,7,0xff);  // range 0, 0 bytes in, 1 byte requested
	DeviceSimMemory(&longBytes[0],1,0xff,9,0xff);  // range 0, 3 bytes in, 1 byte requested
	DeviceSimMemory(&longBytes[0],1,0xff,20,0xff); // not in a range
	DeviceSimMemory(&longBytes[0],200,0xff,0,0xff); // encompasses both

	DeviceSimLog("*** End of DeviceSimMemory test");
#endif    
    
    if (errs != 0)
    	DeviceSimError("Errors during DeviceInit");
}


//
//	Returns AUTO-ID gathered from DEVICE.DM file
//
void DeviceSimAutoId(unsigned long *id)
{
    *id = AutoId;
}

//
//	Returns TIME-OF-SAVE (seconds) gathered from DEVICE.DM file
//
void DeviceSimTimeOfSave(unsigned long *id)
{
    *id = TimeOfSave;
}

//
//	Returns TIME-OF-LAST-SESSION (seconds) gathered from DEVICE.DM file
//
void DeviceSimTimeOfLastSession(unsigned long *id)
{
    *id = TimeOfLastSession;
}



//
// Simulates telemetry by looking up range in RangesOfDiskFile[] and returning the
// data for it stored on the PC in DEVICE.DM.
//
int DeviceSimMemory(char *dataDestination, u32 length, u32 bank, u32 address, u32 mask)
{

    u32 blocks, remainder, thisLength,
    	requestedRangeEnd,diskRangeEnd,
    	thisStart, thisEnd, diff; 
    	
    int x, errs, currentBlock, range, 
        fileId, matchCount;
    
    u32 offsetIntoRange, offsetIntoFile;
    
    static char bufr[120];
    char *thisMemoryDestination;
    
    int RangeList[MAX_MATCHES];

    errs = 0;

    for (range = 0, matchCount = 0; (range < NumberOfRanges) && (matchCount < MAX_MATCHES); range++)
    {
        //  Check bank    
        if (bank == RangesOfDiskFile[range].bank)
        {
			// Check for overlap - if the end of this range on disk
			// is less than the start address, OR, if the start of the
			// range on disk is greater than the end address, then
			// there's no overlap.
			
			if (((RangesOfDiskFile[range].address + 
					RangesOfDiskFile[range].length) <= address) ||
					
				(RangesOfDiskFile[range].address  
					 >= (address + length)))	
			{
				continue; 
			}
			else
			{
				// Save this range
            	RangeList[matchCount++] = range;
			}
        }
    }
    
    //
    // Interpret the match count
    //

	
    switch(matchCount)
    {
    
    	case 0: // No matches at all
    	    
   		(void)sprintf(bufr,
   		"\nInconsistent call to DeviceSimMemory B=%lx, Addr=%08lx,Mask=%lx, Len=%ld",
   		 	bank, address, mask, length);
    	    
			DeviceSimError(bufr); 
			return (0);  // Return here - don't continue.   

		case MAX_MATCHES:

   		(void)sprintf(bufr,
   		"\nToo many matches in DeviceSimMemory B=%lx, Addr=%08lx,Mask=%lx, Len=%ld",
   		 	bank, address, mask, length);
			DeviceSimError(bufr); 
			return (0);  // Return here - don't continue.   
		
			
		default: // 1 or more matches for range.			
		
		    // Open file on the PC
			
		    if (-1 == (fileId = open(DEV_MEMORY_FILE, O_RDONLY|O_BINARY, 0)))
		        errs++;
		        
			// Apply each overlapping range's data to final memory image
					        
			for (x = 0; x < matchCount; x++)
			{
				
				range = RangeList[x];
							
				// If requested range starts prior to the start of this range
				// set start to this range's start
				
				if (address < RangesOfDiskFile[range].address)
				{
					thisStart = RangesOfDiskFile[range].address; 
					diff = RangesOfDiskFile[range].address - address;
					thisMemoryDestination = dataDestination + diff; 
					offsetIntoRange = 0;
				}
				else // Addr >= range start address
				{
					thisStart = address; // No address offset
					diff = address - RangesOfDiskFile[range].address;
					thisMemoryDestination = dataDestination;
					offsetIntoRange = diff;
				}	

			 		    	     	    	 
				// If requested range ends after the end of this range
				// set end to this range's end
			    diskRangeEnd = RangesOfDiskFile[range].address +   				
			    					RangesOfDiskFile[range].length;
			    					
				requestedRangeEnd = address + length;
				
				if (diskRangeEnd < requestedRangeEnd)
					thisEnd = diskRangeEnd;
				else	
					thisEnd = requestedRangeEnd;
				
				// Based on start and end determined above, set a length
				
				thisLength = thisEnd - thisStart;					

				// Now set offset into range's data section in the PC file
			    offsetIntoFile = RangesOfDiskFile[range].fileOffset + offsetIntoRange;

			    // Seek to start of range data
			
				if (offsetIntoFile != lseek(fileId, (off_t)offsetIntoFile, SEEK_SET))
			        errs++;
				
			    // The DSP BIOS and CCS can only handle BUFSIZ (256) byte chunks of data 
			
				blocks = thisLength/BUFSIZ;
				remainder = thisLength % BUFSIZ;
			
			    // Do all the full 256-byte blocks
				for (currentBlock = 0; currentBlock < blocks; currentBlock++)
				{
					SLEEP_A_LITTLE;
					
					if (BUFSIZ != read(fileId, thisMemoryDestination, BUFSIZ))
						errs++;
			        thisMemoryDestination += BUFSIZ;   // point to next data area in caller's memory
				}
			
			    // Do any remainder
			
			    if (remainder != 0)
			    {
			        if (remainder != read(fileId, thisMemoryDestination, remainder))
						errs++;
			    }	
			}	
			
			// Close the file
    		close(fileId);
    		
			break;
	
	} // end of switch	
	
    return(1);
} 



//
// Returns waveform data
// Currently, the PWC file that matches the PDD isn't used.
//
void DeviceSimWaveform(char *dataDestination, u32 length)
{
	u32 x;
	for (x = 0; x < length; x++) 
		*(dataDestination++) = 0x88; 
		
	return; 

#ifdef JHGJGHJGJHGJHGJHGJHGJHG
    // Open file on the PC

    if (-1 == (fileId = open(WAVEFORM_FILE, O_RDONLY|O_BINARY, 0)))
        errs++;

    // Seek to start of waveform data

	if (WAVEDATA_START != lseek(fileId, (off_t)WAVEDATA_START, SEEK_SET))
        errs++;

    // The DSP BIOS and CCS can only handle BUFSIZ (256) byte chunks of data 

	blocks = length/BUFSIZ;
	remainder = length % BUFSIZ;

    // Do all the full 256-byte blocks
	for (x = 0; x < blocks; x++)
	{
		if (BUFSIZ != read(fileId, (char *)dataDestination, BUFSIZ))
			errs++;
        dataDestination += BUFSIZ;   // point to next data area in caller's memory
	}

    // Do any remainder

    if (remainder != 0)
    {
        if (remainder != read(fileId, dataDestination, remainder))
			errs++;
    }

    // Close the file

    close(fileId);

    if (0 != errs)
        bsm_EHLock("Can't read waveform file properly");
#endif
        
}


//
// "Error" breakpoint for the PERL script
//
void DeviceSimErrorBreakpoint(void)
{
}

//
// "Successful" breakpoint for the PERL script
//
void DeviceSimCompleteBreakpoint(void)
{
}


//
// Outputs error information before going to breakpoint.
//
void DeviceSimError(char * message)
{
	DeviceSimLog(message);
   	bsm_TNSound(20,10,bsc_TONEHIGH,1);
   	NU_Sleep(50); 	
	DeviceSimErrorBreakpoint();
}


//
// Outputs log information before going to breakpoint.
//

void DeviceSimComplete(char * message)
{
	DeviceSimLog(message);
   	bsm_TNSound(20,20,bsc_TONEHIGH,2);
   	NU_Sleep(200); 	
	DeviceSimCompleteBreakpoint();
}





#ifdef __2490TELEMA__

#ifndef __BRADY__

/***********************************************************************

 FUNCTION:   aim_RetrieveModelAccessCodeA()

 DESCRIPTION:
This function returns the model access code for the current model.

 FUNCTION PARAMETERS:.

***********************************************************************
*/
char aim_RetrieveModelAccessCodeA(void)
{
  switch(AutoId)
  {
	  case AUTO_ID_7273: return ( 0xC3 );
	  case AUTO_ID_7271: return ( 0x4F );
	  case AUTO_ID_7275: return ( 0xCC );  
	  case AUTO_ID_7227: return	( 0x4B );  
	  case AUTO_ID_7229: return ( 0x65 );
	  case AUTO_ID_7231: return ( 0xC6 );        
  }
  
  bsm_EHLock("Unknown GEM device");   
  return 0;
}



tat_status aim_SimulatedSendTelemetryA_DSP(char *p_downlink, int downlinkSize, 
                                      char *p_uplink,   int uplinkSize, 
                                      char timeOut)

{
   char controlByte;
   char hi;
   char lo;
   char bank;
   unsigned int i, j;
   unsigned int record;
   USHORT address;
   ait_Address a;
   char *ptr;
   char modelAccessCode;
   char modelIdCode;
   tat_status status = tac_successful;
   int result;
   
   timeOut = timeOut;

   modelAccessCode = aim_RetrieveModelAccessCodeA();
   //modelIdCode = aim_RetrieveModelIdCodeA();
   modelIdCode = aim_RetrieveModelAccessCodeA(); // Appears to have same value
   
         
   // check for auto id & resume
   if (downlinkSize == 4)
   {
      if (p_downlink[1] == AIC_RESUME_DETECTION)
      {  // resume detection
         i=0;
         p_uplink[i++] = modelIdCode;
         p_uplink[i++] = 0x00;
         p_uplink[i++] = 0x00;
         
#ifndef __BRADY         
         aim_AddCRC(p_uplink, i);
#endif
         
      }
      else
      {  // auto id
         i=0;
         p_uplink[i++] = modelIdCode;
         p_uplink[i++] = 0x00;
         p_uplink[i++] = 0x05;
         
#ifndef __BRADY           
         aim_AddCRC(p_uplink, i);
#endif   
      
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

            
            result = DeviceSimMemory(&p_uplink[j], (u32) controlByte, bank, address, 0xff);

 
            // The address is in the disk file.
            if (result != 0)
            {
               /////memcpy(&p_uplink[j], ptr, controlByte);
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

#ifndef __BRADY
         j = aim_AddCRC(p_uplink, j);
#endif         

         // compared actual uplinksize to expected.
         if (j != uplinkSize)
            status = tac_downlinkCommandFailed; // This just has to be non-successful.

      }
      else
      {
         // actually wrong device
         status = tac_downlinkCommandFailed;  // This just has to be non-successful.
      }

   }

   return(status);
}

#endif // !Brady

#endif // TelemB


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
void  aim_SimulatedSendTelemetryB_DSP(char *p_downlink, int downlinkSize,
                                  char *p_uplink,   int uplinkSize,
                                  bool updateProgress)

{
   char hi;
   char med;
   char lo;
   unsigned int i, j;
   unsigned int record;
   unsigned long address;
   //ait_Address a;
   int retval;
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
     
     // Fill with some data in case of incomplete coverage
     memset(&p_uplink[j], '1'+record, length);
     
	 retval = DeviceSimMemory(&p_uplink[j],length, aic_noBank, address, 0xFF);

     // The address is in a simulated area.
     if (retval != 0)
     {
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





//
// Deletes old and creates new log file on the PC for output from 
// this software.
//

void DeviceSimLogInit(void)
{
	int devLog; 
	
	// Delete old log
	unlink(DEV_LOG_FILE);
	
	// Open/create new log file on PC
	if (-1 == (devLog = open(DEV_LOG_FILE, O_WRONLY|O_BINARY|O_CREAT, 0)))
		DeviceSimError("Can't init log");
		
	(void)close(devLog);
}


//
// Write string and <CR><LF> to log file on PC.
//
void DeviceSimLog(char *messageForPCLog)
{
	int devLogFile;
	int errs = 0;
	
	static char *crLf = "\n";
	int len = strlen(messageForPCLog);
	
	if ( len > BUFSIZ)
		len = BUFSIZ;

	devLogFile = open(DEV_LOG_FILE, O_WRONLY|O_BINARY|O_APPEND, 0);
	
	// Write string
    if (len != write(devLogFile, (const char *)messageForPCLog, len))
			errs++;
		
	// Write CR/LF
    if (strlen(crLf) != write(devLogFile, (const char *)crLf, strlen(crLf)))
			errs++;
			
	(void)close(devLogFile);
	
}


//
// Writes completed 3-part package file to PC
//
#define BLOCK_SIZE BUFSIZ //DSP/BIOS limit for file system!!!

BOOL nwm_Send_Data(void)
{

	long xL, blocks, remainder;
	static char mem[BLOCK_SIZE]; // Don't put on the stack!
	int networkFile;
	long err = 0;

	// Assume for now the current index is the size

	long sizeL;
   	
    /* Update the data file with the asset information and encrypt. */
    fsm_UpdateAssetDataAndCloseFile();

   	NU_Sleep(100);
	uim_ModemWarning(OFF);
   	NU_Sleep(100);	
	uim_ModemStart(ON);
	
	uim_StrobePhoneLeds(ON);
	
	sizeL = fsm_PackedBfrGetIndex(FSV_FILE);	
	
	networkFile = open(PACKAGE_FILE, O_WRONLY|O_BINARY|O_CREAT, 0);
	
	if (networkFile < 0)
		err++;							// error occurred 
	
	if ((off_t)0 != lseek(networkFile, (off_t)0 , SEEK_SET))
		err++;
				
	fsm_PackedBfrSetIndex(FSV_FILE, 0); // Rewind
	
	blocks = sizeL/BLOCK_SIZE;
	remainder = sizeL % BLOCK_SIZE;

	for (xL = 0; xL < blocks; xL++)
	{
        fsm_PackedBfrReadMultipleAt(FSV_FILE, xL*BLOCK_SIZE, mem, BLOCK_SIZE);
		NU_Sleep(5);	
        
		if (BLOCK_SIZE != write(networkFile, (const char *)mem, BLOCK_SIZE))
			err++;
	}
		
    fsm_PackedBfrReadMultipleAt(FSV_FILE, xL*BLOCK_SIZE, mem, remainder);
    if (remainder != write(networkFile, (const char *)mem, remainder))
			err++;

	(void)close(networkFile);

	
	//uim_ModemTransferComplete();
	
	DeviceSimComplete("Done");
	
	return(1);

}

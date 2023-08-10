/*
***********************************************************************

 Copyright (c) Medtronic, Inc. 2001

 MODULE: pdd2cspy

 OWNER: Medtronic

 $Revision$

 $Date$

 $RCSfile$

 DESCRIPTION:
   What this utility does:
   -----------------------
   This utility creates a *.c file which when compiled in with the
   2490A code allows a user to run C-SPY and simulate a session with
   a device and the specific device memory.

   The basic idea:
   ---------------

   1.) The 9790-PDD contains the ranges (address and data) of device memory.
   2.) Convert the PDD (address and data) to the format that is setup in
       the 2490 simulator.
   3.) Run the C-Spy simulator and create a 2490 PDD file.
   4.) Run both the 9790 PDD file and 2490 PDD file through stddmp.exe and 
       compare the results.

   How to use this utility:
   -------------------------
   1.) Given a 9790 PDD file run:

       pdd2cspy xxxx.pdd
  
       The scrolled output is a hex-ascii dump of the pdd broken up into 
       the fields/records of save-to-disk.  This is very helpful if 
       stddmp.exe is bombing on the PDD and you need to see the raw data 
       in a parsed format.

       A file cspy_pdd.c is generated in the current directory.

       A file cspy2pdd.pdd is generated in the current directory.
       This file is the exact binary contents of the input *.pdd file
       up to and including the checksum record.  This allows the macro
       in C-Spy to do a binary memory dump of more data than the actual
       *.pdd file.  Running pdd2cspy xxxx.pdd would remove the unwanted
       binary data following the save-to-disk checksum.  This allows the
       file to then work with the translation utility.

   2.) Copy the cspy_pdd.c file into 2490\aim\.

   3.) In cspy.h enable CSPY.

   4.) In aim_cspy.c enable CSPY_PDD.

   5.) Build the project and run CSPY.

   6.) Use a macro to dump the 2490-PDD info to a PDD file.
       a.) Copy the example.mac at the end of these notes to a file 
	       into a directory.
           When running in C-SPY....
       b.) Select Options/Load Macro, find the macros listed below and select one.
           (the *big* is used for max data situations and takes longer)
       c.) The macro is activated on reset.
       d.) Run C-SPY, break on the CloseSaveToDisk() call in the appropriate
           device-interrogate function, and step over the close-function.
       e.) Select CSPY-reset and the data is being written to a file defined in the macro.
           The resulting file is a PDD file.

   7.) Run the resulting 2490 PDD file generated in #6 through stddmp.exe and compare to
       original 9790 PDD file run through stddmp.exe.


   The basic design:
   -----------------
   The output files:
   cspy2pdd.pdd - this file is opened in the main() and every read that is done 
                  from the user-entered-pdd file is echoed out to this file until
                  and including the checksum bytes. At this point the utility is
                  finished and the files are closed.

                  This is just a cheap and easy way to eacho the data out and
                  use this utility to read a C-SPY memory dump and extract the
                  pdd file.

   cspy_pdd.c - this file is opened by do_cspy.cpp code.  The basic idea is that
                the pdd contains device memory ranges which are addresses and 
                data.  When processing the pdd file and a range is encountered,
                save the range address and data in do_cspy.c/functions. When finished
                reading the pdd file write the ranges addresses and data to
                cspy_pdd.c

   The logic:
   pdd2cspy.cpp's main opens the save-to-disk file and initializes do_cspy.cpp code.
   The main() then calls then reads the pdd file based on the main structures of
   save-to-disk file.  The proper routines are called to process the data as it is
   read.  Some devices may have a feature that others do not. For the most part this
   can be conditional code in the main.

   When adding a new device/application:
   1.) Add the string to SetModelId()(pdd2cspy.cpp).
   2.) Step through the main() and verify what features are used for the new 
       device.
   3.) Run the utility.
   4.) If there are problems look at the raw hex-ascii output.
       Locate where the data starts to be invalid and fix that
       specific function using conditional code for that specific device.
   

Macro file for CSPY:
--------------------
execUserReset ()
{
var filehandle, i, addr, xx, data1, write1;
  {
     xx = __openFile(filehandle,"D:\\dev\\test\\testxx.tst","wb");
     if (xx == 0)
     {
        addr = 0x402885;
        //addr = 0x409627;        start addr of fsv_file + waveform first
                                  // search for fsv_file
        i=0;
        while (i<40000)
        {
          data1 = __readMemoryByte (addr, "MEMORY");
          write1 = __writeFile(filehandle, data1);
          addr = addr + 1;
          i++;
        }
        __closeFile(filehandle);
     }
     else
     {
        message "no open completed";
     }  
  }
}


***********************************************************************
*/




#include "stdafx.h"
#include "process.h" // exit()
#include "stdlib.h"  // atoi()
#include "pdd2cspy.hpp"
#include "do_cspy.hpp"
#include "string.h"

#include "time.h"  // mktime, etc,.


// Globals
FILE *fileHandle = NULL;
FILE *fileHandleCSPY2PDD = NULL;
unsigned long totalCountOfBinaryBytesRead = 0;

// Model ID's
#define MODEL_ID_7227 0x4B     /* Model 7227 */
#define MODEL_ID_7273 0xC3     /* Model 7273 */
#define MODEL_ID_7229 0x65     /* Model 7229 */
#define MODEL_ID_7271 0x4F     /* Model 7271 */
#define MODEL_ID_7272 0xC5     /* Model 7272 (HF) */
#define MODEL_ID_7275 0xCC     /* Model 7275 */
#define MODEL_ID_7231 0xC6     /* Model 7231 */
#define MODEL_ID_7274 0x000201     /* Model 7274 */
#define MODEL_ID_7230 0x000202     /* Model 7230 */
#define MODEL_ID_7277 0x000205     /* Model 7277 */


int  currentModelId = 0;

// Function prototypes
void PrintInfo();
void FileHeader();
void TimeOfLastSession();
void TimeStamp(int numberOfIndentSpaces);
unsigned long  Number(int numberOfIndentSpaces);
void IndentOutput(int numberOfIdentSpaces);
void LVImpedanceData();
void ParameterData();
void DeviceMemory(int numberOfIndentSpaces);
AddressType Address(int numberOfIndentSpaces);
void Range(int numberOfIndentSpaces);
void PatientInformation();
void PatientAlertLogData();
void PatientAlertLogDataRecord(int numberOfIndentSpaces);
void DeviceBuffer(int numberOfIndentSpaces);
void VTVFLogData();
void VTVFEpisodeLogData();
void NSTLogData();
void NSTEpisodeData();
void ModeSwitchLogData();
void EpisodeData();
void RRIntervalData();
void CardiacCompassData();
void CardiacCompassCurrentDayData();
void RRBufferData(int numberOfIndentSpaces);
void DailyLogData();
void WeeklyLogData();
void MostRecentData();
void ClockData();
void EGMWidthTestData();
void CheckSum();
void SetModelId(unsigned char *buffer);
void WaveletTestData();
void TemplateHistoryBufferData();


char inputFile[256];					// 2490G testing. 
unsigned long timeOfSave = 0;			// 2490G testing
unsigned long timeOfLastSession = 0;	// 2490G testing



// The regular fread() with a wrapper to count characters
// and track location in the file.
int myfread(void *ptr, int size, int numberOfObjects, FILE *stream);

int main(int argc, char* argv[])
{

	// currently only accepting the one
	// filename.
	if (argc != 2)
		return 1;

	fileHandle = fopen(argv[1], "rb");
	if (fileHandle == NULL)
	{
		printf("File not found: %s\n",argv[1]);
		return(1);
	}

    // Open the PDD2CSPY file which is just the binary data echoed out.
	// This allows us to do a large memory dump from the 2490 CSPY
	// and extract the pdd file.
	fileHandleCSPY2PDD = fopen("cspy2pdd.pdd", "wb");
	if (fileHandleCSPY2PDD == NULL)
	{
		printf("Can't open cspy2pdd.pdd for writing.\n");
		return(1);
	}


	//**************************************************************************
	// 2490G Testing vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
	//
	// Obtain input file name. Find base name by looking for ".pdd" in name
	// We use a secondary lower case version of the string for finding the extension

	char inputFile_LC[_MAX_PATH]; 
	int x;

    // Fill with terminators

	memset(inputFile_LC,0,256);
	memset(inputFile   ,0,256);

	x = sprintf(inputFile_LC,"%s",argv[1]); // get file name

	_fullpath(inputFile,inputFile_LC, 256); // Create full path to pdd


	// 2490G Testing ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	//**************************************************************************



    // initialize the CSPY code.
	CSPY_Initialize();

	// Start processing the file.
	totalCountOfBinaryBytesRead = 0;
	PrintInfo();
	FileHeader();
	printf("--\n");
	TimeOfLastSession();
	printf("--\n");
	if (currentModelId == MODEL_ID_7277)
	{
		LVImpedanceData();
		printf("--\n");
	}
	ParameterData();
	printf("--\n");
	if (currentModelId == MODEL_ID_7230)
	{
		WaveletTestData();
		TemplateHistoryBufferData();
		printf("--\n");
	}
	if ((currentModelId != MODEL_ID_7227) && (currentModelId != MODEL_ID_7271))
	{
      PatientInformation();
	  printf("--\n");
	}
	PatientAlertLogData();
	printf("--\n");
	VTVFLogData();
	printf("--\n");
	if ((currentModelId == MODEL_ID_7274) || (currentModelId == MODEL_ID_7230) ||
		(currentModelId == MODEL_ID_7277))
	{
	  VTVFEpisodeLogData();
	  printf("--\n");
	}
	NSTLogData();
	printf("--\n");
	if ((currentModelId != MODEL_ID_7227) && (currentModelId != MODEL_ID_7229)
		  && (currentModelId != MODEL_ID_7231) && (currentModelId != MODEL_ID_7274)
		  && (currentModelId != MODEL_ID_7230) && (currentModelId != MODEL_ID_7277))
	{
	  ModeSwitchLogData();
	  printf("--\n");
	}
    
	if ((currentModelId == MODEL_ID_7274) || (currentModelId == MODEL_ID_7230) ||
		(currentModelId == MODEL_ID_7277))
	{
      NSTEpisodeData();
	  printf("--\n");
	}
	else
	{
      EpisodeData();
  	  printf("--\n");
	}
    if ((currentModelId == MODEL_ID_7274) || (currentModelId == MODEL_ID_7277))
	{
	  ModeSwitchLogData();
	  printf("--\n");
	}
	RRIntervalData();
	printf("--\n");
	if ((currentModelId == MODEL_ID_7274) || (currentModelId == MODEL_ID_7230) ||
		(currentModelId == MODEL_ID_7277))
	{
		CardiacCompassData();
	    printf("--\n");
		CardiacCompassCurrentDayData();
	    printf("--\n");
	}
	DailyLogData();
	printf("--\n");
	WeeklyLogData();
	printf("--\n");
	if ((currentModelId == MODEL_ID_7274) || (currentModelId == MODEL_ID_7230) ||
		(currentModelId == MODEL_ID_7277))
	{
		MostRecentData();
		printf("--\n");
	}
	ClockData();
	printf("--\n");
	if ((currentModelId == MODEL_ID_7227) || (currentModelId == MODEL_ID_7229)
		|| (currentModelId == MODEL_ID_7231))
	{
	  EGMWidthTestData();
	  printf("--\n");
	}
	CheckSum();

	fclose(fileHandle);
    fclose(fileHandleCSPY2PDD);

	CSPY_WriteFile();

	return 0;
}

void PrintInfo()
{
	printf("A helpful debug hint:\n");
	printf("Use emacs and open the binary save to disk in hexl-mode.\n");
	printf("This will give an offset of the data or address relative to 0.\n");
	printf("The range listings have a hex offset which can be lined up\n");
	printf("with the emacs listing for debugging.\n\n");
}


void FileHeader()
{
	int i;
	int numberRead;
	int integerToPrint;
	unsigned char buffer[100];
	unsigned char ch;

	// print the <file header>
	printf("File Header:\n");

	// Read the <file type>
	printf("  File type (binary(high byte, low-byte)): \n");
    numberRead = myfread(&buffer[0], sizeof(unsigned char), 1, fileHandle);
	if (numberRead != 1)
	{
		printf("Not enough data.\n");
		exit(1);
	}
	integerToPrint = (int)buffer[0];
	printf("    %.2X ", (const char *)buffer[0]);

    numberRead = myfread(&buffer[0], sizeof(unsigned char), 1, fileHandle);
	if (numberRead != 1)
	{
		printf("Not enough data.\n");
		exit(1);
	}
	integerToPrint = (int)buffer[0];
	printf("%.2X\n", (const char *)buffer[0]);

	// Read the <file id tag>
    printf("  File id tag (binary - 81 bytes): \n");
    numberRead = myfread(&buffer, sizeof(unsigned char), 81, fileHandle);
	if (numberRead != 81)
	{
		printf("Not enough data.\n");
		exit(1);
	}

	// Indent
	printf("   ");

	// Dump the data
	for (i=0; i < 81; i++)
	{
	  integerToPrint = (int)buffer[i];
      printf(" %.2X ", (const char *)buffer[i]);
      if ((((i+1) % 10) == 0) && (i != 0))
	  {
		  printf("\n");
		  printf("   ");
	  }
	}
	printf("\n");

	// Read the <application ID>
	printf("  Application ID (null terminated string): \n");
	printf("    ");
	i = 0;
	do
	{
		// read the data one-by-one
		myfread(&ch, sizeof(unsigned char), 1, fileHandle);
		// dump the binary to ascii-hex value
		// save the string.
		buffer[i] = ch;
		printf("%.2X ",ch);
		i++;
	} while (ch != 0);
	// print the final character - null character
	printf(".....%s\n",buffer);

	// Set Model ID.
    SetModelId(buffer);

	// Save the Data for CSPY.
	CSPY_LogDeviceName(buffer, i);
    
	// Read the <application version>
	printf("  Application version (null terminated string): \n");
	printf("    ");
	i = 0;
	do
	{
		// read the data one-by-one
		myfread(&ch, sizeof(unsigned char), 1, fileHandle);
		// dump the binary to ascii-hex value
		// save the string.
		buffer[i] = ch;
		printf("%.2X ",ch);
		i++;
	} while (ch != 0);
	// print the final character - null character
	printf(".....%s\n",buffer);


	// Read the number of bytes in serial number <n>
	// Read the file id tag
    printf("  Number of bytes in serial number (binary):\n");
	numberRead = myfread(&buffer[0], sizeof(unsigned char), 1, fileHandle);
	if (numberRead != 1)
	{
		printf("Not enough data.\n");
		exit(1);
	}
	integerToPrint = (int)buffer[0];
	printf("    %.2X", (const char *)buffer[0]);
	printf(".....value-base-10= %i\n", buffer[0]);

	// Read the <serial number>
	printf("  Serial number (binary):\n");
	// number of bytes in serial number read above.
	i = buffer[0];
	numberRead = myfread(&buffer, sizeof(unsigned char), i, fileHandle);
	if (numberRead != i)
	{
		printf("Not enough data.\n");
		exit(1);
	}
	printf("    ");
	for (int l = 0; l < i; l++)
	{
		printf("%.2X ", buffer[l]);
	}
	printf("\n");

	// Read the <time of save>
	printf("  Time of save (null terminated string): \n");
	printf("  (format=YYYYmmDDHHMMSS)\n");
	printf("    ");
	i = 0;
	do
	{
		// read the data one-by-one
		myfread(&ch, sizeof(unsigned char), 1, fileHandle);
		// dump the binary to ascii-hex value
		// save the string.
		buffer[i] = ch;
		printf("%.2X ",ch);
		i++;
	} while (ch != 0);
	// print the final character - null character
	printf(".....%s\n",buffer);

	//	
	// For 2490G, get time-of-save in Medtronic time
	//

	time_t timeInMSSeconds;
	time_t medtronicStartSeconds;
	tm aTm;

	aTm.tm_isdst = 0; // No DST
	aTm.tm_wday = 0;
	aTm.tm_yday = 0;

	sscanf((const char *)buffer,"%04d%02d%02d%02d%02d%02d",
		&aTm.tm_year,
		&aTm.tm_mon,
		&aTm.tm_mday,
		&aTm.tm_hour,
		&aTm.tm_min,
		&aTm.tm_sec );

	// Adjust year/month
	aTm.tm_year -= 1900;
	aTm.tm_mon--; 

	// Get time-of-save in seconds since 1/1/1970

	timeInMSSeconds = mktime(&aTm);

	// Set up to get seconds for Medtronic's start time

	aTm.tm_year = 1994 - 1900;
	aTm.tm_mon = 0;		// Jan
	aTm.tm_mday = 1;
	aTm.tm_hour = 0;
	aTm.tm_min = 0;
	aTm.tm_sec = 0;
	aTm.tm_isdst = 0;	// No DST
	aTm.tm_wday = 0;
	aTm.tm_yday = 0;

	medtronicStartSeconds = mktime(&aTm);
	
	// OK - so store away the time-of-save bytes

	timeOfSave = (unsigned long)
					(timeInMSSeconds - medtronicStartSeconds);

}

void TimeOfLastSession()
{
	// From programmer ecm\da1\include\da1tstmp.hpp file 
	/**
		Device epoch in number of days since Julian epoch (Jan 1,4713 BC).
		This number was returned by IDate::julianDate() for Jan 1, 1994.
	*/
	const unsigned long jday_beginDeviceEpoch  = 2449354L;




	long oldPos, newPos;
	char bufr[80];
	char kve[6] = {0x31, 0x0A, 0x31, 0x0A, 0x30, 0x0A };
	unsigned long julian_days, julian_secs;


	// Grab position before time-of-last-session
	oldPos = ftell(fileHandle);

	printf("Time of last session <time stamp>:\n");
    
    // Call the routine to process a <time stamp>
	// pass in the number of spaces to indent.
	TimeStamp(2);

	// Grab new position after time-of-last-session
	newPos  = ftell(fileHandle);
	
	long numBytes = newPos - oldPos;

	// Back up to start of time-of-last-session info
	(void)fseek(fileHandle, oldPos, SEEK_SET);

	// Read it
	(void)fread(bufr, (size_t)numBytes , 1, fileHandle);

	// Set file pointer back to expected position	
	(void)fseek(fileHandle, newPos, SEEK_SET);

	// Now decode. The first 6 bytes should be
	// 0x31, 0x0A, 0x31, 0x0A, 0x30, 0x0A which indicates
	// "known, valid, not empty". If not exactly that, set 
	// timeOfLastSession to 0;

	if (memcmp(bufr,kve, sizeof(kve)) != 0)
	{
		timeOfLastSession = 0;
	}
	else
	{
		sscanf(&bufr[sizeof(kve)],"%d\n%d", &julian_days, &julian_secs);

		// Find days since 1994, not 4713 BC
		julian_days -= jday_beginDeviceEpoch; 

		timeOfLastSession = julian_secs + (julian_days * 24L * 60L * 60L);
	}
}


void TimeStamp(int numberOfIndentSpaces)
{

	// print the number of indent spaces.
	IndentOutput(numberOfIndentSpaces);
	printf("Value known <number>:\n");
	IndentOutput(numberOfIndentSpaces);
	Number(numberOfIndentSpaces);

	// print the number of indent spaces.
	IndentOutput(numberOfIndentSpaces);
	printf("Value valid <number>:\n");
	IndentOutput(numberOfIndentSpaces);
	Number(numberOfIndentSpaces);

	// print the number of indent spaces.
	IndentOutput(numberOfIndentSpaces);
	printf("Value empty <number>:\n");
	IndentOutput(numberOfIndentSpaces);
	Number(numberOfIndentSpaces);

	// print the number of indent spaces.
	IndentOutput(numberOfIndentSpaces);
	printf("Julian day <number>:\n");
	IndentOutput(numberOfIndentSpaces);
	Number(numberOfIndentSpaces);

	// print the number of indent spaces.
	IndentOutput(numberOfIndentSpaces);
	printf("Julian seconds <number>:\n");
	IndentOutput(numberOfIndentSpaces);
	Number(numberOfIndentSpaces);
}

unsigned long Number(int numberOfIndentSpaces)
{
	int i;
	unsigned char ch;
	unsigned char buffer[100];

	// read in the number.
	// print the raw data and the value.
	IndentOutput(numberOfIndentSpaces);
	i = 0;
	do
	{
		// read the data one-by-one
		myfread(&ch, sizeof(unsigned char), 1, fileHandle);
		// dump the binary to ascii-hex value
		// save the string.
		buffer[i] = ch;
		printf("%.2X ",ch);
		i++;
	} while (ch != 0x0A); // the break is hex=0A
	// print the final character - null character
	// remove the 0x0A from the buffer and print the number-string.
	buffer[i-1] = 0x00;
	printf(".....%s\n",buffer);

	// return the value of the number
	return(atoi((const char *)buffer));
}

void IndentOutput(int numberOfIndentSpaces)
{
	for (int i=0; i < numberOfIndentSpaces; i++)
		printf(" ");
}

void LVImpedanceData()
{
	int numberOfIndentSpaces = 2;

	// Print the header.
	printf("LV Impedance data <lv impedance data>:\n");
    
    // Call the routine to process a <time stamp>
	// pass in the number of spaces to indent.
	IndentOutput(numberOfIndentSpaces);
	printf("Time Of LV measurement <time stamp>:\n");
	TimeStamp(numberOfIndentSpaces + 2);

	// Call the routine to process a <number>
	// pass in the number of spaces to indent.
	IndentOutput(numberOfIndentSpaces);
	printf("LV impedance value known <number>:\n");
	IndentOutput(numberOfIndentSpaces);
	Number(numberOfIndentSpaces);

	// Call the routine to process a <number>
	// pass in the number of spaces to indent.
	IndentOutput(numberOfIndentSpaces);
	printf("LV impedance value valid <number>:\n");
	IndentOutput(numberOfIndentSpaces);
	Number(numberOfIndentSpaces);

	// Call the routine to process a <number>
	// pass in the number of spaces to indent.
	IndentOutput(numberOfIndentSpaces);
	printf("LV impedance value empty <number>:\n");
	IndentOutput(numberOfIndentSpaces);
	Number(numberOfIndentSpaces);

	// Call the routine to process a <number>
	// pass in the number of spaces to indent.
	IndentOutput(numberOfIndentSpaces);
	printf("LV impedance <number>:\n");
	IndentOutput(numberOfIndentSpaces);
	Number(numberOfIndentSpaces);
}

void ParameterData()
{
	// Print the header.
	printf("Parameter data <device memory>:\n");
    
    // Call the routine to process a <device memory>
	// pass in the number of spaces to indent.
	DeviceMemory(2);
}

void DeviceMemory(int numberOfIndentSpaces)
{
	unsigned long numberOfRanges;
	unsigned long i;

	// <time of last interrogate>
    IndentOutput(numberOfIndentSpaces);
	printf("Time Of Last Interrogate <time stamp>:\n");
    TimeStamp(numberOfIndentSpaces+2);

	// <number of ranges>
	IndentOutput(numberOfIndentSpaces);
	printf("  Number Of Ranges <number>:\n");
	numberOfRanges = Number(numberOfIndentSpaces+4);

	// <range>
	i = 0;
	while (i < numberOfRanges)
	{
		IndentOutput(numberOfIndentSpaces);
		printf("  Range <range> number = %i:\n", i+1);
		Range(numberOfIndentSpaces+2);
		i++;
	}
}

void Range(int numberOfIndentSpaces)
{
	unsigned char ch;
	unsigned long sizeOfRange;
	unsigned long i;
	AddressType  address;

	// For a reference, print the offset that
	// the range is located at.  In other words,
	// the number of bytes.
	// for debug
	IndentOutput(numberOfIndentSpaces);
	printf("  Location(index into data) = %i (decimal) %X (hex)\n", 
		   totalCountOfBinaryBytesRead, 
		   totalCountOfBinaryBytesRead);


	// <address>
	IndentOutput(numberOfIndentSpaces);
	printf("  Address <address>:\n");
	IndentOutput(numberOfIndentSpaces);
    address = Address(numberOfIndentSpaces+2);

	// <size>
	IndentOutput(numberOfIndentSpaces);
	printf("  Size <number>:\n");
    sizeOfRange = Number(numberOfIndentSpaces+4);

	// <data>
	IndentOutput(numberOfIndentSpaces);
	printf("  Data (binary):\n");
	IndentOutput(numberOfIndentSpaces+4);
	CSPY_OpenRange(address, sizeOfRange);
	for (i = 0; i < sizeOfRange; i++)
	{
		myfread(&ch, sizeof(unsigned char), 1, fileHandle);
		// echo it out in both hex and ASCII
		printf("%.2X ", ch);
		CSPY_LogData(address, &ch, 1);
		address.physicalAddress++;
		if ((((i+1) % 10) == 0) && (i != 0))
		{
		  printf("\n");
		  IndentOutput(numberOfIndentSpaces+4);
		}
	}
	CSPY_CloseRange(address);
	printf("\n");

}


AddressType Address(int numberOfIndentSpaces)
{
	unsigned char ch;
	AddressType   address;

	// <bank> binary
	// TBD - same as next TBD
	IndentOutput(numberOfIndentSpaces-2);
	// TBD - not sure why this has to be pulled over - format.
	printf("Bank (binary byte):\n");
	IndentOutput(numberOfIndentSpaces+4);
    // read the 1-byte
	myfread(&ch, sizeof(unsigned char), 1, fileHandle);
	// echo it out in both hex and ASCII
	printf("%.2X.....%i\n", ch, ch);
    address.bank = ch; 

	// <physical address> in <number> format
	IndentOutput(numberOfIndentSpaces);
	printf("  Physical Address <number>:\n");
	address.physicalAddress = Number(numberOfIndentSpaces+4);

	// <mask> binary
	IndentOutput(numberOfIndentSpaces);
	printf("  Mask (binary byte):\n");
	IndentOutput(numberOfIndentSpaces+4);
    // read the 1-byte
	myfread(&ch, sizeof(unsigned char), 1, fileHandle);
	// echo it out in both hex and ASCII
	printf("%.2X.....%i\n", ch, ch);
    address.mask = ch;

	return(address);

}

int myfread(void *ptr, int size, int numberOfObjects, FILE* stream)
{
	int  value;

	value = fread(ptr, size, numberOfObjects, stream);
	
	totalCountOfBinaryBytesRead = 
		totalCountOfBinaryBytesRead + (size * value);

	// Echo the binary data back out to the "cspy2pdd.pdd" file.
	fwrite(ptr, size, numberOfObjects, fileHandleCSPY2PDD);

	return (value);
}

void PatientInformation()
{
	// Print the header.
	printf("Patient Information <device memory>:\n");
    
    // Call the routine to process a <device memory>
	// pass in the number of spaces to indent.
	DeviceMemory(2);
}

void PatientAlertLogData()
{
	// Print the header.
	printf("Patient Alert Log Data <patient alert log data>:\n");
    
    // Call the routine to process a <patient alter log data>
	// pass in the number of spaces to indent.
	PatientAlertLogDataRecord(2);

}

void PatientAlertLogDataRecord(int numberOfIndentSpaces)
{
	// <entries since last session>
	IndentOutput(numberOfIndentSpaces);
	printf("Entries since last session <number>:\n");
	IndentOutput(numberOfIndentSpaces);
	Number(numberOfIndentSpaces+2);

	// <all data interrogated>
	IndentOutput(numberOfIndentSpaces);
	printf("All data interrogated <number>:\n");
	IndentOutput(numberOfIndentSpaces);
	Number(numberOfIndentSpaces+2);

	// <most recent entry in progress>
	IndentOutput(numberOfIndentSpaces);
	printf("Most recent entry in progress <number>:\n");
	IndentOutput(numberOfIndentSpaces);
	Number(numberOfIndentSpaces+2);

	// <total entries>
	IndentOutput(numberOfIndentSpaces);
	printf("Total Entries <number>:\n");
	IndentOutput(numberOfIndentSpaces);
	Number(numberOfIndentSpaces+2);

	// <device buffer>
	IndentOutput(numberOfIndentSpaces);
	printf("Device buffer <device buffer>:\n");
	IndentOutput(numberOfIndentSpaces);
	DeviceBuffer(numberOfIndentSpaces+2);

	// <time of last clear>
	IndentOutput(numberOfIndentSpaces);
	printf("Time of last clear <time stamp>:\n");
	IndentOutput(numberOfIndentSpaces);
	TimeStamp(numberOfIndentSpaces+2);

	// <device memory>
	IndentOutput(numberOfIndentSpaces);
	printf("Device memory <device memory>:\n");
	IndentOutput(numberOfIndentSpaces);
    DeviceMemory(2);

}


void DeviceBuffer(int numberOfIndentSpaces)
{
	// <data state>
	IndentOutput(numberOfIndentSpaces);
	printf("Data state <number>:\n");
	IndentOutput(numberOfIndentSpaces);
	// TBD - Not sure why this format has to be modified.
	Number(numberOfIndentSpaces);

	// <start address>
	IndentOutput(numberOfIndentSpaces);
	printf("Start address <address>:\n");
	IndentOutput(numberOfIndentSpaces);
	Address(numberOfIndentSpaces+2);

	// <end address>
	IndentOutput(numberOfIndentSpaces);
	printf("End address <address>:\n");
	IndentOutput(numberOfIndentSpaces);
	Address(numberOfIndentSpaces+2);

	// <first address>
	IndentOutput(numberOfIndentSpaces);
	printf("First address <address>:\n");
	IndentOutput(numberOfIndentSpaces);
	Address(numberOfIndentSpaces+2);

	// <last address>
	IndentOutput(numberOfIndentSpaces);
	printf("Last address <address>:\n");
	IndentOutput(numberOfIndentSpaces);
	Address(numberOfIndentSpaces+2);

	// <wrap count>
	IndentOutput(numberOfIndentSpaces);
	printf("Wrap count <number>:\n");
	IndentOutput(numberOfIndentSpaces);
	Number(numberOfIndentSpaces+2);

	// <size of entry>
	IndentOutput(numberOfIndentSpaces);
	printf("Size of entry <number>:\n");
	IndentOutput(numberOfIndentSpaces);
	Number(numberOfIndentSpaces+2);

	// <end of entry offset>
	IndentOutput(numberOfIndentSpaces);
	printf("End of entry offset <number>:\n");
	IndentOutput(numberOfIndentSpaces);
	Number(numberOfIndentSpaces+2);

	// <max data size>
	IndentOutput(numberOfIndentSpaces);
	printf("Max data size <number>:\n");
	IndentOutput(numberOfIndentSpaces);
	Number(numberOfIndentSpaces+2);

}

void	VTVFLogData()
{
	// Print the header.
	printf("VT/VF Log Data <patient alert log data>:\n");
    
    // Call the routine to process a <patient alter log data>
	// pass in the number of spaces to indent.
	PatientAlertLogDataRecord(2);
}

void VTVFEpisodeLogData()
{
	// Print the header.
	printf("VT/VF Episode Data <combination....>:\n");
    
    // Call the routine to process a <patient alter log data>
	// pass in the number of spaces to indent.
	// Print the header.
	printf("  Most Recent Device Buffer <device buffer>:\n");
	DeviceBuffer(4);

	// Call the routine to process a <patient alter log data>
	// pass in the number of spaces to indent.
	// Print the header.
	printf("  Most Recent Available Device Buffer <device buffer>:\n");
	DeviceBuffer(4);

	// Call the routine to process a <patient alter log data>
	// pass in the number of spaces to indent.
	// Print the header.
	printf("  Device Memory <device memory>:\n");
	DeviceMemory(4);
    
}

void	NSTLogData()
{
	// Print the header.
	printf("NST Log Data <patient alert log data>:\n");
    
    // Call the routine to process a <patient alter log data>
	// pass in the number of spaces to indent.
	PatientAlertLogDataRecord(2);
}

void NSTEpisodeData()
{
	// Print the header.
	printf("NST Episode Data <combination....>:\n");
    
    // Call the routine to process a <patient alter log data>
	// pass in the number of spaces to indent.
	// Print the header.
	printf("  Most Recent Device Buffer <device buffer>:\n");
	DeviceBuffer(4);

	// Call the routine to process a <patient alter log data>
	// pass in the number of spaces to indent.
	// Print the header.
	printf("  Most Recent Available Device Buffer <device buffer>:\n");
	DeviceBuffer(4);

	// Call the routine to process a <patient alter log data>
	// pass in the number of spaces to indent.
	// Print the header.
	printf("  Device Memory <device memory>:\n");
	DeviceMemory(4);
}

void	ModeSwitchLogData()
{
	// Print the header.
	printf("Mode Switch Log Data <patient alert log data>:\n");
    
    // Call the routine to process a <patient alter log data>
	// pass in the number of spaces to indent.
	PatientAlertLogDataRecord(2);
}

void	EpisodeData()
{
	// Print the header.
	printf("Episode Data <combination....>:\n");
    
    // Call the routine to process a <patient alter log data>
	// pass in the number of spaces to indent.
	// Print the header.
	printf("  Most Recent Device Buffer <device buffer>:\n");
	DeviceBuffer(4);

	// Call the routine to process a <patient alter log data>
	// pass in the number of spaces to indent.
	// Print the header.
	printf("  Most Recent Available Device Buffer <device buffer>:\n");
	DeviceBuffer(4);

	// Call the routine to process a <patient alter log data>
	// pass in the number of spaces to indent.
	// Print the header.
	printf("  Device Memory <device memory>:\n");
	DeviceMemory(4);
}

void RRIntervalData()
{
	// Print the header.
	printf("RR Interval Data <combination....>:\n");	

	// Print the header.
	printf("  Most Recent Overall State <data state>:\n");
	printf("    Data State <number>:\n");
	Number(6);

	if ((currentModelId != MODEL_ID_7274) && (currentModelId != MODEL_ID_7230) &&
		(currentModelId != MODEL_ID_7277))
	{
		// Print the header.
		printf("  Last Cleared Time <time stamp>:\n");
		TimeStamp(4);
	}

	// Print the header.
	printf("  Current RR Interval Data <combination....>:\n");
	printf("    RR Buffer Data <rr buffer data>:\n");
	RRBufferData(6);
    printf("    RR Device Buffer Data <device buffer>:\n");
	DeviceBuffer(6);

	// Print the header.
	printf("  VT Episode RR Interval Data <combination....>:\n");
	printf("    RR Buffer Data <rr buffer data>:\n");
	RRBufferData(6);
    printf("    RR Device Buffer Data <device buffer>:\n");
	DeviceBuffer(6);

	// Print the header.
	printf("  VF Episode RR Interval Data <combination....>:\n");
	printf("    RR Buffer Data <rr buffer data>:\n");
	RRBufferData(6);
    printf("    RR Device Buffer Data <device buffer>:\n");
	DeviceBuffer(6);

	// Print the header.
	printf("  RR Interval Memory <device memory>:\n");
	DeviceMemory(6);
}

void CardiacCompassData()
{
	// Print the header.
	printf("Cardiac Compass Data <combination....>:\n");

	// <most recent entry in progress>
	printf("  Most Recent Entry In Progress (0 = not in progress) <number>:\n");
	Number(4);

	// <total entries>
	printf("  Total Entries <number>:\n");
	Number(4);

	// <device buffer>
    printf("  Device Buffer <device buffer>:\n");
	DeviceBuffer(4);

	// <time of last clear>
	printf("  Time Of Last Clear <time stamp>:\n");
	TimeStamp(4);

	// <device memory>
	printf("  Device Memory <device memory>:\n");
	DeviceMemory(4);

}


void CardiacCompassCurrentDayData()
{
	// Print the header.
	printf("Cardiac Compass Current Day Data <device memory>:\n");
    
    // Call the routine to process a <device memory>
	// pass in the number of spaces to indent.
	DeviceMemory(2);

}

void RRBufferData(int numberOfIndentSpaces)
{
	int	numberRead;
	unsigned char buffer[100];  // more than what is needed.
	int integerToPrint;

	// <buffer address>
	IndentOutput(numberOfIndentSpaces);
	printf("Buffer address <address>:\n");
	IndentOutput(numberOfIndentSpaces);
	Address(numberOfIndentSpaces);

	// <episode number>
	IndentOutput(numberOfIndentSpaces);
	printf("Episode Number <number>:\n");
	Number(numberOfIndentSpaces+2);	

	if ((currentModelId == MODEL_ID_7274) || (currentModelId == MODEL_ID_7230) ||
		(currentModelId == MODEL_ID_7277))
	{
	  // <clear in progress>
	  IndentOutput(numberOfIndentSpaces);
	  printf("Episode Number Validity (0 = invalid, 1 = valid) <number>:\n");
      Number(numberOfIndentSpaces+2);
	}

	// <time of episode>
	IndentOutput(numberOfIndentSpaces);
	printf("Time Of Episode <time stamp>:\n");
	IndentOutput(numberOfIndentSpaces);
	TimeStamp(numberOfIndentSpaces+2);	

	// <data exists flag>
	IndentOutput(numberOfIndentSpaces);
	printf("Data Exists Flag (0 = no intervals, 1 = one or more intervals) <number>:\n");
	Number(numberOfIndentSpaces+2);	

	// <wrap count>
	IndentOutput(numberOfIndentSpaces);
	printf("Wrap count <number>:\n");
	Number(numberOfIndentSpaces+2);

	// <buffer number> a binary byte
	IndentOutput(numberOfIndentSpaces);
    printf("Buffer Number (binary):\n");
	numberRead = myfread(&buffer[0], sizeof(unsigned char), 1, fileHandle);
	if (numberRead != 1)
	{
		printf("Not enough data.\n");
		exit(1);
	}
	integerToPrint = (int)buffer[0];
	printf("        %.2X", (const char *)buffer[0]);
	printf(".....value-base-10= %i\n", buffer[0]);

	// <since last session>
	IndentOutput(numberOfIndentSpaces);
	printf("Since Last Session (0 = no data since last session, 1 = data since last session) <number>:\n");
	Number(numberOfIndentSpaces+2);	

	if ((currentModelId == MODEL_ID_7274) || (currentModelId == MODEL_ID_7230) ||
		(currentModelId == MODEL_ID_7277))
	{
	  // <clear in progress>
	  IndentOutput(numberOfIndentSpaces);
	  printf("Clear In Progress (0 = False, 1 = True) <number>:\n");
      Number(numberOfIndentSpaces+2);

	  // <time of last clear>
	  IndentOutput(numberOfIndentSpaces);
      printf("Time of last clear <time stamp>:\n");
	  TimeStamp(numberOfIndentSpaces+2);
	}

}

void DailyLogData()
{
	// Print the header.
	printf("Daily Log Data <combination....>:\n");

	// <most recent entry in progress>
	printf("  Most Recent Entry In Progress (0 = not in progress) <number>:\n");
	Number(4);

	// <total entries>
	printf("  Total Entries <number>:\n");
	Number(4);

	// <device buffer>
    printf("  Device Buffer <device buffer>:\n");
	DeviceBuffer(4);

	// <time of last clear>
	printf("  Time Of Last Clear <time stamp>:\n");
	TimeStamp(4);

	// <device memory>
	printf("  Device Memory <device memory>:\n");
	DeviceMemory(4);
}

void WeeklyLogData()
{
	// Print the header.
	printf("Weekly Log Data <combination....>:\n");

	// <most recent entry in progress>
	printf("  Most Recent Entry In Progress (0 = not in progress) <number>:\n");
	Number(4);

	// <total entries>
	printf("  Total Entries <number>:\n");
	Number(4);

	// <device buffer>
    printf("  Device Buffer <device buffer>:\n");
	DeviceBuffer(4);

	// <time of last clear>
	printf("  Time Of Last Clear <time stamp>:\n");
	TimeStamp(4);

	// <device memory>
	printf("  Device Memory <device memory>:\n");
	DeviceMemory(4);
}


void MostRecentData()
{
	// Print the header.
	printf("Most Recent Data <device memory>:\n");
    
    // Call the routine to process a <device memory>
	// pass in the number of spaces to indent.
	DeviceMemory(2);

}

void ClockData()
{
	// Print the header.
	printf("Clock Data <device memory>:\n");

	// <most recent entry in progress>
	printf("  Device Memory:\n");
	DeviceMemory(4);
}


void EGMWidthTestData()
{
	// Print the header.
	printf("EGM Width Test Data <device memory>:\n");
    
    // Call the routine to process a <device memory>
	// pass in the number of spaces to indent.
	DeviceMemory(2);
}
void CheckSum()
{
	unsigned char ch;

	// Print the header.
	printf("Check Sum (binary):\n");
	printf("  Byte 1:\n");
    // read the 1-byte
	myfread(&ch, sizeof(unsigned char), 1, fileHandle);
	// echo it out in both hex and ASCII
	printf("    %X\n", ch);

	// Print the header.
	printf("  Byte 2:\n");
	// read the 1-byte
	myfread(&ch, sizeof(unsigned char), 1, fileHandle);
	// echo it out in both hex and ASCII
	printf("    %X\n", ch);
}

void SetModelId(unsigned char *buffer)
{

    if (0 == strncmp("7227", (const char*)buffer, 4))
      currentModelId = MODEL_ID_7227;
    else if (0 == strncmp("7229", (const char*)buffer, 4))
      currentModelId = MODEL_ID_7229;
    else if (0 == strncmp("7231", (const char*)buffer, 4))
      currentModelId = MODEL_ID_7231;
    else if (0 == strncmp("7271", (const char*)buffer, 4))
      currentModelId = MODEL_ID_7271;
    else if (0 == strncmp("7272", (const char*)buffer, 4))
      currentModelId = MODEL_ID_7272;
    else if (0 == strncmp("7273", (const char*)buffer, 4))
      currentModelId = MODEL_ID_7273;
    else if (0 == strncmp("7275", (const char*)buffer, 4))
      currentModelId = MODEL_ID_7275;
	else if (0 == strncmp("7274", (const char*)buffer, 4))
      currentModelId = MODEL_ID_7274;
	else if (0 == strncmp("7230", (const char*)buffer, 4))
      currentModelId = MODEL_ID_7230;
	else if (0 == strncmp("7277", (const char*)buffer, 4))
      currentModelId = MODEL_ID_7277;
    else
	{
	  printf("Not configured to process device: %s\n", buffer);
	  exit(1);
	}

   return;
}


void WaveletTestData()
{
	// Print the header.
	printf("Wavelet Test Data <device memory>:\n");
    
    // Call the routine to process a <device memory>
	// pass in the number of spaces to indent.
	DeviceMemory(2);

}
		
void TemplateHistoryBufferData()
{
	// Print the header.
	printf("Template History Buffer Data <patient alert log data>:\n");
    
    // Call the routine to process a <patient alter log data>
	// pass in the number of spaces to indent.
	PatientAlertLogDataRecord(2);

}


void InputFileName(char *destination)
{

	(void)strcpy(destination,inputFile);
}

unsigned long AutoIdCodeFileName()
{

	if (0 == currentModelId)
	{
	  printf("Model Id not known.");
	  exit(1);
	}

	return(currentModelId);
}


unsigned long TimeOfSave()
{
	return(timeOfSave);
}


unsigned long TimeOfLastSessionInSeconds()
{
	return(timeOfLastSession);
}




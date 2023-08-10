
#include "stdafx.h"
#include "pdd2cspy.hpp"
#include "process.h" // exit()
#include "stdlib.h"  // atoi()
#include "string.h"
#include "winsock2.h"


/*
 * This file contains the functions to print the data 
 * into a *.c file which can be added to the 2490A CSPY
 * setup and run using CSPY.
 *
 * This allows a 9790 PDD to be converted to a CSPY file
 * which is then used to simulate the device data which
 * is interrogated by the in-home remote monitor.
 *
 * The strategy is to convert the parameter data (ranges)
 * to the CSPY format. Then convert all the buffers that are
 * contained in the *.PDD file.
 *
 * The current process.
 * 1.) Initialize the data arrays which are used to store
 *     the device memory data.  The structure is made up of
 *     banks of memory.
 * 2.) As data is written by the regular pdd processor.
 *     These files routines are called to store the data in
 *     the device memory array.
 * 3.) When the PDD processing has been completed, then
 *     write the data to a *.c which can be used by the 2490A 
 *     and cspy.
 * TBD - the option to create CSPY should be passed in on command line.
 *       it would then get passed to these routines which would
 *       return if not enabled.
 */

typedef struct {
  bool			  inUse;
  AddressType	  address;
  unsigned char*  buffer;
  unsigned long   bufferLength;
  int			  index;
} RangeType;

#define CSPY_MAX_NUMBER_RANGES	1000

RangeType	   rangeTable[CSPY_MAX_NUMBER_RANGES];
int            currentRangeIndex = 0;
unsigned char* currentBufferPointer;

#define CSPY_MAX_DEVICE_MODEL_NAME_LENGTH	20
char deviceModelName[CSPY_MAX_DEVICE_MODEL_NAME_LENGTH];
int  deviceModelNameLength = 0;

// private functions
void CSPY_SortRanges();
void CSPY_SortAddresses();
void CSPY_WriteSimulatorRange();
void CSPY_NumberOfRangesInBank(unsigned char bank, int *startIndex, int *numberOfElements);
void CSPY_WriteRangesToFile();
void CSPY_WriteRangeToFile(int index, bool isNoBank);
void CSPY_WriteModelIdNameToFile();
void CSPY_WriteHeaderToFile();

FILE *CSPY_fileHandle;

FILE *CSPY_binaryHandle;


void CSPY_Initialize()
{
	int i;

	// Initialize the arrays.
    for (i = 0; i < CSPY_MAX_NUMBER_RANGES; i++)
	{
		rangeTable[i].inUse = false;
		rangeTable[i].address.bank = 0xFE;  // figure this is invalid.
		rangeTable[i].address.physicalAddress = 0;
		rangeTable[i].buffer = NULL;
		rangeTable[i].bufferLength = 0;
		rangeTable[i].index = 0;
	}

    currentRangeIndex = 0;

	for (i = 0; i < CSPY_MAX_DEVICE_MODEL_NAME_LENGTH; i++)
	{
		deviceModelName[i] = '\0';
	}

}

void CSPY_LogDeviceName(unsigned char *name, int length)
{
  strncpy(deviceModelName, (const char *)name, length);
  deviceModelNameLength = length;
}

void CSPY_OpenRange(AddressType address, int length)
{
	// Verify we haven't exceeded the limit.
	if (currentRangeIndex >= CSPY_MAX_NUMBER_RANGES)
	{
	  printf("Exceeded range maximum.\n");
	  printf("address.bank: %i, address.physicalAddress: %i\n", 
		     address.bank, address.physicalAddress);
	  exit(1);
	}

	// Allocate the buffer space based on length.
    rangeTable[currentRangeIndex].buffer = (unsigned char*)malloc(length);
	currentBufferPointer = rangeTable[currentRangeIndex].buffer;

	// Enter the info in the rangeTable entry and increase the currentRangeIndex.
	rangeTable[currentRangeIndex].bufferLength = length;
	rangeTable[currentRangeIndex].inUse = true;
	rangeTable[currentRangeIndex].address = address;
	rangeTable[currentRangeIndex].index = currentRangeIndex;

	return;
}


void CSPY_LogData(AddressType address, unsigned char* buffer, unsigned long length)
{
	unsigned long i;
	unsigned char* bufferPointer;

	// write the data to the current range.
	bufferPointer = buffer;
	for (i = 0; i < length; i++)
	{
	  *currentBufferPointer = *buffer;
	  currentBufferPointer++;
	  buffer++;
	}


}

void CSPY_CloseRange(AddressType address)
{
	// This is probably a do nothing but to keep with the open/close.
	currentRangeIndex++;

}


// Sort the ranges based on bank.
// Sort the ranges based on address.
// Create the simulator-range structure which sits at the top of the
//  cspy-dev.c file and tells the user how to map addresses to arrays.
// Write the arrays out in the format required for cspy.
// Note the position of the sorted array will be added to the name of
// the array.
void CSPY_WriteFile()
{
  FILE *fileHandle = NULL;


  // Sort the Ranges.
  // So the simulator will access them in ascending order.
  CSPY_SortRanges();

  // Open the file and write the file header.
  CSPY_fileHandle = fopen("cspy_pdd.c", "w");
  if (CSPY_fileHandle == NULL)
  {
	printf("Could not open: cspy_pdd.c\n");
	exit(1);
  }

  // Open the file and write the file header.

  CSPY_binaryHandle = fopen("device.dm", "wb");

  if (CSPY_binaryHandle == NULL)
  {
	printf("Could not open \"device.dm\"\n");
	exit(1);
  }

  char fullFileName[256]; 
  memset(fullFileName,0,256);

  InputFileName(fullFileName);  
  fwrite(fullFileName,1, 256 ,CSPY_binaryHandle);

  // Write any header info to the file (includes, etc....)
  CSPY_WriteHeaderToFile();

  // Write the model id structure to the *.c file.
  CSPY_WriteModelIdNameToFile();

  // The ranges must be written before the simulatorRange(table).
  // Since the table references the ranges.
  // For each bank of memory, convert the data to ASCII and 
  // write the data out.
  CSPY_WriteRangesToFile();

  // Write the simulator range structure.
  CSPY_WriteSimulatorRange();

  // Close the file.
  fclose(CSPY_fileHandle);
  fclose(CSPY_binaryHandle);

}

// Sort the ranges based on the bank.
// Then with in each bank sort the ranges based on address.
void CSPY_SortRanges()
{
  int pass;
  int i;
  RangeType hold;

  // Use the bubble sort.
  // Sort based on bank.
  for (pass = 1; pass < currentRangeIndex; pass++)
  {
	  for (i = 0; i < currentRangeIndex - 1; i++)
	  {
		if (rangeTable[i].address.bank > rangeTable[i + 1].address.bank)
		{
			hold = rangeTable[i];
            rangeTable[i] = rangeTable[i + 1];
			rangeTable[i + 1] = hold;
		}
	  }
  }

  // Use the bubble sort.
  // Sort based on addresses in same bank.
  for (pass = 1; pass < currentRangeIndex; pass++)
  {
	  for (i = 0; i < currentRangeIndex - 1; i++)
	  {
		if (rangeTable[i].address.bank == rangeTable[i + 1].address.bank)
		{
			if (rangeTable[i].address.physicalAddress > rangeTable[i].address.physicalAddress)
			{
			  hold = rangeTable[i];
              rangeTable[i] = rangeTable[i + 1];
			  rangeTable[i + 1] = hold;
			}
		}
	  }
  }
}


// Create the structure which the simulator uses to find data.
void CSPY_WriteSimulatorRange()
{
	int i;

	// Print the structure header.
    fprintf(CSPY_fileHandle, "ait_Range simulatorRange[] = \n");
	fprintf(CSPY_fileHandle, "{\n");

	// run through and print the noBank's.
    for (i = 0; i < currentRangeIndex; i++)
	{
       if (rangeTable[i].address.bank == 0xFF)
	   {
		   fprintf(CSPY_fileHandle, 
			       "   aic_noBank,                         // R0 - bank\n");
		   fprintf(CSPY_fileHandle,
                   "   0x%.4X,                             // R0 - physicalAddress\n",
				   rangeTable[i].address.physicalAddress);
		   fprintf(CSPY_fileHandle,
                   "   0x%.2X,                               // R0 - mask\n",
				   rangeTable[i].address.mask);
		    fprintf(CSPY_fileHandle,
                   "   sizeof(simulatorDataBank%i),        // R0 - size\n",
				   i);
			fprintf(CSPY_fileHandle,
                   "   simulatorDataBank%i,                // R0 - data\n\n",
				   i);
	   }
	}

	// run through and print the non-noBank's
    for (i = 0; i < currentRangeIndex; i++)
	{
       if (rangeTable[i].address.bank != 0xFF)
	   {
		   fprintf(CSPY_fileHandle, 
			       "   0x%.2X,                               // R0 - bank\n",
				   rangeTable[i].address.bank);
		   fprintf(CSPY_fileHandle,
                   "   0x%.4X,                             // R0 - physicalAddress\n",
				   rangeTable[i].address.physicalAddress);
		   fprintf(CSPY_fileHandle,
                   "   0x%.2X,                               // R0 - mask\n",
				   rangeTable[i].address.mask);
		   fprintf(CSPY_fileHandle,
                   "   sizeof(simulatorDataBank%i),        // R0 - size\n",
				   i);
	  	   fprintf(CSPY_fileHandle,
                   "   simulatorDataBank%i,                // R0 - data\n\n",
				   i);
	   }
	}

	// Print the completion of the structure.
    fprintf(CSPY_fileHandle, "};\n\n\n");

}

// Find the number of ranges in a bank
void CSPY_NumberOfRangesInBank(unsigned char bank, int *startIndex, int *numberOfElements)
{
	bool  firstFound = false;
	int   i;

	// Scan all the elements
	*startIndex = 0;
	*numberOfElements = 0;

	for (i = 0; i < currentRangeIndex; i++)
	{
		if (bank == rangeTable[i].address.bank)
		{
			if (!firstFound)
			{
				firstFound = true;
				*startIndex = i;
			}
            *numberOfElements++;
		}

	}

    return;
}

void CSPY_WriteRangesToFile()
{
	int i;
	unsigned long  aLong;


	aLong = htonl(AutoIdCodeFileName());
	fwrite(&aLong,1, sizeof(unsigned long), CSPY_binaryHandle);

	aLong = htonl((long)currentRangeIndex);
	fwrite(&aLong,1, sizeof(unsigned long), CSPY_binaryHandle);

	aLong = htonl(TimeOfSave());
	fwrite(&aLong,1, sizeof(unsigned long), CSPY_binaryHandle);

	aLong = htonl(TimeOfLastSessionInSeconds());
	fwrite(&aLong,1, sizeof(unsigned long), CSPY_binaryHandle);

	
	// for-each range
	// write a comment-line noting the address.
	// write the array-name
	// write the array converted from binary to ASCII.

	// write the nobank(0xFF) first.
    for (i = 0; i < currentRangeIndex; i++)
	{
       if (rangeTable[i].address.bank == 0xFF)
	     CSPY_WriteRangeToFile(i, true);
	}

	// now process the rest of the ranges up to the noBank.
    for (i = 0; i < currentRangeIndex; i++)
	{
       if (rangeTable[i].address.bank != 0xFF)
         CSPY_WriteRangeToFile(i, false);
	}

}

void CSPY_WriteRangeToFile(int index, bool isNoBank)
{
	unsigned int i;
	int numberOnLineCounter;
	unsigned char *bufferPointer;
	unsigned long bank, addr, mask, length;


	if (isNoBank)
	{
	  fprintf(CSPY_fileHandle, "// Bank: NO BANK, Address: 0x%X, Mask: %X\n", 
			  rangeTable[index].address.physicalAddress,
			  rangeTable[index].address.mask);

	  bank = 0x000000FF;
	}
	else
	{
      fprintf(CSPY_fileHandle, "// Bank: %i, Address: 0x%X, Mask: %X\n", 
	  	      rangeTable[index].address.bank,
			  rangeTable[index].address.physicalAddress,
			  rangeTable[index].address.mask);

	  bank = rangeTable[index].address.bank;

	}

	bank = htonl(bank);
	addr = htonl((long)rangeTable[index].address.physicalAddress);
	mask = htonl((long)rangeTable[index].address.mask);

   fwrite(&bank,1 , sizeof(unsigned long), CSPY_binaryHandle);
   fwrite(&addr,1 , sizeof(unsigned long), CSPY_binaryHandle);
   fwrite(&mask,1 , sizeof(unsigned long), CSPY_binaryHandle);
	
	
	fprintf(CSPY_fileHandle, "unsigned char simulatorDataBank%i[] = \n{\n", index);

	bufferPointer = rangeTable[index].buffer;

	length = htonl((long)rangeTable[index].bufferLength);

	fwrite(&length,1,sizeof(unsigned long), CSPY_binaryHandle);

	numberOnLineCounter = 0;
	for (i = 0; i < rangeTable[index].bufferLength; i++)
	{

	  fwrite((const void *)bufferPointer,1,1, CSPY_binaryHandle);  //2490G Testing

      fprintf(CSPY_fileHandle, "0x%.2X,", *bufferPointer);
	  bufferPointer++;
	  numberOnLineCounter++;
	  if (numberOnLineCounter > 15)
	  {
		  fprintf(CSPY_fileHandle, "\n");
		  numberOnLineCounter = 0;
	  }

	}
	fprintf(CSPY_fileHandle, "\n};\n\n\n");
}

void CSPY_WriteModelIdNameToFile()
{
    fprintf(CSPY_fileHandle, "\n\n");

	// The length of the array is 1 less than the length stored here to 
	// strip off the null terminator.
    fprintf(CSPY_fileHandle, "char simulatorModelIdName[%i] = \"%s\";\n", 
	       deviceModelNameLength - 1, deviceModelName);
    fprintf(CSPY_fileHandle, "int simulatorModelIdNameLength = %i;\n", 
	       deviceModelNameLength - 1);
    fprintf(CSPY_fileHandle, "\n\n");
}


void CSPY_WriteHeaderToFile()
{
    fprintf(CSPY_fileHandle, "\n\n");
	fprintf(CSPY_fileHandle, "// NOTE!!!! This file is auto-generated.\n");
	fprintf(CSPY_fileHandle, "#include \"aim_GEM.h\"\n");
	fprintf(CSPY_fileHandle, "#include \"aim_deviceLog.h\"\n");
    fprintf(CSPY_fileHandle, "\n\n");
}
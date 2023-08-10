/*
************************************************************************
 CRC Calculator for 2490G firmware.

 Copyright (c) Medtronic, Inc. 2004

 OWNER: Medtronic

 $Revision$

 $Date$

 $RCSfile$

 This source code was copied from WinCRC. For WinCRC source code
 see 2490G\WinCRC. The changes made from WinCRC to create this 
 command line version that is specific to the Motorola S-Record 
 format currently used by 2490G are:

 1.) The class InputTranslation was changed to Translation.
     All but the Motorola S-Record logic and what is calls was removed.
	 The write Motorola file was added to write the file and add the
	 new CRC.

 2.) No templates are read or written to put the CRC into a *.c file
     and compile it into the firmware. This logic has been removed.
	 It is in WinCRC.

 Notes on updating this file:
 1.) Before updating any settings in this file, run the WinCRC.exe
     program from the gui with the new settings and verify the
	 new settings work as expected.

 3.) Run this and compare output of WinCRC.exe. Usa an ASCII text
     comparison tool to compare the before and after of Motorola
	 S-Record files.

 Notes on how CRC is done in the 2490G:
 1.) The CRC value is located at the end of the image.

 2.) When the calculation is done for CRC, the *.hex image is
     calculated up to and before the CRC-value-location in the file.
	 Thus it is not included in CRC calculation.

************************************************************************
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Translation.h"
#include "calcCRC.h"


// The following settings were taken from the WinCRC file.
// The original settings in the WinCRC file are shown
// in comments.

// ffff  ; CRC Seed Value
#define  INI_CRC_SEED_VALUE 0xFFFF

// ffff  ; Unused Memory Fill Value
#define  INI_UNUSED_MEMORY_FILL_VALUE 0xFFFF

// 1  ; Input File Format (0:Intel Hex, 1:Motorola S-Rec, 2:ASCII Hex, 3:ASCII Text Box)
#define  INI_INPUT_FILE_FORMAT 1

// 0  ; Reverse Bits (0:Unchecked, 1:Checked)
#define  INI_REVERSE_BITS 0

// 1  ; Compliment CRC (0:Unchecked, 1:Checked)
#define  INI_COMPLIMENT_CRC 1

// 4  ; Algorithm (0:CCITT CRC, 1:X^16+X^15+X^2+1), 2:Checksum, 3:8 bit CRC, 4: 32 bit CRC, 
#define  INI_ALGORITHM 4

// The new hex data is written to this file.
#define  OUTPUT_HEX_FILE  "out.hex"

// The new bin data is written to this file.
#define  OUTPUT_BIN_FILE  "out.bin"

void OnCalc(char *inputFileName, unsigned long min_addr, unsigned long max_addr);
unsigned short reverseBits(unsigned short data);
unsigned long reverseBits32(unsigned long data);
bool getValidAddress(char *, unsigned long *);

int main(int argc, char* argv[])
{
   unsigned long min_addr, max_addr;
   char  inputFileName[300]="\0";

   // If the filename to read is not entered then exit.
   if (argc != 4)
   {
	  printf("Invalid number of arguments entered.\n\n");
	  printf("The command:\n");
	  printf("2490Gcrc a b c\n");
	  printf("a = starting address for crc calculation. Ex.:0x00\n");
	  printf("b = ending address for crc calculation. Ex:0x1EFFFB\n");
	  printf("c = hex input file name including path\n");
	  printf("new hex file is written to out.hex.\n");
	  printf("new bin file is written to out.bin.\n");
	  exit (1);
   }
   else
   {
      strcpy(inputFileName, __argv[3]);

	  if (!getValidAddress(__argv[1], &min_addr))
	  {
		  printf("Invalid starting address entered.\n");
		  exit(1);
	  }

	  if (!getValidAddress(__argv[2], &max_addr))
	  {
		  printf("Invalid ending address entered.\n");
		  exit(1);
	  }
   }

   printf("Calculating CRC for file: %s\n",inputFileName);

   // Calulate the CRC
   OnCalc(inputFileName, min_addr, max_addr);

   return(0);

}

/*
***********************************************************************

 FUNCTION:   onCalc

 DESCRIPTION:
This is the main function that calculates the CRC. It is taken from
the WinCRC dialog code.

***********************************************************************
*/
void OnCalc(char *inputFileName, unsigned long min_addr, unsigned long max_addr)
{
unsigned long   hex_size;
unsigned char   *ptr;
unsigned long   y;
unsigned short  chksum;
unsigned long	crc32;
unsigned short  seed = 0;
unsigned short  fill_char = 0xffff;
unsigned char   *hex_data;
char            *input_file;
Translation     translation;
calcCRC			 crc;
int				 readStatus, writeStatus;
FILE            *fbin=NULL;
unsigned long   crc_line;
	
    // Setup the variables.
    seed = INI_CRC_SEED_VALUE;

	fill_char = INI_UNUSED_MEMORY_FILL_VALUE;

	input_file = inputFileName;

	hex_size = max_addr - min_addr + 1;

	// allocate memory and if an issue exit.
	if ((hex_data = (unsigned char *)malloc (hex_size)) == NULL) 
	{
		printf("** Out of Memory for Hex Data. **\n\n");
		exit(1);
	}
	
	memset (hex_data, (char) (0xff & fill_char), hex_size);

	//
	// Which input format is to be used?
	// Read the file, leave it in a format that crc can be calculated.
	// Save the line where the new crc will be written to.
	//
	switch (INI_INPUT_FILE_FORMAT)
	{
		case 1:
			readStatus = translation.readMotorolaFile (input_file, hex_data, min_addr, max_addr, &crc_line);
			break;

		default:
			printf("Illegal Input File Type.");
			exit(1);
			break;
	}

	if (readStatus < 0)
	{
		printf("Input File Open Error.\n");
		exit(1);
	}
		
	// Calulcate the CRC.
	chksum = seed;

	crc32 = seed;
	crc32 <<= 16;
	crc32 += seed;
		

	for  (ptr=hex_data, y=0; y < hex_size; ++y, ++ptr) 
	{
      switch(INI_ALGORITHM)
      {
         case 0:
            chksum = crc.calculate (chksum, *ptr);
            break;
		 case 1:
            chksum = crc.calculate_X16_X15_X2_1(chksum, (int)(*ptr));
            break;
         case 2:
		    chksum += *ptr;
            break;
         case 3:
            chksum = crc.calcCRC8(chksum, *ptr);
            break;
		 case 4:
			crc32 = crc.calc32(crc32, *ptr);
      }
	}

	if (INI_REVERSE_BITS)
	{
		chksum = reverseBits(chksum);
		crc32 = reverseBits32(crc32);

	}

	if (INI_COMPLIMENT_CRC)
	{
		chksum ^= 0xffff;
		crc32 ^= 0xffffffff;
	}

	// Write out the binary file.
	fbin = fopen(OUTPUT_BIN_FILE, "wb+" );
	if( fbin == NULL )
	{
		printf("Output Binary File Open Error.\n");
		exit(1);
	}
	else {
		ptr=hex_data;	
		fwrite(ptr, 0x4000, hex_size/0x4000, fbin);
		if (hex_size%0x4000) {
			ptr += ((hex_size/0x4000) * 0x4000);
			fwrite(ptr, hex_size%0x4000, 1, fbin);
		}

		fputc((crc32>>24)& 0xff, fbin);
		fputc((crc32>>16)& 0xff, fbin);
		fputc((crc32>>8) & 0xff, fbin);
		fputc((crc32)    & 0xff, fbin);
		fclose (fbin);
	} 
	
	free (hex_data);

	// Tell the user what the CRC is.
	if (INI_ALGORITHM ==  4) {
		printf("CRC value: 0x%08x\n", crc32);
	}
	else {
		printf("CRC value: 0x%04x\n", chksum);
	}

	// Currently only the Motorola-S Record format is supported for Medtronic.
    // For this reason, a forced call to update a copy of the input file with
	// the new crc is done for specific Motorola.
	// Currently, only care about crc-32.
	if (INI_ALGORITHM == 4)
	{
        writeStatus = translation.writeMotorolaFileWithCRC(input_file, OUTPUT_HEX_FILE, 
		                         min_addr, max_addr, crc_line, crc32);
	}

}


unsigned short reverseBits(unsigned short data) 
{
unsigned short a, b, temp;

	for (	a = 0x8000, b = 0x0001, temp = 0;
			b != 0; 
			b <<= 1, a >>= 1)
	{
		temp |= (data & b) ? a:0; 
	}

return temp;
}

unsigned long reverseBits32(unsigned long data) 
{
unsigned long a, b, temp;

	for (	a = 0x80000000, b = 0x00000001, temp = 0;
			b != 0; 
			b <<= 1, a >>= 1)
	{
		temp |= (data & b) ? a:0; 
	}

return temp;
}

bool getValidAddress(char *inputString, unsigned long *outputInt)
{
	bool returnStatus = false;

    if (sscanf(inputString,"%i", outputInt) == 1)
		returnStatus = true;
	else
		returnStatus = false;

	return (returnStatus);
}
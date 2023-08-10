/*
************************************************************************
 Translation.cpp: implementation of the Translation class.

 Copyright (c) Medtronic, Inc. 2004

 OWNER: Medtronic

 $Revision$

 $Date$

 $RCSfile$

  Translation.cpp: implementation of the Translation class.

************************************************************************
*/

#include "string.h"

#include "Translation.h"
#include "stdlib.h"

#define	TRUE 1
#define FALSE 0


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Translation::Translation()
{
}

Translation::~Translation()
{

}

//*******************************************************************************
// fgetline - Read a line from the file.
//*******************************************************************************
int Translation::fgetline(FILE *fptr, char *string, int size )
{
int  c;
int  i=0;

	/*
	** get characters from the file until the maximum number of
	** characters, "size",  for the string "string" has been reached
	** or until EOF has been reached or until the end of line has
	** been reached.
	*/
	while( ( --size > 0 ) && 
		(((c = fgetc(fptr)) != EOF ) && c != '\n' )) {

		if (c == '\\') 
			fgetc (fptr);
		else 
			string[i++] = c;
	}

	/*
	** verify that the string is NULL terminated.
	*/
	string[i] = '\0';

	/*
	** we will only return EOF if EOF is the only character read.
	*/
	if( c == EOF && i == 0 ){
		return( EOF );
	}
	else {

		/*
		** if EOF was found at the end of a line of characters,
		** put the EOF back and return just the number of
		** characters read.  The EOF will be picked up on the
		** next call to fgetline.
		*/
		if( c == EOF ){
			fputc( c, fptr );
			i--;
		}
	
		/*
		** otherwise, return the number of characters read.     
		*/
		return( i );
	}
}

//*******************************************************************************
// readMotorolaFile - Parses a Motorola S-Record
//*******************************************************************************
int Translation::readMotorolaFile(char *input_file, 
				 unsigned char *hex_data, 
				 unsigned long min_addr, 
				 unsigned long max_addr,
				 unsigned long *record_line_number)
{
char            line[520], done = FALSE;
int             data, iInit;
unsigned long   tline_cnt = 0, dline_cnt = 0; /* DEBUG */
unsigned long   byte_cnt = 0;
unsigned long   nextAddressToWrite = min_addr;
unsigned long   address;
unsigned        lsize, x;
unsigned char   *ptr;
FILE *fin;
unsigned long   abs_offset;
int             bytePos;

	if (input_file[0] != '\0') 
	{
		fin = fopen( input_file, "r" );
		if( fin == NULL )
		{
			return(-1);
		}
	}
	else
	{
		return(-1);
	}

	while( (fgetline( fin, line, sizeof( line ) )) != EOF 
			&& !done )
	{

		++tline_cnt;

		/* is it a null line? */
		if(line[0] == '\0') continue;

		/* Intel and Motorola Examples (spaces added for readability)
			Intel Hex 
			----------
			:10 0008 00 46FC27006000003046FC27006000003E E8
			:00 0000 01 FF

			Motorola Equiv. S-Record
			------------------------
			S1 13 0008 46FC27006000003046FC27006000003E E4
			S9 04 0000 FB
		*/

		/* 
		** all S-Records begin with 'S' 
		*/
		if(line[0] != 'S') continue;

		++dline_cnt;

		switch (line[1]) {

			case '1':		/* S1 Record - 2 byte address */
			case '2':		/* S2 Record - 3 byte address */
				/* get the current line's size */
				sscanf (&line[2], "%02x", &lsize);

				/* get the address to start at.*/
				if (line[1] == '1')
				{
					/* 2 bytes = 4 hex chars */
					sscanf (&line[4], "%04x", &address);
				}
				else
				{
					/* 3 bytes = 6 hex chars */
					sscanf (&line[4], "%06x", &address);
				}

				// The first line of hex data is NOT AT THE BEGINNING of the hex file line
				if (( min_addr > address) && (min_addr < (address + lsize)))
				{
					abs_offset = 0;
					bytePos = min_addr - address;
					lsize -= bytePos;
				}
				// Outside of our range.
				else if (( address < min_addr) || (address > max_addr)) 
				{
					continue;
				}
				// A normal full line of hex data.
				else 
				{
					abs_offset = address - min_addr;
					bytePos = 0;
				}

				ptr = &hex_data[abs_offset];				

				if (line[1] == '1')
				{
					iInit = 8;
					/* 1 checksum byte, 2 address bytes included in size aren't written out */
					lsize -= 3;
				}
				else
				{
					iInit = 10;
					/* 1 checksum byte, 3 address bytes included in size aren't written out */
					lsize -= 4;
					}

				for (x = 0; 
					 (x < lsize && !done);
					 bytePos++, x++, ++byte_cnt) {

					if (address + bytePos <= max_addr)
					{
						sscanf (&line[(bytePos * 2) + iInit], "%02x", &data);
					*ptr++ = data;
					}
					
				}
				break;
				
			case '3':		/* S3 Record - 4 byte address */
				/* TBD: unimplemented */
				break;

			/*
			** The current line is specifying EOF
			*/
			case '9':		/* S9 Record */
				done = TRUE;
				break;

		} /* END switch (line[1]) { */
	} /* END while( (fgetline( fin, line, sizeof( line ) )) != EOF 
			&& !done ) */

	fclose(fin);

	*record_line_number = tline_cnt - 1;

return 0;
} /* END readMotorolaFile */


//*******************************************************************************
// writeMotorolaFileWithCRC - writes a new crc value to the Motorola file.
//*******************************************************************************
int Translation::writeMotorolaFileWithCRC(char *input_file,
				 char *output_file,
				 unsigned long min_addr, 
				 unsigned long max_addr,
				 unsigned long record_line_number,
				 unsigned long crc32)
{
char            line[520];
unsigned long   tline_cnt = 0;
int				i, iInit;
unsigned long   address;
unsigned        lsize, x, xLimit;
FILE            *fin, *fout;
int             checksum;
int				lineSize;

    // Verify the input file can be read.
	if (input_file[0] != '\0') 
	{
		fin = fopen( input_file, "r" );
		if( fin == NULL )
		{
			return(-1);
		}
	}
	else
	{
		return(-1);
	}

	// Verify the output file can be written.
    // Verify the input file can be read.
	if (output_file[0] != '\0') 
	{
		fout = fopen( output_file, "wb" );
		if( fout == NULL )
		{
			return(-1);
		}
	}
	else
	{
		return(-1);
	}

    // echo lines from input to output until the line for crc.
	// then insert the new line. Continue echoing out the lines.
	while( (fgetline( fin, line, sizeof( line ) )) != EOF )
	{
		++tline_cnt;

		// if this is the line number for crc then write it out.
        // else continue echoing out the lines.
        if (tline_cnt == record_line_number)
		{
            // START
		  if(line[0] != 'S') 
		  	return -1;

		  switch (line[1]) {

			case '1':		/* S1 Record - 2 byte address */
			case '2':		/* S2 Record - 3 byte address */
				/* get the current line's size */
				sscanf (&line[2], "%02x", &lsize);

				/* get the address to start at.*/
				if (line[1] == '1')
				{
					/* 2 bytes = 4 hex chars */
					sscanf (&line[4], "%04x", &address);
				}
				else
				{
					/* 3 bytes = 6 hex chars */
					sscanf (&line[4], "%06x", &address);
				}


				if (line[1] == '1')
				{
					iInit = 8;
					/* 1 checksum byte, 2 address bytes included in size aren't written out */
					xLimit = lsize - 3;
				}
				else
				{
					iInit = 10;
					/* 1 checksum byte, 3 address bytes included in size aren't written out */
					xLimit = lsize - 4;
				}


				// iInit = starts the processing after the "S1NNAAAAAA" for S2. 
				// iInit=10 for 10 bytes. xLimit is the string of bytes minus the 2 bytes
				// for checksum and 2 bytes for CR and LF.
				for (i = iInit, x = 0; 	/* Starting index depends on # of addr bytes */
					x < xLimit;
					i += 2, x++) 
				{
					if ((address + x) == (max_addr + 1))
					{
						// Overwrite the old CRC.
                        line[i]   = convertIntToUpperChar((crc32>>28) & 0x0f);
						line[i+1] = convertIntToUpperChar((crc32>>24) & 0x0f);
						line[i+2] = convertIntToUpperChar((crc32>>20) & 0x0f);
						line[i+3] = convertIntToUpperChar((crc32>>16) & 0x0f);
						line[i+4] = convertIntToUpperChar((crc32>>12) & 0x0f);
						line[i+5] = convertIntToUpperChar((crc32>>8)  & 0x0f);
						line[i+6] = convertIntToUpperChar((crc32>>4)  & 0x0f);
						line[i+7] = convertIntToUpperChar(crc32       & 0x0f);
						break;
					}
					
				}

				// Definition: checksum -- A char[2] field. 
				// These characters when paired and interpreted as a hexadecimal value 
				// display the least significant byte of the ones complement of the sum 
				// of the byte values represented by the pairs of characters making up 
				// the count, the address, and the data fields.
				checksum = ((convertCharToHex(line[2]) << 4) & 0xf0) | (convertCharToHex(line[3]) & 0x0f);
				lineSize = strlen(line) - 1;
				for (i = 4;
					 i < lineSize - 1;  // Doesn't include  checksum, LF, CR.
					 i += 2) 
				{
                    checksum += (((convertCharToHex(line[i]) << 4) & 0xf0) | (convertCharToHex(line[i+1]) & 0x0f));
					
				}

				// Insert the new checksum in the line and null-terminate.
			    checksum = ~checksum;
				line[lineSize - 1] = convertIntToUpperChar((checksum >> 4) & 0x000f);
				line[lineSize] = convertIntToUpperChar(checksum & 0x000f);
				line[lineSize + 1] = 0x00;
				break;
				
			case '3':		/* S3 Record - 4 byte address */
			case '9':		/* S9 Record */
			default:
				// the read of the Motorola file should have the crc on
				// an S1 or S2 record. Anything else is an error.
				return -1;
				break;


          } // switch statement.
		} // if - correct line number
		
        fprintf(fout, "%s\r\n",line);
		
	} /* END while( (fgetline( fin, line, sizeof( line ) )) != EOF 
			&& !done ) */

	fclose(fin);
	fclose(fout);

return 0;
} /* END writeMotorolaFileWithCRC */

//*******************************************************************************
// convertCharToHex - Given an ASCII representation of a hex-number return the integer.
//*******************************************************************************
unsigned char Translation::convertCharToHex(char value)
{ 
	unsigned char returnValue;

	if ((value >= 0x30) && (value <= 0x39))
       returnValue = value - 0x30;
	else if ((value >= 0x41) && (value <= 0x46))
	   returnValue = value - 0x37;
    else if ((value >= 61) && (value <= 0x66))
	   returnValue = value - 0x57;
	else
	{
		printf("An invalid ASCII-Hex number was input!\n");
		exit(1); // This should never happen!
	}

	return(returnValue);
}


//*******************************************************************************
// convertIntToUpperChar - Given an integer equal to or less than 0x0F, return an 
//                         upper-case ASCII-hex representation.
//*******************************************************************************
unsigned char Translation::convertIntToUpperChar(int value)
{

	unsigned char returnValue;

	if ((value >= 0x00) && (value <= 0x09))
		returnValue = value + 0x30;
    else if ((value >= 0x0A) && (value <= 0x0F))
        returnValue = value + 0x37;
    else
	{
		printf("An invalid number has been passed to convertIntToUpperChar: %i\n", value);
		exit (1); // This should never happen!
	}

	return(returnValue);

}

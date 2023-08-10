// InputTranslation.cpp: implementation of the InputTranslation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WinCRC.h"
#include "InputTranslation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#define	TRUE 1
#define FALSE 0


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

InputTranslation::InputTranslation()
{

}

InputTranslation::~InputTranslation()
{

}


int InputTranslation::readHexFile(char *input_file, 
				 unsigned char *hex_data, 
				 unsigned long min_addr, 
				 unsigned long max_addr)
{
char            new_seg = FALSE;
char            seg_line[200];
char            line[500], done = FALSE;
int             data, bytePos;
unsigned long   tline_cnt = 0, dline_cnt = 0;
unsigned long   byte_cnt = 0;
unsigned long   phys_addr;
unsigned        segment=0;
unsigned        offset;
unsigned        lsize, x;
unsigned long   abs_offset;
unsigned char   *ptr;
FILE            *fin=NULL;

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
			&& !done ){

		++tline_cnt;

		/* is it a null line? */
		if(line[0] == '\0') continue;

		/*
		This is an example of intel hex
		:02000002E68096
		:14000000558BEC83EC0E1EB800008ED856803E33040075287F
		*/

		/* 
		** all intel hex records for load data and address 
		** specification begin with ':' 
		*/
		if(line[0] != ':') continue;

		++dline_cnt;

		switch (line[8]) {

			/*
			** The current line is specifying a new segment 
			** value to use. If the current intel hex file never 
			** specifies a segment, then 0 is used.
			*/
			case '4':
				strcpy (seg_line, line);
				new_seg = TRUE;
				sscanf (&line[9], "%04x", &segment);
				break;

			/*
			** The current line is specifying EOF
			*/
			case '1':
				done = TRUE;
				break;

			/*
			** The current line is specifying a size, offset, and 
			** data to load.
			*/
			case '0':

				/* get the current line's size */
				sscanf (&line[1], "%02x", &lsize);

				/* get the current offset to start at */
				sscanf (&line[3], "%04x", &offset);

				/*
				** calculate the physical address of the start of
				** this block; then verify its within range 
				*/
				phys_addr = (segment << 16) + offset;
				
				// The first line of hex data is NOT AT THE BEGINNING of the hex file line
				if (( min_addr > phys_addr) && (min_addr < (phys_addr + lsize)))
				{
					abs_offset = 0;
					bytePos = min_addr - phys_addr;
					lsize -= bytePos;
				}
				// The line of hex data is outside of our range of interest.
				else if (( phys_addr < min_addr) || (phys_addr > max_addr))
				{
					continue;
				}
				// Full lines of hex data.
				else
				{
					abs_offset = phys_addr - min_addr;
					bytePos = 0;
				}

				ptr = &hex_data[abs_offset];

				for (x = 0; 
					 (x < lsize && !done);
					 bytePos++, x++, ++byte_cnt) {

					if (phys_addr + bytePos <= max_addr)
					{
						sscanf (&line[(bytePos * 2) + 9], "%02x", &data);
						*ptr++ = data;
					}
					
				}
				break;
		} 
	}

	fclose(fin);

return 0;
}

int InputTranslation::fgetline(FILE *fptr, char *string, int size )
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
int InputTranslation::readMotorolaFile(char *input_file, 
				 unsigned char *hex_data, 
				 unsigned long min_addr, 
				 unsigned long max_addr)
{
char            line[500], done = FALSE;
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

return 0;
} /* END readMotorolaFile */


//
//******************************************************************************
// readASCIIFile - Parses a Text File. Input data bytes are listed one per line.
// Returns the number of data bytes read from the input file.
//******************************************************************************
//
int InputTranslation::readHexFile(char *input_file, unsigned char *hex_data, int revBits) 
{
char	line[500], temp[10];
int		data, byteCount = 0; 
char	*ptr, *str1, *str2;
FILE	*fin;

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

	ptr = (char*)hex_data;

	while( (fgetline( fin, line, sizeof( line ) )) != EOF)
	{
		/* is it a null line? */
		if(line[0] == '\0') continue;

		/* Calculate CRC on all characters requested. */
		str1 = line;
		str2 = temp;
		while ((str2 = strtok(str1, " ")) != NULL)
		{
			sscanf(str2,"%02x",&data);
			++byteCount;
			if (revBits)
			{
				data = reverseBits(data);
			}
			*ptr++ = data;
			str1 = NULL;
		}					
	} 

	fclose(fin);

return byteCount;
} 

//
//******************************************************************************
// readHexBox - Parses a Text Box. Contains one line of data.
// Returns the number of data bytes read from the input file.
//******************************************************************************
//
int InputTranslation::readHexBox(char *input_data, unsigned char *hex_data, int revBits) 
{
char	temp[10];
int   data, byteCount = 0; 
char	*ptr, *str1, *str2;

	ptr = (char*)hex_data;

	/* is it a null line? */
	if(input_data[0] == '\0') return 0;

	/* Calculate CRC on all characters requested. */
	str1 = input_data;
	str2 = temp;
	while ((str2 = strtok(str1, " ")) != NULL)
	{
		sscanf(str2,"%02x",&data);
		++byteCount;
		if (revBits)
		{
			data = reverseBits(data);
		}
		*ptr++ = data;
		str1 = NULL;
	}					

return byteCount;
} 

unsigned char InputTranslation::reverseBits(unsigned char data) 
{
unsigned char a, b, temp;

	for (	a = 0x80, b = 0x01, temp = 0;
			b != 0; 
			b <<= 1, a >>= 1)
	{
		temp |= (data & b) ? a:0; 
	}

return temp;
}
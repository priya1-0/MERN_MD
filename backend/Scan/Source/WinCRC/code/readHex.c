#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>

int fgetline(FILE *, char *, int);


#define DEFINED_HERE
#include "readHex.h"
#undef DEFINED_HERE

#define	TRUE 1
#define FALSE 0


void readHexFile(char *input_file, 
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
		fin = fopen( input_file, "r+" );
		if( fin == NULL )
		{
			printf("File Open Error: %s", input_file);
			exit(-1);
		}
	}
	else
	{
		printf("No Input File!");
		exit(-1);
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
}

int fgetline(FILE *fptr, char *string, int size )
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

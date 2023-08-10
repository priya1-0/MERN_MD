typedef unsigned int UINT_32
typedef int INT_32

//******************************************************************
//* Calculates a 32 bit CRC. Uses the standard CRC-32 Polynomial of 
//* x^32+x^26+x^23+x^22+x^16+x^12+x^11+x^10+x^8+x^7+x^5+x^4+x^2+x+1
//******************************************************************


// Global Data
UINT_32  crc32table[512];

// Function Prototypes
void    buildcrc32table();
INT_32 calc_crc32(char *, UINT_32);

void buildcrc32table()
{
	const UINT_32 crcpoly=0xEDB88320;
	UINT_32	i,j;
	UINT_32	r;

	for (i=0;i<512;i++) crc32table[i]=0;

	for (i=0;i<=255;i++)
	{ r = (i << 1);
		for (j=8; j>0; j--)
		{ if ((r & 1)!=0)
			{ r= (r>>1)^crcpoly;
			}
			else { r = (r >>1); 
			}
		}
		crc32table[i]=r;
	}
}

INT_32 calc_crc32(char *buffer, UINT_32 size)
{
	UINT_32	u,h,tcrc;
	UINT_32	i;

	tcrc=0xFFFFFFFF;
	for (i=0;i<=(size-1);i++)
	{ 
		u=buffer[i];         // one byte signextend
		h=crc32table[(unsigned char)(u ^ tcrc)] ^ ((tcrc>>8) & 0x00FFFFFF);
		tcrc=h;
	}
	return -h;
}
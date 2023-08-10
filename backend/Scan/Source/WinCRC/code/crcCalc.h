#ifdef DEFINED_HERE
  	#define SCOPE
#else
  	#define SCOPE extern
#endif

//Functions
SCOPE unsigned short crc_calc (unsigned short, unsigned char); 

#undef SCOPE
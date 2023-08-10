#ifdef DEFINED_HERE
  	#define SCOPE
#else
  	#define SCOPE extern
#endif

// Functions
SCOPE void readHexFile(char *, unsigned char *, unsigned long, unsigned long);

#undef SCOPE
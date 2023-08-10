
#ifndef dumpsave_hpp
#define dumpsave_hpp

typedef struct
{
	unsigned char		bank;
	unsigned char       mask;
	unsigned long       physicalAddress;
} AddressType;



void InputFileName(char *destination);
unsigned long AutoIdCodeFileName(void);
unsigned long TimeOfSave(void);
unsigned long TimeOfLastSessionInSeconds(void);

#endif


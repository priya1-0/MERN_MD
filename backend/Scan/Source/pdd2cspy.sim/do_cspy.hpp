
#ifndef do_cspy_hpp
#define do_cspy_hpp

#include "pdd2cspy.hpp"

// externs
void CSPY_Initialize();
void CSPY_LogDeviceName(unsigned char *name, int length);
void CSPY_OpenRange(AddressType address, int length);
void CSPY_LogData(AddressType address, unsigned char* buffer, unsigned long length);
void CSPY_CloseRange(AddressType address);
void CSPY_WriteFile();

#endif
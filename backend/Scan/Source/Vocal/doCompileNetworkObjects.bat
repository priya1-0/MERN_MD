cls
@echo OFF
set path=c:\ti\c5500\cgtools\bin;..;.\local;..\local;%PATH%
set INCTI=c:\ti\c5500\cgtools\include -ic:\ti\c5500\bios\include
set LIBTI=c:\ti\c5500\cgtools\lib
set DIRTI=c:\ti

REM Save both STDIO and STDERR to file
ECHO. Compiling Network Code, Please Wait...
local\gmake subs  > compileLog.txt 2>&1
exit


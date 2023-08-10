ECHO OFF
REM 
REM  $Revision$
REM
REM  $Date$
REM
REM  $RCSfile$
REM
REM This is a generic command file to
REM call the utility to update the CRC of
REM the 2490G firmware.
REM
REM The arguments:
REM
REM %1 - This is the current path of the files.
REM %2 - This is the hex-file to be processed.
REM 
REM The process:
REM
REM 1.) Check for the file name entered (%1).
REM     If it does not exist then exit.
REM
REM 2.) Delete the out.hex and out.bin files that
REM     were created the last time this was run.
REM
REM 3.) Call the 2490Gcrc.exe utility to calculate
REM     the CRC.
REM
REM 4.) If out.hex or out.bin do not exist then flag
REM     it as an error.
REM
REM 5.) Delete the orignal input hex file, rename
REM     the out.hex to the input file name. Rename
REM     the out.bin to the input file with .bin.
REM

REM If the file does not exist then this batch file
REM will not continue.
IF EXIST %1\%2 (
  REM Delete the old files.
  ECHO -
  ECHO Deleting old out.hex
  DEL out.hex
  ECHO Deleting old out.bin
  DEL out.bin
  ECHO -    

  REM Call the utility to calculate CRC.
  CALL .\2490Gcrc\2490Gcrc.exe 0x00 0x1EFFFB %1\%2
  ECHO - 

  REM Delete the original *.hex file
  REM Copy the new out.hex to the specific filename.
  IF EXIST .\out.hex (
    ECHO Updating file: %1\%2
    DEL %1\%2
    COPY .\out.hex %1\%2
  ) ELSE (
    ECHO Error: Motorola S-Record file out.hex could not be created!
    ECHO Error: There was a problem creating out.hex.    
    GOTO error
  )  

  REM Delete the binary file.
  REM Copy the new out.bin to the specific filename binary file.
  IF EXIST .\out.bin (
     ECHO Updating binary file used for sw. update: %1\%~n2.bin
     COPY .\out.bin %1\%~n2.bin
  ) ELSE (
     ECHO Error: Sw. update file "out.bin" could not be created!
     ECHO Error: There was a problem creating the out.bin file.
     GOTO error
  )

  GOTO success

) ELSE (
  ECHO Error: Input hex file does not exist: %1\%2
  GOTO error
)

REM delete all the files so they are not out out of synch.
:error
ECHO -
ECHO Because of an error hex and bin files are deleted.
ECHO Fix the problem and rebuild to get this batch process to run.
DEL .\out.bin
DEL .\out.hex
DEL %1\%2
DEL %1\%~n2.bin
ECHO - 

:success
REM nothing to do here but exit.

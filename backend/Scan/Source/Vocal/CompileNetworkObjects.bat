
@echo off
REM When the batch file is called from CCS it is called from
REM the project's root directory and not from it's stored
REM location. Check if the Vocal folder exists, if it does traverse
REM to that folder and begin execution.
REM check to see if a folder exists

if  exist  vocal  goto  folderexists
goto  nofolder


:folderexists
rem  go into that folder
cd vocal
SET CCS=1
goto  continue

:nofolder
echo.  the folder vocal does not exist
SET CCS=0
goto  continue




:continue
REM create a new process to compile and wait for it to return
start "Compiling Network Objects" /WAIT doCompileNetworkObjects.bat
REM print the output of the compilation
type compileLog.txt

 
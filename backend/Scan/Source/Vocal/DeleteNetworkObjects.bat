
@echo off
REM When the batch file is called from CCS it is called from
REM the project's root directory and not from it's stored
REM location. Check if the Vocal folder exists, if it does traverse
REM to that folder and begin execution.
REM check to see if a folder exists
REM Note: the '> nul 2>&1' removes output from the command, i.e. not sent to
REM       STDIN or STDERR

if  exist  vocal  goto  folderexists
goto  nofolder


:folderexists
rem  go into that folder
cd vocal
SET CCS=1
goto  objects

:nofolder
echo.  the folder vocal does not exist
SET CCS=0
goto  objects

REM @echo on

:objects
if not exist objects goto work
if not exist objects\csc goto customer
cd objects\csc
erase /q /f itel.*   > nul 2>&1
cd..
cd..

:customer
if not exist objects goto work
if not exist objects\customer goto dev
cd objects\customer
erase /q /f cx077a.*   > nul 2>&1
erase /q /f netdump.*   > nul 2>&1
cd..
cd..

:dev
if not exist objects goto work
if not exist objects\dev goto ip
cd objects\dev
erase /q /f dev.*   > nul 2>&1
erase /q /f devcmd.*   > nul 2>&1
erase /q /f devmdm.*   > nul 2>&1
erase /q /f devparam.* > nul 2>&1
erase /q /f iface.*    > nul 2>&1
erase /q /f mdmcmd.*   > nul 2>&1
cd..
cd..

:ip
if not exist objects goto work
if not exist objects\ip goto lansend
cd objects\ip
erase /q /f domain.*   > nul 2>&1
erase /q /f domhdr.*   > nul 2>&1
erase /q /f icmp.*     > nul 2>&1
erase /q /f icmpcmd.*  > nul 2>&1
erase /q /f icmpdump.* > nul 2>&1
erase /q /f icmphdr.*  > nul 2>&1
erase /q /f icmpmsg.*  > nul 2>&1
erase /q /f ip.*       > nul 2>&1
erase /q /f ipcmd.*    > nul 2>&1
erase /q /f ipdump.*   > nul 2>&1
erase /q /f iphdr.*    > nul 2>&1
erase /q /f iproute.*  > nul 2>&1
erase /q /f ipsock.*   > nul 2>&1
erase /q /f tcpcmd.*   > nul 2>&1
erase /q /f tcpdump.*  > nul 2>&1
erase /q /f tcphdr.*   > nul 2>&1
erase /q /f tcpin.*    > nul 2>&1
erase /q /f tcpmisc.*  > nul 2>&1
erase /q /f tcpout.*   > nul 2>&1
erase /q /f tcpsock.*  > nul 2>&1
erase /q /f tcpsubr.*  > nul 2>&1
erase /q /f tcptimer.* > nul 2>&1
erase /q /f tcpuser.*  > nul 2>&1
erase /q /f udp.*      > nul 2>&1
erase /q /f udpcmd.*   > nul 2>&1
erase /q /f udpdump.*  > nul 2>&1
erase /q /f udphdr.*   > nul 2>&1
erase /q /f udpsock.*  > nul 2>&1
cd..
cd..

:lansend
if not exist objects goto work
if not exist objects\lansend goto net
cd objects\lansend
erase /q /f account.*  > nul 2>&1
erase /q /f commands.* > nul 2>&1
erase /q /f config.*   > nul 2>&1
erase /q /f main.*     > nul 2>&1
erase /q /f debug.*     > nul 2>&1
erase /q /f test.*     > nul 2>&1
erase /q /f quick.*    > nul 2>&1
erase /q /f version.*  > nul 2>&1
erase /q /f view.*     > nul 2>&1
cd..
cd..

:net
if not exist objects goto work
if not exist objects\net goto support
cd objects\net
erase /q /f af.*       > nul 2>&1
erase /q /f locsock.*  > nul 2>&1
erase /q /f net.*  > nul 2>&1
erase /q /f netuser.*  > nul 2>&1
erase /q /f route.*    > nul 2>&1
erase /q /f sockcmd.*  > nul 2>&1
erase /q /f socket.*   > nul 2>&1
erase /q /f sockuser.* > nul 2>&1
erase /q /f sockutil.* > nul 2>&1
cd..
cd..

:support
if not exist objects goto work
if not exist objects\support goto sys
cd objects\support
erase /q /f network.* > nul 2>&1
erase /q /f print.*  > nul 2>&1
erase /q /f serial.*    > nul 2>&1
erase /q /f support.*  > nul 2>&1
erase /q /f time.*   > nul 2>&1
cd..
cd..

:sys
if not exist objects goto work
if not exist objects\sys goto term
cd objects\sys
erase /q /f alloc.* > nul 2>&1
erase /q /f cmdparse.* > nul 2>&1
erase /q /f display.*  > nul 2>&1
erase /q /f files.*    > nul 2>&1
erase /q /f filesys.*  > nul 2>&1
erase /q /f getopt.*   > nul 2>&1
erase /q /f intr.*     > nul 2>&1
erase /q /f kernel.*   > nul 2>&1
erase /q /f ksubr.*    > nul 2>&1
erase /q /f mbuf.*     > nul 2>&1
erase /q /f misc.*     > nul 2>&1
erase /q /f pathname.* > nul 2>&1
erase /q /f serial.*  > nul 2>&1
erase /q /f session.*  > nul 2>&1
erase /q /f stdio.*    > nul 2>&1
erase /q /f string.*   > nul 2>&1
erase /q /f sys.*   > nul 2>&1
erase /q /f ti.*       > nul 2>&1
erase /q /f timer.*    > nul 2>&1
erase /q /f ttydrvr.*  > nul 2>&1
cd..
cd..

:term
if not exist objects goto work
if not exist objects\term goto trace
cd objects\term
erase /q /f chat.*     > nul 2>&1
erase /q /f decide.*   > nul 2>&1
erase /q /f shell.*    > nul 2>&1
erase /q /f term.*    > nul 2>&1
cd..
cd..

:trace
if not exist objects goto work
if not exist objects\trace goto utils
cd objects\trace
erase /q /f trace.*    > nul 2>&1
cd..
cd..

:utils
if not exist objects goto work
if not exist objects\utils goto wan
cd objects\utils
erase /q /f httpcli.*  > nul 2>&1
erase /q /f ping.*     > nul 2>&1
erase /q /f utils.*     > nul 2>&1
cd..
cd..

:wan
if not exist objects goto work
if not exist objects\wan goto work
cd objects\wan
erase /q /f md5c.*     > nul 2>&1
erase /q /f ppp.*      > nul 2>&1
erase /q /f pppchap.*  > nul 2>&1
erase /q /f pppcmd.*   > nul 2>&1
erase /q /f pppdump.*  > nul 2>&1
erase /q /f pppfsm.*   > nul 2>&1
erase /q /f pppipcp.*  > nul 2>&1
erase /q /f ppplcp.*   > nul 2>&1
erase /q /f ppppap.*   > nul 2>&1
erase /q /f slhc.*     > nul 2>&1
erase /q /f slhcdump.* > nul 2>&1
erase /q /f wan.* > nul 2>&1
cd..
cd..

:work
if not exist work goto end
erase /q /f /s work > nul 2>&1
rd    /q    /s work > nul 2>&1

:end

@echo off
REM Don't pause if we detect we were called by CCS
if "%CCS%"=="0" pause



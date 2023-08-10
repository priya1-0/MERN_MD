## ######################################################################### ##
##
## root
##
## ######################################################################### ##

## ######################################################################### ##

#
# ARCH contains the segment architecture files.
# CTL  contains the linker response file.
#

OBJ = objects/
WORK = work/
ARCH = arch/
CTL = arch/
MDM = mdm/
INCLUDE_DIR = include/
LINKSRC = $(CTL)mst_link.src
LINKRSP = $(CTL)mst_link.rsp
OPTIONS = $(INCLUDE_DIR)options.h
RECONFIG_FILE = $(INCLUDE_DIR)reconfig.h
LOCAL = local/
PROFILE =

# ########################################################################### #
#
# Include automatically generated makefile
#

-include makefile.lst

#DO_BUILD_LINUX = #Uncomment this line for source code release processing after setting configuration

# ########################################################################### #
#
# Default target
#
.PHONY:		all

all:		link

## ######################################################################### ##
#
# Negate compiler symbols when build a PC webserver
#

# ########################################################################### #
#
# Per arch setup for compiling
#

# WARNING if you're wondering why you have DO_BUILD_LINUX set in options.h
# yet for some reason it isn't seen here, it's because makefile.lst hasn't been
# rebuilt yet.  Unfortunately, you need perl for that, so you'll have to edit
# makefile.lst and add DO_BUILD_LINUX to bootstrap the make process.

PERL = perlb

# ########################################################################### #
#
# Customer specific targets
#

# ########################################################################### #
#
# Setup source subdirectories and architecture file list
#
REMAKE_MAKEFILE_LST = $(PERL) $(LOCAL)makelist.prl $(OPTIONS) $(LINKRSP) makefile.lst

REMAKE_LINKRSP = echo not rebuilding $(LINKRSP)

makefile.lst:	$(OPTIONS) $(RECONFIG_FILE) $(LINKRSP)
				$(REMAKE_MAKEFILE_LST)
#				@del $(LINKRSP)
#				gmake $(LINKRSP)

# ########################################################################### #
#
# Setup linker options
#

MATHLIB =

# ########################################################################### #
#
# Build source subdirectories (MODLIST defined in makefile.lst)
#

.PHONY:		subs *.sub

subs:		$(foreach module, $(MODLIST), $(module).sub)

%.sub:
		@echo [Processing $*]
		@$(subst /,\,if not exist $(OBJ)$*/nul mkdir $(OBJ)$*)
		@$(subst /,\,if not exist $(WORK)$*/nul mkdir $(WORK)$*)
		@$(MAKE) -s -C$*

linkdir:
		if not exist $(OBJ)/nul mkdir $(OBJ)
workdir:
		if not exist $(WORK)/nul mkdir $(WORK)

# ########################################################################### #
#
# Rebuild data files
#

.PHONY:		datalist
.PHONY:		xref
.PHONY:		hfiles

data: datalist xref hfiles offsets ataoffs

datalist:
			@echo "Building databld.h (dataproc.prl)"
			@$(PERL) $(LOCAL)dataproc.prl data/databld.h data/*.src

xref:
			@echo "Building xref.cat (finddata.prl)"
ifeq ($(OS),Windows_NT)
			@perl560 $(LOCAL)finddata.prl ./
			@echo .
else
			@start /w $(PERL) $(LOCAL)finddata.prl ./
endif

hfiles:
			@echo "Building all data .h files (mkdata.prl)"
			@$(PERL) $(LOCAL)mkdata.prl data/auto sys data/sys.src
			@$(PERL) $(LOCAL)mkdata.prl data/auto cmn data/cmn.src
			@$(PERL) $(LOCAL)mkdata.prl data/auto mod data/mod.src
			@$(PERL) $(LOCAL)mkdata.prl data/auto ph1 data/ph1.src
			@$(PERL) $(LOCAL)mkdata.prl data/auto lsd data/lsd.src
			@$(PERL) $(LOCAL)mkdata.prl data/auto v32 data/v32.src
			@$(PERL) $(LOCAL)mkdata.prl data/auto fax data/fax.src
			@$(PERL) $(LOCAL)mkdata.prl data/auto ph2 data/ph2.src
			@$(PERL) $(LOCAL)mkdata.prl data/auto v34 data/v34.src
			@$(PERL) $(LOCAL)mkdata.prl data/auto user data/user.src
			@$(PERL) $(LOCAL)mkdata.prl data/auto tel data/tel.src

			@echo "Building weak.cat (weaklst.prl)"
			@$(PERL) $(LOCAL)weaklst.prl
			@echo gmake data done.
			
# ########################################################################### #
# 
.PHONY:		offsets

offsets:
			@echo [Resolving structure offsets]
			@cl55 -i. -i$(INCTI) -DBUILDING_OFFSETS -c -q -k -ss -ml -g -fsdata -frdata data/data.c
			@$(PERL) $(LOCAL)\ti54x\tioffs_s.prl data/data.asm
#			@rm data.asm data.obj > nul

# ########################################################################### #
#
#.PHONY:		ataoffs

ataoffs:

# ########################################################################### #
#
# Rebuild makefile dependencies
#

.PHONY:		depend *.dep

#depend:		$(foreach module, $(MODLIST), $(module).dep)

depend: dependall headerall

%.dep:
			$(MAKE) -C$* depend

dependall:
			$(PERL) $(LOCAL)makedep.prl $(LINKRSP) */makefile

.PHONY:		headerall *.hed

headerall: $(foreach module, $(MODLIST), $(module).hed)

%.hed:
			$(MAKE) -C$* headers

# ########################################################################### #
#
# Freshen all file dates
#

.PHONY:		touch

touch:
			@$(PERL) $(LOCAL)touch.prl $(foreach module, $(MODLIST), $(module)/*.*)

.PHONY:		objtouch

objtouch:
			$(PERL) $(LOCAL)touch.prl link/*/*.obj
			$(PERL) $(LOCAL)touch.prl arch\mst_link.rsp makefile.lst
			$(PERL) $(LOCAL)touch.prl */makefile

# ########################################################################### #
#
# Prepare object files for compare
#

.PHONY:		objlist

objlist:
			$(PERL) $(LOCAL)ti54x/tilst.prl link/*/*.lst

# ########################################################################### #
#
# rebuild symlist file
#

.PHONY:		symbols

symbols:
ifeq ($(OS),Windows_NT)
			@perl560 $(LOCAL)makesyml.prl ./
else
			@echo Building symauto.h
			@start /w perlb $(LOCAL)makesyml.prl ./
endif
			@copy makesym.tmp symbol\symauto.h > nul
			@del makesym.tmp
			@echo done

# ########################################################################### #
#
# Link the code
#

.PHONY:		link

FLAG_LIST = $(foreach mod, $(MODLIST), $(OBJ)$(mod)/flag)

# ########################################################################### #
#
# Build linker file list
#

$(LINKRSP): $(LINKSRC) $(OPTIONS)
			$(REMAKE_LINKRSP)

# ########################################################################### #
#
# TI DSP Support
#

# ######################################
LINKCMD = $(CTL)t55_link.cmd
LINKCTL = $(CTL)t55_link.ctl
LINKLIST = $(LINKCTL)
LINKINC = -I$(DIRTI)\c5500\cgtools\lib -I$(DIRTI)\c5500\bios\lib -I$(DIRTI)\c5500\rtdx\lib

LINKLIST += dspbios\plxcfg.cmd

TILINK = lnk55
TI_LFLAGS =

link:		timdm.out
$(mdm)timdm.out: $(FLAG_LIST) $(LINKCMD)
			@echo Linking...
			@$(PERL) $(LOCAL)linkrsp.prl -cmd -ordered -o $(LINKCTL) $(LINKCMD)
			@cpp0.exe -P -C $(LINKCTL) > tempfile.tmp
			@$(subst /,\,copy tempfile.tmp $(LINKCTL))
			@del tempfile.tmp
			@$(TILINK) -w -wr -c -q -a -otimdm.out -mtimdm.map -x $(LINKINC) -f 0h $(LINKLIST)
			-@$(LOCAL)ti54x\tisym55.exe timdm
			@$(PERL) $(LOCAL)ti54x\tisym.prl timdm.$$ym timdm.sym

# ########################################################################### #
#
# ATA Support Targets
#

# ######################################

# ######################################

# ######################################

# ######################################

ATAROM = atarom/

ATA = local/ata.exe

.PHONY:		atabin

# Runtime code image
atabin:
			gmake subs all
			@echo 0x0000, > atarom\atacode0.dat
			@echo 0x0000, > atarom\atacode1.dat
			@echo 0x0000, > atarom\atacode2.dat
			@echo 0x0000, > atarom\atacode3.dat
			@echo 0x0000, > atarom\atacode4.dat
			@echo 0x0000, > atarom\atacode5.dat
			@echo 0x0000, > atarom\atacode6.dat
			@echo 0x0000, > atarom\atacode7.dat
			@echo 0x0000, > atarom\atacode8.dat
			@echo 0x0000, > atarom\atacode9.dat
			@echo 0x0000, > atarom\atacode10.dat
			@echo 0x0000, > atarom\atacode11.dat
			@echo 0x0000, > atarom\atacode12.dat
			@echo 0x0000, > atarom\atacode13.dat
			@echo 0x0000, > atarom\atacode14.dat
			@echo 0x0000, > atarom\atacode15.dat
			@cpp0.exe -P $(ATAROM)ata.fls > $(ATAROM)ata.rsp
			@hex55 $(ATAROM)ata.rsp
			@$(PERL) $(LOCAL)ti54x/tihex2bin.prl <$(ATAROM)atacode.hex >$(ATAROM)atacode.bin
			@$(PERL) $(LOCAL)ti54x/tihex2dat.prl $(ATAROM)atacode.hex
			@$(subst /,\,copy $(ATAROM)atacode.ece $(ATAROM)$(VOIPCODE).ece)

# ######################################

# ######################################

# ########################################################################### #
#
# Blackfin Server Support Targets
#

# ########################################################################### #
#
# Video Server Support Targets
#

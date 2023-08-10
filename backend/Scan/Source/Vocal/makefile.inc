## ######################################################################### ##
##
## Common include file
##
## ######################################################################### ##

-include ../makefile.lst

## ######################################################################### ##
#
# Negate compiler symbols when build a PC webserver
#

## ######################################################################### ##

PERL = perlb

PROFILE =

## ######################################################################### ##

LOCALDEF = -D$(subst /,,$(MOD))_$(subst @,a,$(subst !,b,$(basename $<)))_c
MODDEF = -D$(subst /,,$(MOD))_module

ASM = asm55
CC = cl55
AFLAGS =
OPTFLAGS = -o3
ORIGOPTFLAGS := $(OPTFLAGS)
#INCTI = -i$(DIRTI)\c5500\cgtools\include -i$(DIRTI)\c5500\bios\include
INCTI = -i$(DIRTI)\c5500\cgtools\include -i..\..\cslc5500\include -i$(DIRTI)\c5500\bios\include
# miscellaneous warnings (DO NOT suppress these):
# 112 - statement is unreachable
# 145 - initializer type conflict
# 169 - type conversion
# 172 - address generation obviously outside of array bounds
# 179 - variable declared but never referenced
# 515 - pointer type conversion
# 551 - variable used before initialization
# 994 - missing return statement
#OTHER_WARNINGS = -pds112 -pds145 -pds169 -pds172 -pds179 -pds515 -pds551 -pds994

# required warnings - these cause compile fail:
# 225 - implicit function declaration
REQUIRED_WARNINGS = -pdse225

# suppressed warnings:
#  69 - integer conversion resulted in change of sign
# 174 - previously extern declared thing redeclared static
# 190 - enumerated type mixed with another type
# 552 - variable set but never used
WARNING_FLAGS = -pdv -pden -pds69 -pds174 -pds190 -pds552 $(REQUIRED_WARNINGS)

#CFLAGS = -i.. -i$(INCTI) -c -q -k -al -mr $(OPTFLAGS) $(WARNING_FLAGS)
#CFLAGS = -i.. -i$(INCTI) -c -q -k -al  $(OPTFLAGS) $(WARNING_FLAGS) -g

# for xref use -ax (but not with DSPC)
#CFLAGS  = -i.. -i$(INCTI) -ma -c -q -k -al -ax $(OPTFLAGS) $(WARNING_FLAGS) -v5502:1
CFLAGS  = -i.. -i$(INCTI) -ma -c -q -k -al $(OPTFLAGS) $(WARNING_FLAGS) -v5502:1
# += is used since DEFINES may be passed in to process "gmake ataboot" in root makefile
DEFINES += -DCHIP_5502

CFLAGS += -ml

## ######################################################################### ##
## Various gcc based compilers

## This first DO_COMPILER_GCC block is for generic gcc.
## These options will be overridden by architecture specific blocks below.

## ######################################################################### ##

ifndef ROOT_DIR
ROOT_DIR = ../
endif # ROOT_DIR

#OBJ = $(ROOT_DIR)link/
OBJ = ../objects/
PP = ../pp/

WORK = ../work/
SRC = ../
ARCH = ../arch/
CTL = ../arch/
INCLUDE_DIR = ../include/
LINKSRC = $(CTL)mst_link.src
LINKRSP = $(CTL)mst_link.rsp
OPTIONS = $(INCLUDE_DIR)options.h
LOCAL = ../local/

.path.c = $(SRC)$(MOD)
.path.obj = $(OBJ)$(MOD)
.path.pp = $(PP)$(MOD)

# ########################################################################### #
#
# Default rules
#

%.obj:
	$(if $(filter-out $(ORIGOPTFLAGS),$(OPTFLAGS)),@echo CHANGING OPTIMIZATIONS ($(OPTFLAGS)),)
	@echo $(MOD)$<
	@$(PERL) $(LOCAL)pp1acode.prl -w $< $(WORK)$(MOD)$<
	@$(CC) -i.. $(INCTI) $(DEFINES) $(LOCALDEF) $(MODDEF) -ppl -ppo -qq $(WORK)$(MOD)$<
	@$(PERL) $(LOCAL)ti54x\pp2ti_s.prl $(WORK)$(MOD)$(basename $<).pp $(WORK)$(MOD)$(basename $<).pp2
	@$(CC) $(CFLAGS) $(DEFINES) -fr$(OBJ)$(MOD) -fs$(WORK)$(MOD) $(WORK)$(MOD)$(basename $<).pp2
	@$(if $(filter-out $(ORIGOPTFLAGS),$(OPTFLAGS)),@echo REENABLING DEFAULT OPTIMIZATIONS ($(ORIGOPTFLAGS)),)
	@$(subst /,\,if exist $(WORK)$(MOD)$(basename $<).pp del $(WORK)$(MOD)$(basename $<).pp > nul)
	@$(subst /,\,if exist $(WORK)$(MOD)$(basename $<).c del $(WORK)$(MOD)$(basename $<).c > nul)

%.o:
	$(if $(filter-out $(ORIGOPTFLAGS),$(OPTFLAGS)),@echo CHANGING OPTIMIZATIONS ($(OPTFLAGS)),)
	@echo $(MOD)$<
	@$(PERL) $(LOCAL)pp1acode.prl -w $< $(WORK)$(MOD)$<
	$(CC) -i.. $(INCTI) $(DEFINES) $(LOCALDEF) $(MODDEF) -ppo -qq $(WORK)$(MOD)$<
	@$(PERL) $(LOCAL)ti54x\pp2ti_s.prl $(WORK)$(MOD)$(basename $<).pp $(WORK)$(MOD)$(basename $<).pp2
	$(CC) $(CFLAGS) $(DEFINES) -eo.o -fr$(OBJ)$(MOD) -fs$(WORK)$(MOD) -fa$(WORK)$(MOD)$(basename $<).pp2
	$(if $(filter-out $(ORIGOPTFLAGS),$(OPTFLAGS)),@echo REENABLING DEFAULT OPTIMIZATIONS ($(ORIGOPTFLAGS)),)

ifdef 0
	$(if $(filter-out $(ORIGOPTFLAGS),$(OPTFLAGS)),@echo CHANGING OPTIMIZATIONS ($(OPTFLAGS)),)
	@echo $(MOD)$<
	@$(CC) $(CFLAGS) -eo.o -fr$(OBJ)$(MOD) -fs$(WORK)$(MOD) $(basename $<).s55
	$(if $(filter-out $(ORIGOPTFLAGS),$(OPTFLAGS)),@echo REENABLING DEFAULT OPTIMIZATIONS ($(ORIGOPTFLAGS)),)
endif

# ########################################################################### #
#
# Default target
#

.PHONY:		subs all

CLIST = $(foreach file, $(MODULE_FILELIST.$(subst /,,$(MOD))), $(file).c)

OBJCLIST = $(foreach file, $(MODULE_CLIST.$(subst /,,$(MOD))), $(.path.obj)$(file).obj)

OBJALIST = $(foreach file, $(MODULE_SLIST.$(subst /,,$(MOD))), $(.path.obj)$(file).o)

subs:		all

all:		$(.path.obj)flag

$(.path.obj)flag:	$(OBJCLIST) $(OBJALIST)
			@$(PERL) $(LOCAL)touch.prl $(.path.obj)flag

.PHONY:		pp

CLIST = $(foreach file, $(MODULE_FILELIST.$(subst /,,$(MOD))), $(file).c)

PPLIST = $(foreach file, $(MODULE_CLIST.$(subst /,,$(MOD))) $(MODULE_SLIST.$(subst /,,$(MOD))), $(.path.pp)$(file).pp)

pp:	$(.path.pp)flag

$(.path.pp)flag:	$(PPLIST)
			@$(PERL) $(LOCAL)touch.prl $(.path.pp)flag

# ########################################################################### #
#
# Rebuild makefile.dep dependencies
#

.PHONY:		depend

REMAKE_DEPENDENCIES = $(PERL) $(LOCAL)makedep.prl $(LINKRSP) $(.path.c)makefile

depend:
			$(REMAKE_DEPENDENCIES)
ifndef DO_PARTIAL_SOURCE
			$(PERL) $(LOCAL)mkheader.prl
endif # DO_PARTIAL_SOURCE

.PHONY:		headers

headers:
ifndef DO_PARTIAL_SOURCE
			$(PERL) $(LOCAL)mkheader.prl
endif # DO_PARTIAL_SOURCE

# keep first line to automatically rebuild dependicies
# use second line to avoid this feature when constantly touching stuff

# ########################################################################### #
#
# Clean build
#

.PHONY:		clean delete *.del

clean:		delete all

delete:		$(foreach file, $(basename $(OBJCLIST)), $(file).cde.del \
													$(file).int.del \
													$(file).obj.del)

%.del:
			@$(subst /,\,if exist $* del $* > nul)
# ########################################################################### #
.PHONY:		ataoffs

ataoffs:
	$(PERL) $(LOCAL)\mkataoff.prl ataweb/atapages.c ataweb/ataoffs.h

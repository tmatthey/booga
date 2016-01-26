#
# Default Makefile for library directories
#
# Copyright (C) 1995, Stephan Amann <amann@iam.unibe.ch>
#                     Christoph Streit <streit@iam.unibe.ch>
#                     University of Berne, Switzerland
#
# All rights reserved.
#
# This software may be freely copied, modified, and redistributed
# provided that this copyright notice is preserved on all copies.
#
# You may not distribute this software, in whole or in part, as part of
# any commercial product without the express consent of the authors.
#
# There is no warranty or other guarantee of fitness of this software
# for any purpose.  It is provided solely "as is".
#
# -----------------------------------------------------------------------------
#  $Id: default.mk,v 1.16 1996/04/25 14:54:58 buhlmann Exp $
# -----------------------------------------------------------------------------
#

# Define Targets:
# -----------------------------------------------------------------------------
SUBDIRS       = src include
EXEC_TARGET   =
LIB_TARGET    = 

# Define Libraries:
# -----------------------------------------------------------------------------
DEP_LIBS   =
OTHER_LIBS =


# -----------------------------------------------------------------------------
# Don NOT change anything below this line !!
# -----------------------------------------------------------------------------

# Which non-standard files have to be removed?
# -----------------------------------------------------------------------------
MOSTLYCLEAN =
CLEAN       = GNUmakefile $(wildcard lib/*)
REALCLEAN   =
DISTCLEAN   =

# Set vpath for different types
# -----------------------------------------------------------------------------

# Include generated makefile support files
# -----------------------------------------------------------------------------
override SNIFF_MAKEDIR = .sniffdir
include $(SNIFF_MAKEDIR)/macros.incl

# Include common stuff
# -----------------------------------------------------------------------------
include $(SNIFF_RELATIVE_ROOT_DIR)/config/general.mk

#
# Generate Makefiles and Directories
# -----------------------------------------------------------------------------
.PHONY: Directories
Directories: ;

.PHONY: Makefiles
Makefiles: $(SUBDIRS:%=%/GNUmakefile) src/generated.incl

.PHONY: LinksToTarget
LinksToTarget: ;


src/GNUmakefile: ../default-src.mk
	@echo Copying $@
	$(debug)rm -f $@
	$(debug)cp ../default-src.mk $@

src/generated.incl: $(SNIFF_PROJECT)
	@echo Generating $@ 
	$(debug)rm -f $@
	$(debug)echo GEN_OFILES = $(GEN_OBJS) > $@

include/GNUmakefile: ../default-inc.mk
	@echo Copying $@
	$(debug)rm -f $@
	$(debug)cp ../default-inc.mk $@


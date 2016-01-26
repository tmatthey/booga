#
# Makefile for root of BOOGA
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
#  $Id: GNUmakefile,v 1.3 1995/04/21 12:32:43 amann Exp $
# -----------------------------------------------------------------------------
#

# Define Targets:
# -----------------------------------------------------------------------------
SUBDIRS       = $(wildcard *-app)
EXEC_TARGET   =
LIB_TARGET    =

# Define Libraries:
# -----------------------------------------------------------------------------
DEP_LIBS   =
OTHER_LIBS =

# -----------------------------------------------------------------------------
# Do NOT change anything below this line !!
# -----------------------------------------------------------------------------

# Which non-standard files have to be removed?
# -----------------------------------------------------------------------------
MOSTLYCLEAN =
CLEAN       =
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
Directories: bin

.PHONY: Makefiles
Makefiles: $(SUBDIRS:%=%/GNUmakefile) 

.PHONY: LinksToTarget
LinksToTarget: ;

bin:
	@echo Generating Directory $@
	$(debug)mkdir bin

$(SUBDIRS:%=%/GNUmakefile): default.mk
	@echo Copying $@
	$(debug)rm -f $@
	$(debug)cp default.mk $@



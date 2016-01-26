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
#  $Id: GNUmakefile,v 1.13 1995/08/22 11:23:01 amann Exp $
# -----------------------------------------------------------------------------
#

# Define Targets:
# -----------------------------------------------------------------------------
SUBDIRS       = $(BOOGALIBS)
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
REALCLEAN   = lib include
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
Directories: Dirs Links

.PHONY: Dirs
Dirs: lib include include/booga 

.PHONY: LinksToTarget
LinksToTarget: ;

lib include include/booga:
	@echo Generating Directory $@
	$(debug)mkdir $@

.PHONY: Links
Links: $(SUBDIRS:%=include/booga/%)

include/booga/%: 
	$(debug){ \
	  if [ ! -r $@ ] ; then \
	    echo Generating Link $@; \
	    ln -s ../../$*/include $@; \
	  fi; \
	}

.PHONY: Makefiles
Makefiles: $(SUBDIRS:%=%/GNUmakefile) 

$(SUBDIRS:%=%/GNUmakefile): default.mk
	@echo Copying $@
	$(debug)rm -f $@
	$(debug)cp default.mk $@

#
# Default Makefile for applications
#
# Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
#                        Christoph Streit <streit@iam.unibe.ch>
#                        University of Berne, Switzerland
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
#  $Id: default.mk,v 1.11 1996/03/01 10:36:58 amann Exp $
# -----------------------------------------------------------------------------
#

# Define Targets:
# -----------------------------------------------------------------------------
SUBDIRS       = 
EXEC_TARGET   = $(subst -app.shared,,$(SNIFF_PROJECT))
LIB_TARGET    = 


# Define Libraries:
# -----------------------------------------------------------------------------
DEP_LIBS   = 
OTHER_LIBS =

# Application specific stuff
# -----------------------------------------------------------------------------
ifeq "$(wildcard app-specific.mk)" "app-specific.mk"
  include app-specific.mk 
endif

# -----------------------------------------------------------------------------
# Don NOT change anything below this line !!
# -----------------------------------------------------------------------------

# Which non-standard files have to be removed?
# -----------------------------------------------------------------------------
MOSTLYCLEAN =
CLEAN       = GNUmakefile
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
Makefiles: ;

.PHONY: LinksToTarget
LinksToTarget: ../bin/$(EXEC_TARGET)

../bin/$(EXEC_TARGET):
	@{ \
	  if [ ! -h $@ ] ; then \
	    echo Generating Link $@ ; \
	    ln -s ../$(EXEC_TARGET)-app/$(EXEC_TARGET) $@; \
	  fi; \
	}
	

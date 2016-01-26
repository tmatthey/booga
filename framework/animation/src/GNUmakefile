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
#  $Id: default-src.mk,v 1.5 1996/04/25 14:54:54 buhlmann Exp $
# -----------------------------------------------------------------------------
#

# Define Targets:
# -----------------------------------------------------------------------------
SUBDIRS       =
EXEC_TARGET   =
LIB_TARGET    = lib$(subst _src.shared,,$(SNIFF_PROJECT))

# Define Libraries:
# -----------------------------------------------------------------------------
DEP_LIBS   =
OTHER_LIBS =

# -----------------------------------------------------------------------------
# Don NOT change anything below this line !!
# -----------------------------------------------------------------------------

# Library specific stuff
# -----------------------------------------------------------------------------
ifeq "$(wildcard lib-specific.mk)" "lib-specific.mk"
  include lib-specific.mk 
endif

# Which non-standard files have to be removed?
# -----------------------------------------------------------------------------
MOSTLYCLEAN =
CLEAN       = GNUmakefile
REALCLEAN   =
DISTCLEAN   =

# Include generated makefile support files
# -----------------------------------------------------------------------------
override SNIFF_MAKEDIR = .sniffdir
include $(SNIFF_MAKEDIR)/macros.incl

# Include dependencies for generated files
# -----------------------------------------------------------------------------
include generated.incl

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
LinksToTarget: 
	-$(debug){ \
	  if [ ! -r ../../lib/lib$(subst .shared,,$(SNIFF_PROJECT)).$(LIB_EXT) ] ; then \
	    if [ -r lib$(subst .shared,,$(SNIFF_PROJECT)).$(LIB_EXT) ] ; then \
	      echo Generating link ../../lib/lib$(subst .shared,,$(SNIFF_PROJECT)).$(LIB_EXT); \
	      ln -s lib$(subst .shared,,$(SNIFF_PROJECT)).$(LIB_EXT) \
		     ../../lib/lib$(subst .shared,,$(SNIFF_PROJECT)).$(LIB_EXT); \
	    fi; \
	  fi; \
	}

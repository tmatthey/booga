# SNiFF+ - Makefile configuration for GNU cc 2.6.3
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
#  $Id: sun-3.0.1.mk,v 1.9 1995/09/01 08:47:52 amann Exp $
# -----------------------------------------------------------------------------
#

# Select STATIC or SHARED
compiler_buildType := STATIC

ifeq ($(USER),booga)
 objWorkspaces = $(SHARED_OBJ)
else
 objWorkspaces = $(WORKSPACE) $(SHARED_OBJ)
endif
allWorkspaces = $(objWorkspaces) $(SHARED_SRC)
templateDB    = $(foreach d, $(objWorkspaces), $(d:%=-ptr%))

# C++ compiler
CXX             = CC
CXXFLAGS        = -g +w $(templateDB) \
                  $(foreach ws, $(allWorkspaces), $(BOOGALIBS:%=-I$(ws)/framework/%/src))
SHARED_CXXFLAGS = -G -pic
STATIC_CXXFLAGS = 
SHARED_LDFLAGS  = -G
STATIC_LDFLAGS  = -Bstatic $(templateDB)
SHARED_LIBS     = 
STATIC_LIBS     = 
OTHER_LIBS     += -Bdynamic -ldl -lsocket -lnsl

BUILD_SH_LIB    = -G $(templateDB)
BUILD_DEPEND    = g++ -MM -MG

# Archives with templates have to be built using CC -xar
AR      = $(CXX) $(templateDB) -xar -o 
ARFLAGS = 

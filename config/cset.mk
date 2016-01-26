# SNiFF+ - Makefile configuration for IBM CSet++ 3.1
#
# Copyright (C) 1995, Bernhard Buehlmann <buhlmann@iam.unibe.ch>
#                     Stephan Amann <amann@iam.unibe.ch>
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
#  $Id: cset.mk,v 1.3 1996/04/25 14:54:50 buhlmann Exp $
# -----------------------------------------------------------------------------
#

# Select STATIC or SHARED
compiler_buildType := STATIC

# C++ compiler
CXX             = xlC
CXXFLAGS        = -O2 -DTEMPLATE_IN_HEADER -w
SHARED_CXXFLAGS = 
STATIC_CXXFLAGS = 
SHARED_LDFLAGS  = 
STATIC_LDFLAGS  =
SHARED_LIBS     = 
STATIC_LIBS     =

BUILD_SH_LIB    = -shared -h$@
BUILD_DEPEND    = g++ -MM -MG

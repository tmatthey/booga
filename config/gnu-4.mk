#
# gnu-2.8.1.mk
#
# SNiFF+ - Makefile configuration for GNU cc 2.8.1
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
#  $Id: gnu-2.8.1.mk,v 1.0 1998/07/13 15:27:21 matthey Exp $
# -----------------------------------------------------------------------------
#

# Select STATIC or SHARED
compiler_buildType := STATIC
#compiler_buildType := SHARED

# C++ compiler
CXX             = g++
CXXFLAGS        = -g -Wall  -DTEMPLATE_IN_HEADER  
SHARED_CXXFLAGS = -fPIC
STATIC_CXXFLAGS = 
SHARED_LDFLAGS  = 
# STATIC_LDFLAGS  = -pg
STATIC_LDFLAGS  =
SHARED_LIBS     = 
STATIC_LIBS     =

BUILD_SH_LIB    = -G
BUILD_DEPEND    = g++ -MM -MG

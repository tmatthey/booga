#
# MIPSpro.mk
#
# SNiFF+ - Makefile configuration for MIPSpro
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
#  $Id: MIPSpro.mk,v 1.0 1996/04/01 15:27:21 matthey Exp $
# -----------------------------------------------------------------------------
#

# Select STATIC or SHARED
#compiler_buildType := STATIC
compiler_buildType := SHARED

# C++ compiler
CXX             = CC
CXXFLAGS        = -DTEMPLATE_IN_HEADER -mips4 -O3 -r10000 #-pca keep# -pedantic
SHARED_CXXFLAGS = -fPIC
STATIC_CXXFLAGS = 
SHARED_LDFLAGS  = 
# STATIC_LDFLAGS  = -pg
STATIC_LDFLAGS  =
SHARED_LIBS     = 
STATIC_LIBS     =

BUILD_SH_LIB    = -G
BUILD_DEPEND    = g++ -MM -MG

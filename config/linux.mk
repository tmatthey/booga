# 
# linux.mk
#
# SNiFF+ - Makefile configuration for Linux 95 ;-) 
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
#  $Id: linux.mk,v 1.3 1996/06/05 12:12:59 amann Exp $
# -----------------------------------------------------------------------------
#

# Select STATIC or SHARED
# -------------------------------------------------------
system_buildType := SHARED

# System Flags
# -------------------------------------------------------
SYSTYPE = -DSVR4 -DSYSV -DCPP='"/usr/bin/cpp "' -DSHELL='"/bin/sh"'

# Some special include and library paths
# -------------------------------------------------------

# X11 include files and library
# HAVE_X11  = 
HAVE_X11  = -DHAVE_X11
X11_INC   = -I/usr/X11R6/include
X11_LPATH = -L/usr/X11R6/lib
X11_LIB   = -lXext -lXmu -lX11 -lXi

# OpenGL includes and library
# HAVE_OPENGL  = 
HAVE_OPENGL  = -DHAVE_OPENGL
OPENGL_INC   = -I/usr/local/include
OPENGL_LPATH = -L/usr/local/lib
OPENGL_LIB   = -lglut -lGLU -lGL 

# SRGP includes and library
HAVE_SRGP  =
#HAVE_SRGP  = -DHAVE_SRGP
#SRGP_INC   = -I/home/fcg/include/srgp
#SRGP_LPATH = -L/home/fcg/lib
#SRGP_LIB   = -lsrgp

# MPEGE include files and library
HAVE_MPEGE  = 
#HAVE_MPEGE  = -DHAVE_MPEGE
#MPEGE_INC   = -I/usr/local/include
#MPEGE_LPATH = -L/usr/local/lib
#MPEGE_LIB   = -lmpege 

# wxWin includes and library
# HAVE_WXWIN  =
HAVE_WXWIN  = -DHAVE_WXWIN
WXWIN_INC   = -I/usr/wxwin/unix/include/x -I/usr/wxwin/unix/include/base
WXWIN_LPATH = -L/usr/wxwin/unix/lib
WXWIN_LIB   = -lwx_ol
CPPFLAGS   += -Dwx_xview

# libwww includes and library
HAVE_WWW  =
#HAVE_WWW  = -DHAVE_WWW
#WWW_INC   = -I/home/fcg/include
#WWW_LPATH = -L/home/fcg/lib 
#WWW_LIB   = -lwww -lsocket -lnsl

# Conclusion:
CPPFLAGS += $(HAVE_X11) $(HAVE_OPENGL) $(HAVE_SRGP) $(HAVE_WXWIN)
CPPFLAGS += $(X11_INC) $(OPENGL_INC) $(SRGP_INC) $(WXWIN_INC)

FW_OTHER_LIBS = $(WWW_LPATH) $(WWW_LIB)

# Archive maintaining
# -------------------------------------------------------
AR      = ar
ARFLAGS = r
RANLIB  = true

# How do we build shared libraries?
# -------------------------------------------------------
define build-shared-lib
  $(debug)$(CXX) $(BUILD_SH_LIB) -o $(notdir $@) $^
endef

# Extension of Libraries 
# -------------------------------------------------------
SHARED_LIB_EXT = so
STATIC_LIB_EXT = a

# yacc compiler and lexical analysis program generator
# -------------------------------------------------------
BISON++  = bison++
B++FLAGS = -vd
FLEX++   = flex++
F++FLAGS = 

# GNU awk program
# -------------------------------------------------------
GAWK   = gawk

# Utilities
# -------------------------------------------------------
WC        = wc
RM_INTACT = rm -i
CUT	   = /bin/cut

# Where and how do you want BOOGA to be installed?
# -------------------------------------------------------
prefix       = /home/fcg/BOOGA
exec_prefix  = $(prefix)
bindir       = $(exec_prefix)/bin
libdir       = $(exec_prefix)/lib
includedir   = $(prefix)/include
mandir       = $(prefix)/man
tmpdir	    = /tmp

INSTALL_PROG = /usr/ucb/install -m 755 -c
INSTALL_DATA = /usr/ucb/install -m 644 -c


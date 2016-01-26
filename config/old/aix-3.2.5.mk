#
# aix-3.2.5.mk
#
# SNiFF+ - Makefile configuration for IBM RS/6000 AIX 3.2.5 
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
#  $Id: aix-3.2.5.mk,v 1.19 1996/07/19 09:41:27 buhlmann Exp $
# -----------------------------------------------------------------------------
#

# Select STATIC or SHARED
# -------------------------------------------------------
system_buildType := SHARED

# System Flags
# -------------------------------------------------------
SYSTYPE = -O2 -D_POWER -DSVR4 -DSYSV -DCPP='"/usr/lib/cpp"' -DSHELL='"/bin/sh"'

# Some special include and library paths
# -------------------------------------------------------

# X11 include files and library
# HAVE_X11  = 
HAVE_X11  = -DHAVE_X11
X11_INC   =
X11_LPATH = -L/usr/lib
X11_LIB   = -lXext -lXmu -lX11 

# OpenGL includes and library
# HAVE_OPENGL  = 
HAVE_OPENGL  = -DHAVE_OPENGL
#OPENGL_INC   = 
#OPENGL_LPATH = -L/usr/local/lib/glut
#OPENGL_LIB   = -lglut -lGLU -lGL 
# For mesa on AIX
OPENGL_INC   = -I/usr/local/include/Mesa-2.4 -I/usr/local/include/glut
OPENGL_LPATH = -L/usr/local/lib -L/usr/local/lib/glut
OPENGL_LIB   = -lglut -lMesaGLU -lMesaGL 

# SRGP includes and library
HAVE_SRGP  =
# HAVE_SRGP  = -DHAVE_SRGP
# SRGP_INC   = -I/home/fcg/include/srgp
# SRGP_LPATH = -L/home/fcg/lib
# SRGP_LIB   = -lsrgp

# MPEGE include files and library
# HAVE_MPEGE  = 
HAVE_MPEGE  = -DHAVE_MPEGE
MPEGE_INC   = -I/usr/local/include
MPEGE_LPATH = -L/usr/local/lib
MPEGE_LIB   = -lmpege 
 
# JPEG include files and library
# HAVE_JPEG  = 
HAVE_JPEG  = -DHAVE_JPEG 
JPEG_INC   = -I/usr/local/include/jpeg
JPEG_LPATH = -L/usr/local/lib/jpeg 
JPEG_LIB   = -ljpeg

# wxWin includes and library
# HAVE_WXWIN  =
HAVE_WXWIN  = -DHAVE_WXWIN
WXWIN_INC   = -I/usr/local/include/wxWindows-1.6.7/x  -I/usr/local/include/wxWindows-1.6.7/base
WXWIN_LPATH = -L/usr/local/lib/wxWindows-1.6.7
WXWIN_LIB   = -lwx_motif -lXm -lXGLW 
CPPFLAGS   += -Dwx_motif

# libwww includes and library
HAVE_WWW  =
HAVE_WWW  = -DHAVE_WWW
WWW_INC   = -I/home/fcg/include
WWW_LPATH = -L/usr/local/lib 
WWW_LIB   = -lwww 

# libmpi includes and library
HAVE_MPI  =
HAVE_MPI  = -DHAVE_MPI
MPI_INC   = -I/home/fcg/parallel/mpi/include
MPI_LPATH = -L/home/fcg/parallel/mpi/lib/rs6000/ch_p4
MPI_LIB   = -lmpi

# Conclusion:
CPPFLAGS += $(HAVE_X11) $(HAVE_OPENGL) $(HAVE_SRGP) $(HAVE_WXWIN) $(HAVE_MPEGE) $(HAVE_JPEG) $(HAVE_WWW) $(HAVE_MPI)
CPPFLAGS += $(X11_INC) $(OPENGL_INC) $(SRGP_INC) $(WXWIN_INC) $(MPEGE_INC) $(JPEG_INC) $(WWW_INC) $(MPI_INC)

FW_OTHER_LIBS = $(WWW_LPATH) $(WWW_LIB) 

# Archive maintaining
# -------------------------------------------------------
AR      = ar
ARFLAGS = r
RANLIB  = ranlib

# How do we build shared libraries?
# -------------------------------------------------------
MAKESHARED = /usr/lpp/xlC/bin/makeC++SharedLib
define build-shared-lib
  $(debug)-rm /tmp/$(notdir $@)-tmp.a
  $(debug)ar rv /tmp/$(notdir $@)-tmp.a $^
  $(debug)-rm $(notdir $@)
  $(debug)$(MAKESHARED) -p 0 -o /tmp/$(notdir $@)-shr.o -L$(SNIFF_RELATIVE_ROOT_DIR)/framework/lib $(DEP_ON_LIBS:%=-l%) $(OTHER_LIBS) /tmp/$(notdir $@)-tmp.a
  $(debug)ar rv $(notdir $@) /tmp/$(notdir $@)-shr.o
  $(debug)-rm /tmp/$(notdir $@)-shr.o
  $(debug)-rm /tmp/$(notdir $@)-tmp.a
endef
 
# Extension of Libraries 
# -------------------------------------------------------
SHARED_LIB_EXT = a
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
CUT	   = /usr/bin/cut

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

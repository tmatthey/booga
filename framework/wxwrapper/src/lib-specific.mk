#
# lib-specific.mk
#
# Special flags and dependecies for libraries
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
#  $Id: lib-specific.mk,v 1.3 1996/05/17 13:42:43 buhlmann Exp $
# -----------------------------------------------------------------------------
#

DEP_ON_LIBS = base object texture pixmapOp nurbs animation component glwrapper
OTHER_LIBS = $(OPENGL_LPATH) $(OPENGL_LIB) $(WXWIN_LPATH) $(WXWIN_LIB) $(MPEGE_LPATH)  $(MPEGE_LIB) $(X11_LPATH) $(X11_LIB) -lXt 

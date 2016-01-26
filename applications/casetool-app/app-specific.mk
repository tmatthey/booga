#
# Application specific add-ons 
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
#  $Id: app-specific.mk,v 1.8 1997/01/17 10:33:57 matthey Exp $
# -----------------------------------------------------------------------------
#

LDFLAGS    = $(OPENGL_LPATH) $(X11_LPATH) $(MPEGE_LPATH) $(JPEG_LPATH)
#DEP_LIBS   = -lglwrapper -lcomponent -lanimation -lbuilding -lnurbs -lobject -ltexture -lpixmapOp -lbase
#OTHER_LIBS = $(OPENGL_LIB) $(X11_LIB) $(MPEGE_LIB) $(JPEG_LIB) -lm
DEP_LIBS   = -lglwrapper -lcomponent -lanimation -lbuilding -lnurbs -lobject -ltexture -lpixmapOp -lbase
OTHER_LIBS = $(OPENGL_LIB) $(X11_LIB) $(JPEG_LIB) -lm

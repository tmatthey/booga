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
#  $Id: app-specific.mk,v 1.8 1997/03/27 13:32:25 habegger Exp $
# -----------------------------------------------------------------------------
#

LDFLAGS    = $(OPENGL_LPATH) $(WXWIN_LPATH) $(X11_LPATH) $(MPEGE_LPATH) $(JPEG_LPATH)
DEP_LIBS   = -lwxwrapper -lglwrapper -lcomponent -lnurbs -lanimation -lbuilding -ltexture -lobject -lpixmapOp -lbase
OTHER_LIBS = $(OPENGL_LIB) $(WXWIN_LIB) $(X11_LIB) $(MPEGE_LIB) $(WWW_LIB) $(JPEG_LIB) -lm

#ifeq ($(PLATFORM),linux) # will be deleted ...
# Linux stuff
#DEP_LIBS   = -lglwrapper -lnurbs -lpixmapOp -ltexture -lcomponent -lobject -lpixmapOp -lbase 
#
#CPPFLAGS  += $(WXWIN_INC) $(XVIEW_INC)
#LDFLAGS    = $(OPENGL_LPATH) $(WXWIN_LPATH) $(XVIEW_LPATH) $(X11_LPATH) 
#OTHER_LIBS = $(OPENGL_LIB) $(WXWIN_LIB) $(XVIEW_LIB) $(X11_LIB) -lXt -lm
#else

#LDFLAGS    = $(OPENGL_LPATH) $(WXWIN_LPATH) $(X11_LPATH) $(JPEG_LPATH)
#DEP_LIBS   = -lwxwrapper -lglwrapper -lcomponent -lanimation -lnurbs -ltexture -lobject -lbase   
#
#OTHER_LIBS = $(OPENGL_LIB) $(WXWIN_LIB) $(X11_LIB) $(JPEG_LIB) -lm
#
#endif
# CPPFLAGS   += -I-

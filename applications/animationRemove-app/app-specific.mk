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
#  $Id: app-specific.mk,v 1.7 1997/01/17 10:33:52 matthey Exp $
# -----------------------------------------------------------------------------
#

LDFLAGS    =  $(JPEG_LPATH) 
DEP_LIBS   = -lcomponent -lanimation -lbuilding -lnurbs -ltexture -lobject -lpixmapOp -lbase
OTHER_LIBS =   $(JPEG_LIB) -lm  

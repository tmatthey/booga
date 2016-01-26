/*
 * GlutBridge.C 
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
 *                        University of Berne, Switzerland
 *
 * All rights reserved.
 *
 * This software may be freely copied, modified, and redistributed
 * provided that this copyright notice is preserved on all copies.
 *
 * You may not distribute this software, in whole or in part, as part of
 * any commercial product without the express consent of the authors.
 *
 * There is no warranty or other guarantee of fitness of this software
 * for any purpose.  It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: GlutBridge.C,v 1.2 1997/09/19 07:14:08 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
#ifdef HAVE_OPENGL
#ifdef HAVE_X11
# include <X11/Xlib.h>  // XPending
#endif
# include <GL/glut.h>   // glutSwapBuffers
#endif

#include "booga/glwrapper/GlutBridge.h"

//___________________________________________________________________ GlutBridge

bool GlutBridge::isEventPending()
{
#ifdef HAVE_X11
#ifdef HAVE_OPENGL
  //
  // NOTE: This hack is "very, very DIRTY!!!"
  //
  // The name of the display variable may change, 
  // when a new release of GLUT is available.
  //
  extern Display* __glutDisplay;

  if (XPending(__glutDisplay))
    return true;
  else
#endif // HAVE_OPENGL
#endif
    return false;
}

void GlutBridge::swapBuffers()
{

  glutSwapBuffers();
}


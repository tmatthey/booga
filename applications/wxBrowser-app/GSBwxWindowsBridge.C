/*
 * GSBwxWindowsBridge.C 
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
 *  $Id: GSBwxWindowsBridge.C,v 1.4 1997/04/08 11:05:41 habegger Exp $
 * -----------------------------------------------------------------------------
 */
 
#ifdef HAVE_OPENGL
# include <X11/Xlib.h>  // XPending
# include <GL/glx.h>   // glXSwapBuffers
#endif

#include "GSBwxWindowsBridge.h"

//_______________________________________________________________________ GSBwxWindowsBridge

bool GSBwxWindowsBridge::isEventPending()
{
  //
  // NOTE: This hack is "very, very DIRTY!!!"
  //
  // 
  // 
  //
  extern Display* _wxGLDisplay;

  if (XPending(_wxGLDisplay))
    return true;
  else
    return false;
}

void GSBwxWindowsBridge::swapBuffers()
{
  extern Display* _wxGLDisplay;
  extern Window _wxGLWindow;
          
  glXSwapBuffers(_wxGLDisplay, _wxGLWindow);
}



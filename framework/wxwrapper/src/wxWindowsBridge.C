/*
 * wxWindowsBridge.C 
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
 *  $Id: wxWindowsBridge.C,v 1.5 1997/09/19 08:42:22 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
#if defined(HAVE_OPENGL) && defined(HAVE_X11)
# include <X11/Xlib.h>  // XPending
# include <GL/glx.h>   // glXSwapBuffers
#endif

#include "booga/wxwrapper/wxWindowsBridge.h"
#include "booga/base/Report.h"
//#include "wx.h"
//_______________________________________________________________________ wxWindowsBridge

#if defined (HAVE_OPENGL) && defined(HAVE_X11)

bool wxWindowsBridge::isEventPending()
{
  //
  // NOTE: This hack is "very, very DIRTY!!!"
  //
  // 
  // 
  //
  extern Display* _wxGLDisplay;

  if (XPending(_wxGLDisplay)) {

    XEvent event;
    XPeekEvent (_wxGLDisplay, &event);
#ifdef wx_xview
//    if (event.type == ButtonRelease || event.type == MotionNotify)
    if (event.type == MotionNotify)
      return false;
    else
      return true;
#else
    return true;
    // if the user selects an object, the button up event interrupts the refresh of the scene.
    // this prevents to draw the whole scene after selecting an object.
    // this needs further investigation.
      
//    if (event.type == ButtonRelease)
//      return false;
//    else
//      return true;
#endif
//    ostrstream os;
//    os << "[wxWindowsBridge::isEventPending]: PeekEvent is " << event.type; 
//    Report::warning (os);
  }
  else
    return false;
}

void wxWindowsBridge::swapBuffers()
{
  extern Display* _wxGLDisplay;
  extern Window _wxGLWindow;
          
  glXSwapBuffers(_wxGLDisplay, _wxGLWindow);
}
#endif

#if defined(HAVE_OPENGL) && defined(WIN32)
#include <windows.h> // SwapBuffers

extern wxWindow* _wxGLWindow;

bool wxWindowsBridge::isEventPending()
{
  MSG             msg;            // Windows message structure
  if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
    return true;
  else
    return false;
}

void wxWindowsBridge::swapBuffers()
{
  SwapBuffers(wglGetCurrentDC());
}

#endif


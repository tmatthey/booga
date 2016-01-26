/*
 * $RCSfile: GLTraversal.C,v $
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: GLTraversal.C,v 1.3 1997/09/19 07:14:06 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
#ifdef HAVE_OPENGL
# include <GL/gl.h>
#endif

#include "booga/glwrapper/GLUtilities.h"
#include "booga/glwrapper/GLTraversal.h"

//__________________________________________________________________ GLTraversal

GLTraversal::GLTraversal()
{
  myMaxTimeInBackbuffer = 1;  // Stay max. 1 second in back buffer.
  myTimePerFrame = 1. / 20.;  // 20 frames/sec.
  myInFrontbuffer = false;
  myCheckPendingEvents = true;
}

bool GLTraversal::abortTraversal()
{
#ifdef HAVE_OPENGL
  
  Real currentTime = myTimer.getTime().getRealTime();

  // 
  // Stop traversal if event is pending. Limit the redisplay time to 'myTimePerFrame'.
  //
  
  if (!myCheckPendingEvents && (currentTime > myTimePerFrame))
    return true;
    
  if ((currentTime > myTimePerFrame) && myCheckPendingEvents)  // we are over the framerate, so check if an event is pending!
	if (GLUtilities::isEventPending()) 
      return true;

  //
  // We are drawing in the GL_BACK buffer but never longer 
  // than 'myMaxTimeInBackbuffer' seconds. This way we can give
  // visual feedback to the user if the rendering process takes
  // too much time.
  //    -> On fast hardware, the entire scene is drawn in the
  //       backbuffer so we get much better performance.
  //
  if (!myInFrontbuffer && currentTime > myMaxTimeInBackbuffer) {
    GLint drawBuffer;
    glGetIntegerv(GL_DRAW_BUFFER, &drawBuffer);
    if (drawBuffer == GL_BACK) {
      GLUtilities::swapBuffers();
      glDrawBuffer(GL_FRONT);
      myInFrontbuffer = true;
    }
  }

#endif // HAVE_OPENGL

  return false;
}

void GLTraversal::reset()
{
  myInFrontbuffer = false;
  myTimer.reset();
  myTimer.start();
}

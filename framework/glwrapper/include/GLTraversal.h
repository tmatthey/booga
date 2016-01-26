/*
 * $RCSfile: GLTraversal.h,v $
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: GLTraversal.h,v 1.3 1997/09/05 08:56:03 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifndef _GLTraversal_H
#define _GLTraversal_H

#include "booga/base/Timer.h"

//__________________________________________________________________ GLTraversal

class GLTraversal {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GLTraversal();
  // GLTraversal(const GLTraversal&);            
  // Use default version.

public:
  // virtual ~GLTraversal();                       
  // Use default version.      

public:
  // GLTraversal& operator=(const GLTraversal&); 
  // Use default version.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class GLTraversal
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Real getMaxTimeInBackbuffer() const;
  void setMaxTimeInBackbuffer(Real maxTimeInBackbuffer);
  // Rendering in back buffer mode is much faster then using the front 
  // buffer. For interactive applications, one has to give visual feedback 
  // to the user as soon as possible. For large scenes rendered into the 
  // back buffer this is not possible, so we have to be able to limit the 
  // rendering time in back buffer mode and switch automatically to the 
  // front buffer to conclude the rendering of the scene when the maximum 
  // back buffer time is exceeded.

  int getFrameRate() const;
  void setFrameRate(int frameRate);
  // For interactive applications a high frame rate is essential. But 
  // for (very) large scenes the frame rate is always too low, even if  
  // a fast rendering hardware is in use. As a consequence the rendering 
  // process has to be interupted if a request (event) from the user is 
  // pending. However, it makes no sense to interupt too quickly. 
  // The setFrameRate method allows to limit the frame rate to a maximal 
  // value. 
  // This option has no influence, if the total rendering time of the scene 
  // is not longer than (1./'frameRate') seconds.

  Real getCurrentTime() const;
  bool isInFrontbuffer() const;

  // While the user is moving a scene, the whole scene is redrawn
  // at the selected framerate. If no event of the windwoing system is 
  // pending, the redraw continues until an event occurs. This default
  // behaviour can be controlled using the following functions.    

  void setCheckPendingEvents (bool check);
  bool doCheckPendingEvents () const;
  
protected:
  bool abortTraversal();
  // Returns true,  if user event is pending.
  //         false, otherwise.
  
  void reset();
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Timer myTimer;
  Real myMaxTimeInBackbuffer;
  bool myInFrontbuffer;
  Real myTimePerFrame;
  bool myCheckPendingEvents;
};

//______________________________________________________________________ INLINES

inline int GLTraversal::getFrameRate() const
{
  return int(1. / myTimePerFrame);
}

inline void GLTraversal::setCheckPendingEvents(bool check)
{
  myCheckPendingEvents = check;
}

inline void GLTraversal::setFrameRate(int frameRate)
{
  if (frameRate < 0) {
    Report::warning("[GLTraversal::setFramesRate] illegal frame rate");
    return;
  }
  
  if (frameRate == 0) {
    myTimePerFrame = 9999999; // very long...
    return;
  }
  
  myTimePerFrame = 1. / frameRate;
}

inline Real GLTraversal::getMaxTimeInBackbuffer() const
{
  return myMaxTimeInBackbuffer;
}

inline void GLTraversal::setMaxTimeInBackbuffer(Real maxTimeInBackbuffer)
{
  myMaxTimeInBackbuffer = maxTimeInBackbuffer;
}

inline bool GLTraversal::isInFrontbuffer() const
{
  return myInFrontbuffer;
}
 
inline Real GLTraversal::getCurrentTime () const
{
  return myTimer.getTime().getRealTime();
}

inline bool GLTraversal::doCheckPendingEvents () const
{
  return myCheckPendingEvents;
}

#endif // _GLTraversal_H

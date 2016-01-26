/*
 * $RCSfile: wxAdaptiveTraceCommand.C,v $ 
 *
 * Copyright (C) 1996, Bernhard Bühlmann <buhlmann@iam.unibe.ch>
 *                     University of Berne, Switzerland
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
 *  $Id: wxAdaptiveTraceCommand.C,v 1.2 1998/05/01 07:11:08 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include <GL/glu.h>

#include "booga/object/Camera3D.h"
#include "booga/object/Viewing3D.h"
#include "booga/glwrapper/GLTraversal3D.h"
#include "booga/wxwrapper/wxWindowsBridge.h"
#include "booga/wxwrapper/wxAdaptiveTraceCommand.h"
//#include "wxTraversal3D.h"

//_____________________________________________________________________ wxAdaptiveTraceCommand

implementRTTI(wxAdaptiveTraceCommand, wxCommand);

wxAdaptiveTraceCommand::wxAdaptiveTraceCommand (wxView3D *v) : wxViewCommand(v)
{
  oldX = oldY = 0;
  myDx = myDy = 0;
  // set current GL context
  v->GLSetCurrent();
  mywxAdaptiveTraceTimer = new wxAdaptiveTraceTimer(this);
  myRenderer = new wxAdaptiveTracer();
  // set current camera
  myRenderer->adoptCamera ((Camera3D *)getView()->getRenderer()->getCamera()->copy());
  myRenderer->execute(getView()->getViewManager()->getWorld());
  Report::warning("[wxAdaptiveTraceCommand::wxAdaptiveTraceCommand]");
  mywxAdaptiveTraceTimer->Start(10);        
/*
  if (getView()->getRenderer()->getFrameRate() > 0.0) 
    mywxAdaptiveTraceTimer->Start((int)(1000.0/getView()->getRenderer()->getFrameRate()));
  else 
    mywxAdaptiveTraceTimer->Start(1000);        
  */
}

wxAdaptiveTraceCommand::~wxAdaptiveTraceCommand()
{
  delete mywxAdaptiveTraceTimer;
  delete myRenderer;
}

void wxAdaptiveTraceCommand::execute ()
{
  float x,y;
  if (getView()->getMouseEvent().ButtonDown()) {
    mywxAdaptiveTraceTimer->Stop();
    getView()->getMouseEvent().Position(&x,&y);
    myDx = 0;
    myDy = 0;
    oldX = x;
    oldY = y;
  } else if (getView()->getMouseEvent().Dragging() && getView()->getMouseEvent().ShiftDown()) {
    return;
  } else if ( getView()->getMouseEvent().ButtonUp()) {
    getView()->getMouseEvent().Position(&x,&y);
    int resY = getView()->getRenderer()->getCamera()->getViewing()->getResolutionY();
    BoundingRect r;
    r.expand(oldX, resY-oldY);
    r.expand(x,resY-y);
    myRenderer->setRectangle(r);
/*
    if (getView()->getRenderer()->getFrameRate() > 0.0) 
      mywxAdaptiveTraceTimer->Start((int)(1000.0/getView()->getRenderer()->getFrameRate()));
    else 
	*/
      mywxAdaptiveTraceTimer->Start(10);        
  }
}

void wxAdaptiveTraceCommand::doMotion ()
{

//  // trace next 5 squares
  getView()->GLSetCurrent();

  for (register long i=0; i<3; i++)
    myRenderer->nextSquare();
}

//-----------------------------------------------------
// class wxAdaptiveTraceTimer
//-----------------------------------------------------

wxAdaptiveTraceTimer::wxAdaptiveTraceTimer (wxAdaptiveTraceCommand *c)
{
  mywxAdaptiveTraceCommand = c;
}

void wxAdaptiveTraceTimer::Notify()
{
//  wxWindowsBridge myBridge;
//  if (!myBridge.isEventPending())
//  Report::warning("[wxAdaptiveTraceTimer::Notify]");
  mywxAdaptiveTraceCommand->doMotion();
//  else 
//    Stop();
}


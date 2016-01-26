/*
 * $RCSfile: AdaptiveTraceCommand.C,v $ 
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
 *  $Id: AdaptiveTraceCommand.C,v 1.3 1996/12/06 13:52:37 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include <GL/glu.h>

#include "booga/object/Camera3D.h"
#include "booga/object/Viewing3D.h"
#include "booga/glwrapper/GLTraversal3D.h"
#include "booga/wxwrapper/wxWindowsBridge.h"
#include "AdaptiveTraceCommand.h"
#include "wxTraversal3D.h"

//_____________________________________________________________________ AdaptiveTraceCommand

implementRTTI(AdaptiveTraceCommand, wxCommand);

AdaptiveTraceCommand::AdaptiveTraceCommand (wxView3D *v) : wxViewCommand(v)
{
  oldX = oldY = 0;
  myDx = myDy = 0;
  myAdaptiveTraceTimer = new AdaptiveTraceTimer(this);
  myRenderer = new AdaptiveTracer();
  // set current camera
  myRenderer->adoptCamera ((Camera3D *)getView()->getRenderer()->getCamera()->copy());
  myRenderer->execute(getView()->getViewManager()->getWorld());
  Report::warning("[AdaptiveTraceCommand::AdaptiveTraceCommand]");
  if (getView()->getRenderer()->getFrameRate() > 0.0) 
    myAdaptiveTraceTimer->Start((int)(1000.0/getView()->getRenderer()->getFrameRate()));
  else 
    myAdaptiveTraceTimer->Start(1000);        
}

AdaptiveTraceCommand::~AdaptiveTraceCommand()
{
  delete myAdaptiveTraceTimer;
  delete myRenderer;
}

void AdaptiveTraceCommand::execute ()
{
  float x,y;
  if (getView()->getMouseEvent().MiddleDown()) {
    myAdaptiveTraceTimer->Stop();
    getView()->getMouseEvent().Position(&x,&y);
    myDx = 0;
    myDy = 0;
    oldX = x;
    oldY = y;
  } else if (getView()->getMouseEvent().Dragging() && getView()->getMouseEvent().ShiftDown()) {
    return;
  } else if ( getView()->getMouseEvent().MiddleUp()) {
    getView()->getMouseEvent().Position(&x,&y);
    int resY = getView()->getRenderer()->getCamera()->getViewing()->getResolutionY();
    BoundingRect r;
    r.expand(oldX, resY-oldY);
    r.expand(x,resY-y);
    myRenderer->setRectangle(r);

    if (getView()->getRenderer()->getFrameRate() > 0.0) 
      myAdaptiveTraceTimer->Start((int)(1000.0/getView()->getRenderer()->getFrameRate()));
    else 
      myAdaptiveTraceTimer->Start(1000);        
  }
}

void AdaptiveTraceCommand::doMotion ()
{

//  // trace next 5 squares
  getView()->GLSetCurrent();

//  for (register long i=0; i<5; i++)
    myRenderer->nextSquare();
}

//-----------------------------------------------------
// class AdaptiveTraceTimer
//-----------------------------------------------------

AdaptiveTraceTimer::AdaptiveTraceTimer (AdaptiveTraceCommand *c)
{
  myAdaptiveTraceCommand = c;
}

void AdaptiveTraceTimer::Notify()
{
//  wxWindowsBridge myBridge;
//  if (!myBridge.isEventPending())
//  Report::warning("[AdaptiveTraceTimer::Notify]");
  myAdaptiveTraceCommand->doMotion();
//  else 
//    Stop();
}


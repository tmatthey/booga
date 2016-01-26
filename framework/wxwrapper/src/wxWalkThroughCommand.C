/*
 * $RCSfile: wxWalkThroughCommand.C,v $ 
 *
 * Copyright (C) 1995, Bernhard Bühlmann <buhlmann@iam.unibe.ch>
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
 *  $Id: wxWalkThroughCommand.C,v 1.2 1997/09/19 08:42:21 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "booga/object/Camera3D.h"
#include "booga/object/Viewing3D.h"
#include "booga/wxwrapper/wxWalkThroughCommand.h"
#include "booga/wxwrapper/wxWindowsBridge.h"

//_____________________________________________________________________ wxWalkThroughCommand

//implementRTTI(wxWalkThroughCommand, wxCommand);

wxWalkThroughCommand::wxWalkThroughCommand (wxView3D *v) : wxViewCommand(v)
{
  oldX = oldY = 0;
  myDx = myDy = 0;
  myWalkThroughTimer = new WalkThroughTimer(this);
  myTimer.reset();
}

void wxWalkThroughCommand::execute ()
{
  float x,y;
  
  if (getView()->getMouseEvent().ButtonDown()) {
    myWalkThroughTimer->Stop();
    myTimer.reset();
    myTimer.start();
    getView()->getMouseEvent().Position(&x,&y);
    myDx = 0;
    myDy = 0;
    oldX = x;
    oldY = y;
  } else if (getView()->getMouseEvent().Dragging() && getView()->getMouseEvent().ShiftDown()) {
    getView()->getMouseEvent().Position(&x,&y);
    myDx = x - oldX;
    myDy = y - oldY;
    oldX = x;
    oldY = y;
      
    moveCamera (myDx,myDy);
    myTimer.stop();
    myTimer.reset();    
    getView()->useMotionQuality();
    getView()->OnPaint();
    return;
  } else if (getView()->getMouseEvent().Dragging()) {
    getView()->getMouseEvent().Position(&x,&y);
    Real theta = x - oldX;
    Real phi = y - oldY;
  
    oldX = x;
    oldY = y;

    turnHead (theta, phi);
    myTimer.stop();
    myTimer.reset();    
    
    getView()->useMotionQuality();
    getView()->OnPaint();
    return;
  } else if ( getView()->getMouseEvent().ButtonUp()) {
    // check if user stopped for less than 0.2 seconds    
    if ((myTimer.getTime().getRealTime() < .2) && ((myDx != 0.0) || (myDy != 0.0))) {
      // user wants to spin object...
      if (getView()->getRenderer()->getFrameRate() > 0.0)  
        myWalkThroughTimer->Start((int)(1000.0/getView()->getRenderer()->getFrameRate()));
      else 
        myWalkThroughTimer->Start(1000);        
    } else {
      // user paused, disable spinning...
      getView()->useRenderingQuality();
      getView()->OnPaint();
    }
    myTimer.stop();
    myTimer.reset();    
  }
}

void wxWalkThroughCommand::turnHead(Real theta, Real phi)
{
  Viewing3D* viewing = getView()->getRenderer()->getCamera()->getViewing();
  
  //
  // n: Direction to the observer.
  // v: Up direction.
  // u: To the right.
  //
  Vector3D n = viewing->getLookat() - viewing->getEye(); 
  n.normalize(); 

  Vector3D v = viewing->getUp() - (n^viewing->getUp())*n;  
  v.normalize(); 

  Vector3D u = n * v; 
  u.normalize();

  TransMatrix3D phi_rot;
  phi_rot.rotate(v, sin(dtor(-theta)), cos(dtor(-theta)));
  TransMatrix3D rot = phi_rot;
  rot.rotate(u*phi_rot, sin(dtor(-phi)), cos(dtor(-phi))); 
  
  TransMatrix3D rotateEye;
  rotateEye.translate(-viewing->getEye());
  rotateEye *= rot;
  rotateEye.translate(viewing->getEye());

  viewing->setLookat(viewing->getLookat() * rotateEye);
}


void wxWalkThroughCommand::moveCamera(Real dx, Real dy)
{
  Viewing3D* viewing = getView()->getRenderer()->getCamera()->getViewing();

  Vector3D eyep  = viewing->getEye();	
  Vector3D lookp = viewing->getLookat();	
  Vector3D up    = viewing->getUp();
  Vector3D direction = eyep - lookp;
  direction[2] = 0;

  Vector3D dist = eyep-lookp;
  dist[2] = 0;

  // Move left / right

  Vector3D left = up*(eyep-lookp);
  Vector3D l = -dx * left/left.length()*dist.length()*.005;
  

  // Move forward / backward

  Vector3D m = dy * direction.normalized() * dist.length() * .005;
  eyep += m - l; 
  lookp += m - l;
  eyep[2]  = 1.8;

  viewing->setEye(eyep);
  viewing->setLookat(lookp);
}

void wxWalkThroughCommand::doMotion ()
{
  // spin object...
  moveCamera (myDx, myDy);
  getView()->OnPaint();
}

//-----------------------------------------------------
// class WalkThroughTimer
//-----------------------------------------------------

WalkThroughTimer::WalkThroughTimer (wxWalkThroughCommand *c)
{
  mywxWalkThroughCommand = c;
}

void WalkThroughTimer::Notify()
{
  wxWindowsBridge myBridge;
  if (!myBridge.isEventPending())
    mywxWalkThroughCommand->doMotion();
}


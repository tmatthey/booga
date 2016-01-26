/*
 * $RCSfile: InspectCommand.C,v $ 
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
 *  $Id: InspectCommand.C,v 1.1 1996/09/27 15:07:48 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "booga/object/Camera3D.h"
#include "booga/object/Viewing3D.h"
#include "booga/glwrapper/GLTraversal3D.h"
#include "booga/wxwrapper/wxWindowsBridge.h"
#include "InspectCommand.h"
#include "wxTraversal3D.h"

//_____________________________________________________________________ InspectCommand

//implementRTTI(InspectCommand, wxCommand);

InspectCommand::InspectCommand (wxView3D *v) : wxViewCommand(v)
{
  oldX = oldY = 0;
  myDx = myDy = 0;
  myInspectTimer = new InspectTimer(this);
  myTimer.reset();
}

InspectCommand::~InspectCommand()
{
  myTimer.stop();
  Report::warning("[InspectCommand::~InspectCommand]");
  delete myInspectTimer;
}

void InspectCommand::execute ()
{
  float x,y;
  
  if (getView()->getMouseEvent().MiddleDown()) {
    myInspectTimer->Stop();
    myTimer.reset();
    myTimer.start();
    getView()->getMouseEvent().Position(&x,&y);
    myDx = 0;
    myDy = 0;
    oldX = x;
    oldY = y;
    // attach normal traversal;
    GLTraversal3D* t = new GLTraversal3D;
    t->setFrameRate (getView()->getRenderer()->getFrameRate());
    getView()->getRenderer()->adoptTraversal(t);        
  } else if (getView()->getMouseEvent().Dragging() && getView()->getMouseEvent().ShiftDown()) {
    getView()->getMouseEvent().Position(&x,&y);
    myDx = x - oldX;
    myDy = y - oldY;
    oldX = x;
    oldY = y;
      
    moveCamera (myDx, myDy);
    getView()->useMotionQuality();
    getView()->OnPaint();
    return;
  } else if (getView()->getMouseEvent().Dragging() && getView()->getMouseEvent().MiddleIsDown()) {
    getView()->getMouseEvent().Position(&x,&y);
    myDx = x - oldX;
    myDy = y - oldY;
    oldX = x;
    oldY = y;  

    rotateAroundLookpoint (myDx, myDy);

    myTimer.reset();
    myTimer.start();
    
    getView()->useMotionQuality();
    getView()->OnPaint();
    return;
  } else if ( getView()->getMouseEvent().MiddleUp()) {
    // check if user stopped for less than 0.2 seconds    
    if ((myTimer.getTime().getRealTime() < .2) && ((myDx != 0.0) || (myDy != 0.0))) {
      // user wants to spin object...
      if (getView()->getRenderer()->getFrameRate() > 0.0) {
//        ostrstream os;
//        os << "[InspectCommand::execute]: Start (";
//        os << (int)(1000.0/getView()->getRenderer()->getFrameRate());
//        os << ")";
//        Report::warning(os);
        // attach special traversal for constant framerate
        wxTraversal3D* t = new wxTraversal3D;
        t->setFrameRate (getView()->getRenderer()->getFrameRate());
        getView()->getRenderer()->adoptTraversal(t);        
        myInspectTimer->Start((int)(1000.0/getView()->getRenderer()->getFrameRate()));
      } else 
        myInspectTimer->Start(1000);        
    } else {
      // user paused, disable spinning...
      getView()->useRenderingQuality();
      getView()->OnPaint();
    }
    myTimer.stop();
    myTimer.reset();
  }
}

void InspectCommand::rotateAroundLookpoint (Real theta, Real phi)
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
  
  Real angle = n^viewing->getUp(); // cos of angle between up and viewdirection
  
  // check if we get to close to polar regions..
  
  if ((angle < -0.9  && phi > 0) || (angle > 0.9 && phi < 0))
    phi = 0;
   
  TransMatrix3D phi_rot;
  phi_rot.rotate(v, sin(dtor(-theta)), cos(dtor(-theta)));
  TransMatrix3D rot = phi_rot;
  rot.rotate(u*phi_rot, sin(dtor(-phi)), cos(dtor(-phi))); 
  
  TransMatrix3D rotateEye;
  rotateEye.translate(-viewing->getLookat());
  rotateEye *= rot;
  rotateEye.translate(viewing->getLookat());

  viewing->setEye(viewing->getEye() * rotateEye);
}

void InspectCommand::moveCamera(Real dx, Real dy)
{
  Viewing3D* viewing = getView()->getRenderer()->getCamera()->getViewing();

  Vector3D eyep  = viewing->getEye();	
  Vector3D lookp = viewing->getLookat();	
  Vector3D up    = viewing->getUp();
  Vector3D direction = eyep - lookp;

  Vector3D dist = eyep-lookp;

  // Move left / right

  Vector3D left = up*(eyep-lookp);
  Vector3D l = -dx * left/left.length()*dist.length()*.005;
  

  // Move forward / backward

  Vector3D m = dy * direction.normalized() * dist.length() * .005;
  eyep += m - l; 
  lookp += m - l;

  viewing->setEye(eyep);
}

void InspectCommand::doMotion ()
{
  // spin object...
  rotateAroundLookpoint (myDx, myDy);
  getView()->useMotionQuality();
  getView()->OnPaint();
}

//-----------------------------------------------------
// class InspectTimer
//-----------------------------------------------------

InspectTimer::InspectTimer (InspectCommand *c)
{
  myInspectCommand = c;
}

void InspectTimer::Notify()
{
  wxWindowsBridge myBridge;
  if (!myBridge.isEventPending())
    myInspectCommand->doMotion();
  else 
    Stop();
}


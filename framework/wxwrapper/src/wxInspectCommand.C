/*
 * $RCSfile: wxInspectCommand.C,v $ 
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
 *  $Id: wxInspectCommand.C,v 1.3 1997/09/19 08:41:56 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "booga/object/Camera3D.h"
#include "booga/object/Viewing3D.h"
#include "booga/wxwrapper/wxInspectCommand.h"
#include "booga/wxwrapper/wxWindowsBridge.h"

//_____________________________________________________________________ wxInspectCommand

implementRTTI(wxInspectCommand, wxViewCommand);

wxInspectCommand::wxInspectCommand (wxView3D *v) : wxViewCommand(v)
{
  oldX = oldY = 0;
  myDx = myDy = 0;
  mywxInspectTimer = new wxInspectTimer(this);
  myTimer.reset();
}

wxInspectCommand::~wxInspectCommand()
{
  myTimer.reset();
  mywxInspectTimer->Stop();
  delete mywxInspectTimer;
}

void wxInspectCommand::execute ()
{
  float x,y;
  
  if (getView()->getMouseEvent().ButtonDown()) {
    mywxInspectTimer->Stop();
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
      
    moveCamera (myDx, myDy);
    getView()->useMotionQuality();
    getView()->OnPaint();
    return;
  } else if (getView()->getMouseEvent().Dragging()) {
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
  } 
  else if ( getView()->getMouseEvent().ButtonUp()) {
/*
    // check if user stopped for less than 0.2 seconds    
    if ((myTimer.getTime().getRealTime() < .2) && ((myDx != 0.0) || (myDy != 0.0))) {
      // user wants to spin object...
      if (getView()->getRenderer()->getFrameRate() > 0.0) {
//        std::stringstream os;
//        os << "[wxInspectCommand::execute]: Start (";
//        os << (int)(1000.0/getView()->getRenderer()->getFrameRate());
//        os << ")";
//        Report::warning(os);
        mywxInspectTimer->Start((int)(1000.0/getView()->getRenderer()->getFrameRate()));
      } else 
        mywxInspectTimer->Start(1000);        
    } else {
      // user paused, disable spinning...
*/
      getView()->useRenderingQuality();
      getView()->OnPaint();
/*
    }
    myTimer.stop();
    myTimer.reset();
*/
  }
}

void wxInspectCommand::rotateAroundLookpoint (Real theta, Real phi)
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

void wxInspectCommand::moveCamera(Real dx, Real dy)
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

void wxInspectCommand::doMotion ()
{
  // spin object...
  rotateAroundLookpoint (myDx, myDy);
  getView()->OnPaint();
}

//-----------------------------------------------------
// class wxInspectTimer
//-----------------------------------------------------

wxInspectTimer::wxInspectTimer (wxInspectCommand *c)
{
  mywxInspectCommand = c;
}

void wxInspectTimer::Notify()
{
  wxWindowsBridge myBridge;
  if (!myBridge.isEventPending())
    mywxInspectCommand->doMotion();
}


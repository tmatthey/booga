/*
 * $RCSfile: wxMotionCommands.C,v $
 *
 * Copyright (C) 1996, Bernhard Buehlmann <buhlmann@iam.unibe.ch>
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
 *  $Id: wxMotionCommands.C,v 1.5 1998/05/22 11:57:50 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/object/Camera3D.h"
#include "booga/object/Viewing3D.h"
#include "booga/object/OrthographicViewing3D.h"
#include "booga/object/PerspectiveViewing3D.h"

#include "booga/component/Picker3D.h"
#include "booga/component/Collector3DFor.h"
#include "booga/component/SetStandardView3D.h"

#include "booga/wxwrapper/wxWindowsBridge.h"
#include "booga/wxwrapper/wxMotionCommands.h"

#include "wx_gdi.h"

wxZoomCommand::wxZoomCommand (wxView3D *v) : wxViewCommand(v)
{
  oldX = oldY = 0.0;
  myDx = myDy = 0.0;
  getView()->SetCursor(new wxCursor(wxCURSOR_MAGNIFIER )); 
}
  

void wxZoomCommand::execute ()
{
  float x,y;
  
  if (getView()->getMouseEvent().ButtonDown()) {
    getView()->getMouseEvent().Position(&x,&y);
    myDx = 0.0;
    myDy = 0.0;
    oldX = x;
    oldY = y;
  } else if (getView()->getMouseEvent().Dragging()) {
    getView()->getMouseEvent().Position(&x,&y);
    myDx = x - oldX;
    myDy = y - oldY;
    oldX = x;
    oldY = y;  

    Viewing3D* viewing = getView()->getRenderer()->getCamera()->getViewing();

	if (dynamic_cast(OrthographicViewing3D, viewing)) {
      if ((viewing->getHFov()+(myDy/50.0)) > 0 && 
		  (viewing->getHFov()+(myDy/50.0)) < M_PI)
        viewing->setHFov(viewing->getHFov()+(myDy/50.0));
	} else {

      Vector3D eyep  = viewing->getEye();	
      Vector3D lookp = viewing->getLookat();	
      Vector3D direction = eyep - lookp;

      Vector3D dist = eyep-lookp;

      // Move forward / backward

      Vector3D m = myDy * direction.normalized() * dist.length() * .005;
      eyep += m; 

      viewing->setEye(eyep);
	}
    getView()->useMotionQuality();
    getView()->OnPaint();
    return;
  } else if ( getView()->getMouseEvent().ButtonUp()) {
  	  getView()->getViewManager()->notify(wxViewManager::CAMERAS_CHANGED,
		  (Object3D *)getView()->getRenderer()->getCamera());

      getView()->useRenderingQuality();
      getView()->OnPaint();
  }
}

wxWalkCommand::wxWalkCommand (wxView3D *v) : wxViewCommand(v)
{
  oldX = oldY = 0.0;
  myDx = myDy = 0.0;
  getView()->SetCursor(new wxCursor(wxCURSOR_BULLSEYE)); 
}


void wxWalkCommand::execute ()
{
  float x,y;
  
  if (getView()->getMouseEvent().ButtonDown()) {
    getView()->getMouseEvent().Position(&x,&y);
    myDx = 0.0;
    myDy = 0.0;
    oldX = x;
    oldY = y;
  } else if (getView()->getMouseEvent().Dragging()) {
    getView()->getMouseEvent().Position(&x,&y);
    myDx = x - oldX;
    myDy = y - oldY;
    oldX = x;
    oldY = y;  

    Viewing3D* viewing = getView()->getRenderer()->getCamera()->getViewing();

    Vector3D eyep  = viewing->getEye();	
    Vector3D lookp = viewing->getLookat();	
    Vector3D up    = viewing->getUp();
    Vector3D left = up*(eyep-lookp);

    Vector3D dist = eyep-lookp;

    // Move forward / backward

	Vector3D new_direction = left*up;

    Vector3D m = myDy * new_direction.normalized() * dist.length() * .005;
    eyep += m; 
    lookp += m; 

    viewing->setEye(eyep);
    viewing->setLookat(lookp);

    getView()->useMotionQuality();
    getView()->OnPaint();
    return;
  } 
  else if ( getView()->getMouseEvent().ButtonUp()) {
  	  getView()->getViewManager()->notify(wxViewManager::CAMERAS_CHANGED,
		  (Object3D *)getView()->getRenderer()->getCamera());

      getView()->useRenderingQuality();
      getView()->OnPaint();
  }
}

wxLookCommand::wxLookCommand (wxView3D *v) : wxViewCommand(v)
{
  oldX = oldY = 0.0;
  myDx = myDy = 0.0;
  getView()->SetCursor(new wxCursor(wxCURSOR_BULLSEYE)); 
}


void wxLookCommand::execute ()
{
  float x,y;
  
  if (getView()->getMouseEvent().ButtonDown()) {
    getView()->getMouseEvent().Position(&x,&y);
    myDx = 0;
    myDy = 0;
    oldX = x;
    oldY = y;
  } else if (getView()->getMouseEvent().Dragging()) {
    getView()->getMouseEvent().Position(&x,&y);
    myDx = x - oldX;
    myDy = y - oldY;
    oldX = x;
    oldY = y;  

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
    phi_rot.rotate(v, sin(dtor(-myDx)), cos(dtor(-myDx)));
    TransMatrix3D rot = phi_rot;
    rot.rotate(u*phi_rot, sin(dtor(-myDy)), cos(dtor(-myDy))); 
  
    TransMatrix3D rotateEye;
    rotateEye.translate(-viewing->getEye());
    rotateEye *= rot;
    rotateEye.translate(viewing->getEye());

    viewing->setLookat(viewing->getLookat() * rotateEye);
  
    getView()->useMotionQuality();
    getView()->OnPaint();
    return;
  } 
  else if ( getView()->getMouseEvent().ButtonUp()) {
  	  getView()->getViewManager()->notify(wxViewManager::CAMERAS_CHANGED,
		  (Object3D *)getView()->getRenderer()->getCamera());

      getView()->useRenderingQuality();
      getView()->OnPaint();
  }
}

wxInspectCommand::wxInspectCommand (wxView3D *v) : wxViewCommand(v)
{
  oldX = oldY = 0;
  myDx = myDy = 0;
  getView()->SetCursor(new wxCursor(wxCURSOR_BULLSEYE)); 
}


void wxInspectCommand::execute ()
{
  float x,y;
  
  if (getView()->getMouseEvent().ButtonDown()) {
    getView()->getMouseEvent().Position(&x,&y);
    myDx = 0;
    myDy = 0;
    oldX = x;
    oldY = y;
  } else if (getView()->getMouseEvent().Dragging()) {
    getView()->getMouseEvent().Position(&x,&y);
    myDx = x - oldX;
    myDy = y - oldY;
    oldX = x;
    oldY = y;  

    Viewing3D* viewing = getView()->getRenderer()->getCamera()->getViewing();

    if (dynamic_cast(OrthographicViewing3D, viewing)) {
      Camera3D *c = (Camera3D*)getView()->getRenderer()->getCamera()->copy();

		// change the viewing to a perspective one
      PerspectiveViewing3D *p = new PerspectiveViewing3D;

 	  p->setEye(viewing->getEye());
 	  p->setLookat(viewing->getLookat());
 	  p->setUp(viewing->getUp());
 	  p->setHFov(45);
	  c->adoptViewing(p);

      getView()->getRenderer()->adoptCamera(c);
	}
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
  
    if ((angle < -0.9  && myDy > 0) || (angle > 0.9 && myDy < 0))
      myDy = 0;
   
    TransMatrix3D phi_rot;
    phi_rot.rotate(v, sin(dtor(-myDx)), cos(dtor(-myDx)));
    TransMatrix3D rot = phi_rot;
    rot.rotate(u*phi_rot, sin(dtor(-myDy)), cos(dtor(-myDy))); 
  
    TransMatrix3D rotateEye;
    rotateEye.translate(-viewing->getLookat());
    rotateEye *= rot;
    rotateEye.translate(viewing->getLookat());

    viewing->setEye(viewing->getEye() * rotateEye);
  
    getView()->useMotionQuality();
    getView()->OnPaint();
    return;
  } 
  else if ( getView()->getMouseEvent().ButtonUp()) {
	  getView()->getViewManager()->notify(wxViewManager::CAMERAS_CHANGED,
		  (Object3D *)getView()->getRenderer()->getCamera());
      getView()->useRenderingQuality();
      getView()->OnPaint();
  }
}

wxPanCommand::wxPanCommand (wxView3D *v) : wxViewCommand(v)
{
  oldX = oldY = 0;
  myDx = myDy = 0;
  getView()->SetCursor(new wxCursor(wxCURSOR_HAND));
}


void wxPanCommand::execute ()
{
  float x,y;
  
  if (getView()->getMouseEvent().ButtonDown()) {
    getView()->getMouseEvent().Position(&x,&y);
    myDx = 0;
    myDy = 0;
    oldX = x;
    oldY = y;
  } else if (getView()->getMouseEvent().Dragging()) {
    getView()->getMouseEvent().Position(&x,&y);
    myDx = x - oldX;
    myDy = y - oldY;
    oldX = x;
    oldY = y;  

    Viewing3D* viewing = getView()->getRenderer()->getCamera()->getViewing();

    Vector3D eyep  = viewing->getEye();	
    Vector3D lookp = viewing->getLookat();	
    Vector3D up    = viewing->getUp();
    Vector3D direction = eyep - lookp;

    Vector3D dist = eyep-lookp;
	Vector3D left = up*(eyep-lookp);
	Vector3D new_up = left*direction;

    Vector3D l = -myDx * left/left.length()*dist.length()*.005;


    // Move forward / backward

    Vector3D m = -myDy * new_up.normalized() * dist.length() * .005;
    eyep += m + l; 
    lookp += m + l;

    viewing->setEye(eyep);
    viewing->setLookat(lookp);

    getView()->useMotionQuality();
    getView()->OnPaint();
    getView()->useRenderingQuality();
    return;
  } else if ( getView()->getMouseEvent().ButtonUp()) {
	  getView()->getViewManager()->notify(wxViewManager::CAMERAS_CHANGED,
		  (Object3D *)getView()->getRenderer()->getCamera());
      getView()->useRenderingQuality();
      getView()->OnPaint();
  }
}

wxGetCloseCommand::wxGetCloseCommand (wxView3D *v) : wxViewCommand(v)
{
  getView()->SetCursor(new wxCursor(wxCURSOR_MAGNIFIER)); 
}

void wxGetCloseCommand::execute()
{  
  float x, y;
  
  getView()->getMouseEvent().Position(&x,&y);
  
  if (getView()->getMouseEvent().ButtonDown()) {
    Picker3D *myPicker = new Picker3D;  
    myPicker->setCamera(getView()->getRenderer()->getCamera()); 
    myPicker->setPickOrigin((int)x, (int)(getView()->getRenderer()->getCamera()->getViewing()->getResolutionY()-y-1));
    myPicker->execute(getView()->getViewManager()->getWorld());

    if (myPicker->getPath() != NULL) {
      Viewing3D* viewing = getView()->getRenderer()->getCamera()->getViewing();
	  if (!viewing) {
		  Report::warning("GetCloseCommand::execute: viewing == NULL!");
		  delete myPicker;
		  return;
	  }

      Vector3D HitPoint = myPicker->getHitPoint(); // store hitpoint
	  Vector3D distance = HitPoint - viewing->getEye();


	  Vector3D oldlookat = viewing->getLookat();
  	  Vector3D oldeye = viewing->getEye();
  

      Vector3D newlookat = HitPoint;
      Vector3D neweye = viewing->getEye()+.75*distance;
	  
      Vector3D dlookat = newlookat - oldlookat;
	  Vector3D deye = neweye - oldeye;


	  Real intervall = 100;
	  Real frames = 10;
      for (Real i=1; i<=intervall; i+=intervall /(Real)frames) {
        Real value = log (i) / log (intervall);
        Vector3D clookat = oldlookat + value*dlookat;
        Vector3D ceye = oldeye + value*deye;
        viewing->setLookat(clookat);
        viewing->setEye(ceye);
		getView()->useMotionQuality();
        getView()->OnPaint();
	  }
	  getView()->getViewManager()->notify(wxViewManager::CAMERAS_CHANGED,
		  (Object3D *)getView()->getRenderer()->getCamera());
      getView()->useRenderingQuality();
      getView()->OnPaint();

	}
 
    delete myPicker;
  }

}

wxPointToCommand::wxPointToCommand (wxView3D *v) : wxViewCommand(v)
{
  getView()->SetCursor(new wxCursor(wxCURSOR_ARROW)); 
}

void wxPointToCommand::execute()
{  
  float x, y;
  
  getView()->getMouseEvent().Position(&x,&y);
  
  if (getView()->getMouseEvent().ButtonDown()) {
    Picker3D *myPicker = new Picker3D;  
    myPicker->setCamera(getView()->getRenderer()->getCamera()); 
    myPicker->setPickOrigin((int)x, (int)(getView()->getRenderer()->getCamera()->getViewing()->getResolutionY()-y-1));
    myPicker->execute(getView()->getViewManager()->getWorld());

    if (myPicker->getPath() != NULL) {
      Viewing3D* viewing = getView()->getRenderer()->getCamera()->getViewing();
	  if (!viewing) {
		  Report::warning("GetCloseCommand::execute: viewing == NULL!");
		  delete myPicker;
		  return;
	  }

      Vector3D HitPoint = myPicker->getHitPoint(); // store hitpoint
      Vector3D oldlookat = viewing->getLookat();
      Vector3D newlookat = HitPoint;
	  
      Vector3D dlookat = newlookat - oldlookat;

	  Real intervall = 100;
	  Real frames = 10;
      for (Real i=1; i<=intervall; i+=intervall /(Real)frames) {
        Real value = log (i) / log (intervall);
        Vector3D clookat = oldlookat + value*dlookat;
        viewing->setLookat(clookat);
		getView()->useMotionQuality();
        getView()->OnPaint();
	  }
	  getView()->getViewManager()->notify(wxViewManager::CAMERAS_CHANGED,
		  (Object3D *)getView()->getRenderer()->getCamera());
      getView()->useRenderingQuality();
      getView()->OnPaint();

	}
 
    delete myPicker;
    getView()->getViewManager()->notify(wxViewManager::CAMERAS_CHANGED,
		  (Object3D *)getView()->getRenderer()->getCamera());

  }

}

wxHomeCommand::wxHomeCommand (wxView3D *v) : wxViewCommand(v)
{
  getView()->SetCursor(new wxCursor(wxCURSOR_BULLSEYE)); 
}

void wxHomeCommand::execute()
{
  Collector3DFor<Camera3D> camCollector;
  camCollector.execute(getView()->getViewManager()->getWorld());
      
  if (!camCollector.count()) {
    SetStandardView3D v;
	v.execute(getView()->getViewManager()->getWorld());
  }

  camCollector.execute(getView()->getViewManager()->getWorld());
	  
  Camera3D* camera = NULL;

  //
  // Look for first camera in newWorld, that is switched on.
  //
  for (camCollector.first(); !camCollector.isDone(); camCollector.next())
    if (camCollector.getObject()->isOn()) {
      camera = camCollector.createTransformedObject(); 
      break;
    }

  if (camera == NULL) {
	Report::error("[GetCloseCommand::execute]:scene contains no active camera");
    exit(1);
  }


  Viewing3D* viewing = getView()->getRenderer()->getCamera()->getViewing();

  Vector3D oldlookat = viewing->getLookat();
  Vector3D oldeye = viewing->getEye();
  

  Vector3D newlookat = camera->getViewing()->getLookat();
  Vector3D neweye = camera->getViewing()->getEye();
	  
  Vector3D dlookat = newlookat - oldlookat;
  Vector3D deye = neweye - oldeye;


  Real intervall = 100;
  Real frames = 10;
  for (Real i=1; i<=intervall; i+=intervall /(Real)frames) {
    Real value = log (i) / log (intervall);
    Vector3D clookat = oldlookat + value*dlookat;
    Vector3D ceye = oldeye + value*deye;
    viewing->setLookat(clookat);
    viewing->setEye(ceye);
    getView()->useMotionQuality();
    getView()->OnPaint();
  }
  getView()->getViewManager()->notify(wxViewManager::CAMERAS_CHANGED,
		  (Object3D *)getView()->getRenderer()->getCamera());
  getView()->useRenderingQuality();
  getView()->OnPaint();
}


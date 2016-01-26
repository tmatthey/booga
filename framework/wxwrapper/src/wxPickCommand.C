/*
 * $RCSfile: wxPickCommand.C,v $
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
 *  $Id: wxPickCommand.C,v 1.3 1997/09/19 08:42:14 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/object/Object3D.h"
#include "booga/object/Disc3D.h"
#include "booga/object/Camera3D.h"
#include "booga/object/PointLight.h"
#include "booga/object/Viewing3D.h"
#include "booga/wxwrapper/wxPickCommand.h"

//_____________________________________________________________________ wxPickCommand

implementRTTI(wxPickCommand, wxViewCommand);

wxPickCommand::wxPickCommand (wxView3D *v) : wxViewCommand (v)
{
  myOldObject = NULL; 
  myMovingFlag = false;
  myOldx = myOldy = 0;
  myPicker = NULL;
}

void wxPickCommand::execute()
{
  Object3D* pickedObject = NULL;
  
  float x, y;
  
  getView()->getMouseEvent().Position(&x,&y);
  
  if (getView()->getMouseEvent().LeftDown()) {
//    myPicker->reset();
    if (myPicker)
      delete myPicker;
    myPicker = new Picker3D;  
    myPicker->setCamera(getView()->getRenderer()->getCamera()); 
    myPicker->setPickOrigin((int)x, (int)(getView()->getRenderer()->getCamera()->getViewing()->getResolutionY()-y-1));
    myPicker->execute(getView()->getViewManager()->getWorld());

    if (myPicker->getPath() != NULL) {
      // select second object in path
      myPicker->getPath()->first(); myPicker->getPath()->next();
      pickedObject = myPicker->getPath()->getObject();
      getView()->getViewManager()->setSelection(pickedObject);
    } else {
      getView()->getViewManager()->clearSelection();
    }    

	//    getView()->OnPaint();
    if (pickedObject && (pickedObject == myOldObject)) {
      Report::warning ("[wxPickCommand::execute]: you've hit the same object, so you wanna move it??");
      myOldHitPoint = myPicker->getHitPoint(); // store hitpoint
      myMovingFlag = true;
    } else
      myMovingFlag = false;
  } else if (getView()->getMouseEvent().Dragging() && myMovingFlag && getView()->getMouseEvent().ShiftDown()) {
    moveObjectVertical();
  } else if (getView()->getMouseEvent().Dragging() && myMovingFlag && getView()->getMouseEvent().ControlDown()) {
    rotateObject();
  } else if (getView()->getMouseEvent().Dragging() && myMovingFlag) {
    moveObjectHorizontal();
  } else if (getView()->getMouseEvent().LeftUp()) {
    myOldObject = getView()->getViewManager()->getSelection();
    if (myMovingFlag)
      getView()->OnPaint();
  }
  myOldx = (int)x;
  myOldy = (int)y;
}

void wxPickCommand::moveObjectHorizontal ()
{
  float x, y;
  Picker3D toolPicker;
  
  getView()->getMouseEvent().Position(&x,&y);
  
  World3D *toolWorld = new World3D;
  BoundingBox b = getView()->getViewManager()->getWorld()->getObjects()->getBounds();
  Vector3D diag = b.getMin() - b.getMax();
  b.expand (diag - b.getMin());
  b.expand (diag + b.getMax());
  
  // we create a disc with center at myOldHitPoint which is twice as big in xy-plane
  Disc3D *theDisc = new Disc3D (2*diag.length(), myOldHitPoint, Vector3D(0,0,1));
  toolWorld->getObjects()->adoptObject(theDisc);
  toolWorld->getObjects()->computeBounds();                                     
  
  // store old picker position
  // Vector3D oldToolPosition = toolPicker.getHitPoint();

  // find point on plane: pick object in toolWorld
  toolPicker.setCamera(getView()->getRenderer()->getCamera()); 
  toolPicker.setPickOrigin((int)x, (int)(getView()->getRenderer()->getCamera()->getViewing()->getResolutionY()-y));
  toolPicker.execute(toolWorld);

  if (toolPicker.getPath() != NULL) {
    // we've hit the plane!
    // calculate the offset to the previous hit-point on the plane

    Vector3D offset = toolPicker.getHitPoint() - myOldHitPoint;
    
    for (long i=0; i<getView()->getViewManager()->getSelection()->countSubobject(); i++) {
      Object3D *obj = getView()->getViewManager()->getSelection()->getSubobject(i);																		    
      // check if this is a pointlight: if so, set it's position (translations
      // with pointlights not yet supported
    
      PointLight *p = dynamic_cast (PointLight, obj);
    
      if (p) {
        p->setPosition (p->getPosition()+offset);
        getView()->getViewManager()->notify(wxViewManager::LIGHTS_CHANGED, obj);
      } else {
        // it is a normal object, translate it with offset
        TransMatrix3D t;
        Transform3D myTrans = obj->getTransform();    
        obj->addTransform (t.makeTranslate (offset));
      }
    
      obj->recomputeBounds(*myPicker->getPath());
      getView()->useMotionQuality();
      getView()->OnPaint();
      getView()->useRenderingQuality();
      myOldHitPoint = toolPicker.getHitPoint();
    }
    getView()->useMotionQuality();
    getView()->OnPaint();
    getView()->useRenderingQuality();
    myOldHitPoint = toolPicker.getHitPoint();
  }
  delete toolWorld;
}

void wxPickCommand::moveObjectVertical ()
{
  float x, y;
  Picker3D toolPicker;
  
  getView()->getMouseEvent().Position(&x,&y);
  
  World3D *toolWorld = new World3D;
  BoundingBox b = getView()->getViewManager()->getWorld()->getObjects()->getBounds();
  Vector3D diag = b.getMin() - b.getMax();
  b.expand (diag - b.getMin());
  b.expand (diag + b.getMax());
  
  // we create a disc with center at myOldHitPoint which is twice as big in xy-plane
  Vector3D eye = getView()->getRenderer()->getCamera()->getViewing()->getEye();
  Vector3D lookp = getView()->getRenderer()->getCamera()->getViewing()->getLookat();
  
  Vector3D dist = lookp - eye;
  
  Disc3D *theDisc = new Disc3D (2*diag.length(), myOldHitPoint, Vector3D(dist.x(), dist.y(), 0));
  toolWorld->getObjects()->adoptObject(theDisc);
  toolWorld->getObjects()->computeBounds();                                     
  
  // store old picker position
  // Vector3D oldToolPosition = toolPicker.getHitPoint();

  // find point on plane: pick object in toolWorld
  toolPicker.setCamera(getView()->getRenderer()->getCamera()); 
  toolPicker.setPickOrigin((int)x, (int)(getView()->getRenderer()->getCamera()->getViewing()->getResolutionY()-y));
  toolPicker.execute(toolWorld);

  if (toolPicker.getPath() != NULL) {
    // we've hit the plane!
    // calculate the offset to the previous hit-point on the plane

    Vector3D offset = toolPicker.getHitPoint() - myOldHitPoint;
    for (long i=0; i<getView()->getViewManager()->getSelection()->countSubobject(); i++) {
      Object3D *obj = getView()->getViewManager()->getSelection()->getSubobject(i);													
    
      // check if this is a pointlight: if so, set it's position (translations
      // with pointlights not yet supported
    
      PointLight *p = dynamic_cast (PointLight, obj);
    
      if (p) {
        p->setPosition (p->getPosition()+offset);
        getView()->getViewManager()->notify(wxViewManager::LIGHTS_CHANGED, obj);
      } else {
        // it is a normal object, translate it with offset
        TransMatrix3D t;
        Transform3D myTrans = obj->getTransform();    
        obj->addTransform (t.makeTranslate (offset));
      }
    
      obj->recomputeBounds(*myPicker->getPath());
    }
    getView()->useMotionQuality();
    getView()->OnPaint();
    getView()->useRenderingQuality();
    myOldHitPoint = toolPicker.getHitPoint();
  }
  delete toolWorld;
}

void wxPickCommand::rotateObject ()
{
  float x, y;
  Picker3D toolPicker;
  
  getView()->getMouseEvent().Position(&x,&y);
  
//  std::stringstream os;
//  os << "[wxPickCommand::rotateObject]: myOldx = " << myOldx;
//  Report::warning(os);
  
  Object3D *obj = getView()->getViewManager()->getSelection();																		
  Vector3D bbmid = obj->getBounds().getMin() + (obj->getBounds().getMax() - obj->getBounds().getMin())/2;

  TransMatrix3D t;
  Transform3D myTrans = obj->getTransform();
  t = t * t.makeTranslate(-bbmid); // translate to origin
  t = t * t.makeRotateZ (dtor(x-myOldx)); // rotate around z axis
  t = t * t.makeTranslate(bbmid); // translate back to bbmid

  obj->addTransform (t); // add the new transformation
  obj->recomputeBounds(*myPicker->getPath()); // recompute the boundingboxes 
  
  getView()->useMotionQuality();
  getView()->OnPaint();
  getView()->useRenderingQuality();
}

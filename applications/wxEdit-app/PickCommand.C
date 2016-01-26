/*
 * $RCSfile: PickCommand.C,v $
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
 *  $Id: PickCommand.C,v 1.4 1997/02/20 09:42:06 matthey Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "PickCommand.h"
#include "GravityCommand.h"
#include "booga/object/Object3D.h"
#include "booga/object/Disc3D.h"
#include "booga/object/Line3D.h"
#include "booga/object/List3D.h"
#include "booga/object/Camera3D.h"
#include "booga/object/PointLight.h"
#include "booga/object/Viewing3D.h"

//_____________________________________________________________________ PickCommand

implementRTTI(PickCommand, wxViewCommand);

PickCommand::PickCommand (wxView3D *v) : wxViewCommand (v)
{
  myOldObject = NULL; 
  myMovingFlag = false;
  myOldx = myOldy = 0;
  myPicker = NULL;
}

void PickCommand::execute()
{  
  // we store the current mouse position
  float x, y;
  getView()->getMouseEvent().Position(&x,&y);
  
  if (getView()->getMouseEvent().ButtonDown() && getView()->getMouseEvent().ShiftDown()) {
    // user wants to add or remove an object to the selection
    if (myPicker)
      delete myPicker;

    myPicker = new Picker3D;
    myMovingFlag = false;
    myOldObject = NULL; // reset 
    
    // setup picker:
    myPicker->setCamera(getView()->getRenderer()->getCamera()); 
    myPicker->setPickOrigin((int)x, (int)(getView()->getRenderer()->getCamera()->getViewing()->getResolutionY()-(int)y-1));
    myPicker->execute(getView()->getViewManager()->getWorld());

    if (myPicker->getPath() != NULL) {
      myPicker->getPath()->first(); myPicker->getPath()->next();
      myOldObject = myPicker->getPath()->getObject();
      getView()->getViewManager()->addToSelection(myOldObject);
    }
  } else if (getView()->getMouseEvent().ButtonDown()) { 
    // user wants to select an object
    if (myPicker)
      delete myPicker;
      
    myPicker = new Picker3D;

    myMovingFlag = false;
    myOldObject = NULL; // reset 
    
    myPicker->setCamera(getView()->getRenderer()->getCamera()); 
    myPicker->setPickOrigin((int)x, (int)(getView()->getRenderer()->getCamera()->getViewing()->getResolutionY()-(int)y-1));
    myPicker->execute(getView()->getViewManager()->getWorld());

    if (myPicker->getPath() != NULL) {
      // select second object in path
      Report::warning ("[PickCommand::execute]: hit!");
      myPicker->getPath()->first(); myPicker->getPath()->next();
      myOldObject = myPicker->getPath()->getObject();
      myOldHitPoint = myPicker->getHitPoint(); // store hitpoint

      if (!getView()->getViewManager()->isSelected(myOldObject)) 
        getView()->getViewManager()->setSelection(myOldObject);
    } else {
      getView()->getViewManager()->clearSelection();
    }    
  } else if (getView()->getMouseEvent().Dragging() && myOldObject && getView()->getMouseEvent().ShiftDown()) {
    myMovingFlag = true;
    moveObjectVertical();
  } else if (getView()->getMouseEvent().Dragging() && myOldObject && getView()->getMouseEvent().ControlDown()) {
    myMovingFlag = true;
    rotateObject();
  } else if (getView()->getMouseEvent().Dragging() && myOldObject ) {
    myMovingFlag = true;
    moveObjectHorizontal();
  } else if (getView()->getMouseEvent().LeftUp() && myOldObject ) {
    myOldObject = getView()->getViewManager()->getSelection();
    if (myMovingFlag) {
//      getView()->OnPaint();
      GravityCommand c(getView());
      c.execute();
    }
  }
  // store old mouse position
  myOldx = (int)x; 
  myOldy = (int)y;
}

void PickCommand::moveObjectHorizontal ()
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
    
      obj->computeBounds();
    }
    getView()->getViewManager()->getWorld()->getObjects()->computeBounds();
    getView()->useMotionQuality();
    getView()->OnPaint();
    getView()->useRenderingQuality();
    myOldHitPoint = toolPicker.getHitPoint();
  }
  delete toolWorld;
}

void PickCommand::moveObjectVertical ()
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
    
      obj->computeBounds();
    }
    getView()->getViewManager()->getWorld()->getObjects()->computeBounds();
    getView()->useMotionQuality();
    getView()->OnPaint();
    getView()->useRenderingQuality();
    myOldHitPoint = toolPicker.getHitPoint();
  }
  delete toolWorld;
}

void PickCommand::rotateObject ()
{
  float x, y;
  Picker3D toolPicker;
  
  getView()->getMouseEvent().Position(&x,&y);
  
//  ostrstream os;
//  os << "[PickCommand::rotateObject]: myOldx = " << myOldx;
//  Report::warning(os);
  for (long i=0; i<getView()->getViewManager()->getSelection()->countSubobject(); i++) {
    Object3D *obj = getView()->getViewManager()->getSelection()->getSubobject(i);													

    Vector3D bbmid = obj->getBounds().getMin() + (obj->getBounds().getMax() - obj->getBounds().getMin())/2;

    TransMatrix3D t;
    Transform3D myTrans = obj->getTransform();
    t = t * t.makeTranslate(-bbmid); // translate to origin
    t = t * t.makeRotateZ (dtor(x-myOldx)); // rotate around z axis
    t = t * t.makeTranslate(bbmid); // translate back to bbmid

    obj->addTransform (t); // add the new transformation
    obj->recomputeBounds(*myPicker->getPath()); // recompute the boundingboxes 
  }
  getView()->useMotionQuality();
  getView()->OnPaint();
  getView()->useRenderingQuality();
}

implementRTTI(SelectCommand, wxViewCommand);

SelectCommand::SelectCommand (wxView3D *v) : wxViewCommand (v)
{
}

void SelectCommand::execute()
{
  // we store the current mouse position
  float x, y;
  getView()->getMouseEvent().Position(&x,&y);
  Picker3D myPicker;
  
  if (getView()->getMouseEvent().ButtonDown() && getView()->getMouseEvent().ShiftDown()) {
    // user wants to add or remove an object to or from the selection
    
    // setup picker:
    myPicker.setCamera(getView()->getRenderer()->getCamera()); 
    myPicker.setPickOrigin((int)x, (int)(getView()->getRenderer()->getCamera()->getViewing()->getResolutionY()-(int)y-1));
    myPicker.execute(getView()->getViewManager()->getWorld());

    if (myPicker.getPath() != NULL) {
      // select second object in path:
      myPicker.getPath()->first(); myPicker.getPath()->next();
      getView()->getViewManager()->addToSelection(myPicker.getPath()->getObject());
    }
  } else if (getView()->getMouseEvent().ButtonDown()) { 
    myPicker.setCamera(getView()->getRenderer()->getCamera()); 
    myPicker.setPickOrigin((int)x, (int)(getView()->getRenderer()->getCamera()->getViewing()->getResolutionY()-(int)y-1));
    myPicker.execute(getView()->getViewManager()->getWorld());

    if (myPicker.getPath() != NULL) {
      // select second object in path
      myPicker.getPath()->first(); myPicker.getPath()->next();
      if (!getView()->getViewManager()->isSelected(myPicker.getPath()->getObject())) 
        getView()->getViewManager()->setSelection(myPicker.getPath()->getObject());
    } else {
      getView()->getViewManager()->clearSelection();
    }    
  }
}

implementRTTI(MoveHorizontalCommand, wxViewCommand);

MoveHorizontalCommand::MoveHorizontalCommand (wxView3D *v) : wxViewCommand (v)
{
  myMovingFlag = false;
  myOldx = myOldy = 0;
}

void MoveHorizontalCommand::execute()
{
  // we store the current mouse position
  float x, y;
  getView()->getMouseEvent().Position(&x,&y);
  Picker3D myPicker;
  
  if (getView()->getMouseEvent().ButtonDown()) {
    // check if we hit one of the selected objects
    
    // setup picker:
    myPicker.setCamera(getView()->getRenderer()->getCamera()); 
    myPicker.setPickOrigin((int)x, (int)(getView()->getRenderer()->getCamera()->getViewing()->getResolutionY()-(int)y-1));
    myPicker.execute(getView()->getViewManager()->getWorld());

    myMovingFlag = false;

    if (myPicker.getPath() != NULL) {
      // select second object in path:
      myPicker.getPath()->first(); myPicker.getPath()->next();
      if (getView()->getViewManager()->isSelected(myPicker.getPath()->getObject())) {
        myOldHitPoint = myPicker.getHitPoint();
        myMovingFlag = true;
      } 
    }
  } else if (getView()->getMouseEvent().Dragging()) { 
    if (myMovingFlag)
      moveObjectHorizontal();
  } else if (getView()->getMouseEvent().LeftUp() && myMovingFlag ) {
    getView()->OnPaint();
  }
  myOldx = (int)x; myOldy = (int)y;
}

void MoveHorizontalCommand::moveObjectHorizontal ()
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
    
      obj->computeBounds();
    }
    getView()->getViewManager()->getWorld()->getObjects()->computeBounds();
    myOldHitPoint = toolPicker.getHitPoint();
    getView()->useMotionQuality();
    List3D* theList = new List3D;
    Line3D* cx = new Line3D(Vector3D(-100, myOldHitPoint[1],myOldHitPoint[2]),
              Vector3D(100, myOldHitPoint[1],myOldHitPoint[2]));
    cx->computeBounds();
    theList->adoptObject(cx);                                    
    Line3D* cy = new Line3D(Vector3D(myOldHitPoint[0], -100, myOldHitPoint[2]),
              Vector3D(myOldHitPoint[0], 100, myOldHitPoint[2]));
    cy->computeBounds(); 
    theList->adoptObject(cy);                                    
    Line3D* cz = new Line3D(Vector3D(myOldHitPoint[0], myOldHitPoint[1], -100),
              Vector3D(myOldHitPoint[0], myOldHitPoint[1], 100));
    cz->computeBounds();
    theList->adoptObject(cz);
                                         
    getView()->getViewManager()->getWorld()->getObjects()->adoptObject(theList);                                             
    getView()->OnPaint();
    getView()->getViewManager()->getWorld()->getObjects()->orphanObject(theList);
    delete theList;
    getView()->useRenderingQuality();
  }
  delete toolWorld;
}

implementRTTI(MoveVerticalCommand, wxViewCommand);

MoveVerticalCommand::MoveVerticalCommand (wxView3D *v) : wxViewCommand (v)
{
  myMovingFlag = false;
  myOldx = myOldy = 0;
}

void MoveVerticalCommand::execute()
{
  // we store the current mouse position
  float x, y;
  getView()->getMouseEvent().Position(&x,&y);
  Picker3D myPicker;
  
  if (getView()->getMouseEvent().ButtonDown()) {
    // check if we hit one of the selected objects
    
    // setup picker:
    myPicker.setCamera(getView()->getRenderer()->getCamera()); 
    myPicker.setPickOrigin((int)x, (int)(getView()->getRenderer()->getCamera()->getViewing()->getResolutionY()-(int)y-1));
    myPicker.execute(getView()->getViewManager()->getWorld());

    myMovingFlag = false;

    if (myPicker.getPath() != NULL) {
      // select second object in path:
      myPicker.getPath()->first(); myPicker.getPath()->next();
      if (getView()->getViewManager()->isSelected(myPicker.getPath()->getObject())) {
        myOldHitPoint = myPicker.getHitPoint();
        myMovingFlag = true;
      } 
    }
  } else if (getView()->getMouseEvent().Dragging()) { 
    if (myMovingFlag)
      moveObjectVertical();
  } else if (getView()->getMouseEvent().LeftUp() && myMovingFlag ) {
    getView()->OnPaint();
  }
  myOldx = (int)x; myOldy = (int)y;
}



void MoveVerticalCommand::moveObjectVertical ()
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

  // find point on plane: pick object in toolWorld
  toolPicker.setCamera(getView()->getRenderer()->getCamera()); 
  toolPicker.setPickOrigin((int)x,(int)(getView()->getRenderer()->getCamera()->getViewing()->getResolutionY()-y));
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
    
      obj->computeBounds();
    }
    getView()->getViewManager()->getWorld()->getObjects()->computeBounds();
    getView()->useMotionQuality();
    myOldHitPoint = toolPicker.getHitPoint();
    Line3D* cx = new Line3D(Vector3D(-100, myOldHitPoint[1],myOldHitPoint[2]),
              Vector3D(100, myOldHitPoint[1],myOldHitPoint[2]));
    cx->computeBounds();                                     
    Line3D* cy = new Line3D(Vector3D(myOldHitPoint[0], -100, myOldHitPoint[2]),
              Vector3D(myOldHitPoint[0], 100, myOldHitPoint[2]));
    cy->computeBounds();                                     
    Line3D* cz = new Line3D(Vector3D(myOldHitPoint[0], myOldHitPoint[1], -100),
              Vector3D(myOldHitPoint[0], myOldHitPoint[1], 100));
    cz->computeBounds();
                                         
    getView()->getViewManager()->getWorld()->getObjects()->adoptObject(cx);                                             
    getView()->getViewManager()->getWorld()->getObjects()->adoptObject(cy);                                            
    getView()->getViewManager()->getWorld()->getObjects()->adoptObject(cz);                                            
    getView()->OnPaint();
    getView()->useRenderingQuality();
    getView()->getViewManager()->getWorld()->getObjects()->orphanObject(cx);
    delete cx;
    getView()->getViewManager()->getWorld()->getObjects()->orphanObject(cy);
    delete cy;
    getView()->getViewManager()->getWorld()->getObjects()->orphanObject(cz);
    delete cz;
                                                    
    myOldHitPoint = toolPicker.getHitPoint();
  }
  delete toolWorld;
}


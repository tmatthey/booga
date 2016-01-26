/*
 * $RCSfile: RotateCommand.C,v $
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
 *  $Id: RotateCommand.C,v 1.3 1997/02/20 09:42:07 matthey Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/object/Line3D.h"
#include "booga/object/Camera3D.h"
#include "booga/object/Viewing3D.h"
#include "booga/component/Picker3D.h"
#include "RotateCommand.h"

implementRTTI(RotateCommand, wxViewCommand);

char *rotateStrings[] = {
  "X",
  "Y",
  "Z"
};

const int rotateCount = 3;


RotateCommand::RotateCommand (wxView3D *v) : wxViewCommand (v), wxDialogBox (NULL, "Rotation")
{
  myMovingFlag = false;
  myAxis = Vector3D(0,0,1);
  myOldx = myOldy = 0;
  myObjectList = new List3D;
  createGUI();

}

RotateCommand::~RotateCommand()
{

  // orphan objects from world;
  getView()->getViewManager()->getWorld()->getObjects()->orphanObject(myObjectList);

  if (myObjectList)
     delete myObjectList;
}

void RotateCommand::execute()
{
  // we store the current mouse position
  float x, y;
  getView()->getMouseEvent().Position(&x,&y);
  Picker3D myPicker;
  
  if (getView()->getMouseEvent().ButtonDown()) {
    // check if we hit one of the selected objects
    
    // setup picker:
    myPicker.setCamera(getView()->getRenderer()->getCamera()); 
    myPicker.setPickOrigin((int)x, (int)(getView()->getRenderer()->getCamera()->getViewing()->getResolutionY()-y-1));
    myPicker.execute(getView()->getViewManager()->getWorld());

    myMovingFlag = false;

    if (myPicker.getPath() != NULL) {
      // select second object in path:
      myPicker.getPath()->first(); myPicker.getPath()->next();
      if (getView()->getViewManager()->isSelected(myPicker.getPath()->getObject())) {
        myMovingFlag = true;
      } 
    }
  } else if (getView()->getMouseEvent().Dragging()) { 
    if (myMovingFlag)
      rotateObject(myAxis, x-myOldx);
  } else if (getView()->getMouseEvent().LeftUp() && myMovingFlag ) {
    getView()->OnPaint();
  }
  myOldx = (int)x; myOldy = (int)y;
}

void RotateCommand::rotateObject (Vector3D axis, Real angle)
{
  for (long i=0; i<getView()->getViewManager()->getSelection()->countSubobject(); i++) {
    Object3D *obj = getView()->getViewManager()->getSelection()->getSubobject(i);													

    Vector3D bbmid = obj->getBounds().getMin() + (obj->getBounds().getMax() - obj->getBounds().getMin())/2;

    TransMatrix3D t;
    Transform3D myTrans = obj->getTransform();
    t = t * t.makeTranslate(-bbmid); // translate to origin
    t = t * t.makeRotate (axis, dtor(angle)); // rotate around axis
    t = t * t.makeTranslate(bbmid); // translate back to bbmid

    obj->addTransform (t); // add the new transformation
    obj->computeBounds(); // recompute the boundingboxes 
  }
  getView()->useMotionQuality();
  getView()->OnPaint();
  getView()->useRenderingQuality();
}

void RotateCommand::createGUI()
{
  myRadio = new wxManagedRadioBox (this, this, "Axis:", -1, -1, -1, -1,
                                   rotateCount, rotateStrings);
  myRadio->SetSelection (2);
  NewLine();
  myMinusButton = new wxManagedButton (this, this, "-90");
  myPlusButton = new wxManagedButton (this, this, "+90");
  
  Fit();
  Show(true);
}

void RotateCommand::widgetCallbackFunction(wxObject* widget, wxCommandEvent& )
{
  if (widget == myRadio) {
    wxManagedRadioBox *c = (wxManagedRadioBox *) widget;

    switch (c->GetSelection()) {
      case 0:
        setAxis(Vector3D(1,0,0));
        break;
      case 1:
        setAxis(Vector3D(0,1,0));
        break;
      case 2:
        setAxis(Vector3D(0,0,1));
        break;
      default: 
        break;
    }
  } else if (widget == myPlusButton) {
    rotateObject (getAxis(), 90);
  } else if (widget == myMinusButton) {
    rotateObject (getAxis(), -90);
  }
}

void RotateCommand::setAxis(Vector3D a)
{
  myAxis = a;
  attachObjects();
}

void RotateCommand::update(wxViewManager::NotifyEvent event, Object3D*)
{
  switch (event) {
    case wxViewManager::SELECTION_CHANGED: {
      attachObjects();
      }
      break;
    default:
      break;
  }
}

void RotateCommand::attachObjects() 
{
  // first orphan old list from world;
  getView()->getViewManager()->getWorld()->getObjects()->orphanObject(myObjectList);
  
  if (myObjectList)
     delete myObjectList;

  myObjectList = new List3D;  
  // check if any objects are selected:
  
  Aggregate3D *a = getView()->getViewManager()->getSelection();
  
  if (!a)
    return;
  if (a->countSubobject() == 0)
    return;
      
  for (long i=0; i<a->countSubobject(); i++) {
    BoundingBox b = a->getSubobject(i)->getBounds();
    Vector3D diag = b.getMax() - b.getMin();
    Vector3D bbmid = b.getMin() + (b.getMax() - b.getMin())/2;
    Vector3D start = bbmid + diag.length()*myAxis;
    Vector3D end   = bbmid - diag.length()*myAxis;
    myObjectList->adoptObject (new Line3D (start,end));
  }
  getView()->getViewManager()->getWorld()->getObjects()->adoptObject(myObjectList);
  getView()->OnPaint();
}

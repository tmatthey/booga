/*
 * $RCSfile: AlignTool.C,v $
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
 *  $Id: AlignTool.C,v 1.3 1997/02/20 09:41:55 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/object/Line3D.h"
#include "booga/object/List3D.h"
#include "booga/texture/Whitted.h"
#include "AlignTool.h"
#include "InspectCommand.h"

//_____________________________________________________________________ AlignTool

implementRTTI(AlignTool, wxBOOGAView);

char *alignStrings[] = {
  "MinX", "MaxX", 
  "MinY", "MaxY",
  "MinZ", "MaxZ"
};

const int alignCount = 6;




AlignTool::AlignTool() : wxBOOGAView(), wxDialogBox (NULL, "Align Selection")
{
  myObjectList = new List3D;
  createGUI();
}

AlignTool::~AlignTool()
{
  // first orphan old list from world;
  getViewManager()->getWorld()->getObjects()->orphanObject(myObjectList);
  if (myObjectList)
    delete myObjectList;
  getViewManager()->notify(wxViewManager::WORLD_CHANGED, NULL);
}

void AlignTool::createGUI ()
{
  myRadioBox = new wxManagedRadioBox (this, this, "Align:", -1, -1, -1, -1,
                                      alignCount, alignStrings);
  NewLine();
  myApply = new wxManagedButton (this, this, "Apply");
  Fit();
  Show(true);
}

int AlignTool::OnClose ()
{
  delete this;
  return 1;
}

void AlignTool::update(wxViewManager::NotifyEvent event, Object3D*)
{
  switch (event) {
    case wxViewManager::SELECTION_CHANGED: {
      if (getViewManager()->getSelection()) {
        if (getViewManager()->getSelection()->countSubobject() > 1) {
          myApply->Enable(true);
        } else {
          myApply->Enable(false);
        }
      }
      attachObjects();
      break;
    }
    
    default:
      break;
  }
}

void AlignTool::execute ()
{
  if (!getViewManager()->getSelection())
    return;
  
  Aggregate3D *a = getViewManager()->getSelection();
  
  if (a->countSubobject() == 0 || a->countSubobject() == 1)
    return;
  
  a->computeBounds();
  BoundingBox bb = a->getBounds();
  
  // move objects...
  
  for (long j=0; j<a->countSubobject(); j++) {
    Object3D *obj = a->getSubobject(j);
    Vector3D diff;
    switch (myRadioBox->GetSelection()) {
      case 0: // minx { 
        diff = Vector3D(bb.getMin()[0]-obj->getBounds().getMin()[0],0,0);
        break;
      case 1: // maxx 
        diff = Vector3D(bb.getMax()[0]-obj->getBounds().getMax()[0],0,0);
        break;
      case 2: // miny 
        diff = Vector3D(0, bb.getMin()[1]-obj->getBounds().getMin()[1], 0);
        break;
      case 3: // maxy 
        diff = Vector3D(0, bb.getMax()[1]-obj->getBounds().getMax()[1], 0);
        break;
      case 4: // minz 
        diff = Vector3D(0,0,bb.getMin()[2]-obj->getBounds().getMin()[2]);
        break;
      case 5: // maxz 
        diff = Vector3D(0,0,bb.getMax()[2]-obj->getBounds().getMax()[2]);
        break;
      default:
        break;
    }
    TransMatrix3D t;
    Transform3D myTrans = obj->getTransform();
    t = t * t.makeTranslate(diff); // translate 
    obj->addTransform (t); // add the new transformation
    obj->computeBounds(); // recompute the boundingboxes 
  }
  
  getViewManager()->notify(wxViewManager::WORLD_CHANGED, NULL);
}

void AlignTool::attachObjects ()
{
  // first orphan old list from world;
  getViewManager()->getWorld()->getObjects()->orphanObject(myObjectList);
  if (myObjectList)
    delete myObjectList;
 
  myObjectList = new List3D;  

  // check if any objects are selected:
  
  Aggregate3D *a = getViewManager()->getSelection();
  
  // compute bounds of selection
  
  a->computeBounds();
  BoundingBox bb = a->getBounds();
  
  Vector3D bbmid = bb.getMin() + ((bb.getMax() - bb.getMin())/2.0);
  Real diag = (bb.getMax() - bb.getMin()).length();
  
  if (!a)
    return;
  if (a->countSubobject() == 0)
    return;


  // find out minimal value:
  
  Vector3D origin, x,y;
  switch (myRadioBox->GetSelection()) {
    case 0: // minx 
      origin = Vector3D(bb.getMin()[0], bbmid[1], bbmid[2]);
      x = Vector3D(0, 0, 1); 
      y = Vector3D(0, 1, 0);
      break;
    case 1: // maxx 
      origin = Vector3D(bb.getMax()[0], bbmid[1], bbmid[2]);
      x = Vector3D(0, 0, 1); 
      y = Vector3D(0, 1, 0);
      break;
    case 2: // miny 
      origin = Vector3D(bbmid[0], bb.getMin()[1], bbmid[2]);
      x = Vector3D(0, 0, 1); 
      y = Vector3D(1, 0, 0);
      break;
    case 3: // maxy 
      origin = Vector3D(bbmid[0], bb.getMax()[1], bbmid[2]);
      x = Vector3D(0, 0, 1); 
      y = Vector3D(1, 0, 0);
      break;
    case 4: // minz 
      origin = Vector3D(bbmid[0], bbmid[1], bb.getMin()[2]);
      x = Vector3D(1, 0, 0); 
      y = Vector3D(0, 1, 0);
      break;
    case 5: // maxz 
      origin = Vector3D(bbmid[0], bbmid[1], bb.getMax()[2]);
      x = Vector3D(1, 0, 0); 
      y = Vector3D(0, 1, 0);
      break;
    default:
      break;
  }
 
  // add disc...
  x = x*(diag/10.0);
  y = y*(diag/10.0);
    
  Whitted *w = new Whitted;
  w->setDiffuse (Color(1,1,1));
  // w->setTransparency (.7);
  //disc->appendTexture(w);
  myObjectList->adoptObject(createGrid(origin,x,y,10));
  myObjectList->computeBounds();  
  getViewManager()->getWorld()->getObjects()->adoptObject(myObjectList);
  getViewManager()->notify(wxViewManager::WORLD_CHANGED, NULL);
}

Aggregate3D* AlignTool::createGrid (Vector3D origin, Vector3D x, Vector3D y, int count)
{
  List3D *l = new List3D;
  
  for (int i=-count; i<count; i++) {
    l->adoptObject (new Line3D (origin - count*x + i*y, origin + count*x + i*y));
    l->adoptObject (new Line3D (origin + i*x - count*y, origin + i*x + count*y));
  }
  l->computeBounds();
  return l;
}

void AlignTool::widgetCallbackFunction(wxObject* widget, wxCommandEvent&)
{
  if (widget == myApply) {
    execute();
  }
  if (widget == myRadioBox) {
    attachObjects();
  }
}


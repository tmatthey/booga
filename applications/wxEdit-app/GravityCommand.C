/*
 * $RCSfile: GravityCommand.C,v $
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
 *  $Id: GravityCommand.C,v 1.4 1997/02/20 09:42:01 matthey Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/object/Viewing3D.h"
#include "booga/object/Ray3D.h"
#include "booga/object/Ray3DFactory.h"
#include "GravityCommand.h"

//_____________________________________________________________________ GravityCommand

implementRTTI(GravityCommand, wxViewCommand);

// compare function for quicksort:

int compare (const void *o1, const void* o2) 
{
  Object3D *obj1 = (Object3D *) o1;
  Object3D *obj2 = (Object3D *) o2;
  if (obj1->getBounds().getMin()[2] < obj2->getBounds().getMin()[2])
    return 1;
  else
    return 0;
}


GravityCommand::GravityCommand(wxView3D *v) : wxViewCommand(v)
{}

void GravityCommand::execute()
{
  Aggregate3D *selection = getView()->getViewManager()->getSelection();
    
  if (!selection)
    return; // nothing to do!

  // sort the bboxes after z-value:

//  Object3D **array = new Object3D*[selection->countSubobject()];
//  for (long i=0; i<selection->countSubobject(); i++) 
//    array[i] = selection->getSubobject(i);
//  
//  qsort (array, sizeof(Object3D*), selection->countSubobject(), compare);

  for (long j=0; j<selection->countSubobject(); j++) {
//    Object3D *obj = array[j];
    Object3D *obj = selection->getSubobject(j);
    // hover object just a little bit...
    TransMatrix3D t;
    Transform3D myTrans = obj->getTransform();    
    obj->addTransform (t.makeTranslate (Vector3D(0,0,.1)));  
    obj->computeBounds();
  
    Vector3D samples[4];
      
    // die vier eckpunkte:
  
    samples[0] = Vector3D (obj->getBounds().getMin());
    samples[1] = Vector3D (obj->getBounds().getMin()[0],obj->getBounds().getMax()[1],obj->getBounds().getMin()[2]);
    samples[2] = Vector3D (obj->getBounds().getMax()[0],obj->getBounds().getMax()[1],obj->getBounds().getMin()[2]);
    samples[3] = Vector3D (obj->getBounds().getMax()[0],obj->getBounds().getMin()[1],obj->getBounds().getMin()[2]);

    Real dist = 100000.0;
    Vector3D theOffset(0,0,0);
    Vector3D gravityVector(0, 0, -1); // we assume gravity = (0,0,-1)
  
    int max_samples = 10;
  
    Vector3D dx = samples[1] - samples[0];
    Vector3D dy = samples[2] - samples[1]; 
  
    for (Real i=0.0; i<1.0; i+=1.0/max_samples) {
      for (Real k=0.0; k<1.0; k+=1.0/max_samples) {
        Vector3D b = samples[0] + i*dx + k*dy;
      
        Ray3D *theRay = Ray3DFactory::createRay(b, gravityVector);

        getView()->getViewManager()->getWorld()->getObjects()->intersect(*theRay);
  
        Vector3D hit = theRay->getHitPoint();
  
        Vector3D offset = hit - b;
    
        if (offset.length() < dist) {
          theOffset = offset;
          dist = offset.length();
        } 
      }
    }
    if (dist > 0.0) {
      interpolateTranslation(obj, theOffset);
      getView()->getViewManager()->getWorld()->getObjects()->computeBounds();
      getView()->OnPaint();
    }  
  }
//  delete array;
}

void GravityCommand::interpolateTranslation (Object3D *obj, Vector3D offset)
{
  Real intervall = 100.0;
  Real frames = 20;
 
//  Aggregate3D *selection = getView()->getViewManager()->getSelection();
 
  for (Real i=1; i<=intervall; i+=intervall /(Real)frames) {
    Real value = log (i) / log (intervall);
//    for (long j=0; j<selection->countSubobject(); j++) {
//    Object3D *obj = selection->getSubobject(j);

    TransMatrix3D t;
    Transform3D myTrans = obj->getTransform();    
    obj->addTransform (t.makeTranslate (value*offset));
    obj->computeBounds();
//    }
    offset -= value*offset;
    getView()->useMotionQuality();
    getView()->OnPaint();
    getView()->useRenderingQuality();
  }
}

implementRTTI(ReorderGravityCommand, wxViewCommand);

ReorderGravityCommand::ReorderGravityCommand(wxView3D *v) : wxViewCommand(v)
{
}


void ReorderGravityCommand::execute()
{

  Aggregate3D *a = getView()->getViewManager()->getWorld()->getObjects();
  
  if (a->countSubobject()==0)
    return;
  
  Object3D **array = new Object3D*[a->countSubobject()];
  for (long i=0; i<a->countSubobject(); i++) 
    array[i] = a->getSubobject(i);
  
  qsort (array, sizeof(Object3D*), a->countSubobject(), compare);

  for (long j=0; j<a->countSubobject(); j++) {
    Object3D *obj = array[j];
    // hover object just a little bit...
    TransMatrix3D t;
    Transform3D myTrans = obj->getTransform();    
    obj->addTransform (t.makeTranslate (Vector3D(0,0,.1)));  
    obj->computeBounds();
  
    Vector3D samples[4];
    
    // die vier eckpunkte:
  
    samples[0] = Vector3D (obj->getBounds().getMin());
    samples[1] = Vector3D (obj->getBounds().getMin()[0],obj->getBounds().getMax()[1],obj->getBounds().getMin()[2]);
    samples[2] = Vector3D (obj->getBounds().getMax()[0],obj->getBounds().getMax()[1],obj->getBounds().getMin()[2]);
    samples[3] = Vector3D (obj->getBounds().getMax()[0],obj->getBounds().getMin()[1],obj->getBounds().getMin()[2]);

    Real dist = 100000.0;
    Vector3D theOffset(0,0,0);
    Vector3D gravityVector(0, 0, -1); // we assume gravity = (0,0,-1)
  
    int max_samples = 10;
  
    Vector3D dx = samples[1] - samples[0];
    Vector3D dy = samples[2] - samples[1]; 
  
    for (Real i=0.0; i<1.0; i+=1.0/max_samples) {
      for (Real k=0.0; k<1.0; k+=1.0/max_samples) {
        Vector3D b = samples[0] + i*dx + k*dy;
      
        Ray3D *theRay = Ray3DFactory::createRay(b, gravityVector);

        getView()->getViewManager()->getWorld()->getObjects()->intersect(*theRay);
  
        Vector3D hit = theRay->getHitPoint();
  
        Vector3D offset = hit - b;
    
        if (offset.length() < dist) {
          theOffset = offset;
          dist = offset.length();
        } 
      }
    }
  }
  getView()->OnPaint();
//    if (dist > 0.0) {
//      interpolateTranslation(theOffset);
//      getView()->getViewManager()->getWorld()->getObjects()->computeBounds();
//    }
//  }  
}


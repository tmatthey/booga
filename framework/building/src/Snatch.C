/*
 * $RCSfile: Snatch.C,v $
 *
 * Copyright (C) 1997, Thierry Matthey <matthey@iam.unibe.ch>
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
 *  $Id: Snatch.C,v 1.3 1997/02/06 14:14:05 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/building/Snatch.h"
#include "booga/building/Building.h"
#include "booga/object/Aggregate3D.h"
#include "booga/object/Primitive3D.h"
#include "booga/object/MakeableHandler.h"
#include "booga/object/DummyMakeable.h"
#include "booga/object/Ray3D.h"
#include "booga/object/Ray3DFactory.h"

// ____________________________________________________________________ Snatch

implementRTTI(Snatch, BuildingObject);

Snatch::Snatch()
{} 

Snatch::Snatch(Exemplar exemplar)
:BuildingObject(exemplar)
{} 

Object3D* Snatch::createSubject(Building* building) const
{  
  if (building->getHeight() < EPSILON || ! isOn())
    return new NullObject3D();

  Vector3D from,to, r;
  getRaySegment(from,to);

  r = to-from;
  if (r.length() < EPSILON)
    return new NullObject3D();
  r.normalize();

  Object3D* snatch = getSnatchObjects(building);
  if (snatch == NULL)
    return new NullObject3D();
  
  snatch->computeBounds();
  if(snatch->getBounds().isEmpty()){
    Report::hint("[Snatch::createSubject] no snatch object hit");  
    return new NullObject3D();
  }
  
  Vector3D min(snatch->getBounds().getMin());
  Vector3D max(snatch->getBounds().getMax());
  Real l = (max - min).length();

  long index;  
  if (fabs(r.z()) >= fabs(r.y()) && fabs(r.z()) >= fabs(r.x()))
    index = 2;
  else if (fabs(r.y()) >= fabs(r.x()))
    index = 1;  
  else 
    index = 0;

  // compute the start point of the ray
  Vector3D start;
  start[index] = ((max + min)[index])*0.5;
  Real t = (start[index] - from[index])/r[index];
  start[(index+1)%3] = from[(index+1)%3] + r[(index+1)%3]*t;
  start[(index+2)%3] = from[(index+2)%3] + r[(index+2)%3]*t;
  start -= l*r;
  
  Ray3D* ray = Ray3DFactory::createRay(start,r);
  Object3D* subject;
  
  if (snatch->intersect(*ray)){
    Vector3D hitpoint = ray->getHitPoint();
    Vector3D normal(0,0,0);
    Primitive3D* primitive = NULL;
    for (ray->getPath()->first(); !ray->getPath()->isDone(); ray->getPath()->next()){
      primitive = dynamic_cast<Primitive3D*>(ray->getPath()->getObject());
      if (primitive){
        normal = primitive->normal(hitpoint);
        if (normal.length() > EPSILON)
          break;
      }
    }
    
    Snatch* This = (Snatch*)this;
    This->setTransform(getRotation(hitpoint, normal));
    This->addTransform(TransMatrix3D::makeTranslate(hitpoint));
    subject = doCreateSubject(building);
  }
  else {
    Report::hint("[Snatch::createSubject] no snatch object hit");  
    subject = new NullObject3D();
  }
  
  // clean up
  delete ray;

  Aggregate3D* aggregate = dynamic_cast<Aggregate3D*>(snatch);
  if (aggregate){
    while(aggregate->countSubobject()){
      Object3D* obj = aggregate->getSubobject(0);
      aggregate->orphanObject(obj);
    }
    delete aggregate;
  }
  
  return subject;
}

int Snatch::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  // 
  // Let papa do the rest ...
  //
  return BuildingObject::setSpecifier(errMsg, specifier);
}

void Snatch::iterateAttributes(MakeableHandler *handler) {
  this->BuildingObject::iterateAttributes(handler);
}

TransMatrix3D Snatch::getRotation(const Vector3D &, const Vector3D &) const
{
  return TransMatrix3D();
}

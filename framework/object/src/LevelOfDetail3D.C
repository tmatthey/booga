/*
 * $RCSfile: LevelOfDetail3D.C,v $ 
 *
 * Copyright (C) 1994-98, Bernhard Buehlmann <buhlmann@iam.unibe.ch>
 *                        University of Berne, Switzerland
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
 *  $Id: LevelOfDetail3D.C,v 1.1 1998/05/06 07:33:30 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Value.h"
#include "booga/object/LevelOfDetail3D.h"
#include "booga/object/MakeableHandler.h"


//_______________________________________________________________________ LevelOfDetail3D

implementRTTI(LevelOfDetail3D, Aggregate3D);

LevelOfDetail3D::LevelOfDetail3D() {}

LevelOfDetail3D::LevelOfDetail3D(Exemplar exemplar) 
: Aggregate3D(exemplar)
{
  myActiveObject = 0;
}

Aggregate3D* LevelOfDetail3D::makeEmpty() const
{
  return new LevelOfDetail3D;
}

void LevelOfDetail3D::removeDistances()
{
  myDistanceList.removeAll();
}

void LevelOfDetail3D::addDistance(Real d)
{
  myDistanceList.append(d);
}

Real LevelOfDetail3D::countDistances()
{
  return myDistanceList.count();
}

Real LevelOfDetail3D::getDistance(long i)
{
  if (i >= 0 && i < myDistanceList.count())
    return myDistanceList.item(i);
  else 
    return 0.0;
}

void LevelOfDetail3D::setActiveObject (int i)
{
  myActiveObject = i;
}

Object3D* LevelOfDetail3D::copy() const
{
  return new LevelOfDetail3D(*this);
}

long LevelOfDetail3D::countSubobject() const
{
 if (myElements.count())
   return 1;
 else
   return 0;

}

Object3D* LevelOfDetail3D::getSubobject(long)
{
  long m = myElements.count()-1;
  return myElements.item(min(m,(long)myActiveObject));
}

bool LevelOfDetail3D::doIntersect(Ray3D& ray)
{
  bool hit = false;

  if (myElements.count())
    if (myElements.item(0)->intersect(ray))
      hit = true;

  return hit;
}

Makeable* LevelOfDetail3D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  if (parameters == NULL) {
    errMsg = "No parameters specified. Use Real values for intervals";   
    return NULL;
  }
  
  LevelOfDetail3D* newLevelOfDetail = new LevelOfDetail3D(*this);

  newLevelOfDetail->removeDistances();

  for (int i=1; i<=parameters->count() ; i++) {
    getParameter(i, Real, number);
    newLevelOfDetail->addDistance(number);
  }

  return newLevelOfDetail;
}

static const RCString LevelOfDetail3DKeyword("levelOfDetail");

RCString LevelOfDetail3D::getKeyword() const {
  return LevelOfDetail3DKeyword;
}

List<Value*>* LevelOfDetail3D::createParameters()
{
  List<Value*>* parameters = new List<Value*>;
  for(long i=0; i<myDistanceList.count();i++){
    parameters->append(new Value(myDistanceList.item(i)));
  }
  return parameters;
}

void LevelOfDetail3D::iterateAttributes(MakeableHandler *handler)
{
  Object3D::iterateAttributes(handler);
  
  for(long i=0; i<myElements.count();i++)
    handler->handle(myElements.item(i));
}

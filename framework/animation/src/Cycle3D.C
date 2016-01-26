/*
 * $RCSfile: Cycle3D.C,v $
 *
 * Copyright (C) 1995-96, Thierry Matthey <matthey@iam.unibe.ch>
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
 *  $Id: Cycle3D.C,v 1.1 1996/11/18 15:43:26 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <strstream.h>
#include "booga/base/mathutilities.h"
#include "booga/base/Report.h"
#include "booga/base/Value.h"
#include "booga/base/Vector3D.h"
#include "booga/object/List3D.h"
#include "booga/object/DummyMakeable.h"
#include "booga/object/MakeableHandler.h"
#include "booga/animation/ActionInfo.h"
#include "booga/animation/Cycle3D.h"

// ____________________________________________________________________ Cycle3D

implementRTTI(Cycle3D, Animation3D);

Cycle3D::Cycle3D(Exemplar)
{
  myLastObjectNum = 0;
}

Cycle3D::Cycle3D()
{
  myLastObjectNum = 0;
}

bool Cycle3D::doFrame(Real frame)
{
  Real ticks = 0;
  long count = 0;
 
  count = (myAnimatedObjects == NULL) ? 0 : myAnimatedObjects->countSubobject();

  if (count == 0)
    return false;
    
  for(long i = 0; i < myActionList.count() ; i++){
    ActionInfo* item = myActionList.item(i);
    if (item->isCycle()) {
      ticks += item->computeTicks(frame);
    }
    else {
      ostrstream os;
      os << "[Cycle3D::doTicks] action ("
         <<  item->getStartFrame() << ","
         <<  item->getEndFrame() << ") not of type Cycle3D. Skip";
      Report::recoverable(os);          
    }
  }
  
  long n = ((long)(ticks * count)) % count;

  if (n < 0)
    n += count;
    
  if (myLastObjectNum == n)
    return false;
  else {  
    myLastObjectNum = n;
    return true;  
  }
}  

Object3D* Cycle3D::copy() const
{
  return new Cycle3D(*this);
}

Makeable* Cycle3D::make(RCString&, const List<Value*>* ) const
{
  Cycle3D* newCycle = new Cycle3D(*this);

  return newCycle;
}

static const RCString cycleKeyword("cycle");

RCString Cycle3D::getKeyword() const 
{
  return cycleKeyword;
}

void Cycle3D::iterateAttributes(MakeableHandler *handler)
{
  Object3D::iterateAttributes(handler);
  for(long i=0; i<myActionList.count(); i++)
    handler->handle(myActionList.item(i));
  
  if (myAnimatedObjects != NULL)
    for(long i=0; i<myAnimatedObjects->countSubobject();i++)
      handler->handle(myAnimatedObjects->getSubobject(i));

}

int Cycle3D::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  //
  // There might be an object passed, so lets try to cast
  // specifier to Object3D* :
  //
  // Take all Object3D and make a list of it
  //
  Object3D* object = dynamic_cast(Object3D, specifier);
  if (object != NULL) {
    List3D* list = dynamic_cast(List3D, myAnimatedObjects);
    if (list == NULL){
      delete myAnimatedObjects;
      list = new List3D;
      myAnimatedObjects = list;
    }
    list->adoptObject(object);

    return 1;
  }

  // 
  // Let papa do the rest ...
  //
  return Animation3D::setSpecifier(errMsg, specifier);
}

bool Cycle3D::doIntersect(Ray3D& ray)
{
  // Do the intersect with the actual object
  if (myAnimatedObjects != NULL)
    return myAnimatedObjects->getSubobject(myLastObjectNum)->intersect(ray);
  else
    return false;
}

void Cycle3D::doComputeBounds()
{
  // Return the bounds of the actual object
  if (myAnimatedObjects != NULL)
    myBounds.expand(myAnimatedObjects->getSubobject(myLastObjectNum)->getBounds());
}

Object3D* Cycle3D::getSubobject(long index) 
{
  if (index != 0){
    Report::error("[Cycle3D::getSubobject] index out of range");
    return NULL;
  }
  else
    if (myAnimatedObjects == NULL)
      return NULL;
    else
      return  myAnimatedObjects->getSubobject(myLastObjectNum);
}


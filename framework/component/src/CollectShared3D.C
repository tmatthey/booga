/*
 * $RCSfile: CollectShared3D.C,v $
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
 *                        Andrey Collison <collison@iam.unibe.ch>
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
 *  $Id: CollectShared3D.C,v 1.9 1996/09/13 08:03:44 streit Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "booga/object/Shared3D.h"
#include "booga/component/CollectShared3D.h"

//______________________________________________________________ CollectShared3D

implementRTTI(CollectShared3D, Operation3D);

CollectShared3D::CollectShared3D()
{
  mySortList = true;
}

void CollectShared3D::setSortCollection(bool sort)
{
  mySortList = sort;
}

bool CollectShared3D::getSortCollection() const
{
  return mySortList;
}

Shared3D* CollectShared3D::getCurrent() const
{
  return curItem();
}

bool CollectShared3D::preprocessing()
{
  if (!Operation3D::preprocessing())
    return false;

  myShared.removeAll();
  myCurrent = 0;

  return true;
}

Traversal::Result CollectShared3D::visit(Shared3D* obj)
{
  RCString sharedTypeName = obj->getTypeName();

  long i;
  // List will only be sorted, if flag is true (default)
  if (mySortList) {
    for (i=0; i<myShared.count(); i++) {
      // already stored in the list? Tests subobject not typename, 
      // as differnt types might have same name
      // e.g. after a makeUnique call
      if (obj->getSubobject(0) == myShared.item(i)->getSubobject(0)) {
        break;
      }
      // insert the element at the current position if the name is "smaller" 
      // than the one stored in the list -> insertion sort
      if (sharedTypeName < myShared.item(i)->getTypeName()) {
        myShared.insert(i, obj);
        break;
      }
    }
    if (i>=myShared.count()) {
      myShared.append(obj);
    }
  }
  else {
    for (i=0; i<myShared.count(); i++) {
      // already stored in the list?
      // Tests subobject as differnt types might have same name
      // e.g. after a makeUnique call
      if (obj->getSubobject(0) == myShared.item(i)->getSubobject(0)) {
        // move object to the end of list
        // this results in a special list order
        // where object A allways preceeds object B when A depends on (has-a) B
        myShared.remove(i);
        i = myShared.count(); // force later appending of object
        break;
      }
    }
    if (i>=myShared.count()) {
      myShared.append(obj);
    }
  }
  return Traversal::CONTINUE;
}

List<Shared3D*>* CollectShared3D::getContainer()
{
  return &myShared;
}

Traversal::Result CollectShared3D::dispatch(Makeable* obj)
{
  tryConcrete(Shared3D, obj);
  
  return Traversal::CONTINUE;
}

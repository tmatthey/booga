/*
 * $RCSfile: CollectShared2D.C,v $
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: CollectShared2D.C,v 1.8 1996/09/13 08:03:37 streit Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "booga/object/Shared2D.h"
#include "booga/component/CollectShared2D.h"

//______________________________________________________________ CollectShared2D

implementRTTI(CollectShared2D, Operation2D);

CollectShared2D::CollectShared2D()
{
  mySortList = true;
}

void CollectShared2D::setSortCollection(bool sort)
{
  mySortList = sort;
}

bool CollectShared2D::getSortCollection() const
{
  return mySortList;
}

Shared2D* CollectShared2D::getCurrent() const
{
  return curItem();
}

bool CollectShared2D::preprocessing()
{
  if (!Operation2D::preprocessing())
    return false;

  myShared.removeAll();
  myCurrent = 0;

  return true;
}

Traversal::Result CollectShared2D::visit(Shared2D* obj)
{
  RCString sharedTypeName = obj->getTypeName();

  long i;
  // List will only be sorted, if flag is true (default)
  if (mySortList) {
    for (i=0; i<myShared.count(); i++) {
      // already stored in the list?
      // Tests subobject as differnt types might have same name
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
        break;
        // move object to the end of list
        // this results in a special list order
        // where object A allways preceeds object B when A depends on (has-a) B

        // myShared.remove(i);
        // i = myShared.count(); // force later appending of object
        // break;
      }
    }
    if (i>=myShared.count()) {
      myShared.append(obj);
    }
  }
  return Traversal::CONTINUE;
}

List<Shared2D*>* CollectShared2D::getContainer()
{
  return &myShared;
}

Traversal::Result CollectShared2D::dispatch(Makeable* obj)
{
  tryConcrete(Shared2D, obj);
  
  return Traversal::CONTINUE;
}

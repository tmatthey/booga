/*
 * $RCSfile: CollectBuilding.C,v $
 *
 * Copyright (C) 1994-96, Andrey Collison <collison@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: CollectBuilding.C,v 1.4 1996/09/13 08:03:47 streit Exp $
 * -----------------------------------------------------------------------------
 */ 

#include "booga/object/Object3D.h"
#include "booga/building/Building.h"
#include "CollectBuilding.h"

//______________________________________________________________ CollectBuilding

implementRTTI(CollectBuilding, Operation3D);

CollectBuilding::CollectBuilding()
{
  mySortList = true;
}

void CollectBuilding::setSortCollection(bool sort)
{
  mySortList = sort;
}

bool CollectBuilding::getSortCollection() const
{
  return mySortList;
}

Building* CollectBuilding::getCurrent() const
{
  return curItem();
}

bool CollectBuilding::preprocessing()
{
  if (!Operation3D::preprocessing())
    return false;

  myBuilding.removeAll();
  myCurrent = 0;

  return true;
}

Traversal::Result CollectBuilding::visit(Building* obj)
{
  myBuilding.append(obj);
  return Traversal::PRUNE;
}

List<Building*>* CollectBuilding::getContainer()
{
  return &myBuilding;
}

Traversal::Result CollectBuilding::dispatch(Makeable* obj)
{
  tryConcrete(Building, obj);
  
  return Traversal::CONTINUE;
}

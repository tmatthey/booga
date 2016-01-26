/*
 * $RCSfile: CollectTexture3D.C,v $
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
 *  $Id: CollectTexture3D.C,v 1.4 1996/09/13 08:03:47 streit Exp $
 * -----------------------------------------------------------------------------
 */ 

#include "booga/object/Object3D.h"
#include "booga/object/Texture3D.h"
#include "booga/component/CollectTexture3D.h"

//______________________________________________________________ CollectTexture3D

implementRTTI(CollectTexture3D, Operation3D);

CollectTexture3D::CollectTexture3D()
{
  mySortList = true;
}

void CollectTexture3D::setSortCollection(bool sort)
{
  mySortList = sort;
}

bool CollectTexture3D::getSortCollection() const
{
  return mySortList;
}

Texture3D* CollectTexture3D::getCurrent() const
{
  return curItem();
}

bool CollectTexture3D::preprocessing()
{
  if (!Operation3D::preprocessing())
    return false;

  myTexture.removeAll();
  myCurrent = 0;

  return true;
}

Traversal::Result CollectTexture3D::visit(Object3D* obj)
{
  Texture3D* texture = (Texture3D*)obj->getTexture();
  if (texture == NULL) {
    return Traversal::CONTINUE;
  }
  RCString textureName = texture->getName();
  if (textureName.isEmpty()) {
    return Traversal::CONTINUE;
  } 

  long i;
  // List will only be sorted, if flag is true (default)
  if (mySortList) {
    for (i=0; i<myTexture.count(); i++) {
      // already stored in the list
      if (textureName == myTexture.item(i)->getName()) {
        break;
      }
      // insert the element at the current position if the name is "smaller" 
      // than the one stored in the list -> insertion sort
      if (textureName < myTexture.item(i)->getName()) {
        myTexture.insert(i, texture);
        break;
      }
    }
    if (i>=myTexture.count()) {
      myTexture.append(texture);
    }
  }
  else {
    for (i=0; i<myTexture.count(); i++) {
      // already stored in the list
      if (textureName == myTexture.item(i)->getName()) {      
        // move object to the end of list
        // this results in a special list order
        // where object A allways preceeds object B when A depends on (has-a) B
        myTexture.remove(i);
        i = myTexture.count(); // force later appending of object
        break;
      }
    }
    if (i>=myTexture.count()) {
      myTexture.append(texture);
    }
  }
  return Traversal::CONTINUE;
}

List<Texture3D*>* CollectTexture3D::getContainer()
{
  return &myTexture;
}

Traversal::Result CollectTexture3D::dispatch(Makeable* obj)
{
  tryAbstract(Object3D, obj);
  
  return Traversal::CONTINUE;
}

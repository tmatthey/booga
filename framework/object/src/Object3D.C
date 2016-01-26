/*
 * $RCSfile: Object3D.C,v $
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: Object3D.C,v 1.22 1996/10/30 08:34:18 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/TransMatrix3D.h"
#include "booga/object/Texture3D.h"
#include "booga/object/Texture3DList.h"
#include "booga/object/Object3D.h"
#include "booga/object/Path3D.h"
#include "booga/object/DummyMakeable.h"
#include "booga/object/MakeableHandler.h"

//_____________________________________________________________________ Object3D

//implementRTTI(Object3D, BOOGAObject);
// weil GNU nicht template + static data kann

implementRTTI(Object3D, Makeable);

Object3D::Object3D()
{
  myTexture = NULL;
}

Object3D::Object3D(Exemplar)
{
  myTexture = NULL; 
}

Object3D::Object3D(const Object3D& object)
: BOOGAObject<Object3D,Transform3D,Vector3D,BoundingBox,Ray3D>(object)
{
  myTransform = object.myTransform;

  if (object.myTexture != NULL)
    myTexture = object.myTexture->copy();
  else
    myTexture = NULL;
}

Object3D::~Object3D()
{
  delete myTexture;
}

void Object3D::recomputeBounds(const Path3D& path)
{
  Object3D* obj;
  
  for (path.last(); !path.isDone(); path.prev()) { 
    obj = path.getObject();
    obj->myBounds.reset();
    obj->doComputeBounds();
    //
    // Apply local transformation.
    //
    if (!obj->myTransform.isIdentity())
      obj->myBounds.transform(obj->myTransform.getTransMatrix());

    //
    // Ensure that the bound of the object is valid:
    //    Empty bound or 
    //    Extension in any dimension does not equal zero.
    //
    obj->myBounds.inflate(); 
  }
}

void Object3D::resetBounds(const Path3D& path)
{
  for (path.last(); !path.isDone(); path.prev())
    path.getObject()->myBounds.reset();
}

void Object3D::appendTexture(Texture3D* adoptTexture)
{
  if (myTexture == NULL)
    myTexture = adoptTexture;
  else {
    //
    //  Check if we already have a Texture3DList.
    //
    Texture3DList* textureList = dynamic_cast<Texture3DList*>(myTexture);

    // Yes -> add 'texture' to the list.
    if (textureList != NULL) 
      textureList->appendTexture(adoptTexture);
    // No -> create new list and add 'texture', myTexture to the list.
    else {
      textureList = new Texture3DList;
      textureList->appendTexture(myTexture);
      textureList->appendTexture(adoptTexture);
      myTexture = textureList;
    }
  }
}

Texture3D* Object3D::orphanTexture()
{
  Texture3D* tmp = myTexture;
  myTexture = NULL;
  
  return tmp;
}

int Object3D::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  //
  // There are not so many different valid specifier types:
  // First lets try, if it is a Texture3D ...
  //
  Texture3D* texture = dynamic_cast<Texture3D*>(specifier);
  if (texture != NULL) {
    appendTexture(texture);
    return 1;
  } 
  //
  // Now let's try to if we have a Transform3D object ...
  //
  else {
    Transform3D* transform = dynamic_cast<Transform3D*>(specifier);
    if (transform != NULL) {
      addTransform(*transform);
      delete transform;
      return 1;
    }
  }

  // 
  // Let papa do the rest ...
  //
  return BOOGAObject<Object3D,Transform3D,Vector3D,BoundingBox,Ray3D>::setSpecifier(errMsg, specifier);
}

void Object3D::iterateAttributes(MakeableHandler *handler) {
  if (myTransform.getTransMatrix() != TransMatrix3D::getIdentity()) {
    handler->handle(&myTransform);
  }
  if (myTexture != NULL) {
    handler->handle(myTexture);
  }
}


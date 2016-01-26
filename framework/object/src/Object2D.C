/*
 * $RCSfile: Object2D.C,v $
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
 *  $Id: Object2D.C,v 1.22 1996/10/30 08:34:17 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/TransMatrix2D.h"
#include "booga/object/Texture2D.h"
#include "booga/object/Texture2DList.h"
#include "booga/object/Object2D.h"
#include "booga/object/Path2D.h"
#include "booga/object/MakeableHandler.h"

//_____________________________________________________________________ Object2D

//implementRTTI(Object2D,'BOOGAObject<Object2D, Transform2D, Vector2D, BoundingRect, Ray2D>');
// !!! weil GNU nicht template + static data kann

implementRTTI(Object2D, Makeable);

Object2D::Object2D()
{
  myTexture = NULL;
}

Object2D::Object2D(Exemplar)
{
  myTexture = NULL; 
}

Object2D::Object2D(const Object2D& object)
: BOOGAObject<Object2D, Transform2D, Vector2D, BoundingRect, Ray2D>(object)
{
  myTransform = object.myTransform;

  if (object.myTexture != NULL)
    myTexture = object.myTexture->copy();
  else
    myTexture = NULL;
}

Object2D::~Object2D()
{
  if (myTexture)     
    delete myTexture;
}

void Object2D::recomputeBounds(const Path2D& path)
{
  Object2D* obj;
  
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

void Object2D::appendTexture(Texture2D* adoptTexture)
{
  if (myTexture == NULL)
    myTexture = adoptTexture;
  else {
    //
    //  Check if we already have a Texture2DList.
    //
    Texture2DList* textureList = dynamic_cast<Texture2DList*>(myTexture);

    // Yes -> add 'texture' to the list.
    if (textureList != NULL) 
      textureList->appendTexture(adoptTexture);
    // No -> create new list and add 'texture', myTexture to the list.
    else {
      textureList = new Texture2DList;
      textureList->appendTexture(myTexture);
      textureList->appendTexture(adoptTexture);
      myTexture = textureList;
    }
  }
}

Texture2D* Object2D::orphanTexture()
{
  Texture2D* tmp = myTexture;
  myTexture = NULL;
  
  return tmp;
}

int Object2D::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  //
  // There are not so many different valid specifier types:
  // First lets try, if it is a Texture2D ...
  //
  Texture2D* texture = dynamic_cast<Texture2D*>(specifier);
  if (texture != NULL) {
    appendTexture(texture);
    return 1;
  } 
  //
  // Now let's try to if we have a Transform2D object ...
  //
  else {
    Transform2D* transform = dynamic_cast<Transform2D*>(specifier);
    if (transform != NULL) {
      addTransform(*transform);
      delete transform;
      return 1;
    }
  }

  // 
  // Let papa do the rest ...
  //
  return BOOGAObject<Object2D,Transform2D,Vector2D,BoundingRect,Ray2D>::setSpecifier(errMsg, specifier);
}

void Object2D::iterateAttributes(MakeableHandler *handler) {
  if (myTransform.getTransMatrix() != TransMatrix2D::getIdentity()) {
    handler->handle(&myTransform);
  }
  if (myTexture != NULL) {
    handler->handle(myTexture);
  }
}

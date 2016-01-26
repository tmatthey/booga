/*
 * $RCSfile: Texture2D.C,v $
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
 *  $Id: Texture2D.C,v 1.11 1996/10/04 09:48:30 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/object/Object2D.h"
#include "booga/object/Path2D.h"
#include "booga/object/Texture2DContext.h"
#include "booga/object/Texture2D.h"
#include "booga/object/MakeableHandler.h"

//____________________________________________________________________ Texture2D

implementRTTI(Texture2D, ObjectSpecifier);

Makeable* Texture2D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return copy();
}

int Texture2D::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  Transform2D* transform = dynamic_cast<Transform2D*>(specifier);
  if (transform != NULL) {
    addTransform(*transform);
    delete transform;
    return 1;
  }

  // 
  // Let papa do the rest ...
  //
  return ObjectSpecifier::setSpecifier(errMsg, specifier); 
}

void Texture2D::texturing(Texture2DContext& context, const Path2D* path)
{
  if (path == NULL) 
    return;

  Object2D* object;

  for (path->first(); !path->isDone(); path->next()) {
    object = path->getObject();

    if (object->getTexture() != NULL) {
      context.setObject(object);
      context.setOCS2WCS(path->getTransform());
      object->getTexture()->texturing(context);
    }
  }
}

void Texture2D::texturing(Texture2DContext& context) const
{
  context.setOCS2TCS(myCumulatedTransform);
  doTexturing(context);
}

void Texture2D::addTransform(const Transform2D& transform)
{
  // 
  // Compute the part of the transformation contributed by the parent
  // of this texture object.
  //
  myCumulatedTransform =  
       myTransform.getInvTransMatrix() * myCumulatedTransform.getTransMatrix();

  myTransform.addTransform(transform);
  
  computeCumulatedTransform(myCumulatedTransform);
}

void Texture2D::computeCumulatedTransform(const Transform2D& additionalTransform)
{
  myCumulatedTransform = myTransform * additionalTransform;
}

void Texture2D::iterateAttributes(MakeableHandler *handler) {
  if (myTransform.getTransMatrix() != TransMatrix2D::getIdentity()) {
    handler->handle(&myTransform);
  }
}

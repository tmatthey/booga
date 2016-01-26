/*
 * $RCSfile: Texture3D.C,v $ 
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
 *  $Id: Texture3D.C,v 1.16 1996/12/04 08:54:18 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/object/Object3D.h"
#include "booga/object/Path3D.h"
#include "booga/object/Texture3D.h"
#include "booga/object/Texture3DContext.h"
#include "booga/object/MakeableHandler.h"

//____________________________________________________________________ Texture3D

implementRTTI(Texture3D, ObjectSpecifier);

Makeable* Texture3D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return copy();
}

int Texture3D::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  Transform3D* transform = dynamic_cast(Transform3D, specifier);
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

void Texture3D::texturing(Texture3DContext& context, const Path3D* path)
{
  if (path == NULL) 
    return;

  Object3D* object;
  
  for (path->first(); !path->isDone(); path->next()) {
    object = path->getObject();

    if (object->getTexture() != NULL) {
      context.setObject(object);
      context.setOCS2WCS(path->getTransform());
      object->getTexture()->texturing(context);
    }
  }
}

void Texture3D::texturing(Texture3DContext& context) const
{
  context.setOCS2TCS(myCumulatedTransform);
  doTexturing(context);
}

void Texture3D::addTransform(const Transform3D& transform)
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

void Texture3D::computeCumulatedTransform(const Transform3D& additionalTransform)
{
  myCumulatedTransform = myTransform * additionalTransform;
}

void Texture3D::iterateAttributes(MakeableHandler *handler) {
  if (myTransform.getTransMatrix() != TransMatrix3D::getIdentity()) {
    handler->handle(&myTransform);
  }
}

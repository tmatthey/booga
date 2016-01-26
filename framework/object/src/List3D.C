/*
 * $RCSfile: List3D.C,v $ 
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
 *  $Id: List3D.C,v 1.10 1996/10/04 09:46:58 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/object/List3D.h"

//_______________________________________________________________________ List3D

implementRTTI(List3D, Aggregate3D);

List3D::List3D() {}

List3D::List3D(Exemplar exemplar) 
: Aggregate3D(exemplar)
{}

Aggregate3D* List3D::makeEmpty() const
{
  return new List3D;
}

Object3D* List3D::copy() const
{
  return new List3D(*this);
}

bool List3D::doIntersect(Ray3D& ray)
{
  bool hit = false;

  for (register long i=0; i<myElements.count(); i++) {
    if (myElements.item(i)->intersect(ray))
      hit = true;
  }

  return hit;
}

Makeable* List3D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return makeEmpty();
}

static const RCString list3DKeyword("list");

RCString List3D::getKeyword() const {
  return list3DKeyword;
}

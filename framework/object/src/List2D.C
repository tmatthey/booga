/*
 * $RCSfile: List2D.C,v $
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: List2D.C,v 1.10 1996/10/04 09:46:53 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/object/List2D.h"

//_______________________________________________________________________ List2D

implementRTTI(List2D, Aggregate2D);

List2D::List2D() {}

List2D::List2D(Exemplar exemplar) 
: Aggregate2D(exemplar)
{}

Aggregate2D* List2D::makeEmpty() const
{
  return new List2D;
}

Object2D* List2D::copy() const
{
  return new List2D(*this);
}

bool List2D::doIntersect(Ray2D& ray)
{
  bool hit = false;

  for (register long i=0; i<myElements.count(); i++) {
    if (myElements.item(i)->intersect(ray))
      hit = true;
  }

  return hit;
}

Makeable* List2D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return makeEmpty();
}

static const RCString list2DKeyword("list");

RCString List2D::getKeyword() const {
  return list2DKeyword;
}

/*
 * $RCSfile: NullObject3D.C,v $
 *
 * Copyright (C) 1996, Thierry Matthey <matthey@iam.unibe.ch>
 *                     University of Berne, Switzerland
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
 *  $Id: NullObject3D.C,v 1.1 1996/11/18 15:43:28 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <strstream.h>

#include "booga/object/NullObject3D.h"

// ______________________________________________________________________ NullObject3D

implementRTTI(NullObject3D, Primitive3D);

NullObject3D::NullObject3D(Exemplar exemplar)
: Primitive3D(exemplar)
{}

NullObject3D::NullObject3D()
{}

Object3D* NullObject3D::createDecomposition() const
{
  return NULL;
}

Vector3D NullObject3D::normal(const Vector3D&) const
{
  return Vector3D(0,0,1);
}

Object3D* NullObject3D::copy() const
{
  return new NullObject3D(*this);
}

bool NullObject3D::doIntersect(Ray3D&)
{
  return false;
}
  
Makeable* NullObject3D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new NullObject3D(*this);
}

static const RCString nullObject3DKeyword("nullobject");

RCString NullObject3D::getKeyword() const 
{
  return nullObject3DKeyword;
}

void NullObject3D::doComputeBounds()
{}

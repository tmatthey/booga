/*
 * $RCSfile: Line3D.C,v $ 
 *
 * Copyright (C) 1994-96, Bernhard Bühlmann <buhlmann@iam.unibe.ch>
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
 *  $Id: Line3D.C,v 1.2 1996/10/16 09:44:59 amann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/Value.h"
#include "booga/object/Line3D.h"

//_______________________________________________________________________ Line3D

implementRTTI(Line3D, Primitive3D);

Line3D::Line3D(Exemplar exemplar)
: Primitive3D(exemplar)
{
  setFrom(Vector3D(0,0,0));
  setTo  (Vector3D(0,0,0));	 
}

Line3D::Line3D(const Vector3D& from, const Vector3D& to)
: myFrom(from), myTo(to)
{}

void Line3D::setFrom(const Vector3D& from)
{
  myFrom = from;
}

void Line3D::setTo(const Vector3D& to)
{
  myTo = to;
}

Object3D* Line3D::createDecomposition() const
{
  // Lines must not be decomposed!
  return NULL;
}

Object3D* Line3D::copy() const
{
  return new Line3D(*this);
}

void Line3D::doComputeBounds()
{
  myBounds.expand(myFrom);
  myBounds.expand(myTo);
}

bool Line3D::doIntersect(Ray3D&)
{
  return false;
}

Vector3D Line3D::normal(const Vector3D&) const
{  
  return Vector3D(0,0,0);
}

Makeable* Line3D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(2);
  getParameter(1, Vector3D, from);
  getParameter(2, Vector3D, to);

  if (from == to ) {
    errMsg = "degenerate line";
    return NULL;
  }

  Line3D* newLine = new Line3D(*this);
  newLine->setFrom(from);
  newLine->setTo(to);
  
  return newLine;
}

static const RCString Line3DKeyword("line");

RCString Line3D::getKeyword() const {
  return Line3DKeyword;
}

List<Value*>* Line3D::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  parameters->append(new Value(getFrom()));
  parameters->append(new Value(getTo()));
  return parameters;
}


/*
 * $RCSfile: Point3D.C,v $ 
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
 *  $Id: Point3D.C,v 1.1 1998/03/26 09:18:30 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/Value.h"
#include "booga/object/Point3D.h"

//_______________________________________________________________________ Point3D

implementRTTI(Point3D, Primitive3D);

Point3D::Point3D(Exemplar exemplar)
: Primitive3D(exemplar)
{
  setPoint(Vector3D(0,0,0));
  setSize(3);
}

Point3D::Point3D(const Vector3D& p, int size)
: myPoint(p), mySize(size)
{}

void Point3D::setPoint(const Vector3D& p)
{
  myPoint = p;
}

void Point3D::setSize(const int s)
{
  mySize = s;
}

Object3D* Point3D::createDecomposition() const
{
  // Lines must not be decomposed!
  return NULL;
}

Object3D* Point3D::copy() const
{
  return new Point3D(*this);
}

void Point3D::doComputeBounds()
{
  myBounds.expand(myPoint);
}

bool Point3D::doIntersect(Ray3D&)
{
  return false;
}

Vector3D Point3D::normal(const Vector3D&) const
{  
  return Vector3D(0,0,0);
}

Makeable* Point3D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Vector3D, point);

  Point3D* newPoint = new Point3D(*this);
  newPoint->setPoint(point);
  
  return newPoint;
}

static const RCString Point3DKeyword("point");

RCString Point3D::getKeyword() const {
  return Point3DKeyword;
}

List<Value*>* Point3D::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  parameters->append(new Value(getPoint()));
  return parameters;
}


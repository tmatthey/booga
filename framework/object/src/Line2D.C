/*
 * $RCSfile: Line2D.C,v $ 
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *		        Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: Line2D.C,v 1.17 1996/10/04 09:46:50 collison Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/Value.h"
#include "booga/object/Line2D.h"

//_______________________________________________________________________ Line2D

implementRTTI(Line2D, Primitive2D);

Line2D::Line2D(Exemplar exemplar)
: Primitive2D(exemplar)
{
  setFrom(Vector2D(0,0));
  setTo  (Vector2D(0,0));	 
}

Line2D::Line2D(const Vector2D& from, const Vector2D& to)
: myFrom(from), myTo(to)
{}

void Line2D::setFrom(const Vector2D& from)
{
  myFrom = from;
}

void Line2D::setTo(const Vector2D& to)
{
  myTo = to;
}

Object2D* Line2D::createDecomposition() const
{
  // Lines must not be decomposed!
  return NULL;
}

Object2D* Line2D::copy() const
{
  return new Line2D(*this);
}

void Line2D::doComputeBounds()
{
  myBounds.expand(myFrom);
  myBounds.expand(myTo);

  if (equal(myFrom.x(), myTo.x())) {
    myBounds.expandX(myFrom.x() + 1);
    myBounds.expandX(myFrom.x() - 1);
  }

  if (equal(myFrom.y(), myTo.y())) {
    myBounds.expandY(myFrom.y() + 1);
    myBounds.expandY(myFrom.y() - 1);
  }
}

/*
 * Compute the distance from the ray origin to the line.
 *
 * Line:       a + td
 * Ray origin: p
 *
 *         (p-a) . d
 *    v = ----------- * d
 *            d . d
 *
 *    distance = | p - a - v |
 */

bool Line2D::doIntersect(Ray2D& ray)
{
  Vector2D d = myTo - myFrom;
  Vector2D v = (((ray.getOrigin()-myFrom) ^ d) / d.sqr()) * d;
  Real distance = (ray.getOrigin()-myFrom-v).length();

  if (distance >= ray.getBestHitDistance())
    return false;

  //
  // HIT!!! 
  // 
  ray.setBestHitObject(this);
  ray.setBestHitDistance(distance); 

  return true;
}

Makeable* Line2D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(2);
  getParameter(1, Vector2D, from);
  getParameter(2, Vector2D, to);

  if (from == to ) {
    errMsg = "degenerate line";
    return NULL;
  }

  Line2D* newLine = new Line2D(*this);
  newLine->setFrom(from);
  newLine->setTo(to);
  
  return newLine;
}

static const RCString line2DKeyword("line");

RCString Line2D::getKeyword() const {
  return line2DKeyword;
}

List<Value*>* Line2D::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  parameters->append(new Value(getFrom()));
  parameters->append(new Value(getTo()));
  return parameters;
}

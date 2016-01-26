/*
 * $RCSfile: Point2D.C,v $
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
 *  $Id: Point2D.C,v 1.13 1996/10/04 09:47:52 collison Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/Value.h"
#include "booga/object/Line2D.h"
#include "booga/object/Point2D.h"

//______________________________________________________________________ Point2D

implementRTTI(Point2D, Primitive2D);

Point2D::Point2D(Exemplar exemplar)
: Primitive2D(exemplar)
{
  setPosition(Vector2D(0,0));
}

Point2D::Point2D(const Vector2D& position)
: myPosition(position)
{}

void Point2D::setPosition(const Vector2D& position)
{
  myPosition = position;
}

Object2D* Point2D::createDecomposition() const
{
  //
  // Create a degenerated line segment.
  // 
  Line2D* line = new Line2D(myPosition, myPosition);
  line->computeBounds();
  
  return line;
}

Object2D* Point2D::copy() const
{
  return new Point2D(*this);
}

void Point2D::doComputeBounds()
{
  myBounds.expand(myPosition);
}

bool Point2D::doIntersect(Ray2D& ray)
{
  Real distance = myPosition.distance(ray.getOrigin());

  if (distance >= ray.getBestHitDistance())
    return false;

  //
  // HIT! 
  // 
  ray.setBestHitObject(this);
  ray.setBestHitDistance(distance); 

  return true;
}

Makeable* Point2D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Vector2D, position);

  Point2D* newPoint = new Point2D(*this);
  newPoint->setPosition(position);
  
  return newPoint;
}

static const RCString point2DKeyword("point");

RCString Point2D::getKeyword() const {
  return point2DKeyword;
}

List<Value*>* Point2D::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  parameters->append(new Value(getPosition()));
  return parameters;
}

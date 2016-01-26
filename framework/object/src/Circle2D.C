/*
 * $RCSfile: Circle2D.C,v $
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
 *  $Id: Circle2D.C,v 1.19 1996/10/04 09:46:10 collison Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/mathutilities.h"
#include "booga/base/TransMatrix2D.h"
#include "booga/base/Value.h"
#include "booga/object/List2D.h"
#include "booga/object/Line2D.h"
#include "booga/object/Circle2D.h"

//_____________________________________________________________________ Circle2D

implementRTTI(Circle2D, Primitive2D);

Circle2D::Circle2D(Exemplar exemplar)
: Primitive2D(exemplar), myRadius(1.0)
{
  setCenter(Vector2D(0,0));
}

Circle2D::Circle2D(const Vector2D& center, Real radius)
: myCenter(center), myRadius(radius)
{}

void Circle2D::setCenter(const Vector2D& center)
{
  myCenter = center;
}

void Circle2D::setRadius(Real radius)
{
  myRadius = radius;
}

Object2D* Circle2D::createDecomposition() const
{
  List2D* segments = new List2D;
  
  int steps = int(getPrecision()*50 + 3);
  
  TransMatrix2D rotate = TransMatrix2D::makeRotateOrigin(M_PI*2/steps);

  Vector2D position(myRadius, 0);
  Vector2D lastPosition = position;

  while (steps-- > 1) {
    lastPosition = position;
    position = transformAsVector(position, rotate);
    segments->adoptObject(new Line2D(myCenter+lastPosition, 
				 myCenter+position));
  }

  // Create closing segment.
  segments->adoptObject(new Line2D(myCenter+position, 
			        myCenter+Vector2D(myRadius,0)));
 
  segments->computeBounds();
  return segments;
}

Object2D* Circle2D::copy() const
{
  return new Circle2D(*this);
}

void Circle2D::doComputeBounds()
{
  myBounds.expand(myCenter[0]-myRadius, myCenter[1]-myRadius);
  myBounds.expand(myCenter[0]+myRadius, myCenter[1]+myRadius);
}

bool Circle2D::doIntersect(Ray2D& ray)
{
  Real distance = fabs(myRadius-ray.getOrigin().distance(myCenter));

  if (distance > myRadius || distance >= ray.getBestHitDistance())
    return false;

  //
  // HIT!!! 
  // The closer to the circle border the better.
  // 
  ray.setBestHitObject(this);
  ray.setBestHitDistance(distance); 

  return true;
}

Makeable* Circle2D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(2);
  getParameter(1, Vector2D, center);
  getParameter(2, Real, radius);

  if (radius < EPSILON) {
    errMsg = "degenerate circle";
    return NULL;
  }

  Circle2D* newCircle = new Circle2D(*this);
  newCircle->setCenter(center);
  newCircle->setRadius(radius);
  
  return newCircle;
}

static const RCString circle2DKeyword("circle");

RCString Circle2D::getKeyword() const {
  return circle2DKeyword;
}

List<Value*>* Circle2D::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  parameters->append(new Value(getCenter()));
  parameters->append(new Value(getRadius()));
  return parameters;
}


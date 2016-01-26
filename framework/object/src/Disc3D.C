/*
 * $RCSfile: Disc3D.C,v $
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: Disc3D.C,v 1.12 1996/10/04 09:46:30 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include <sstream>

#include "booga/base/Report.h"
#include "booga/base/Value.h"
#include "booga/object/Triangle3D.h"
#include "booga/object/List3D.h"
#include "booga/object/Disc3D.h"

// ____________________________________________________________________ Disc3D

implementRTTI(Disc3D, Primitive3D);

Disc3D::Disc3D(Exemplar exemplar)
: Primitive3D(exemplar)
{
  myRadius = 1;
  myCenter = Vector3D(0,0,0);
  myNormal = Vector3D(0,0,1);
}

Disc3D::Disc3D(Real radius, const Vector3D& center, const Vector3D& normal)
: myRadius(radius), myCenter(center), myNormal(normal)
{
  if (myRadius < EPSILON) {
    std::stringstream os;
    os << "[Disc3D::Disc3D] degenerate disc (radius = " << myRadius << ")";
    Report::recoverable(os);
  }
  
  if (equal(myNormal.normalize(), 0)) {
    std::stringstream os;
    os << "[Disc3D::Disc3D] degenerate disc normal " << normal;
    Report::recoverable(os);
  }
}

void Disc3D::setRadius(Real radius)
{
  if (radius < EPSILON) {
    std::stringstream os;
    os << "[Disc3D::setRadius] illegal radius = " << radius << " ignored";
    Report::warning(os);
    return;
  }

  myRadius = radius;
}

void Disc3D::setCenter(const Vector3D& center)
{
  myCenter = center;
}

void Disc3D::setNormal(const Vector3D& normal)
{
  if (equal(normal.sqr(), 0)) {
    std::stringstream os;
    os << "[Disc3D::setNormal] degenerate disc normal " << normal << " ignored";
    Report::warning(os);
    return;
  }

  myNormal = normal;
  myNormal.normalize();
}

Object3D* Disc3D::createDecomposition() const
{
  // The precision argument is converted to 'resolution' by using 
  // the following formula:
  //
  //     resolution = 20 * precison 
  //
  int resolution = (int)rint(20*getPrecision());
  
  List3D* list = new List3D;
  
  TransMatrix3D rot(TransMatrix3D::makeRotate(myNormal, 2*M_PI/resolution));

  Vector3D pointA;
  Vector3D pointB;
  
  if (1 - fabs(myNormal.z()) < EPSILON) {
    pointA.x() = 1;
    pointA.y() = pointA.z() = 0;
  }
  else {
    pointA.x() =  myNormal.y();
    pointA.y() = -myNormal.x();
    pointA.z() = 0;
  }

  pointA = (myNormal * pointA).normalized()*myRadius;

  //
  // Sweep around the normal.
  //
  for (int i=0; i<resolution; i++) {
    pointB = pointA * rot;
    list->adoptObject(new Triangle3D(myCenter,          myNormal, 
                                     myCenter + pointA, myNormal, 
                                     myCenter + pointB, myNormal));
    pointA = pointB;
  }
    
  list->computeBounds();
  
  return list;
}

Vector3D Disc3D::normal(const Vector3D&) const
{
  return myNormal;
}

Object3D* Disc3D::copy() const
{
  return new Disc3D(*this);
}

void Disc3D::doComputeBounds()
{
  //
  // Project along each of x, y and z axes.
  //
  Real extent;
  extent = myRadius * sqrt(1 - sqr(myNormal.x()));
  myBounds.expandX(myCenter.x() - extent);
  myBounds.expandX(myCenter.x() + extent);

  extent = myRadius * sqrt(1 - sqr(myNormal.y()));
  myBounds.expandY(myCenter.y() - extent);
  myBounds.expandY(myCenter.y() + extent);

  extent = myRadius * sqrt(1 - sqr(myNormal.z()));
  myBounds.expandZ(myCenter.z() - extent);
  myBounds.expandZ(myCenter.z() + extent);
}
  
/*
 * Adapted from Craig Kolb's rayshade.
 */
bool Disc3D::doIntersect(Ray3D& ray)
{
  Real denom = myNormal ^ ray.getDirection();
  Real d = myCenter ^ myNormal;
  //
  // Edge-on intersection?
  //
  if (fabs(denom) < EPSILON)
    return false;
 
  Real dist = (d - (myNormal ^ ray.getOrigin())) / denom;
  if (dist < ray.getTolerance() || dist > ray.getBestHitDistance()) 
    // Too close or to far.
    return false;

  //
  // Find difference between point of intersection and center of disc.
  //
  Vector3D hit = ray.getOrigin() + dist*ray.getDirection() - myCenter;

  //
  // If hit point is <= myRadius from center, we've hit the disc.
  //
  if ((hit ^ hit) <= sqr(myRadius)) {
    //
    // HIT!!! 
    // 
    ray.setBestHitObject(this);
    ray.setBestHitDistance(dist);
    return true;
  }
   
  //
  // Sorry no hit...
  //
  return false;
}

Makeable* Disc3D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(3);
  getParameter(1, Real, radius);
  getParameter(2, Vector3D, center);
  getParameter(3, Vector3D, normal);

  if (radius < EPSILON) {
    errMsg = "degenerate disc";
    return NULL;
  }

  if (equal(normal.normalize(), 0)) {
    errMsg = "degenerate disc normal";
    return NULL;
  }

  Disc3D* newDisc = new Disc3D(*this);
  newDisc->setRadius(radius);
  newDisc->setCenter(center);
  newDisc->setNormal(normal);

  return newDisc;
}

static const RCString disc3DKeyword("disc");

RCString Disc3D::getKeyword() const {
  return disc3DKeyword;
}

List<Value*>* Disc3D::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  parameters->append(new Value(getRadius()));
  parameters->append(new Value(getCenter()));
  parameters->append(new Value(getNormal()));
  return parameters;
}

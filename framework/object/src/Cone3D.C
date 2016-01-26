/*
 * $RCSfile: Cone3D.C,v $
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
 *  $Id: Cone3D.C,v 1.26 1996/10/04 09:46:18 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include <strstream.h>

#include "booga/base/Report.h"
#include "booga/base/Value.h"
#include "booga/object/List3D.h"
#include "booga/object/Triangle3D.h"
#include "booga/object/Cylinder3D.h"
#include "booga/object/Shared3D.h"
#include "booga/object/Cone3D.h"
#include "booga/object/Cone3DAttr.h"
#include "booga/object/DummyMakeable.h"
#include "booga/object/MakeableHandler.h"

// ______________________________________________________________________ Cone3D

implementRTTI(Cone3D, Primitive3D);

Cone3D::Cone3D(Exemplar exemplar)
: Primitive3D(exemplar)
{
  myStartRadius = 1;
  myStart = Vector3D(0,0,0);
  myEndRadius = .5;
  myEnd = Vector3D(0,0,1);
  
  open();
  computeCanonicalTransform();
}

Cone3D::Cone3D(Real radiusStart, const Vector3D& start, 
	      Real radiusEnd, const Vector3D& end)
: myStartRadius(radiusStart), 
  myStart(start), 
  myEndRadius(radiusEnd), 
  myEnd(end)
{
  if (equal(radiusStart, radiusEnd)) {
    ostrstream os;
    os << "[Cone3D::Cone3D] start and end radius are equal: " << radiusStart;
    Report::warning(os);
  }
  
  open();
  computeCanonicalTransform();
}

void Cone3D::setStart(const Vector3D& start)
{
  myStart = start;
  computeCanonicalTransform();
}

void Cone3D::setEnd(const Vector3D& end)
{
  myEnd = end;
  computeCanonicalTransform();
}

void Cone3D::setRadius(Real startRadius, Real endRadius)
{
  if (equal(startRadius, endRadius)) {
    Report::warning("[Cone3D::setRadius] start and end radius must not be equal");
    return;
  }
 
  myStartRadius = startRadius;
  myEndRadius   = endRadius;
  computeCanonicalTransform();
}

/*
 * A cone is divided into quadrics along the axis and around the axis.
 * Each quadrant looks like this:
 *
 *              pointA o------------------o pointD
 *                     |                  |
 *		     |                  |      | zHeight in [basePoint, apexPoint]
 *		     |                  |      v  
 *		     |                  |      outer loop
 *		     |                  |
 *	       pointB o------------------o pointC
 *
 *	                 ->  alpha in [0, 2Pi[
 *			     inner loop
 *
 * The points are generated in a cone with the z-axis as cone axis and the
 * base at z=1 with radius 1. the apex is at z=distance. The origin is at the
 * top of the inverted cone. 
 */
Object3D* Cone3D::createDecomposition() const
{
  // The precision argument is converted to 'resolution' by using 
  // the following formula:
  //
  //     resolution = 10 * precison 
  //
  int resolution = (int)rint(10*getPrecision());
  Real steps = 2*M_PI/resolution;

  //
  // Check, if decomposition for a similar cylinder has already been done.
  //
  extern char* form(const char * ...);
  Name key = form("Cone3D#%d#%g%d", steps, myDistance, isClosed());
  Object3D* retval = (Object3D*)Primitive3D::getDecomposition(key);

  if (retval == NULL) {
    //
    // No similar decomposition is present, so we have to create a new one.
    //
    List3D* list = new List3D;

    Vector3D pointA(myDistance, 0, myDistance);
    Vector3D pointB(1, 0, 1);
    Vector3D pointC, pointD;
    Vector3D normalAB(unifiedNormal(pointA));
    Vector3D normalCD;
    Vector3D start(0, 0, 1);
    Vector3D end(0, 0, myDistance);

    //
    // Sweep around the cone.
    //
    Real sin_a, cos_a;
    for (Real alpha=steps; alpha<2*M_PI+steps; alpha+=steps) {
      sincos(alpha, sin_a, cos_a);
      pointC   = Vector3D(cos_a, sin_a, 1);
      pointD   = Vector3D(myDistance*cos_a, myDistance*sin_a, myDistance);
      normalCD = unifiedNormal(pointC);

      if (pointB != pointC)
        list->adoptObject(new Triangle3D(pointA, normalAB, pointB, normalAB, pointC, normalCD));
      if (pointA != pointD)
        list->adoptObject(new Triangle3D(pointA, normalAB, pointC, normalCD, pointD, normalCD));
    
      if (isClosed()) {
        list->adoptObject(new Triangle3D(end, Vector3D(0,0,-1), 
                                         pointA, Vector3D(0,0,-1), pointD, Vector3D(0,0,-1)));
        list->adoptObject(new Triangle3D(start, Vector3D(0,0,1), 
                                         pointB, Vector3D(0,0,1), pointC, Vector3D(0,0,1)));
      }
     
      pointA = pointD;
      pointB = pointC;      
      normalAB = normalCD;
    }

    retval = new Shared3D(list);
    retval->computeBounds();
    Primitive3D::adoptDecomposition(key, retval); 
  }

  retval = retval->copy();
  retval->setTransform(myCanonicalTransform);

  return retval;
}

/*
 * Returns cone surface normal in point. (cone in object coordinate system)
 */
Vector3D Cone3D::normal(const Vector3D& point) const
{
  Vector3D ucsPoint  = myCanonicalTransform.invTransformAsPoint(point);
  Vector3D ucsNormal;

  if (ucsPoint.z() > (1-EPSILON))
    ucsNormal = Vector3D(0,0,1);
  else if (ucsPoint.z() < (myDistance+EPSILON))
    ucsNormal = Vector3D(0,0,-1);
  else
    ucsNormal = unifiedNormal(ucsPoint);
  
  return myCanonicalTransform.transformAsNormal(ucsNormal);
}

/*
 * Returns cone surface normal in point. (cone in unified coordinate system)
 */
Vector3D Cone3D::unifiedNormal(const Vector3D& ucsPoint) const
{
  // Test if point is on z-axis (possible, if one radius is 0)
  if (equal(ucsPoint.x(),0) && equal(ucsPoint.y(),0)) 
    return Vector3D(0,0,1);
  else
    return Vector3D( ucsPoint.x()*ucsPoint.z(), 
                     ucsPoint.y()*ucsPoint.z(),
                    -ucsPoint.x()*ucsPoint.x()-ucsPoint.y()*ucsPoint.y());
}

Object3D* Cone3D::copy() const
{
  return new Cone3D(*this);
}

bool Cone3D::doIntersect(Ray3D& ray)
{
  bool hit = false;
  
  //
  // Transform the ray to canonical cylinder coordinates.
  //
  Vector3D origin = ray.getOrigin();
  Vector3D direction = ray.getDirection();
  Real rescale = 1. / ray.transform(myCanonicalTransform);

  //
  // Step 1: Check the closing disc first.
  // 
  if (isClosed()) {
    Real t;
    // 
    // Top disc first.
    //
    if (!equal(ray.getDirection().z(), 0))
      t = (1-ray.getOrigin().z()) / ray.getDirection().z();
    else
      t = 1-ray.getOrigin().z();              

    if (t > ray.getTolerance()   &&
        t < ray.getBestHitDistance()) {
        
      Real d = sqr(ray.getOrigin().x() + t * ray.getDirection().x()) + 
               sqr(ray.getOrigin().y() + t * ray.getDirection().y());
        
      if (d <= 1) {
        hit = true;
        ray.setBestHitDistance(t);
        ray.setBestHitObject(this);
      }
    }
    
    // 
    // Bottom disc ...
    //
    if (!equal(myDistance, 0)) {
      if (!equal(ray.getDirection().z(), 0))
        t = (myDistance-ray.getOrigin().z()) / ray.getDirection().z();
      else
        t = myDistance-ray.getOrigin().z();              

      if (t > ray.getTolerance()   &&
          t < ray.getBestHitDistance()) {
        
        Real d = sqrt(sqr(ray.getOrigin().x() + t * ray.getDirection().x()) + 
                      sqr(ray.getOrigin().y() + t * ray.getDirection().y()));
        
        if (d <= myDistance) {
          hit = true;
          ray.setBestHitDistance(t);
          ray.setBestHitObject(this);
        }
      }
    }
  }
  
  //
  // Step 2: Intersect with the cone.
  //

  Real a = sqr(ray.getDirection().x()) + 
           sqr(ray.getDirection().y()) -
           sqr(ray.getDirection().z());
  Real b = ray.getDirection().x()*ray.getOrigin().x() + 
           ray.getDirection().y()*ray.getOrigin().y() - 
           ray.getDirection().z()*ray.getOrigin().z();
  Real c = sqr(ray.getOrigin().x()) + 
           sqr(ray.getOrigin().y()) - 
           sqr(ray.getOrigin().z());

  if (fabs(a) < EPSILON) {
    //
    // Only one intersection point...
    //
    Real t = -0.5*c / b;
    Real zpos = ray.getOrigin().z() + t*ray.getDirection().z();
    
    if (t >= ray.getTolerance()  && 
        zpos >= myDistance       && 
        zpos <= 1.               && 
        t < ray.getBestHitDistance()) {
      hit = true;
      ray.setBestHitDistance(t);
      ray.setBestHitObject(this);
    }
  }
  else {
    //
    // Probably two intersection points...
    //
    Real disc = b*b - a*c;

    if (disc >= 0.) {
      disc = sqrt(disc);
      Real t1 = (-b + disc) / a;
      Real t2 = (-b - disc) / a;

      //
      // Clip intersection points.
      //
      Real zpos = ray.getOrigin().z() + t1*ray.getDirection().z();
      if (t1 < ray.getTolerance() || zpos < myDistance || zpos > 1.) {
        zpos = ray.getOrigin().z() + t2*ray.getDirection().z();
        if (t2 < ray.getTolerance() || zpos < myDistance || zpos > 1.)
          // Should jump to "untransform" the ray...
          t1 = ray.getBestHitDistance() + 1;
        else
          t1 = t2;
      } 
      else {
        zpos = ray.getOrigin().z() + t2*ray.getDirection().z();
        if (t2 >= ray.getTolerance() && zpos >= myDistance && zpos <= 1. && t2 < t1)
          t1 = t2;
      }
 
      if (t1 < ray.getBestHitDistance()) {
        hit = true;
        ray.setBestHitDistance(t1);
        ray.setBestHitObject(this);
      }
    }
  }

  //
  // "Untransform" the ray.
  //
  ray.setOrigin(origin);
  ray.setDirection(direction);
  ray.setBestHitDistance(ray.getBestHitDistance() * rescale);
  ray.setTolerance(ray.getTolerance() * rescale);

  return hit;
}

void Cone3D::doComputeBounds()
{
  // We need a valid distance, so be sure you have called computeCanonicalTransform !
  
  myBounds.expand(-1,-1,myDistance);
  myBounds.expand(1,1,1);
  myBounds.transform(myCanonicalTransform.getTransMatrix());
}
  
int Cone3D::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  Cone3DAttr* attr = dynamic_cast(Cone3DAttr, specifier);
  if (attr) {
    // The Cone3DAttr object knows best which method has to be called.
    // So let the object do the job.
    attr->setAttribute(this);

    delete attr;
    return 1;  
  }

  // 
  // Let papa do the rest ...
  //
  return Primitive3D::setSpecifier(errMsg, specifier);
}

Makeable* Cone3D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(4);
  getParameter(1, Real, radiusStart);
  getParameter(2, Vector3D, start);
  getParameter(3, Real, radiusEnd);
  getParameter(4, Vector3D, end);

  //
  // If start and end radius are equal a cylinder object is created.
  //
  if (!equal(radiusStart, radiusEnd)) {
    Cone3D* newCone = new Cone3D(*this);
  
    newCone->setStart(start);
    newCone->setEnd(end); 
    newCone->setRadius(radiusStart, radiusEnd);

    return newCone;
  } 
  else {
    ostrstream os;
    os << "[Cone3D::make] start and end radius are equal: " 
       << radiusStart << "! Creating cylinder";
    Report::warning(os);

    return new Cylinder3D(radiusStart, start, end);
  }
}

/*
 * To improve intersection and bounding box computation we store additionally
 * a normalized form of the cone. 
 * A normalized cone is determined only by distance, implying the apex at z=1
 * and apex radius 1. The base of the cone is oriented towards the origin, thus
 * implying the base radius is smaller than the apex radius. 
 *
 * Heavily based on Craig Colbs rayshade implementation of a cone!
 *
 */
void Cone3D::computeCanonicalTransform()
{
  // 
  // Find base and apex
  //
  Vector3D base, apex;
  Real baseRadius, apexRadius;
  if (myStartRadius < myEndRadius) {
    baseRadius = myStartRadius;
    apexRadius = myEndRadius;
    base = myStart;
    apex = myEnd;
  } else {
    baseRadius = myEndRadius;
    apexRadius = myStartRadius;
    base = myEnd;
    apex = myStart;
  }
  
  // Calculate axis and length
  Vector3D axis(apex-base);
  Real axisLength = axis.normalize();
  // Calculate cotangens of angle of cone, and scale factor of axis
  Real cotTheta  = axisLength/(apexRadius - baseRadius);
  Real axisScale = apexRadius *cotTheta;
  
  // Distance from origin to base of cone
  myDistance = 1 - (axisLength/axisScale);
  
  // Calculate offset
  Vector3D top(apex + axisScale*(base - apex).normalized());
  
  // Set transformation from unit cone to user defined cone.
  // Perform the following transformations :
  // 1.) scale along z-axis -> length of cone
  // 2.) scale along x and y axis -> radius of cone
  // 3.) rotate to reach final direction about the angle
  //                 (    z*axis    )
  //  	     arccos (  ----------  )    (inner product)
  //    	            (  |z|*|axis|  )
  //     around the axis (z x axis) (crossproduct).
  // 4.) translate to final position
  
  // Step 1 and 2:
  myCanonicalTransform = TransMatrix3D::makeScale(apexRadius, apexRadius, axisScale);
  
  // Step 3:
  Vector3D rotAxis(Vector3D(0,0,1)*axis);
  if (equal(rotAxis.length(), 0)) { // axis parallel to z axis?
    if (axis[2] < 0)                // direction of axis towards negative z axis?
      myCanonicalTransform *= TransMatrix3D::makeRotateX(M_PI);
  } else
    myCanonicalTransform *= TransMatrix3D::makeRotate(rotAxis, acos(axis[2]));
    
  // Step 4:
  myCanonicalTransform *= TransMatrix3D::makeTranslate(top);
}

static const RCString cone3DKeyword("cone");

RCString Cone3D::getKeyword() const {
  return cone3DKeyword;
}

List<Value*>* Cone3D::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  parameters->append(new Value(getStartRadius()));
  parameters->append(new Value(getStart()));
  parameters->append(new Value(getEndRadius())); 
  parameters->append(new Value(getEnd()));
  return parameters;
}

void Cone3D::iterateAttributes(MakeableHandler *handler) {
  Object3D::iterateAttributes(handler);
  if (isClosed()) {
    DummyMakeable m("close");
    handler->handle(&m);
  } 
  else {
    DummyMakeable m("open");
    handler->handle(&m);
  }
}

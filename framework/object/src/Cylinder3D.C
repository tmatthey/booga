/*
 * $RCSfile: Cylinder3D.C,v $
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
 *  $Id: Cylinder3D.C,v 1.26 1996/10/04 09:46:27 collison Exp $
 * -----------------------------------------------------------------------------
 */


#include "booga/base/Value.h"
#include "booga/object/List3D.h"
#include "booga/object/Triangle3D.h"
#include "booga/object/Shared3D.h"
#include "booga/object/Cylinder3D.h"
#include "booga/object/Cylinder3DAttr.h"
#include "booga/object/DummyMakeable.h"
#include "booga/object/MakeableHandler.h"

//___________________________________________________________________ Cylinder3D

implementRTTI(Cylinder3D, Primitive3D);

Cylinder3D::Cylinder3D(Exemplar exemplar)
: Primitive3D(exemplar)
{
  myRadius = 1;
  myStart = Vector3D(0,0,0);
  myEnd   = Vector3D(0,0,1);
  
  open();
  computeCanonicalTransform();
}

Cylinder3D::Cylinder3D(Real radius, const Vector3D& start, const Vector3D& end)
: myRadius(radius), myStart(start), myEnd(end)
{
  open();
  
  //
  // Check for correct settings.
  //
  if (myStart.equal(myEnd)) {
    std::stringstream os;
    os << "[Cylinder3D::Cylinder3D] degenerate cylinder: " 
       << "start " << myStart << ", end " << myEnd;
    Report::warning(os);
  }
  if (myRadius < EPSILON) {
    std::stringstream os;
    os << "[Cylinder3D::Cylinder3D] degenerate cylinder, " 
       << "radius: " << myRadius;
    Report::warning(os);
  }
  
  computeCanonicalTransform();
}

void Cylinder3D::setStart(const Vector3D& start)
{
  if (start.equal(myEnd)) {
    std::stringstream os;
    os << "[Cylinder3D::setStart] start == end: " << start;
    Report::warning(os);
  }
  
  myStart = start;
  computeCanonicalTransform();
}

void Cylinder3D::setEnd(const Vector3D& end)
{
  if (end.equal(myStart)) {
    std::stringstream os;
    os << "[Cylinder3D::setEndt] start == end: " << end;
    Report::warning(os);
  }

  myEnd = end;
  computeCanonicalTransform();
}

void Cylinder3D::setRadius(Real radius)
{
  if (radius < EPSILON) {
    std::stringstream os;
    os << "[Cylinder3D::setRadius] illegal value for radius: " << radius;
    Report::recoverable(os);
    return;
  }

  myRadius = radius;
  computeCanonicalTransform();
}

/*
 * A cylinder is divided into quadrics along the axis and around the axis.
 * Each quadrant looks like this:
 *
 *              pointA o------------------o pointD
 *		     |                  |
 *		     |                  |          | zHeight in [0, 1]
 *		     |                  |          v  
 *		     |                  |            outer loop
 *		     |                  |
 *	       pointB o------------------o pointC
 *
 *	                 ->  alpha in [0, 2Pi[
 *
 *			     inner loop
 *
 * The points are generated in a cylinder with the z-axis as cylinder axis and
 * with radius and length 1. 
 */
Object3D* Cylinder3D::createDecomposition() const
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
  char tmp[256];
  sprintf(tmp,"Cylinder3D#%d#%d", static_cast<int>(steps), isClosed());
  Name key(tmp);
  Object3D* retval = (Object3D*)Primitive3D::getDecomposition(key);

  if (retval == NULL) {
    //
    // No similar decomposition is present, so we have to create a new one.
    //
    List3D* list = new List3D;
  
    Vector3D pointA(1, 0, 0);
    Vector3D pointB(1, 0, 1);
    Vector3D pointC, pointD;
    Vector3D normalAB(1, 0, 0);
    Vector3D normalCD;

    //
    // Sweep around the cylinder.
    //
    Real sin_a, cos_a;
    for (Real alpha=steps; alpha<2*M_PI+steps; alpha+=steps) {
      sincos(alpha, sin_a, cos_a);
      pointC   = Vector3D(cos_a, sin_a, 1);
      pointD   = Vector3D(cos_a, sin_a, 0);
      normalCD = Vector3D(cos_a, sin_a, 0);
      
      list->adoptObject(new Triangle3D(pointA, normalAB, pointB, normalAB, pointC, normalCD));
      list->adoptObject(new Triangle3D(pointA, normalAB, pointC, normalCD, pointD, normalCD));

      if (isClosed()) {
        list->adoptObject(new Triangle3D(Vector3D(0,0,0), pointA, pointD));
        list->adoptObject(new Triangle3D(Vector3D(0,0,1), pointB, pointC));
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
 * Returns cone surface normal in point. (cylinder in unified coordinate system)
 */
inline Vector3D Cylinder3D::unifiedNormal(const Vector3D& ucsPoint) const
{
  return Vector3D(ucsPoint.x(), ucsPoint.y(), 0);
}

/*
 * Returns cone surface normal in point. (cylinder in object coordinate system)
 */
Vector3D Cylinder3D::normal(const Vector3D& point) const
{
  Vector3D ucsPoint  = myCanonicalTransform.invTransformAsPoint(point);
  Vector3D ucsNormal;

  if (ucsPoint.z() >= (1-EPSILON))
    ucsNormal = Vector3D(0,0,1);
  else if (ucsPoint.z() < EPSILON)
    ucsNormal = Vector3D(0,0,-1);
  else
    ucsNormal = unifiedNormal(ucsPoint);
  
  return myCanonicalTransform.transformAsNormal(ucsNormal);
}

Object3D* Cylinder3D::copy() const
{
  return new Cylinder3D(*this);
}

/*
 * Adapted from Craig Kolbs rayshade.
 */ 
bool Cylinder3D::doIntersect(Ray3D& ray)
{
  bool hit = false;
  
  //
  // Transform the ray to canonical cylinder coordinates.
  //
  Vector3D origin = ray.getOrigin();
  Vector3D direction = ray.getDirection();
  Real rescale = 1. / ray.transform(myCanonicalTransform);
  
  //
  // Step 1: Check the closing discs first.
  // 
  if (isClosed()) {
    Real t1; // Distance for top disc.
    Real t2; // Distance for bottom disc.
    
    if (!equal(ray.getDirection().z(), 0)) {
      t1 = (1-ray.getOrigin().z()) / ray.getDirection().z();
      t2 = -ray.getOrigin().z() / ray.getDirection().z();
    }
    else {
      t1 = 1-ray.getOrigin().z();              
      t2 = ray.getOrigin().z();
    }
    
    //
    // Is the top or the bottom disc closer the the ray origin?
    //
    if (t1 >= 0) {
      if (t2 >= 0)
        t1 = min(t1, t2);
    }
    else if (t2 >= 0)
      t1 = t2;

    if (t1 > ray.getTolerance() &&
        t1 < ray.getBestHitDistance()) {
        
      Real d = sqr(ray.getOrigin().x() + t1 * ray.getDirection().x()) + 
               sqr(ray.getOrigin().y() + t1 * ray.getDirection().y());
        
      if (d <= 1) {
        hit = true;
        ray.setBestHitDistance(t1);
        ray.setBestHitObject(this);
      }
    }
  }

  //
  // Step 2: Intersect with the cylinder.
  //
  Real a = sqr(ray.getDirection().x()) + sqr(ray.getDirection().y());

  if (a >= EPSILON*EPSILON) { // |ray.getDirection().z()| != 1 ?

    Real b = ray.getDirection().x()*ray.getOrigin().x() +
             ray.getDirection().y()*ray.getOrigin().y();
    Real c = sqr(ray.getOrigin().x()) + sqr(ray.getOrigin().y()) - 1;
    Real disc = b*b - a*c;

    if(disc >= 0.) {
      disc = sqrt(disc);
      Real t1 = (-b + disc) / a;
      Real t2 = (-b - disc) / a;

      if (t1 >= ray.getTolerance() || t2 >= ray.getTolerance()) {
    
        Real zpos1 = ray.getOrigin().z() + t1 * ray.getDirection().z();
        Real zpos2 = ray.getOrigin().z() + t2 * ray.getDirection().z();

        if (t1 < ray.getTolerance() || zpos1 < 0. || zpos1 > 1.) {
          if (t2 < ray.getTolerance() || zpos2 < 0. || zpos2 > 1.)
            // Should jump to "untransform" the ray...
            t1 = ray.getBestHitDistance() + 1;
          else 
            t1 = t2;
        } 
        else if (t2 >= ray.getTolerance() && zpos2 >= 0. && zpos2 <= 1.)
          t1 = min(t1, t2);

        if (t1 < ray.getBestHitDistance()) {
          hit = true;
          ray.setBestHitDistance(t1);
          ray.setBestHitObject(this);
        }
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

void Cylinder3D::doComputeBounds()
{
  // We need a valid local tarnsformation, so be sure to have
  // called computeCanonicalTransform() after changeing anything!
  
  myBounds.expand(-1, -1, 0);
  myBounds.expand( 1,  1, 1);
  myBounds.transform(myCanonicalTransform.getTransMatrix());
}
  
int Cylinder3D::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  Cylinder3DAttr* attr = dynamic_cast<Cylinder3DAttr*>(specifier);
  if (attr) {
    // The Cylinder3DAttr object knows best which method has to be called.
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

Makeable* Cylinder3D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(3);
  getParameter(1, Real, radius);
  getParameter(2, Vector3D, start);
  getParameter(3, Vector3D, end);

  if (radius < EPSILON) {
    errMsg = "degenerate Cylinder";
    return NULL;
  }

  Cylinder3D* newCylinder = new Cylinder3D(*this);
  
  newCylinder->setRadius(radius);
  newCylinder->setStart(start);
  newCylinder->setEnd(end); 
  
  return newCylinder;
}

/*
 * To improve intersection, decomposition and bounding box computation we 
 * store additionally a normalized form of the cylinder. 
 * A normalized cylinder has its start point in (0,0,0) and its end point
 * in (0,0,1). The radius is set to 1. 
 *
 * Heavily based on Craig Colbs rayshade implementation of a cone!
 *
 */
void Cylinder3D::computeCanonicalTransform()
{
  // compute matrix to transform unit cylinder to user defined cylinder
  Vector3D axis(myEnd-myStart);
  Real axisLength = axis.normalize();

  // Set transformation from unit cylinder to user defined cylinder.
  // Perform the following transformations :
  // 1.) scale along z-axis -> length of cylinder
  // 2.) scale along x and y axis -> radius of cylinder
  // 3.) rotate to reach final direction about the angle
  //                 (    z*axis    )
  //  	     arccos (  ----------  )    (inner product)
  //    	            (  |z|*|axis|  )
  //     around the axis (z x axis) (crossproduct).
  // 4.) translate to final position
  
  // Step 1 and 2:
  myCanonicalTransform = TransMatrix3D::makeScale(myRadius, myRadius, axisLength);
  
  // Step 3:
  Vector3D rotAxis(Vector3D(0,0,1)*axis);
  if (equal(rotAxis.length(), 0)) { // axis parallel to z axis?
    if (axis[2] < 0)                // direction of axis towards negative z axis?
      myCanonicalTransform *= TransMatrix3D::makeRotateX(M_PI);
  } else
    myCanonicalTransform *= TransMatrix3D::makeRotate(rotAxis, acos(axis[2]));
    
  // Step 4:
  myCanonicalTransform *= TransMatrix3D::makeTranslate(myStart);
}

static const RCString cylinder3DKeyword("cylinder");

RCString Cylinder3D::getKeyword() const {
  return cylinder3DKeyword;
}

List<Value*>* Cylinder3D::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  parameters->append(new Value(getRadius()));
  parameters->append(new Value(getStart()));
  parameters->append(new Value(getEnd()));
  return parameters;
}

void Cylinder3D::iterateAttributes(MakeableHandler *handler) {
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


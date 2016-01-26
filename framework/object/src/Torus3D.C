/*
 * $RCSfile: Torus3D.C,v $
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
 *  $Id: Torus3D.C,v 1.19 1996/10/04 09:48:43 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/mathutilities.h"  // solveQuartic()
#include "booga/base/Value.h"
#include "booga/base/Name.h"
#include "booga/base/SymTable.h"
#include "booga/object/List3D.h"
#include "booga/object/Triangle3D.h"
#include "booga/object/Shared3D.h"
#include "booga/object/Torus3D.h"

// _____________________________________________________________________ Torus3D

implementRTTI(Torus3D, Primitive3D);

Torus3D::Torus3D(Exemplar exemplar)
: Primitive3D(exemplar),
  myCenter(Vector3D(0,0,0)), myNormal(Vector3D(0,0,1))
{
  mySweptRadius = 1;
  myTubeRadius = 0.1;

  computeCanonicalTransform();
}

Torus3D::Torus3D(Real sweptRadius, Real tubeRadius, 
		const Vector3D& center, const Vector3D& normal)
: mySweptRadius(sweptRadius), myTubeRadius(tubeRadius), 
  myCenter(center), myNormal(normal.normalized())
{
  computeCanonicalTransform();
}

void Torus3D::setCenter(const Vector3D& center)
{
  myCenter = center;
  computeCanonicalTransform();
}

void Torus3D::setNormal(const Vector3D& normal)
{
  myNormal = normal.normalized();
  computeCanonicalTransform();
}

void Torus3D::setSweptRadius(Real sweptRadius)
{
  mySweptRadius = sweptRadius;
  computeCanonicalTransform();
}

void Torus3D::setTubeRadius(Real tubeRadius)
{
  myTubeRadius = tubeRadius;
  computeCanonicalTransform();
}

/*
 * The canonical form of a torus has position [0,0,0] and axis [0,0,1].
 */
void Torus3D::computeCanonicalTransform()
{
  Vector3D rotvec;

  TransMatrix3D canonicalTransform;
 
  if (1 - fabs(myNormal.z()) < EPSILON) {
    rotvec.x() = 1;
    rotvec.y() = rotvec.z() = 0;
  }
  else {
    rotvec.x() = myNormal.y();
    rotvec.y() = -myNormal.x();
    rotvec.z() = 0;
  }
    
  canonicalTransform.rotate(rotvec, -acos(myNormal.z()));
  canonicalTransform.translate(myCenter);
  myCanonicalTransform = canonicalTransform;
}

/*
 * A torus is tesselated into triangle by performing a sweep around the
 * axis [0,0,1] of the torus. 
 */
Object3D* Torus3D::createDecomposition() const
{
  int steps     = int(getPrecision()*12 + 3);
  int tubeSteps = steps/2+3;

  //
  // Check, if decomposition for a similar torus has already been done.
  //
  extern char* form(const char * ...);
  Name key = form("Torus3D#%d#%d#%g#%g", steps, tubeSteps, mySweptRadius, myTubeRadius);
  Object3D* retval = (Object3D*)Primitive3D::getDecomposition(key);

  if (retval == NULL) {
    //
    // No similar decomposition is present, so we have to create a new one.
    //
    List3D* list = new List3D;

    //
    // Rotation around torus axis [0,0,1] -> sweepRotate
    // Rotation for the tube sweep        -> tubeRotate
    //
    TransMatrix3D sweepRotate = TransMatrix3D::makeRotateZ(M_PI*2/steps);
    TransMatrix3D tubeRotate  = TransMatrix3D::makeRotateY(M_PI*2/tubeSteps);
  
    Vector3D sweepPosition = Vector3D(mySweptRadius,0,0);
    Vector3D lastSweepPosition;
    Vector3D* pointsOnTube     = new Vector3D[tubeSteps+1];
    Vector3D* lastPointsOnTube = new Vector3D[tubeSteps+1];

    register long i, j;

    //
    // Initial points on the tube.
    //
    pointsOnTube[0] = Vector3D(myTubeRadius,0,0);
    pointsOnTube[tubeSteps] = pointsOnTube[0];
  
    for (i=1; i<tubeSteps; i++)
      pointsOnTube[i] = transformAsVector(pointsOnTube[i-1], tubeRotate);
    for (i=0; i<=tubeSteps; i++)
      pointsOnTube[i] += sweepPosition;
 
    //
    // Start tesselating the torus by perfoming the sweep.
    //
    for (i=0; i<steps; i++) {
      // 
      // Compute next sweep position.
      //
      lastSweepPosition = sweepPosition;
      sweepPosition = transformAsVector(sweepPosition, sweepRotate);

      //
      // Compute points on the tube for the next sweep position.
      //
      for (j=0; j<=tubeSteps; j++) {
        lastPointsOnTube[j] = pointsOnTube[j];
        pointsOnTube[j] = transformAsVector(pointsOnTube[j], sweepRotate);
      }
 
      //
      // Create the triangles.
      //
      for (j=0; j<tubeSteps; j++) {
        list->adoptObject(
	 new Triangle3D(lastPointsOnTube[j], lastPointsOnTube[j]-lastSweepPosition,
		       pointsOnTube[j],     pointsOnTube[j]-sweepPosition,
		       pointsOnTube[j+1],   pointsOnTube[j+1]-sweepPosition));
        list->adoptObject(
	 new Triangle3D(lastPointsOnTube[j],   lastPointsOnTube[j]-lastSweepPosition,
		       pointsOnTube[j+1], 	   pointsOnTube[j+1]-sweepPosition,
		       lastPointsOnTube[j+1], lastPointsOnTube[j+1]-lastSweepPosition));
      }
    }

    delete [] pointsOnTube;
    delete [] lastPointsOnTube;
 
    retval = new Shared3D(list);
    retval->computeBounds();
    Primitive3D::adoptDecomposition(key, retval); 
  }

  retval = retval->copy();
  retval->setTransform(myCanonicalTransform);

  return retval;
}

/* 
 *  This code is adapted from Craig Kolbs rayshade.
 *
 *  The code for the toroid is simpified by always having the axis
 *  be the z-axis and then transforming information to and from
 *  toroid space.
 */
inline Vector3D Torus3D::unifiedNormal(const Vector3D& ucsPoint) const
{
  //
  // Find distance from axis.
  //
  Real distance = sqrt(sqr(ucsPoint.x()) + sqr(ucsPoint.y()));

  if (distance > EPSILON) {
    return Vector3D(ucsPoint.x() - (mySweptRadius*ucsPoint.x()/distance),
		  ucsPoint.y() - (mySweptRadius*ucsPoint.y()/distance),
		  ucsPoint.z());
  }
  else  // ERROR - dist should not be < EPSILON (should never happen)
    return ucsPoint;
}

Vector3D Torus3D::normal(const Vector3D& point) const
{
  Vector3D ucsPoint  = myCanonicalTransform.invTransformAsPoint(point);
  Vector3D ucsNormal = unifiedNormal(ucsPoint);

  return myCanonicalTransform.transformAsNormal(ucsNormal);
}

Object3D* Torus3D::copy() const
{
  return new Torus3D(*this);
}

/*
 * This code is adapted from Craig Kolbs rayshade.
 *
 * Original Equations for Toroid with position of (0,0,0) and axis (0,0,1)
 *
 * Equation for two circles of radius b centered at (-a,0,0) and (a,0,0) 
 *
 *      ((R-a)^2 + z*2 - b*b) * ((R+a)^2 + z*z - b*b) = 0 
 *
 *       a         is swept radius
 *       b         is tube  radius
 *
 * subsitute R*R = x*x + y*y  to rotate about z-axis
 *
 * and substitute the parametric ray equations:
 *
 *       x = x0 + t * x1;
 *       y = y0 + t * y1;
 *       z = z0 + t * z1;
 *
 * to get a Quartic in t.
 *
 *       c4*t^4 + c3*t^3 + c2*t^2 + c1*t + c0 = 0
 *
 * where the coefficients are:
 *
 *       c4 =   (x1s + y1s + z1s) * (x1s + y1s + z1s); 
 *       c3 =   4.0 * (tx + ty + tz) * (x1s + y1s + z1s);
 *       c2 =   2.0 * (x1s + y1s + z1s) * (x0s + y0s + z0s - as - bs)
 *            + 4.0 * (tx + ty + tz)    * (tx + ty + tz)
 *            + 4.0 * as * z1s;
 *       c1 =   4.0 * (tx + ty + tz) * (x0s + y0s + z0s - as - bs)
 *            + 8.0 * as * tz;
 *       c0 =   (x0s + y0s + z0s - as - bs) * (x0s + y0s + z0s - as - bs)
 *            + 4.0 * as * (z0s - bs);
 *
 *       as        is swept radius squared
 *       bs        is tube  radius squared
 *      (x0,y0,z0) is origin of ray to be tested
 *      (x1,y1,z1) is direction vector of ray to be tested
 *       tx        is x0 * x1
 *       ty        is y0 * y1
 *       tz        is z0 * z1
 *
 *   Since the direction vector (x1,y1,z1) is normalized:
 *              (x1s + y1s + z1s) = 1.0
 *
 *   Also let     g2s = (x1 * x0) + (y1 * y0) + (z1 * z0)
 *    and let     g0s = (x0 * x0) * (y0 * y0) + (z0 * z0) - as - bs 
 *    since these terms are used fairly often
 */

bool Torus3D::doIntersect(Ray3D& ray)
{
  bool hit = false;
  
  //
  // Transform the ray to canonical torus coordinates.
  //
  Vector3D origin = ray.getOrigin();
  Vector3D direction = ray.getDirection();
  Real rescale = 1. / ray.transform(myCanonicalTransform);

  double distance;
  register double g0s, g2s;
  register double as, bs;
  register double z0s, z1s, tz;

  as  = sqr(mySweptRadius);
  bs  = sqr(myTubeRadius);
  z0s = sqr(ray.getOrigin().z());
  z1s = sqr(ray.getDirection().z());
  tz  = ray.getOrigin().z() * ray.getDirection().z();
  g0s = sqr(ray.getOrigin().x()) +  sqr(ray.getOrigin().y()) + z0s - as - bs;
  g2s = ray.getOrigin().x() * ray.getDirection().x() +  
        ray.getOrigin().y() * ray.getDirection().y() +  tz;

  double c[5], s[4];
  
  c[4] = 1.0;
  c[3] = 4.0 * g2s;
  c[2] = 2.0 * (g0s  +  2.0 * g2s * g2s  +  2.0 * as * z1s);
  c[1] = 4.0 * (g2s*g0s  +  2.0*as*tz);
  c[0] = g0s * g0s  +  4.0 * as * (z0s - bs);
 
  int rootsNum = solveQuartic(c, s);

  if (rootsNum > 0) {
    //
    // Of roots return the smallest root > ray.getTolerance()
    //
    distance = 0.0;
    for(int i=0; i<rootsNum; i++) {
      //
      // If root is in front of ray origin ...
      //
      if (s[i] > ray.getTolerance()) {
       // ... first valid root ?
       if (distance == 0.0) 
         distance = (Real) s[i];
      // ... else update only if it's closer to ray origin.
       else if (s[i] < distance) 
         distance = (Real) s[i];
      }
    }
        
    if (distance > ray.getTolerance() && distance < ray.getBestHitDistance()) {
      hit = true;
      ray.setBestHitObject(this);
      ray.setBestHitDistance(distance);
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

void Torus3D::doComputeBounds()
{
  myBounds.expand( mySweptRadius+myTubeRadius, -mySweptRadius-myTubeRadius, -myTubeRadius);
  myBounds.expand( mySweptRadius+myTubeRadius, -mySweptRadius-myTubeRadius,  myTubeRadius);

  myBounds.expand( mySweptRadius+myTubeRadius,  mySweptRadius+myTubeRadius, -myTubeRadius);
  myBounds.expand( mySweptRadius+myTubeRadius,  mySweptRadius+myTubeRadius,  myTubeRadius);

  myBounds.expand(-mySweptRadius-myTubeRadius,  mySweptRadius+myTubeRadius, -myTubeRadius);
  myBounds.expand(-mySweptRadius-myTubeRadius,  mySweptRadius+myTubeRadius,  myTubeRadius);

  myBounds.expand(-mySweptRadius-myTubeRadius,  mySweptRadius+myTubeRadius, -myTubeRadius);
  myBounds.expand(-mySweptRadius-myTubeRadius,  mySweptRadius+myTubeRadius,  myTubeRadius);

  myBounds.transform(myCanonicalTransform.getTransMatrix());
}
  
Makeable* Torus3D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(4);
  getParameter(1, Real, sweptRadius);
  getParameter(2, Real, tubeRadius);
  getParameter(3, Vector3D, center);
  getParameter(4, Vector3D, normal);

  if (sweptRadius < EPSILON) {
    errMsg = "degenerate torus";
    return NULL;
  }

  Torus3D* newTorus = new Torus3D(*this);

  newTorus->setSweptRadius(sweptRadius);
  newTorus->setTubeRadius(tubeRadius);
  newTorus->setCenter(center);
  newTorus->setNormal(normal); 

  return newTorus;
}

static const RCString torus3DKeyword("torus");

RCString Torus3D::getKeyword() const {
  return torus3DKeyword;
}

List<Value*>* Torus3D::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  parameters->append(new Value(getSweptRadius()));
  parameters->append(new Value(getTubeRadius()));
  parameters->append(new Value(getCenter()));
  parameters->append(new Value(getNormal()));
  return parameters;
}


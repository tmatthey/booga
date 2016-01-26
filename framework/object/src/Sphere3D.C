/*
 * $RCSfile: Sphere3D.C,v $
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: Sphere3D.C,v 1.28 1996/10/04 09:48:12 collison Exp $
 * -----------------------------------------------------------------------------
 */


#include "booga/base/Report.h"
#include "booga/base/Value.h"
#include "booga/object/Triangle3D.h"
#include "booga/object/List3D.h"
#include "booga/object/Shared3D.h"
#include "booga/object/Sphere3D.h"

// ____________________________________________________________________ Sphere3D

implementRTTI(Sphere3D, Primitive3D);

Sphere3D::Sphere3D(Exemplar exemplar)
: Primitive3D(exemplar)
{
  myRadius = 1;
  myCenter = Vector3D(0,0,0);
}

Sphere3D::Sphere3D(Real radius, const Vector3D& center)
: myRadius(radius), myCenter(center)
{
  if (myRadius < EPSILON) {
    std::stringstream os;
    os << "[Sphere3D::Sphere3D] degenerate sphere (radius = " << myRadius << ")";
    Report::recoverable(os);
  }
}

void Sphere3D::setCenter(const Vector3D& center)
{
  myCenter = center;
}

void Sphere3D::setRadius(Real radius)
{
  if (radius < EPSILON) {
    std::stringstream os;
    os << "[Sphere3D::setRadius] illegal radius = " << radius << " ignored";
    Report::warning(os);
    return;
  }

  myRadius = radius;
}

void Sphere3D::generateTriangles(const Vector3D& p1, 
			      const Vector3D& p2, 
			      const Vector3D& p3,
			      List3D* triangles, int steps) const
{
  if (steps <= 0)
    triangles->adoptObject(new Triangle3D(p1, p1,
				      p2, p2,
				      p3, p3));
  else {
    Vector3D a = ((p1+p2)/2).normalized();
    Vector3D b = ((p2+p3)/2).normalized();
    Vector3D c = ((p1+p3)/2).normalized();
    generateTriangles(p1, a, c, triangles, steps-1);
    generateTriangles(p2, b, a, triangles, steps-1);
    generateTriangles(p3, c, b, triangles, steps-1);
    generateTriangles(a,  b, c, triangles, steps-1);
  }
}

/* The algorithm used for the tesselation is based after the one by 
 * Jon Leech (leech@cs.unc.edu)
 *
 * Generate a triangle mesh approximating a sphere by recursive subdivision.
 * First approximation is an octahedron. Each level of refinement increases 
 * the number of triangles by a factor of 4.
 *
 * Subdivide each triangle in the old approximation and normalize
 * the new points thus generated to lie on the surface of the unit
 * sphere.
 * Each input triangle with vertices labelled [1,2,3] as shown
 * below will be turned into four new triangles:
 *
 *			Make new points
 *			    a = (1+2)/2
 *			    b = (2+3)/2
 *			    c = (1+3)/2
 *	   3
 *	  /\		Normalize a, b, c
 *	 /  \
 *      c/____\ b	         Construct new triangles
 *      /\    /\	            [1,a,c]
 *     /  \  /  \	            [2,b,a]
 *    /____\/____\	   [3,c,b]
 *  1	  a	 2	   [a,b,c]
 *
 */
Object3D* Sphere3D::createDecomposition() const
{
  // The precision argument is converted to 'steps' of recursion by using 
  // the following formula:
  //
  //                     2
  //     steps = 8 * log (precison + 1)
  //                       
  //     precision = 0   -> steps = 0
  //                 0.5 -> steps = 3
  //                 1   -> steps = 8
  int steps = (int) rint(8.0*pow(log(getPrecision()+1), 2));

  //
  // Check, if decomposition for a similar torus has already been done.
  //
  char tmp[256];
  sprintf(tmp,"Sphere3D#%d#", static_cast<int>(steps));
  Name key(tmp);
  Object3D* retval = (Object3D*)Primitive3D::getDecomposition(key);

  if (retval == NULL) {
    //
    // No similar decomposition is present, so we have to create a new one.
    //
    List3D* triangles = new List3D;
 
    Vector3D p[4] = 
       { Vector3D(1,0,0), Vector3D(0,1,0), Vector3D(-1,0,0), Vector3D(0,-1,0) };

    for (int i=0; i<4; i++) {
      // The upper and lower half of the octahedron are created and 
      // subdivided by recursion.
      generateTriangles(p[i], p[(i+1)%4], Vector3D(0,0,1),  triangles, steps);
      generateTriangles(p[i], Vector3D(0,0,-1), p[(i+1)%4], triangles, steps);
    }
  
    retval = new Shared3D(triangles);
    retval->computeBounds();
    Primitive3D::adoptDecomposition(key, retval); 
  }

  retval = retval->copy();

  //
  // Decomposition of the unit sphere (1, [0,0,0]) has to be transformed first.
  //
  TransMatrix3D localTransform;
  localTransform.scale(myRadius, myRadius, myRadius);
  localTransform.translate(myCenter);
  retval->setTransform(localTransform);

  return retval;
}

Vector3D Sphere3D::normal(const Vector3D& point) const
{
  return (point-myCenter).normalized();
}

Object3D* Sphere3D::copy() const
{
  return new Sphere3D(*this);
}

void Sphere3D::doComputeBounds()
{
  myBounds.expand(myCenter[0]-myRadius, myCenter[1]-myRadius, myCenter[2]-myRadius);
  myBounds.expand(myCenter[0]+myRadius, myCenter[1]+myRadius, myCenter[2]+myRadius);
}
  
/*
 * Adapted from Craig Kolb's rayshade.
 */
bool Sphere3D::doIntersect(Ray3D& ray)
{
  //
  // Translate ray origin to object space and negate everything.
  //(Thus, we translate the sphere into ray space, which saves
  // us a couple of negations below.)
  //
  Real xray = myCenter.x() - ray.getOrigin().x();
  Real yray = myCenter.y() - ray.getOrigin().y();
  Real zray = myCenter.z() - ray.getOrigin().z();
  
  //
  // Solve quadric equation.
  //
  Real b = xray*ray.getDirection().x() + 
           yray*ray.getDirection().y() + 
           zray*ray.getDirection().z();
  Real discrim = b*b - xray*xray - yray*yray - zray*zray + myRadius*myRadius;

  //
  // Discriminante negative?? -> no intersection.
  //
  if (discrim < 0)	
    return false;		
  
  discrim = sqrt(discrim);

  //
  // We may hit the sphere twice, test both cases 
  //   -> check for the first hitpoint.
  //
  Real t = b - discrim;		// Distance from origin: first hitpoint.
  if (t > ray.getTolerance()) {
    if (t < ray.getBestHitDistance()) {
      //
      // HIT!!! 
      // 
      ray.setBestHitObject(this);
      ray.setBestHitDistance(t);
      return true;
    }
    return false;
  }

  //
  //  Check for the second hitpoint.
  //
  t = b + discrim;
  if (t > ray.getTolerance() && t < ray.getBestHitDistance()) {
    //
    // HIT!!! 
    // 
    ray.setBestHitObject(this);
    ray.setBestHitDistance(t);
    return true;
  }

  //
  // Sorry no hit...
  //
  return false;
}

Makeable* Sphere3D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(2);
  getParameter(1, Real, radius);
  getParameter(2, Vector3D, center);

  if (radius < EPSILON) {
    errMsg = "degenerate sphere";
    return NULL;
  }

  Sphere3D* newSphere = new Sphere3D(*this);
  newSphere->setRadius(radius);
  newSphere->setCenter(center);
  
  return newSphere;
}

static const RCString sphere3DKeyword("sphere");

RCString Sphere3D::getKeyword() const {
  return sphere3DKeyword;
}

List<Value*>* Sphere3D::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  parameters->append(new Value(getRadius()));
  parameters->append(new Value(getCenter()));
  return parameters;
}

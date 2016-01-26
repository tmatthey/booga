/*
 * $RCSfile: Triangle3D.C,v $
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
 *  $Id: Triangle3D.C,v 1.24 1997/09/19 07:15:04 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
#ifdef SVR4
#include <stream.h>
#endif
#include <strstream.h>

#include "booga/base/Value.h"
#include "booga/base/Geometry3D.h"
#include "booga/object/Triangle3D.h"

//_______________________________________________________ barycentricInterpolate

Vector3D barycentricInterpolate(Vector3D p1, Vector3D p2, Vector3D p3, Vector3D bc)
{
  return Vector3D(bc.x()*p1.x() + bc.y()*p2.x() + bc.z()*p3.x(),
                  bc.x()*p1.y() + bc.y()*p2.y() + bc.z()*p3.y(),
                  bc.x()*p1.z() + bc.y()*p2.z() + bc.z()*p3.z());
}

//___________________________________________________________________ Triangle3D

implementRTTI(Triangle3D, Primitive3D);

Triangle3D::Triangle3D(Exemplar exemplar)
: Primitive3D(exemplar)
{
  myVertex1 = Vector3D(1,1,0);
  myVertex2 = Vector3D(0,1,0);
  myVertex3 = Vector3D(1,0,0);
  
  myPlaneNormal = myNormal1 = myNormal2 = myNormal3 = Vector3D(0,0,1);

  initTriangle();
}

Triangle3D::Triangle3D(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3)
: myVertex1(v1), myVertex2(v2), myVertex3(v3) 
{
  //
  // Calculate Normals: assume triangle orientation is counter-clockwise.
  //
  myNormal1 = myNormal2 = myNormal3 = 
    ((myVertex2-myVertex1)*(myVertex3-myVertex1)).normalized();
  
  initTriangle();
}

Triangle3D::Triangle3D(const Vector3D& v1, const Vector3D& n1,   
		     const Vector3D& v2, const Vector3D& n2,
		     const Vector3D& v3, const Vector3D& n3)
: myVertex1(v1), myVertex2(v2), myVertex3(v3) 
{
  myNormal1 = n1.normalized();
  myNormal2 = n2.normalized();
  myNormal3 = n3.normalized();
  
  // check orientation
  Vector3D computedNormal = ((myVertex2-myVertex1)*(myVertex3-myVertex1)).normalized();
  Vector3D suppliedNormal = (myNormal1+myNormal2+myNormal3).normalized();
  if ((computedNormal+suppliedNormal).length() < 1) { // directing to different sides
    // Change orientation of triangle
    swap(myNormal1, myNormal2);
    swap(myVertex1, myVertex2);
  } 
    
  initTriangle();
}

const Vector3D& Triangle3D::getVertex(int index) const
{
  if (index < 0 || index > 2)
    Report::error("[Triangle3D::getVertex] index out of range");

  if (index == 0)
    return myVertex1;
  else if (index == 1)
    return myVertex2;
  else
    return myVertex3;
}

void Triangle3D::setVertex(int index, const Vector3D& newValue)
{
  if (index < 0 || index > 2)
    Report::error("[Triangle3D::setVertex] index out of range");

  if (index == 0)
    myVertex1 = newValue;
  else if (index == 1)
    myVertex2 = newValue;
  else
    myVertex3 = newValue;
    
  initTriangle();
}

const Vector3D& Triangle3D::getNormal(int index) const
{
  if (index < 0 || index > 2)
    Report::error("[Triangle3D::getNormal] index out of range");

  if (index == 0)
    return myNormal1;
  else if (index == 1)
    return myNormal2;
  else
    return myNormal3;
}
 
void Triangle3D::setNormal(int index, const Vector3D& newValue)
{
  if (index < 0 || index > 2)
    Report::error("[Triangle3D::setNormal] index out of range");

  if (index == 0)
    myNormal1 = newValue.normalized();
  else if (index == 1)
    myNormal2 = newValue.normalized();
  else
    myNormal3 = newValue.normalized();
    
  initTriangle();
}

Object3D* Triangle3D::createDecomposition() const
{
  return NULL;
}

/*
 * Calculate barycentric coordinates of point in triangle.
 * Use these coordinates to interpolate normal.
 */
Vector3D Triangle3D::normal(const Vector3D& point) const
{
  Vector3D bc;
  if (getBarycentricCoord(point, bc))
    return barycentricInterpolate(myNormal3, myNormal2, myNormal1, bc);
  else {
    Report::warning("[Triangle3D::normal] : point not in triangle");
    return myPlaneNormal;
  }
}

void Triangle3D::initTriangle()
{
  // edges of triangle:
  myEdge21 = myVertex2 - myVertex1;
  myEdge31 = myVertex3 - myVertex1;

  // compute dominant part of normal
  Real scale;
  Vector3D tmpNorm(myEdge21*myEdge31);
  Vector3D absTmpNorm(fabs(tmpNorm[0]), fabs(tmpNorm[1]), fabs(tmpNorm[2]));
  if (absTmpNorm[0] > absTmpNorm[1] && absTmpNorm[0] > absTmpNorm[2]) {
    myDominant1 = 1; myDominant2 = 2; scale = 1/tmpNorm[0];
  } else if (absTmpNorm[1] > absTmpNorm[2]) {
    myDominant1 = 2; myDominant2 = 0; scale = 1/tmpNorm[1];
  } else {
    myDominant1 = 0; myDominant2 = 1; scale = 1/tmpNorm[2];
  }

  // scale edges
  myEdge21 *= scale;
  myEdge31 *= scale;

  // set plane constants
  myPlaneNormal = tmpNorm.normalized();
  if ((myPlaneNormal^myNormal1) < 0) // wrong oriented ...
    myPlaneNormal = -myPlaneNormal;	 // flip normal

  myPlaneDist = myPlaneNormal^myVertex1;
}

bool Triangle3D::getBarycentricCoord(const Vector3D& point, Vector3D& getBC) const
{
  // calculate barycentric coordinate of intersection point
  getBC.x() = myEdge21[myDominant1]*(point[myDominant2]-myVertex1[myDominant2]) - 
              myEdge21[myDominant2]*(point[myDominant1]-myVertex1[myDominant1]);
  if (getBC.x() <= - EPSILON || getBC.x() >= 1 + EPSILON)
    return false;

  getBC.y() = myEdge31[myDominant2]*(point[myDominant1]-myVertex1[myDominant1]) -
              myEdge31[myDominant1]*(point[myDominant2]-myVertex1[myDominant2]);
  if (getBC.y() <= - EPSILON || getBC.y() >= 1 + EPSILON)
    return false;
  
  getBC.z() = 1-getBC.x()-getBC.y();
  if (getBC.z() <= - EPSILON) 
    return false;
  
  // mr. epsilon (27.07.98/tm)
  if (getBC.x() < 0) getBC.x() = 0;
  if (getBC.x() > 1) getBC.x() = 1;
  if (getBC.y() < 0) getBC.y() = 0;
  if (getBC.y() > 1) getBC.y() = 1;
  if (getBC.z() < 0) getBC.z() = 0;

  return true;
}

Object3D* Triangle3D::copy() const
{
  return new Triangle3D(*this);
}

void Triangle3D::doComputeBounds()
{
  myBounds.expand(myVertex1);
  myBounds.expand(myVertex2);
  myBounds.expand(myVertex3);
}
 
bool Triangle3D::doIntersect(Ray3D& ray)
{
  // calculate distance of ray/plane intersection
  Real t = (myPlaneDist - (myPlaneNormal^ray.getOrigin())) / 
                          (myPlaneNormal^ray.getDirection());

  // has already a nearer intersection been found?
  if (t < ray.getTolerance() || t > ray.getBestHitDistance())  
    return false;  

  // test, if point is inside primitive or not.
  Vector3D bc;
  if (!getBarycentricCoord(ray.getOrigin() + t*ray.getDirection(), bc))
    return false;
    
  ray.setBestHitDistance(t);
  ray.setBestHitObject(this);
  
  return true;
}

Makeable* Triangle3D::make(RCString& errMsg, 
                           const List<Value*>* parameters) const
{
  long provided = (!parameters ? 0 : parameters->count());
  if (provided == 3) {
    //
    // No normals provided for triangle.
    //
    getParameter(1, Vector3D, v1);
    getParameter(2, Vector3D, v2);
    getParameter(3, Vector3D, v3);
    
    if (equal(((v2-v1)*(v3-v1)).length(), 0)) {
      errMsg = "degenerate triangle";
      return NULL;
    }

    return new Triangle3D(v1, v2, v3);
  }
  else if (provided == 6) {
    //
    // Triangle with normals.
    //
    getParameter(1, Vector3D, v1);
    getParameter(2, Vector3D, n1);
    getParameter(3, Vector3D, v2);
    getParameter(4, Vector3D, n2);
    getParameter(5, Vector3D, v3);
    getParameter(6, Vector3D, n3);

    if (equal(((v2-v1)*(v3-v1)).length(), 0)) {
      errMsg = "degenerate triangle";
      return NULL;
    }

    return new Triangle3D(v1, n1, v2, n2, v3, n3);
  } else {
    ostrstream os;
    os << " 3 or 6 parameters required, " << provided << " provided";
    errMsg = os;             
    return NULL;				                  
  }
}

static const RCString triangle3DKeyword("triangle");

RCString Triangle3D::getKeyword() const {
  return triangle3DKeyword;
}

List<Value*>* Triangle3D::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  Vector3D normal(Geometry3D::normal(getVertex(2),getVertex(0),getVertex(1)));
  if (normal.equal(getNormal(0)) && normal.equal(getNormal(1)) && normal.equal(getNormal(2))){
    parameters->append(new Value(getVertex(0)));
    parameters->append(new Value(getVertex(1)));
    parameters->append(new Value(getVertex(2)));
  }
  else {
    parameters->append(new Value(getVertex(0)));
    parameters->append(new Value(getNormal(0)));
    parameters->append(new Value(getVertex(1)));
    parameters->append(new Value(getNormal(1)));
    parameters->append(new Value(getVertex(2)));
    parameters->append(new Value(getNormal(2)));
  }
  return parameters;
}

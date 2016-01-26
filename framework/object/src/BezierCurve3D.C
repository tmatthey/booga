/*
 * $RCSfile: BezierCurve3D.C,v $
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
 *  $Id: BezierCurve3D.C,v 1.1 1997/12/15 11:47:28 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include <strstream.h>
#include "booga/base/Value.h"
#include "booga/object/BoundsUtilities.h"  // slapTest
#include "booga/object/List3D.h"
#include "booga/object/BezierCurve3D.h"
#include "booga/object/Cylinder3D.h"
#include "booga/object/Sphere3D.h"
#include "booga/object/Line3D.h"
#include "booga/object/Shared3D.h"

// ____________________________________________________________________ BezierCurve3D

implementRTTI(BezierCurve3D, Primitive3D);

BezierCurve3D::BezierCurve3D(Exemplar exemplar)
: Primitive3D(exemplar)
{
  myRadius = .1;
  myVertices[0] = Vector3D(0,0,0);
  myVertices[1] = Vector3D(1,1,0);
  myVertices[2] = Vector3D(2,2,0);
  myVertices[3] = Vector3D(3,0,0);
  myDecomposition = NULL;
}

BezierCurve3D::BezierCurve3D()
{
  myRadius = .1;
  myVertices[0] = Vector3D(0,0,0);
  myVertices[1] = Vector3D(1,1,0);
  myVertices[2] = Vector3D(2,2,0);
  myVertices[3] = Vector3D(3,0,0);
  myDecomposition = NULL;
}

BezierCurve3D::BezierCurve3D(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3, const Vector3D& v4) 
{
  myVertices[0] = v1;
  myVertices[1] = v2;
  myVertices[2] = v3;
  myVertices[3] = v4;
  myDecomposition = NULL;
}

Object3D* BezierCurve3D::createDecomposition() const
{
  //
  // We already have a valid decomposition of the polygon object -> just make a copy.
  //
  if (myDecomposition != NULL)
    return myDecomposition->copy();
  
  List3D* triangles = new List3D;
 
  if (getPrecision() > .7) 
    doDecomposition (triangles, 5);
  else if (getPrecision() >= .5) 
    doDecomposition (triangles, 4);
  else if (getPrecision() >= .3) 
    doDecomposition (triangles, 3);
  else 
    doDecomposition (triangles, 2);

  ((BezierCurve3D*)this)->myDecomposition = new Shared3D(triangles);
  ((BezierCurve3D*)this)->myDecomposition->computeBounds();
  return myDecomposition->copy();
}

void BezierCurve3D::doDecomposition (Aggregate3D *l, int level) const
{
  if (level > 0) { // do recursion
    // subdivide patch:
    BezierCurve3D left(*this);
    BezierCurve3D right(*this);
    
	left.setRadius(getRadius());
	right.setRadius(getRadius());

    subdivide (left, right);
        
    left.doDecomposition(l, level-1);
    right.doDecomposition(l, level-1);
  } else { // triangulate!
	if (myRadius > 0.0) {
      Sphere3D *s = new Sphere3D (myRadius,myVertices[3]);
	  s->setPrecision(getPrecision());
	  Cylinder3D *c = new Cylinder3D (myRadius,myVertices[0], myVertices[3]);
	  c->setPrecision(getPrecision());
	  l->adoptObject(c);
	  l->adoptObject(s);
	} else 
  	  l->adoptObject(new Line3D (myVertices[0], myVertices[3]));
  }
}


void BezierCurve3D::subdivide (BezierCurve3D& left, BezierCurve3D& right) const
{
  Vector3D h  = myVertices[1] + ((myVertices[2] - myVertices[1])/2.0);
  Vector3D l1 = myVertices[0] + ((myVertices[1] - myVertices[0])/2.0);
  Vector3D r2 = myVertices[3] + ((myVertices[2] - myVertices[3])/2.0);
  Vector3D l2 = l1   + ((h    - l1)/2.0);
  Vector3D r1 = r2   + ((h    - r2)/2.0);
  Vector3D l3 = l2   + ((r1   - l2)/2.0);
  
  left.setVertex(0, myVertices[0]);
  left.setVertex(1,l1);
  left.setVertex(2, l2);
  left.setVertex(3, l3);
  right.setVertex(0, l3);
  right.setVertex(1, r1);
  right.setVertex(2, r2);
  right.setVertex(3, myVertices[3]);
}


Vector3D BezierCurve3D::normal(const Vector3D&) const
{
  return Vector3D(0,0,1);
}

Vector3D BezierCurve3D::evaluate (Real u) const
{
  Vector3D retval;

  retval = (1-u)*(1-u)*(1-u)*myVertices[0] +
           3*u*(1-u)*(1-u)*myVertices[1] +
           3*u*u*(1-u)*myVertices[2] +
           u*u*u*myVertices[3];

  return retval;
}

Object3D* BezierCurve3D::copy() const
{
  return new BezierCurve3D(*this);
}

bool BezierCurve3D::doIntersect(Ray3D& ray)
{
  if (myRadius > 0.0) {
  	if (myDecomposition == NULL)
      delete BezierCurve3D::createDecomposition();
    return myDecomposition->intersect(ray);
  } else
	  return false;
}

void BezierCurve3D::doComputeBounds()
{
  myBounds.expand(myVertices[0]);
  myBounds.expand(myVertices[1]);
  myBounds.expand(myVertices[2]);
  myBounds.expand(myVertices[3]);
}
  
Makeable* BezierCurve3D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(5);

  getParameter(1, Real, r);
  getParameter(2, Vector3D, v1);
  getParameter(3, Vector3D, v2);
  getParameter(4, Vector3D, v3);
  getParameter(5, Vector3D, v4);

  BezierCurve3D* newCurve = new BezierCurve3D(*this);
  newCurve->setRadius(r);
  newCurve->setVertex(0, v1);
  newCurve->setVertex(1, v2);
  newCurve->setVertex(2, v3);
  newCurve->setVertex(3, v4);


  return newCurve;
}

static const RCString boxKeyword("beziercurve");

RCString BezierCurve3D::getKeyword() const {
  return boxKeyword;
}

List<Value*>* BezierCurve3D::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  parameters->append(new Value(myRadius));
  parameters->append(new Value(myVertices[0]));
  parameters->append(new Value(myVertices[1]));
  parameters->append(new Value(myVertices[2]));
  parameters->append(new Value(myVertices[3]));
  return parameters;
}

void BezierCurve3D::interpolate(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3, BezierCurve3D* c1, BezierCurve3D* c2) 
{
// interpolation of three vectors with two bezier curves

  Vector3D a = v2-v1;
  Vector3D b = v3-v2;
  Vector3D c = v1-v3;

  Vector3D p3 = v2 + c.normalized()*a.length()*.3;
  Vector3D e = p3-v1;
  Vector3D p1 = v1+e.normalized()*a.length()*.3;

  Vector3D p4 = v2 - c.normalized()*b.length()*.3;
  Vector3D f = p4-v3;
  Vector3D p5 = v3+f.normalized()*b.length()*.3;
    
  c1->setVertex(0,v1);
  c1->setVertex(1,p1);
  c1->setVertex(2,p3);
  c1->setVertex(3,v2);

  c2->setVertex(0,v2);
  c2->setVertex(1,p4);
  c2->setVertex(2,p5);
  c2->setVertex(3,v3);
}




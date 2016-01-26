/*
 * $RCSfile: BezierCurve3D.h,v $
 *
 * Copyright (C) 1994-97, Bernhard Buehlmann <buhlmann@iam.unibe.ch>
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
 *  $Id: BezierCurve3D.h,v 1.1 1997/12/15 11:47:29 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _BezierCurve3D_H
#define _BezierCurve3D_H

#include "booga/object/Primitive3D.h"
class Aggregate3D;

// ____________________________________________________________________ BezierCurve3D

class BezierCurve3D : public Primitive3D {
declareRTTI(BezierCurve3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  BezierCurve3D(Exemplar);
  BezierCurve3D(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3, const Vector3D& v4);
  BezierCurve3D();
  // BezierCurve3D(const BezierCurve3D&);                 // Use default version.

public:
  // virtual ~BezierCurve3D();                    // Use default version.

private:  
  BezierCurve3D& operator=(const BezierCurve3D& box);     // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class BezierCurve3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Real getRadius() const;
  void setRadius(const Real r);
  
  const Vector3D& getVertex(int i) const;
  void setVertex(int i, const Vector3D& v);

  void subdivide (BezierCurve3D& left, BezierCurve3D& right) const;
  void doDecomposition (Aggregate3D *l, int level) const;
  Vector3D evaluate (Real u) const;
  static void interpolate(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3, BezierCurve3D* c1, BezierCurve3D* c2);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Primitive3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object3D* createDecomposition() const;
  virtual Vector3D normal(const Vector3D& point) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object3D* copy() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual void doComputeBounds();
private:
  virtual bool doIntersect(Ray3D& ray);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual RCString getKeyword() const;
  virtual List<Value*>* createParameters();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Vector3D myVertices[4];
  Real myRadius;
  Object3D* myDecomposition;
};

//______________________________________________________________________ INLINES


inline Real BezierCurve3D::getRadius() const
{
  return myRadius;
}

inline void BezierCurve3D::setRadius(const Real r)
{
  myRadius = r;
}


inline const Vector3D& BezierCurve3D::getVertex(int i) const
{
  if (i>=0 && i<4)
    return myVertices[i];
  else if (i < 0)
    return myVertices[0];
  else
    return myVertices[3];
}

inline void BezierCurve3D::setVertex(int i, const Vector3D& v)
{
  if (i>=0 && i<4)
    myVertices[i] = v;
}

#endif // _BezierCurve3D_H

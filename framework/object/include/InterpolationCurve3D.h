/*
 * $RCSfile: InterpolationCurve3D.h,v $
 *
 * Copyright (C) 1994-96, Bernhard Buehlmann <buhlmann@iam.unibe.ch>
 *                        University of Berne, Switzerland
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
 *  $Id: InterpolationCurve3D.h,v 1.2 1998/01/06 08:25:49 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _InterpolationCurve3D_H
#define _InterpolationCurve3D_H

#include "booga/object/Primitive3D.h"
class Aggregate3D;

// ____________________________________________________________________ InterpolationCurve3D

class InterpolationCurve3D : public Primitive3D {
declareRTTI(InterpolationCurve3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  InterpolationCurve3D(Exemplar);
  InterpolationCurve3D();
  InterpolationCurve3D(const InterpolationCurve3D&);                 // Use default version.
  InterpolationCurve3D(const List<Vector3D>& list);

public:
  // virtual ~InterpolationCurve3D();                    // Use default version.

private:  
  InterpolationCurve3D& operator=(const InterpolationCurve3D& box);     // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class InterpolationCurve3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Real getRadius() const;
  void setRadius(const Real r);

  void appendVector(const Vector3D& v);
  Vector3D evaluate(Real u) const;
  const List<Vector3D>& getVectors() const { return myVectors;}

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
  List<Vector3D> myVectors;
  Real myRadius;
  Object3D* myDecomposition;
};

//______________________________________________________________________ INLINES


inline Real InterpolationCurve3D::getRadius() const
{
  return myRadius;
}

inline void InterpolationCurve3D::setRadius(const Real r)
{
  myRadius = r;
}

inline void InterpolationCurve3D::appendVector(const Vector3D& v)
{
  myVectors.append(v);
}
#endif // _InterpolationCurve3D_H

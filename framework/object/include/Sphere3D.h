/*
 * $RCSfile: Sphere3D.h,v $
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
 *  $Id: Sphere3D.h,v 1.15 1996/10/04 09:48:13 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Sphere3D_H
#define _Sphere3D_H

#include "booga/object/Primitive3D.h"

class List3D;

// ____________________________________________________________________ Sphere3D

class Sphere3D : public Primitive3D {
declareRTTI(Sphere3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Sphere3D(Exemplar);
  Sphere3D(Real radius, const Vector3D& center);
  // Sphere3D(const Sphere3D&);          // Use default version.

public:
  // virtual ~Sphere3D();                // Use default version.

private:  
  Sphere3D& operator=(const Sphere3D&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Sphere3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  const Vector3D& getCenter() const;
  void setCenter(const Vector3D& center);

  Real getRadius() const;
  void setRadius(Real radius);
  
private:
  void generateTriangles(const Vector3D&, const Vector3D&, const Vector3D&, 
		       List3D*, int) const;
		       
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
  Real myRadius;
  Vector3D myCenter;
};

//______________________________________________________________________ INLINES

inline const Vector3D& Sphere3D::getCenter() const
{
  return myCenter;
}

inline Real Sphere3D::getRadius() const
{
  return myRadius;
}

#endif // _Sphere3D_H

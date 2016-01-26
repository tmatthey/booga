/*
 * $RCSfile: Torus3D.h,v $
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
 *  $Id: Torus3D.h,v 1.13 1996/10/04 09:48:44 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Torus3D_H
#define _Torus3D_H

#include "booga/object/Transform3D.h"
#include "booga/object/Primitive3D.h"

// _____________________________________________________________________ Torus3D

class Torus3D : public Primitive3D {
declareRTTI(Torus3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Torus3D(Exemplar);
  Torus3D(Real sweptRadius, Real tubeRadius, 
	  const Vector3D& center, const Vector3D& normal);
  // Torus3D(const Torus3D&);                 // Use default version.

public:
  // virtual ~Torus3D();                      // Use default version.

private:  
  Torus3D& operator=(const Torus3D& sphere);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Torus3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  const Vector3D& getCenter() const;
  void setCenter(const Vector3D& center);

  const Vector3D& getNormal() const;
  void setNormal(const Vector3D& normal);

  Real getSweptRadius() const;
  void setSweptRadius(Real sweptRadius);

  Real getTubeRadius() const;
  void setTubeRadius(Real tubeRadius);

  const Transform3D& getCanonicalTransform() const;

private:
  void computeCanonicalTransform();
  inline Vector3D unifiedNormal(const Vector3D& ucsPoint) const;

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
  Real     mySweptRadius;
  Real     myTubeRadius;
  Vector3D myCenter;
  Vector3D myNormal;
  
  Transform3D myCanonicalTransform;  // General <--> conical transformation.
};

//______________________________________________________________________ INLINES

inline const Vector3D& Torus3D::getCenter() const
{
  return myCenter;
}

inline const Vector3D& Torus3D::getNormal() const
{
  return myNormal;
}

inline Real Torus3D::getSweptRadius() const
{
  return mySweptRadius;
}

inline Real Torus3D::getTubeRadius() const
{
  return myTubeRadius;
}

inline const Transform3D& Torus3D::getCanonicalTransform() const
{
  return myCanonicalTransform;
}

#endif // _Torus3D_H

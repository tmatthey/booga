/*
 * $RCSfile: NurbsCircle3D.h,v $
 *
 * Copyright (C) 1995, Richard Baechler <baechler@iam.unibe.ch>
 *                     University of Berne, Switzerland
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
 *  $Id: NurbsCircle3D.h,v 1.7 1996/09/12 13:51:26 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _NurbsCircle3D_H
#define _NurbsCircle3D_H

#include "booga/nurbs/Nurbs3D.h"

//________________________________________________________________ NurbsCircle3D

class NurbsCircle3D : public Nurbs3D {
  declareRTTI(NurbsCircle3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  NurbsCircle3D();
  NurbsCircle3D(Exemplar exemplar);
  NurbsCircle3D(Real radius, const Vector3D &center, const Vector3D &normal);
  NurbsCircle3D(const NurbsCircle3D &nrb);

public:
  // virtual ~NurbsCircle3D();  // Use default version.

public:
  NurbsCircle3D& operator=(const NurbsCircle3D &nrb);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class NurbsCircle3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Real getRadius() const;
  void setRadius(Real radius);

  const Vector3D& getCenter() const;
  void setCenter(const Vector3D &center);

  const Vector3D& getNormal() const;
  void setNormal(const Vector3D &normal);

  virtual void setAttribute(Nurbs3DPathAttr *attr);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From Nurbs3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void rebuild();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class TPrimitive<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object3D* createDecomposition() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object3D* copy() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class BOOGAObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual void doComputeBounds();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Makeable* make(RCString &errMsg, const List<Value*> *parameters) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Real     myRadius;
  Vector3D myCenter;
  Vector3D myNormal;
  bool     myCalculatedFlag;
};

//_________________________________________________________________ INLINES

inline Real NurbsCircle3D::getRadius() const
{
  return myRadius;
}

inline const Vector3D& NurbsCircle3D::getCenter() const
{
  return myCenter;
}

inline const Vector3D& NurbsCircle3D::getNormal() const
{
  return myNormal;
}

#endif // _NurbsCircle3D_H

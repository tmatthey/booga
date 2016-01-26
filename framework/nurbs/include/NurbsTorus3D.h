/*
 * $RCSfile: NurbsTorus3D.h,v $
 *
 * Copyright(C) 1995, Richard Baechler <baechler@iam.unibe.ch>
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
 *  $Id: NurbsTorus3D.h,v 1.6 1996/09/12 13:51:48 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _NurbsTorus3D_H
#define _NurbsTorus3D_H

#include "booga/nurbs/Nurbs3D.h"

//_________________________________________________________________ NurbsTorus3D

class NurbsTorus3D : public Nurbs3D {
  declareRTTI(NurbsTorus3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  NurbsTorus3D();
  NurbsTorus3D(Exemplar exemplar);
  NurbsTorus3D(Real sweptRadius, Real tubeRadius, 
		const Vector3D& center, const Vector3D& normal);
  NurbsTorus3D(const NurbsTorus3D &nrb);

public:
  // virtual ~NurbsTorus3D();  // Use default version.

public:
  NurbsTorus3D& operator=(const NurbsTorus3D &nrb);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class NurbsTorus3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Real getSweptRadius() const;
  void setSweptRadius(Real sweptRadius);

  Real getTubeRadius() const;
  void setTubeRadius(Real tubeRadius);

  const Vector3D& getCenter() const;
  void setCenter(const Vector3D &center);

  const Vector3D& getNormal() const;
  void setNormal(const Vector3D &normal);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From Nurbs3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void rebuild();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class TPrimitive
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object3D* createDecomposition() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class TObject
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
  Real     mySweptRadius;
  Real     myTubeRadius;
  Vector3D myCenter;
  Vector3D myNormal;
  bool     myCalculatedFlag;
};

//______________________________________________________________________ INLINES

inline Real NurbsTorus3D::getSweptRadius() const
{
  return mySweptRadius;
}

inline Real NurbsTorus3D::getTubeRadius() const
{
  return myTubeRadius;
}

inline const Vector3D& NurbsTorus3D::getCenter() const
{
  return myCenter;
}

inline const Vector3D& NurbsTorus3D::getNormal() const
{
  return myNormal;
}

#endif // _NurbsTorus3D_H

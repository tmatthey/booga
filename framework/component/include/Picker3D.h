/*
 * $RCSfile: Picker3D.h,v $
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
 *  $Id: Picker3D.h,v 1.7 1996/08/01 12:00:29 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Picker3D_H
#define _Picker3D_H

#include "booga/object/Ray3D.h"
#include "booga/component/Operation3D.h"

class Camera3D;

//_____________________________________________________________________ Picker3D

class Picker3D : public Operation3D {
declareRTTI(Picker3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Picker3D();
  // Picker3D(const Picker3D&);            // Use default version.

public:
  virtual ~Picker3D();  

public:
  // Picker3D& operator=(const Picker3D&);  // Use default version.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Picker3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setPickOrigin(int origX, int origY);
  void setCamera(const Camera3D* camera);
  // Set camera to use with this pick operation.

  const Path3D* getPath() const;
  Vector3D getHitPoint() const;
  Real getHitDistance() const;
  // Result accessors.
  //
  // Usage:
  //
  //    Picker3D p;
  //    p.setPickOrigin(30, 30);
  //    p.execute(world);
  //    cerr << p.getHitPoint(); // or getPath(), getHitDistance()
  //

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool doExecute();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  int myOrigX, myOrigY;
  const Camera3D* myCamera;
  Ray3D* myRay;
};

//______________________________________________________________________ INLINES

inline void Picker3D::setPickOrigin(int origX, int origY)
{
  myOrigX = origX;
  myOrigY = origY;
}

inline void Picker3D::setCamera(const Camera3D* camera)
{
  myCamera = camera;
}

inline const Path3D* Picker3D::getPath() const
{
  return myRay->getPath();
}

inline Vector3D Picker3D::getHitPoint() const
{
  return myRay->getHitPoint();
}

inline Real Picker3D::getHitDistance() const
{
  return myRay->getBestHitDistance();
}

#endif // _Picker3D_H


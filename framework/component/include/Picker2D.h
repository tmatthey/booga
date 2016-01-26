/*
 * $RCSfile: Picker2D.h,v $
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
 *  $Id: Picker2D.h,v 1.4 1996/08/01 12:00:26 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Picker2D_H
#define _Picker2D_H

#include "booga/object/Ray2D.h"
#include "booga/component/Operation2D.h"

class Camera2D;

//_____________________________________________________________________ Picker2D

class Picker2D : public Operation2D {
declareRTTI(Picker2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Picker2D();
  // Picker2D(const Picker2D&);             // Use default version.

public:
  // virtual ~Picker2D();                   // Use default version.

public:
  // Picker2D& operator=(const Picker2D&);  // Use default version.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Picker2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setPickOrigin(int origX, int origY);
  void setCamera(const Camera2D* camera);
  // Set camera to use with this pick operation.

  const Path2D* getPath() const;
  Vector2D getHitPoint() const;
  Real getHitDistance() const;
  // Result accessors.
  //
  // Usage:
  //
  //    Picker2D p;
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
  const Camera2D* myCamera;
  Ray2D myRay;
};

//______________________________________________________________________ INLINES

inline void Picker2D::setPickOrigin(int origX, int origY)
{
  myOrigX = origX;
  myOrigY = origY;
}

inline void Picker2D::setCamera(const Camera2D* camera)
{
  myCamera = camera;
}

inline const Path2D* Picker2D::getPath() const
{
  return myRay.getPath();
}

inline Vector2D Picker2D::getHitPoint() const
{
  return myRay.getHitPoint();
}

inline Real Picker2D::getHitDistance() const
{
  return myRay.getBestHitDistance();
}

#endif // _Picker2D_H


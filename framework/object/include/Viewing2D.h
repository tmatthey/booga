/*
 * Viewing2D.h
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
 *  $Id: Viewing2D.h,v 1.6 1996/10/04 09:49:01 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Viewing2D_H
#define _Viewing2D_H

#include <iostream.h>

#include "booga/base/Vector2D.h"
#include "booga/base/TransMatrix2D.h"
#include "booga/object/Ray2D.h"

//____________________________________________________________________ Viewing2D
// 
// The following simple viewing model is used:
//
//   setWindow(origin, resolution)   
//      Specifies the sector of the world to be projected on the screen.
//   
//   setResolution(resX, resY)
//      Specifies the resolution of the screen.
//   
//   transformWorld2Screen(point)
//      Transformation of a point from world to screen coordinates.
//

class Viewing2D {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Viewing2D();
  // Viewing2D(const Viewing2D&);       // Use default version.

public:
  // ~Viewing2D();                      // Use default version.

public:
  // Viewing2D& operator=(Viewing2D&);  // Use default version.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class Viewing2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setWindow(const Vector2D& origin, const Vector2D& size);
  const Vector2D& getWindowOrigin() const;
  const Vector2D& getWindowSize() const;
  
  void setResolution(int resX, int resY);
  int getResolutionX() const;
  int getResolutionY() const;

  Vector2D transformWorld2Screen(const Vector2D& p) const;
  Vector2D transformScreen2World(const Vector2D& p) const;

  void computeRayThrough(int x, int y, Ray2D& ray) const;

  friend ostream& operator<<(ostream& os, const Viewing2D& view);

private:
  void computeConversionFactor();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Vector2D myWindowOrigin, myWindowSize;
  int myResolutionX, myResolutionY;
  
  Vector2D myConversionFactor;
};

//______________________________________________________________________ INLINES

inline const Vector2D& Viewing2D::getWindowOrigin() const
{
  return myWindowOrigin;
}

inline const Vector2D& Viewing2D::getWindowSize() const
{
  return myWindowSize;
}

inline int Viewing2D::getResolutionX() const
{
  return myResolutionX;
}

inline int Viewing2D::getResolutionY() const
{
  return myResolutionY;
}

#endif // _Viewing2D_H

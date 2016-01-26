/*
 * BoundingRect.h
 *
 * Copyright (C) 1994, Stephan Amann <amann@iam.unibe.ch>
 *                     Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: BoundingRect.h,v 1.7 1996/07/05 13:32:39 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _BoundingRect_H
#define _BoundingRect_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/Vector2D.h"

class TransMatrix2D;
class ostream;

//_________________________________________________________________ BoundingRect

class BoundingRect {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  BoundingRect();
  // BoundingRect(const BoundingRect&);             // Use default version.

public:
  // ~BoundingRect();                               // Use default version.
  
public:
  // BoundingRect& operator=(const BoundingRect&);  // Use default version.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class BoundingRect
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void reset();
  // Set bounding rectangle empty.

  void expand(const Vector2D& newPoint);
  void expand(Real x, Real y);
  void expandX(Real x);
  void expandY(Real y);
  void expand(const BoundingRect& b);

  void inflate();
  // Make sure, that bounding rectangle has an extension in all dimensions.

  void transform(const TransMatrix2D& tmat);

  bool inside(const Vector2D& point) const;
  bool inside(Real x, Real y) const;
  
  const Vector2D& getMin() const { return myBRMin; }
  const Vector2D& getMax() const { return myBRMax; }
  Real getMinX() const { return myBRMin.x(); }
  Real getMaxX() const { return myBRMax.x(); }
  Real getMinY() const { return myBRMin.y(); }
  Real getMaxY() const { return myBRMax.y(); }

  bool isEmpty() const;

  friend ostream& operator<<(ostream& os, const BoundingRect& b);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Vector2D myBRMin, myBRMax;  // Opposite vertices of bounding box
  bool myIsEmpty;
};

//______________________________________________________________________ INLINES

inline bool BoundingRect::isEmpty() const
{
  return myIsEmpty;
}

#endif // _BoundingRect_H

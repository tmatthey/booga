/*
 * BoundingBox.h
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
 *  $Id: BoundingBox.h,v 1.7 1996/07/05 13:32:25 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _BoundingBox_H
#define _BoundingBox_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/Vector3D.h"

class TransMatrix3D;
#include  <iostream>

//__________________________________________________________________ BoundingBox

class BoundingBox {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  BoundingBox();
  // BoundingBox(const BoundingBox&);             // Use default version.

public:
  // ~BoundingBox();                              // Use default version.
  
public:
  // BoundingBox& operator=(const BoundingBox&);  // Use default version.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class BoundingBox
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void reset();
  // Set bounding box empty.

  void expand(const Vector3D& newPoint);
  void expand(Real x, Real y, Real z);
  void expandX(Real x);
  void expandY(Real y);
  void expandZ(Real z);
  void expand(const BoundingBox& b);

  void inflate();
  // Make sure, that bounding box has an extension in all dimensions.

  void transform(const TransMatrix3D& tmat);

  bool inside(const Vector3D& point) const;
  bool inside(Real x, Real y, Real z) const;
  
  const Vector3D& getMin() const { return myBBMin; }
  const Vector3D& getMax() const { return myBBMax; }

  bool isEmpty() const;

  friend std::ostream& operator<<(std::ostream& os, const BoundingBox& b);

  friend class BoundsUtilities;
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Vector3D myBBMin, myBBMax;    // Opposite vertices of bounding box.  
  bool myIsEmpty;
};

//______________________________________________________________________ INLINES

inline bool BoundingBox::isEmpty() const
{
  return myIsEmpty;
}

#endif // _BoundingBox_H

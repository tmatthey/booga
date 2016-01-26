/*
 * BoundingBox.C 
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
 *  $Id: BoundingBox.C,v 1.8 1996/07/05 13:32:14 amann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/TransMatrix3D.h"
#include "booga/base/BoundingBox.h"

BoundingBox::BoundingBox() 
: myBBMin(MAXREAL, MAXREAL, MAXREAL), 
  myBBMax(MINREAL, MINREAL, MINREAL),
  myIsEmpty(true)
{}

void BoundingBox::reset()
{
  myBBMin = Vector3D(MAXREAL, MAXREAL, MAXREAL);
  myBBMax = Vector3D(MINREAL, MINREAL, MINREAL);
  myIsEmpty = true;
}

void BoundingBox::expand(const Vector3D& newPoint)
{
  if (newPoint.x() < myBBMin.x()) myBBMin.x() = newPoint.x(); 
  if (newPoint.x() > myBBMax.x()) myBBMax.x() = newPoint.x(); 
  if (newPoint.y() < myBBMin.y()) myBBMin.y() = newPoint.y(); 
  if (newPoint.y() > myBBMax.y()) myBBMax.y() = newPoint.y(); 
  if (newPoint.z() < myBBMin.z()) myBBMin.z() = newPoint.z(); 
  if (newPoint.z() > myBBMax.z()) myBBMax.z() = newPoint.z(); 
  myIsEmpty = false;
}

void BoundingBox::expand(Real x, Real y, Real z)
{
  expandX(x);
  expandY(y);
  expandZ(z);
  myIsEmpty = false;
}

void BoundingBox::expandX(Real x)
{
  if (x < myBBMin.x()) myBBMin.x() = x; 
  if (x > myBBMax.x()) myBBMax.x() = x; 
  myIsEmpty = false;
}

void BoundingBox::expandY(Real y)
{
  if (y < myBBMin.y()) myBBMin.y() = y; 
  if (y > myBBMax.y()) myBBMax.y() = y; 
  myIsEmpty = false;
}

void BoundingBox::expandZ(Real z)
{
  if (z < myBBMin.z()) myBBMin.z() = z; 
  if (z > myBBMax.z()) myBBMax.z() = z; 
  myIsEmpty = false;
}

void BoundingBox::expand(const BoundingBox& b)
{
  if (b.myIsEmpty)
    return;
  
  if (myIsEmpty) {
    myBBMin = b.myBBMin;
    myBBMax = b.myBBMax;
    myIsEmpty = false;
  }
  
  expand(b.myBBMin);
  expand(b.myBBMax);
}

void BoundingBox::inflate()
{
  if (myIsEmpty)
    return;
  // not changeing myIsEmpty, since an empty box will not be inflated
  // and stays empty !

  if (equal(myBBMin.x(), myBBMax.x())) {
    myBBMin.x() -= EPSILON; 
    myBBMax.x() += EPSILON;
  }
  if (equal(myBBMin.y(), myBBMax.y())) {
    myBBMin.y() -= EPSILON; 
    myBBMax.y() += EPSILON;
  }
  if (equal(myBBMin.z(), myBBMax.z())) {
    myBBMin.z() -= EPSILON; 
    myBBMax.z() += EPSILON;
  }
}

void BoundingBox::transform(const TransMatrix3D& tmat)
{
  if (myIsEmpty)
    return;    // No transformation on empty bounding box
    
  BoundingBox tmpBB;

  tmpBB.expand(Vector3D(myBBMin.x(), myBBMin.y(), myBBMin.z())*tmat); // v v v

  tmpBB.expand(Vector3D(myBBMax.x(), myBBMin.y(), myBBMin.z())*tmat); // ^ v v
  tmpBB.expand(Vector3D(myBBMin.x(), myBBMax.y(), myBBMin.z())*tmat); // v ^ v
  tmpBB.expand(Vector3D(myBBMin.x(), myBBMin.y(), myBBMax.z())*tmat); // v v ^

  tmpBB.expand(Vector3D(myBBMax.x(), myBBMax.y(), myBBMin.z())*tmat); // ^ ^ v
  tmpBB.expand(Vector3D(myBBMax.x(), myBBMin.y(), myBBMax.z())*tmat); // ^ v ^
  tmpBB.expand(Vector3D(myBBMin.x(), myBBMax.y(), myBBMax.z())*tmat); // v ^ ^

  tmpBB.expand(Vector3D(myBBMax.x(), myBBMax.y(), myBBMax.z())*tmat); // ^ ^ ^

  myBBMin = tmpBB.myBBMin;
  myBBMax = tmpBB.myBBMax;
}

bool BoundingBox::inside(const Vector3D& point) const
{
  if (myIsEmpty)
    return false;    // nothing inside empty bounding box
    
  return (myBBMin.x() <= point.x() && point.x() <= myBBMax.x() &&
	 myBBMin.y() <= point.y() && point.y() <= myBBMax.y() &&
	 myBBMin.z() <= point.z() && point.z() <= myBBMax.z());
}

bool BoundingBox::inside(Real x, Real y, Real z) const
{
  if (myIsEmpty)
    return false;    // nothing inside empty bounding box
    
  return (myBBMin.x() <= x && x <= myBBMax.x() &&
	 myBBMin.y() <= y && y <= myBBMax.y() &&
	 myBBMin.z() <= z && z <= myBBMax.z());
}

ostream& operator<<(ostream& os, const BoundingBox& b)
{
  if (b.isEmpty())
    return os << "( empty )";
    
  return os << "( min:" << b.myBBMin << ", max:" << b.myBBMax << " )";
}

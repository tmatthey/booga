/*
 * BoundingRect.C
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
 *  $Id: BoundingRect.C,v 1.7 1996/07/05 13:32:33 amann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/TransMatrix2D.h"
#include "booga/base/BoundingRect.h"

BoundingRect::BoundingRect() 
: myBRMin(MAXREAL, MAXREAL), 
  myBRMax(MINREAL, MINREAL),
  myIsEmpty(true)
{}

void BoundingRect::reset()
{
  myBRMin = Vector2D(MAXREAL, MAXREAL);
  myBRMax = Vector2D(MINREAL, MINREAL);
  myIsEmpty = true;
}

void BoundingRect::expand(const Vector2D& newPoint)
{
  expandX(newPoint.x());
  expandY(newPoint.y());
  myIsEmpty = false;
}

void BoundingRect::expand(Real x, Real y)
{
  expandX(x);
  expandY(y);
  myIsEmpty = false;
}

void BoundingRect::expandX(Real x)
{
  if (x < myBRMin.x()) myBRMin.x() = x; 
  if (x > myBRMax.x()) myBRMax.x() = x; 
  myIsEmpty = false;
}

void BoundingRect::expandY(Real y)
{
  if (y < myBRMin.y()) myBRMin.y() = y; 
  if (y > myBRMax.y()) myBRMax.y() = y; 
  myIsEmpty = false;
}

void BoundingRect::expand(const BoundingRect& b)
{
  if (b.myIsEmpty)
    return;
  
  if (myIsEmpty) {
    myBRMin = b.myBRMin;
    myBRMax = b.myBRMax;
    myIsEmpty = false;
  }
  
  expand(b.myBRMin);
  expand(b.myBRMax);
}

void BoundingRect::inflate()
{
  if (myIsEmpty)
    return;
  // not changeing myIsEmpty, since an empty rect will not be inflatet
  // and stays empty !

  if (equal(myBRMin.x(), myBRMax.x())) {
    myBRMin.x() -= EPSILON; 
    myBRMax.x() += EPSILON;
  }
  if (equal(myBRMin.y(), myBRMax.y())) {
    myBRMin.y() -= EPSILON; 
    myBRMax.y() += EPSILON;
  }
}

void BoundingRect::transform(const TransMatrix2D& tmat)
{
  if (myIsEmpty)
    return;    // No transformation on empty bounding box
    
  BoundingRect tmpBR;

  tmpBR.expand(Vector2D(myBRMin.x(), myBRMin.y())*tmat); // v v

  tmpBR.expand(Vector2D(myBRMax.x(), myBRMin.y())*tmat); // ^ v
  tmpBR.expand(Vector2D(myBRMin.x(), myBRMax.y())*tmat); // v ^

  tmpBR.expand(Vector2D(myBRMax.x(), myBRMax.y())*tmat); // ^ ^

  myBRMin = tmpBR.myBRMin;
  myBRMax = tmpBR.myBRMax;
}

bool BoundingRect::inside(const Vector2D& point) const
{
  if (myIsEmpty)
    return false;    // nothing inside empty bounding box
    
  return (myBRMin.x() <= point.x() && point.x() <= myBRMax.x() &&
	 myBRMin.y() <= point.y() && point.y() <= myBRMax.y());
}

bool BoundingRect::inside(Real x, Real y) const
{
  if (myIsEmpty)
    return false;    // nothing inside empty bounding box
    
  return (myBRMin.x() <= x && x <= myBRMax.x() &&
	 myBRMin.y() <= y && y <= myBRMax.y());
}

std::ostream& operator<<(std::ostream& os, const BoundingRect& b)
{
  if (b.isEmpty())
    return os << "( empty )";
    
  return os << "( min:" << b.myBRMin << ", max:" << b.myBRMax << " )";
}

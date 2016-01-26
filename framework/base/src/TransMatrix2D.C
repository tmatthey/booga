/*
 * TransMatrix2D.C
 *
 * Copyright (C) 1995, Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: TransMatrix2D.C,v 1.10 1996/10/04 09:48:50 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include "booga/base/Report.h"
#include "booga/base/TransMatrix2D.h"

//________________________________________________________________ TransMatrix2D

implementInitStatics(TransMatrix2D);
const TransMatrix2D* TransMatrix2D::ourIdentity;

void TransMatrix2D::initClass()
{
  ourIdentity = new TransMatrix2D(1,0, 0,1);
}

TransMatrix2D::TransMatrix2D()
{
  identity();
}

TransMatrix2D::TransMatrix2D(Real x00, Real x01, 
			  Real x10, Real x11, 
			  Real x20, Real x21)
{
  m00 = x00; m01 = x01; 
  m10 = x10; m11 = x11; 
  m20 = x20; m21 = x21; 
}
  
TransMatrix2D::TransMatrix2D(const Vector2D& v1, const Vector2D& v2)
{
  m00 = v1.x(); m01 = v1.y(); 
  m10 = v2.x(); m11 = v2.y(); 
  m20 =         m21 = 0;
}

TransMatrix2D::TransMatrix2D(const Vector2D& v1, const Vector2D& v2, 
			  const Vector2D& v3)
{
  m00 = v1.x(); m01 = v1.y(); 
  m10 = v2.x(); m11 = v2.y(); 
  m20 = v3.x(); m21 = v3.y(); 
}

void TransMatrix2D::identity() 
{
  m00 = 1; m01 = 0; 
  m10 = 0; m11 = 1; 
  m20 = 0; m21 = 0; 
}

bool TransMatrix2D::zero() const
{
  return *this == TransMatrix2D(0,0, 0,0, 0,0);
}

Real TransMatrix2D::operator()(int i, int j) const
{
  if (i == 0) {
    if (j == 0)       return m00;
    else if (j == 1)  return m01;
  }
  else if (i == 1) {
    if (j == 0)       return m10;
    else if (j == 1)  return m11;
  }
  else if (i == 2) {
    if (j == 0)       return m20;
    else if (j == 1)  return m21;
  }

  Report::error("[TransMatrix2D::operator()] index out of range");
  return 0;
}

int TransMatrix2D::operator==(const TransMatrix2D& tm) const
{
  return (equal(m00, tm.m00) && equal(m01, tm.m01) && 
          equal(m10, tm.m10) && equal(m11, tm.m11) && 
	 equal(m20, tm.m20) && equal(m21, tm.m21));
}

int TransMatrix2D::operator!=(const TransMatrix2D& tm) const
{
  return !(*this == tm);
}
 
TransMatrix2D& TransMatrix2D::operator*=(const TransMatrix2D& tm)
{
  TransMatrix2D temp(*this);

  m00 = temp.m00*tm.m00 + temp.m01*tm.m10;
  m01 = temp.m00*tm.m01 + temp.m01*tm.m11;
  
  m10 = temp.m10*tm.m00 + temp.m11*tm.m10;
  m11 = temp.m10*tm.m01 + temp.m11*tm.m11;
  
  m20 = temp.m20*tm.m00 + temp.m21*tm.m10 + tm.m20;
  m21 = temp.m20*tm.m01 + temp.m21*tm.m11 + tm.m21;

  return *this;
}

TransMatrix2D TransMatrix2D::operator*(const TransMatrix2D& tm) const
{
  return TransMatrix2D(m00*tm.m00 +  m01*tm.m10,
		     m00*tm.m01 +  m01*tm.m11,
		       
		     m10*tm.m00 +  m11*tm.m10,
		     m10*tm.m01 +  m11*tm.m11,
		       
		     m20*tm.m00 +  m21*tm.m10 + tm.m20,
		     m20*tm.m01 +  m21*tm.m11 + tm.m21);
}

/*
 * Compute the inverse of a 2D affine matrix; i.e. a matrix with a dimen-
 * sionality of 3 where the right column has entries (0, 0, 1).
 *
 * Returned value:
 *   true   matrix is nonsingular
 *   false  otherwise
 */

bool TransMatrix2D::invert()
{
  TransMatrix2D tmp;
  Real det;

  //
  // Calculate the determinant (optimized version:
  // don't just compute the determinant)
  //
  tmp.m00 = m11;
  tmp.m10 = m10;
  tmp.m20 = m10*m21 - m11*m20;

  tmp.m01 = m01;
  tmp.m11 = m00;
  tmp.m21 = m00*m21 - m01*m20;

  det = m00*tmp.m00 - m01*tmp.m10;

  //
  // singular matrix ?
  //
  if (fabs(det) < EPSILON*EPSILON)
    return false;

  det = 1/det;

  //
  // inverse(A) = adj(A)/det(A)
  //
  tmp.m00 *= det;
  tmp.m11 *= det;
  tmp.m20 *= det;

  det = -det;

  tmp.m01 *= det;
  tmp.m10 *= det;
  tmp.m21 *= det;

  *this = tmp;

  return true;
}

/*
 * Add rotation around 'center' by angle 'angle' to the transformation
 * matrix.
 */

TransMatrix2D& TransMatrix2D::rotate(const Vector2D& center, Real alpha)
{
  return ((*this) *= TransMatrix2D::makeRotate(center, alpha));
}

TransMatrix2D& TransMatrix2D::rotate(const Vector2D& center, Real sinAlpha, Real cosAlpha)
{
  return ((*this) *= TransMatrix2D::makeRotate(center, sinAlpha, cosAlpha));
}

/*
 * Add rotation around origin to the transformation matrix.
 */

TransMatrix2D& TransMatrix2D::rotateOrigin(Real alpha)
{
  Real sinAlpha, cosAlpha;
  sincos(alpha, sinAlpha, cosAlpha);

  return this->rotateOrigin(sinAlpha, cosAlpha);
}

TransMatrix2D& TransMatrix2D::rotateOrigin(Real sinAlpha, Real cosAlpha)
{
  Real x00 = m00, x10=m10, x20=m20;

  m00 = x00*cosAlpha - m01*sinAlpha;
  m01 = x00*sinAlpha + m01*cosAlpha;
  m10 = x10*cosAlpha - m11*sinAlpha;
  m11 = x10*sinAlpha + m11*cosAlpha;
  m20 = x20*cosAlpha - m21*sinAlpha;
  m21 = x20*sinAlpha + m21*cosAlpha;

  return *this;
}

/*
 * Concat translation matrix to the current transformation.
 */
 
TransMatrix2D& TransMatrix2D::translate(Real tx, Real ty)
{  
  m20 += tx; m21 += ty; 
 
  return *this;
}

TransMatrix2D& TransMatrix2D::translate(const Vector2D& trans)
{ 
  m20 += trans.x(); m21 += trans.y(); 

  return *this;
}

/*
 * Concat scale matrix to the current transformation.
 */
 
TransMatrix2D& TransMatrix2D::scale(Real sx, Real sy)
{
  m00 *= sx; m01 *= sy; 
  m10 *= sx; m11 *= sy; 
  m20 *= sx; m21 *= sy; 

  return *this;
}

TransMatrix2D& TransMatrix2D::scale(const Vector2D& scaleFactor)
{
  m00 *= scaleFactor.x(); m01 *= scaleFactor.y(); 
  m10 *= scaleFactor.x(); m11 *= scaleFactor.y(); 
  m20 *= scaleFactor.x(); m21 *= scaleFactor.y(); 

  return *this;
}

/*
 * Static members for the creation of various transformation matrices.
 */
 
TransMatrix2D TransMatrix2D::makeRotate(const Vector2D& center, Real alpha)
{
  Real sinAlpha, cosAlpha;
  sincos(alpha, sinAlpha, cosAlpha);

  return makeRotate(center, sinAlpha, cosAlpha);
}

/*
 * Adapted from Graphics Gems IV
 */
 
TransMatrix2D TransMatrix2D::makeRotate(const Vector2D& center, Real sinAlpha, Real cosAlpha)
{
  return TransMatrix2D( cosAlpha, sinAlpha,
		     -sinAlpha, cosAlpha,
		      center.x()*(1.0-cosAlpha) + center.y()*sinAlpha,
		      center.y()*(1.0-cosAlpha) - center.y()*sinAlpha);
}

TransMatrix2D TransMatrix2D::makeRotateOrigin(Real alpha)
{
  Real sinAlpha, cosAlpha;
  sincos(alpha, sinAlpha, cosAlpha);

  return TransMatrix2D( cosAlpha, sinAlpha,
		     -sinAlpha, cosAlpha);
}

TransMatrix2D TransMatrix2D::makeRotateOrigin(Real sinAlpha, Real cosAlpha)
{
  return TransMatrix2D( cosAlpha, sinAlpha,
		     -sinAlpha, cosAlpha);
}

TransMatrix2D TransMatrix2D::makeTranslate(Real tx, Real ty)
{
  return TransMatrix2D(1,  0,  
		     0,  1,
		     tx, ty);
}

TransMatrix2D TransMatrix2D::makeTranslate(const Vector2D& trans)
{
  return TransMatrix2D(1,  0,
		     0,  1,
		     trans.x(), trans.y());
}

TransMatrix2D TransMatrix2D::makeScale(Real sx, Real sy)
{
  return TransMatrix2D(sx, 0,
		     0,  sy);
}

TransMatrix2D TransMatrix2D::makeScale(const Vector2D& scaleFactor)
{ 
  return TransMatrix2D(scaleFactor.x(), 0,
		     0,  scaleFactor.y());
}

std::ostream& operator<<(std::ostream &os, const TransMatrix2D& tm)
{
  os << "[[" << tm.m00 << ", " << tm.m01 << "], ";
  os <<  "[" << tm.m10 << ", " << tm.m11 << "], ";
  os <<  "[" << tm.m20 << ", " << tm.m21 << "]]";

  return os;
}

Vector2D operator*(const Vector2D& point, const TransMatrix2D& tm)
{
  return Vector2D(tm.m00*point.x() + tm.m10*point.y() + tm.m20,
		tm.m01*point.x() + tm.m11*point.y() + tm.m21);
}


Vector2D transformAsPoint(const Vector2D& point, const TransMatrix2D& tm)
{
  return Vector2D(tm.m00*point.x() + tm.m10*point.y() + tm.m20,
		tm.m01*point.x() + tm.m11*point.y() + tm.m21);
}

/*
 * Apply transformations to a Vector2D (translations have no effect).
 */
 
Vector2D transformAsVector(const Vector2D& vec, const TransMatrix2D& tm)
{
  return Vector2D(tm.m00*vec.x() + tm.m10*vec.y(),
		tm.m01*vec.x() + tm.m11*vec.y());
}

/*
 * Apply transformations to a normal vector: multiply by the 
 * transpose of the given matrix.
 */
/*
!!! Stimmt das ???
Vector2D transformAsNormal(const Vector2D& normal, const TransMatrix2D& tm)
{
  Vector2D n = Vector2D(normal.x()*tm.m00 + normal.y()*tm.m01,
			normal.x()*tm.m10 + normal.y()*tm.m11);

  return n.normalized();
}
*/


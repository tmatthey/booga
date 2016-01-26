/*
 * TransMatrix3D.C
 *
 * Copyright (C) 1995, Christoph Streit <streit@iam.unibe.ch>
 *                     Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: TransMatrix3D.C,v 1.8 1996/10/04 09:48:52 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include <iostream.h>
#include "booga/base/Report.h"
#include "booga/base/TransMatrix3D.h"

//________________________________________________________________ TransMatrix3D

implementInitStatics(TransMatrix3D);

const TransMatrix3D* TransMatrix3D::ourIdentity;

void TransMatrix3D::initClass()
{
  ourIdentity = new TransMatrix3D(1,0,0, 0,1,0, 0,0,1);
}

TransMatrix3D::TransMatrix3D()
{ 
  identity();
}

TransMatrix3D::TransMatrix3D(Real x00, Real x01, Real x02,
		  	  Real x10, Real x11, Real x12,
			  Real x20, Real x21, Real x22,
			  Real x30, Real x31, Real x32)
{
  m00 = x00; m01 = x01; m02 = x02;
  m10 = x10; m11 = x11; m12 = x12;
  m20 = x20; m21 = x21; m22 = x22;
  m30 = x30; m31 = x31; m32 = x32;
}
  
TransMatrix3D::TransMatrix3D(float mat[16])
{
  m00 = *mat++; m01 = *mat++; m02 = *mat++; mat++;
  m10 = *mat++; m11 = *mat++; m12 = *mat++; mat++;
  m20 = *mat++; m21 = *mat++; m22 = *mat++; mat++;
  m30 = *mat++; m31 = *mat++; m32 = *mat++;
}

TransMatrix3D::TransMatrix3D(double mat[16])
{
  m00 = *mat++; m01 = *mat++; m02 = *mat++; mat++;
  m10 = *mat++; m11 = *mat++; m12 = *mat++; mat++;
  m20 = *mat++; m21 = *mat++; m22 = *mat++; mat++;
  m30 = *mat++; m31 = *mat++; m32 = *mat++;
}

TransMatrix3D::TransMatrix3D(const Vector3D& v1, const Vector3D& v2, 
			  const Vector3D& v3)
{
  m00 = v1.x(); m01 = v1.y(); m02 = v1.z();
  m10 = v2.x(); m11 = v2.y(); m12 = v2.z();  
  m20 = v3.x(); m21 = v3.y(); m22 = v3.z();  
  m30 =         m31 =         m32 = 0.;
}

TransMatrix3D::TransMatrix3D(const Vector3D& v1, const Vector3D& v2, 
			  const Vector3D& v3, const Vector3D& v4)
{
  m00 = v1.x(); m01 = v1.y(); m02 = v1.z();
  m10 = v2.x(); m11 = v2.y(); m12 = v2.z();  
  m20 = v3.x(); m21 = v3.y(); m22 = v3.z();  
  m30 = v4.x(); m31 = v4.y(); m32 = v4.z();  
}

void TransMatrix3D::identity() 
{
  m00 = 1; m01 = 0; m02 = 0;
  m10 = 0; m11 = 1; m12 = 0;  
  m20 = 0; m21 = 0; m22 = 1;
  m30 =    m31 =    m32 = 0;
}

bool TransMatrix3D::zero() const
{
  return *this == TransMatrix3D(0,0,0, 0,0,0, 0,0,0);
}

Real TransMatrix3D::operator()(int i, int j) const
{
  if (i == 0) {
    if (j == 0)       return m00;
    else if (j == 1)  return m01;
    else if (j == 2)  return m02;
  }
  else if (i == 1) {
    if (j == 0)       return m10;
    else if (j == 1)  return m11;
    else if (j == 2)  return m12;
  }
  else if (i == 2) {
    if (j == 0)       return m20;
    else if (j == 1)  return m21;
    else if (j == 2)  return m22;
  }
  else if (i == 3) {
    if (j == 0)       return m30;
    else if (j == 1)  return m31;
    else if (j == 2)  return m32;
  }

  Report::error("[TransMatrix3D::operator()] index out of range");
  return 0;
}

int TransMatrix3D::operator==(const TransMatrix3D& tm) const
{
  return (equal(m00, tm.m00) && equal(m01, tm.m01) && equal(m02, tm.m02) &&
          equal(m10, tm.m10) && equal(m11, tm.m11) && equal(m12, tm.m12) &&
	 equal(m20, tm.m20) && equal(m21, tm.m21) && equal(m22, tm.m22) &&
	 equal(m30, tm.m30) && equal(m31, tm.m31) && equal(m32, tm.m32));
}

int TransMatrix3D::operator!=(const TransMatrix3D& tm) const
{
  return !(*this == tm);
}

TransMatrix3D& TransMatrix3D::operator*=(const TransMatrix3D& tm)
{
  TransMatrix3D temp(*this);

  m00 = temp.m00*tm.m00 + temp.m01*tm.m10 + temp.m02*tm.m20;
  m01 = temp.m00*tm.m01 + temp.m01*tm.m11 + temp.m02*tm.m21;
  m02 = temp.m00*tm.m02 + temp.m01*tm.m12 + temp.m02*tm.m22;
  
  m10 = temp.m10*tm.m00 + temp.m11*tm.m10 + temp.m12*tm.m20;
  m11 = temp.m10*tm.m01 + temp.m11*tm.m11 + temp.m12*tm.m21;
  m12 = temp.m10*tm.m02 + temp.m11*tm.m12 + temp.m12*tm.m22;
  
  m20 = temp.m20*tm.m00 + temp.m21*tm.m10 + temp.m22*tm.m20;
  m21 = temp.m20*tm.m01 + temp.m21*tm.m11 + temp.m22*tm.m21;
  m22 = temp.m20*tm.m02 + temp.m21*tm.m12 + temp.m22*tm.m22;
  
  m30 = temp.m30*tm.m00 + temp.m31*tm.m10 + temp.m32*tm.m20 + tm.m30;
  m31 = temp.m30*tm.m01 + temp.m31*tm.m11 + temp.m32*tm.m21 + tm.m31;
  m32 = temp.m30*tm.m02 + temp.m31*tm.m12 + temp.m32*tm.m22 + tm.m32;

  return *this;
}

TransMatrix3D TransMatrix3D::operator*(const TransMatrix3D& tm) const
{
  return TransMatrix3D(m00*tm.m00 +  m01*tm.m10 + m02*tm.m20,
		     m00*tm.m01 +  m01*tm.m11 + m02*tm.m21,
		     m00*tm.m02 +  m01*tm.m12 + m02*tm.m22,
		       
		     m10*tm.m00 +  m11*tm.m10 + m12*tm.m20,
		     m10*tm.m01 +  m11*tm.m11 + m12*tm.m21,
		     m10*tm.m02 +  m11*tm.m12 + m12*tm.m22,
		       
		     m20*tm.m00 +  m21*tm.m10 + m22*tm.m20,
		     m20*tm.m01 +  m21*tm.m11 + m22*tm.m21,
		     m20*tm.m02 +  m21*tm.m12 + m22*tm.m22,
		       
		     m30*tm.m00 +  m31*tm.m10 + m32*tm.m20 + tm.m30,
		     m30*tm.m01 +  m31*tm.m11 + m32*tm.m21 + tm.m31,
		     m30*tm.m02 +  m31*tm.m12 + m32*tm.m22 + tm.m32);
}

/*
   The matrix of cofactors of A is defined as follows:

                                  i+j 
   Entry ij of this matrix is (-1)    times the determinant of the matrix resulting
   from deleting row i and column j from A.

   This matrix can be used instead of the inverse matrix to transform normal vectors.
   (see Foley, van Dam, Feiner, Hughes; "Computer Graphics"; p. 1108)
   The resulting normal vectors have to be normalized.

   By deleting one row and one column of a homogenous transformation matrix A
   exactly two possible types of submatrices exist:

   ( a b 0 )     ( a b 0 )
   ( c d 0 ) and ( c d 0 ),
   ( e f 0 )     ( e f 1 )
   
   The determinants of these two matrices are 0 and (ad-cb), respectively.

   The last column of this matrix of cofactors should be (from top to bottom):

	    | ( m21 m22 m23 ) |
	    | ( m31 m32 m33 ) | = m21*m32*m43 - m21*m33*m42 - m31*m22*m43 +
	    | ( m41 m42 m43 ) |   m31*m23*m42 + m41*m22*m33 - m41*m23*m32
	    
	    | ( m11 m12 m13 ) |
	    | ( m31 m32 m33 ) | = m11*m32*m43 - m11*m33*m42 - m31*m12*m43 +
	    | ( m41 m42 m43 ) |   m31*m13*m42 + m41*m12*m33 - m41*m13*m32
	    
	    | ( m11 m12 m13 ) |
	    | ( m21 m22 m23 ) | = m11*m22*m43 - m11*m23*m42 - m21*m12*m43 +
	    | ( m41 m42 m43 ) |   m21*m13*m42 + m41*m12*m23 - m41*m13*m22
	    
            | ( m11 m12 m13 ) |
	    | ( m21 m22 m23 ) | = m11*m22*m33 - m11*m23*m32 - m21*m12*m33 +
	    | ( m31 m32 m33 ) |   m21*m13*m32 + m31*m12*m23 - m31*m13*m22 
   

 */

void TransMatrix3D::cofactors()
{
  *this = TransMatrix3D(  m11*m22 - m21*m12,
		      -(m10*m22 - m20*m12),
			m10*m21 - m20*m11,
			  
		      -(m01*m22 - m21*m02),
			m00*m22 - m20*m02,
		      -(m00*m21 - m20*m01),
			  
			m01*m12 - m11*m02,
		      -(m00*m12 - m10*m02),
			m00*m11 - m10*m01,
			  
		      0, 0, 0);
}

/*
 * Compute the inverse of a 3D affine matrix; i.e. a matrix with a dimen-
 * sionality of 4 where the right column has entries (0, 0, 0, 1).
 *
 * This procedures treats the 4 by 4 matrix as ablock matrix and calculates
 * the inverse of one submatrix for a significant performance improvement
 * over a general procedure that can invert any nonsingular matrix:
 *        --      --       --         --
 *        |        | -1    |   -1      |
 *        | A    0 |       |  A      0 |
 *   -1   |        |       |           |
 *  M   = |        |    =  |     -1    |
 *        | C    1 |       | -C A    1 |
 *        |        |       |           |
 *        --      --       --         --
 * 
 * where  M is a 4 by 4 matrix,
 *        A is the 3 by 3 upper left submatrix of M,
 *        C is the 1 by 3 lower left subnatrix of M.
 *
 * Returned value:
 *   true   matrix is nonsingular
 *   false  otherwise
 *
 * Reference: GraphicsGems I and Craig Kolbs rayshade.
 */

bool TransMatrix3D::invert()
{
  TransMatrix3D tmp;
  Real det;

  //
  // Calculate the determinant of submatrix A (optimized version:
  // don,t just compute the determinant of A)
  //
  tmp.m00 = m11*m22 - m12*m21;
  tmp.m10 = m10*m22 - m12*m20;
  tmp.m20 = m10*m21 - m11*m20;

  tmp.m01 = m01*m22 - m02*m21;
  tmp.m11 = m00*m22 - m02*m20;
  tmp.m21 = m00*m21 - m01*m20;

  tmp.m02 = m01*m12 - m02*m11;
  tmp.m12 = m00*m12 - m02*m10;
  tmp.m22 = m00*m11 - m01*m10;

  det = m00*tmp.m00 - m01*tmp.m10 + m02*tmp.m20;

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
  tmp.m02 *= det;
  tmp.m11 *= det;
  tmp.m20 *= det;
  tmp.m22 *= det;

  det = -det;

  tmp.m01 *= det;
  tmp.m10 *= det;
  tmp.m12 *= det;
  tmp.m21 *= det;

  tmp.m30 = -(tmp.m00*m30 + tmp.m10*m31 + tmp.m20*m32);
  tmp.m31 = -(tmp.m01*m30 + tmp.m11*m31 + tmp.m21*m32);
  tmp.m32 = -(tmp.m02*m30 + tmp.m12*m31 + tmp.m22*m32);
  
  *this = tmp;

  return true;
}

/*
 * Add rotation around 'axis' by angle 'angle' to the transformation
 * matrix.
 */

void TransMatrix3D::rotate(const Vector3D& axis, Real alpha)
{
  (*this) *= TransMatrix3D::makeRotate(axis, alpha);
}

void TransMatrix3D::rotate(const Vector3D& axis, Real sinAlpha, Real cosAlpha)
{
  (*this) *= TransMatrix3D::makeRotate(axis, sinAlpha, cosAlpha);
}

/*
 * Add rotation around x-axis to the transformation matrix.
 */

void TransMatrix3D::rotateX(Real alpha)
{
  Real sinAlpha, cosAlpha;
  sincos(alpha, sinAlpha, cosAlpha);

  this->rotateX(sinAlpha, cosAlpha);
}

void TransMatrix3D::rotateX(Real sinAlpha, Real cosAlpha)
{
  Real x01 = m01, x11 = m11, x21 = m21, x31 = m31; 

  m01 = x01*cosAlpha - m02*sinAlpha; 
  m02 = x01*sinAlpha + m02*cosAlpha;
  m11 = x11*cosAlpha - m12*sinAlpha; 
  m12 = x11*sinAlpha + m12*cosAlpha;
  m21 = x21*cosAlpha - m22*sinAlpha; 
  m22 = x21*sinAlpha + m22*cosAlpha;
  m31 = x31*cosAlpha - m32*sinAlpha; 
  m32 = x31*sinAlpha + m32*cosAlpha;
}

/*
 * Add rotation around y-axis to the transformation matrix.
 */

void TransMatrix3D::rotateY(Real alpha)
{
  Real sinAlpha, cosAlpha;
  sincos(alpha, sinAlpha, cosAlpha);

  this->rotateY(sinAlpha, cosAlpha);
}

void TransMatrix3D::rotateY(Real sinAlpha, Real cosAlpha)
{
  Real x00 = m00, x10 = m10, x20 = m20, x30 = m30; 

  m00 = x00*cosAlpha - m02*sinAlpha; 
  m02 = x00*sinAlpha + m02*cosAlpha;
  m10 = x10*cosAlpha - m12*sinAlpha; 
  m12 = x10*sinAlpha + m12*cosAlpha;
  m20 = x20*cosAlpha - m22*sinAlpha; 
  m22 = x20*sinAlpha + m22*cosAlpha;
  m30 = x30*cosAlpha - m32*sinAlpha; 
  m32 = x30*sinAlpha + m32*cosAlpha;
}

/*
 * Add rotation around z-axis to the transformation matrix.
 */

void TransMatrix3D::rotateZ(Real alpha)
{
  Real sinAlpha, cosAlpha;
  sincos(alpha, sinAlpha, cosAlpha);

  this->rotateZ(sinAlpha, cosAlpha);
}

void TransMatrix3D::rotateZ(Real sinAlpha, Real cosAlpha)
{
  Real x00 = m00, x10 = m10, x20 = m20, x30 = m30; 
  
  m00 = x00*cosAlpha - m01*sinAlpha; 
  m01 = x00*sinAlpha + m01*cosAlpha;
  m10 = x10*cosAlpha - m11*sinAlpha; 
  m11 = x10*sinAlpha + m11*cosAlpha;
  m20 = x20*cosAlpha - m21*sinAlpha; 
  m21 = x20*sinAlpha + m21*cosAlpha;
  m30 = x30*cosAlpha - m31*sinAlpha; 
  m31 = x30*sinAlpha + m31*cosAlpha;
}

/*
 * Concat translation matrix to the current transformation.
 */
 
void TransMatrix3D::translate(Real tx, Real ty, Real tz)
{  
  m30 += tx; m31 += ty; m32 += tz;     
}

void TransMatrix3D::translate(const Vector3D& trans)
{ 
  m30 += trans.x(); m31 += trans.y(); m32 += trans.z();     
}


/*
 * Concat scale matrix to the current transformation.
 */

void TransMatrix3D::scale(Real sx, Real sy, Real sz)
{
  m00 *= sx; m01 *= sy; m02 *= sz;
  m10 *= sx; m11 *= sy; m12 *= sz;
  m20 *= sx; m21 *= sy; m22 *= sz;
  m30 *= sx; m31 *= sy; m32 *= sz;
}

void TransMatrix3D::scale(const Vector3D& scaleFactor)
{
  m00 *= scaleFactor.x(); m01 *= scaleFactor.y(); m02 *= scaleFactor.z();
  m10 *= scaleFactor.x(); m11 *= scaleFactor.y(); m12 *= scaleFactor.z();
  m20 *= scaleFactor.x(); m21 *= scaleFactor.y(); m22 *= scaleFactor.z();
  m30 *= scaleFactor.x(); m31 *= scaleFactor.y(); m32 *= scaleFactor.z();
}

/* ------------------------------------------------------------------
 * Static members for the creation of various transformation matrices.
 */

TransMatrix3D TransMatrix3D::makeRotate(const Vector3D& axis, Real alpha)
{
  Real sinAlpha, cosAlpha;
  sincos(alpha, sinAlpha, cosAlpha);

  return makeRotate(axis, sinAlpha, cosAlpha);
}

/*
 * Adapted from Craig Kolbs rayshade.
 */

TransMatrix3D TransMatrix3D::makeRotate(const Vector3D& axis, 
				    Real sinAlpha, Real cosAlpha)
{
  Real n1, n2, n3;

  //
  // Check if axis == Vector3D(0,0,0) is performed within Vector3D::normalized()
  //
  Vector3D n(axis.normalized());

  n1 = n.x(); n2 = n.y(); n3 = n.z();

  return TransMatrix3D(n1*n1 + (1. - n1*n1)*cosAlpha, 
		       n1*n2*(1. - cosAlpha) + n3*sinAlpha, 
		       n1*n3*(1. - cosAlpha) - n2*sinAlpha,
		       
		       n1*n2*(1. - cosAlpha) - n3*sinAlpha,
		       n2*n2 + (1. - n2*n2)*cosAlpha,
		       n2*n3*(1. - cosAlpha) + n1*sinAlpha,
		       
		       n1*n3*(1. - cosAlpha) + n2*sinAlpha,
		       n2*n3*(1. - cosAlpha) - n1*sinAlpha,
		       n3*n3 + (1. - n3*n3)*cosAlpha,
		       
		       0 ,0 ,0);
}

/*
 *          [ 1     0       0     0 ]
 * Rx(a) =  [ 0   cos(a)  sin(a)  0 ]
 *          [ 0  -sin(a)  cos(a)  0 ]
 *          [ 0     0       0     1 ]
 */

TransMatrix3D TransMatrix3D::makeRotateX(Real alpha)
{
  Real sinAlpha, cosAlpha;
  sincos(alpha, sinAlpha, cosAlpha);

  return TransMatrix3D(1,     0,        0,
		       0,  cosAlpha, sinAlpha,
		       0, -sinAlpha, cosAlpha,
		       0,     0,        0);
}

TransMatrix3D TransMatrix3D::makeRotateX(Real sinAlpha, Real cosAlpha)
{
  return TransMatrix3D(1,     0,        0,
		       0,  cosAlpha, sinAlpha,
		       0, -sinAlpha, cosAlpha,
		       0,     0,        0);
}

/*
 *          [ cos(a)   0  sin(a)  0 ]
 * Ry(a) =  [   0      1    0     0 ]
 *          [ -sin(a)  0  cos(a)  0 ]
 *          [   0      0    0     1 ]
 */

TransMatrix3D TransMatrix3D::makeRotateY(Real alpha)
{
  Real sinAlpha, cosAlpha;
  sincos(alpha, sinAlpha, cosAlpha);

  return TransMatrix3D( cosAlpha, 0, sinAlpha,
			0,     1,    0,
			-sinAlpha, 0, cosAlpha,
			0,     0,    0);
}

TransMatrix3D TransMatrix3D::makeRotateY(Real sinAlpha, Real cosAlpha)
{
  return TransMatrix3D( cosAlpha, 0, sinAlpha,
			0,     1,    0,
			-sinAlpha, 0, cosAlpha,
			0,     0,    0);
}

/*
 *          [  cos(a)  sin(a)   0    0 ]
 * Rz(a) =  [ -sin(a)  cos(a)   0    0 ]
 *          [    0       0      1    0 ]
 *          [    0       0      0    1 ]
 */

TransMatrix3D TransMatrix3D::makeRotateZ(Real alpha)
{
  Real sinAlpha, cosAlpha;
  sincos(alpha, sinAlpha, cosAlpha);

  return TransMatrix3D( cosAlpha,  sinAlpha, 0,
			-sinAlpha,  cosAlpha, 0,
			0,         0,     1,
			0,         0,     0);
}

TransMatrix3D TransMatrix3D::makeRotateZ(Real sinAlpha, Real cosAlpha)
{
  return TransMatrix3D( cosAlpha,  sinAlpha, 0,
			-sinAlpha,  cosAlpha, 0,
			0,         0,     1,
			0,         0,     0);
}


TransMatrix3D TransMatrix3D::makeTranslate(Real tx, Real ty, Real tz)
{
  return TransMatrix3D(1,  0,  0,
		       0,  1,  0,
		       0,  0,  1,
		       tx, ty, tz);
}

TransMatrix3D TransMatrix3D::makeTranslate(const Vector3D& trans)
{
  return TransMatrix3D(1,  0,  0,
		       0,  1,  0,
		       0,  0,  1,
		       trans.x(), trans.y(), trans.z());
}

TransMatrix3D TransMatrix3D::makeScale(Real sx, Real sy, Real sz)
{
  return TransMatrix3D(sx, 0,  0,
		       0,  sy, 0,
		       0,  0,  sz,
		       0,  0,  0);
}

TransMatrix3D TransMatrix3D::makeScale(const Vector3D& scaleFactor)
{ 
  return TransMatrix3D(scaleFactor.x(), 0,  0,
		       0,  scaleFactor.y(), 0,
		       0,  0,  scaleFactor.z(),
		       0,  0,  0);
}


//______________________________________________________________________ friends

ostream& operator<<(ostream &os, const TransMatrix3D& tm)
{
  os << "[[" << tm.m00 << ", " << tm.m01 << ", " <<tm.m02 << "], ";
  os <<  "[" << tm.m10 << ", " << tm.m11 << ", " <<tm.m12 << "], ";
  os <<  "[" << tm.m20 << ", " << tm.m21 << ", " <<tm.m22 << "], ";
  os <<  "[" << tm.m30 << ", " << tm.m31 << ", " <<tm.m32 << "]]";

  return os;
}

Vector3D operator*(const Vector3D& point, const TransMatrix3D& tm)
{
  return Vector3D(tm.m00*point.x() + tm.m10*point.y() + tm.m20*point.z() + tm.m30,
		tm.m01*point.x() + tm.m11*point.y() + tm.m21*point.z() + tm.m31,
		tm.m02*point.x() + tm.m12*point.y() + tm.m22*point.z() + tm.m32);
}

Vector3D transformAsPoint(const Vector3D& point, const TransMatrix3D& tm)
{
  return Vector3D(tm.m00*point.x() + tm.m10*point.y() + tm.m20*point.z() + tm.m30,
		tm.m01*point.x() + tm.m11*point.y() + tm.m21*point.z() + tm.m31,
		tm.m02*point.x() + tm.m12*point.y() + tm.m22*point.z() + tm.m32);
}

/*
 * Apply transformations to a Vector3D (translations have no effect).
 */
Vector3D transformAsVector(const Vector3D& vec, const TransMatrix3D& tm)
{
  return Vector3D(tm.m00*vec.x() + tm.m10*vec.y() + tm.m20*vec.z(),
		tm.m01*vec.x() + tm.m11*vec.y() + tm.m21*vec.z(),
		tm.m02*vec.x() + tm.m12*vec.y() + tm.m22*vec.z());
}

/*
 * Apply transformations to a normal vector: multiply by the 
 * transpose of the given matrix.
 */
Vector3D transformAsNormal(const Vector3D& normal, const TransMatrix3D& tm)
{
  Vector3D n = Vector3D(normal.x()*tm.m00 + normal.y()*tm.m01 + normal.z()*tm.m02,
			normal.x()*tm.m10 + normal.y()*tm.m11 + normal.z()*tm.m12,
			normal.x()*tm.m20 + normal.y()*tm.m21 + normal.z()*tm.m22);

  return n.normalized();
}

void convert(const TransMatrix3D& from, float to[16])
{
  to[0]  = from.m00; to[1]  = from.m01; to[2]  = from.m02; to[3]  = 0; 
  to[4]  = from.m10; to[5]  = from.m11; to[6]  = from.m12; to[7]  = 0; 
  to[8]  = from.m20; to[9]  = from.m21; to[10] = from.m22; to[11] = 0; 
  to[12] = from.m30; to[13] = from.m31; to[14] = from.m32; to[15] = 1; 
}

void convert(const TransMatrix3D& from, double to[16])
{
  to[0]  = from.m00; to[1]  = from.m01; to[2]  = from.m02; to[3]  = 0; 
  to[4]  = from.m10; to[5]  = from.m11; to[6]  = from.m12; to[7]  = 0; 
  to[8]  = from.m20; to[9]  = from.m21; to[10] = from.m22; to[11] = 0; 
  to[12] = from.m30; to[13] = from.m31; to[14] = from.m32; to[15] = 1; 
}


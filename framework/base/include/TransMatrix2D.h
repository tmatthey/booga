/*
 * TransMatrix2D.h
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
 *  $Id: TransMatrix2D.h,v 1.10 1996/10/04 09:48:51 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _TransMatrix2D_H
# define _TransMatrix2D_H

#include "booga/base/StaticInit.h"
#include "booga/base/PrimitiveTypes.h"
#include "booga/base/mathutilities.h"
#include "booga/base/Vector2D.h"

class ostream;

/*________________________________________________________________ TransMatrix2D
 *
 *  [ m00 m01 0 ]   
 *  [ m10 m11 0 ]   representation of a 
 *  [ m20 m21 1 ]   transformation matrix
 */

class TransMatrix2D {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  TransMatrix2D();
  // TransMatrix2D(const TransMatrix2D&);  // Use default verions.
  TransMatrix2D(Real x00,   Real x01, 
	       Real x10,   Real x11,   
	       Real x20=0, Real x21=0);
  TransMatrix2D(const Vector2D& v1, const Vector2D& v2);
  TransMatrix2D(const Vector2D& v1, const Vector2D& v2, const Vector2D& v3);
  
public:
  // TransMatrix2D& operator=(const TransMatrix2D&);  // Use default version.

public:
  // ~TransMatrix2D();  // Use default version.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class TransMatrix2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  static void initClass();

public:
  static const TransMatrix2D& getIdentity();  // Return the identity matrix.
  void identity();   // Set 'this' to the identity matrix.
  bool zero() const; // Check if all elements equals zero.
  
  Real operator()(int i, int j) const;
  // Extract an element.

  int operator==(const TransMatrix2D& tm) const;
  int operator!=(const TransMatrix2D& tm) const;
 
  TransMatrix2D& operator*=(const TransMatrix2D& tm);
  TransMatrix2D operator*(const TransMatrix2D& tm) const;  
  // Matrix multiplication.

  bool invert();  // Compute the inverse of the given matrix.

  TransMatrix2D& rotate(const Vector2D& center, Real alpha);
  TransMatrix2D& rotate(const Vector2D& center, Real sinAlpha, Real cosAlpha);
  // Add rotation around 'center' by angle 'angle' to the transformation
  // matrix.

  TransMatrix2D& rotateOrigin(Real alpha);
  TransMatrix2D& rotateOrigin(Real sinAlpha, Real cosAlpha);
  // Add rotation around the Origin to the transformation 
  // matrix.

  TransMatrix2D& translate(Real tx, Real ty);
  TransMatrix2D& translate(const Vector2D& trans);
  // Concat translation matrix to the current transformation.

  TransMatrix2D& scale(Real sx, Real sy);
  TransMatrix2D& scale(const Vector2D& scaleFactor);
  // Concat scale matrix to the current transformation.
  
public:
  static TransMatrix2D makeRotate(const Vector2D& center, Real alpha);
  static TransMatrix2D makeRotate(const Vector2D& center, Real sinAlpha, Real cosAlpha);
  static TransMatrix2D makeRotateOrigin(Real alpha);
  static TransMatrix2D makeRotateOrigin(Real sinAlpha, Real cosAlpha);

  static TransMatrix2D makeTranslate(Real tx, Real ty);
  static TransMatrix2D makeTranslate(const Vector2D& trans);

  static TransMatrix2D makeScale(Real sx, Real sy);
  static TransMatrix2D makeScale(const Vector2D& scaleFactor);
  // Static members for the creation of various transformation 
  // matrices.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Friends of class TransMatrix3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  friend ostream& operator<<(ostream& os, const TransMatrix2D& tm);

  friend Vector2D operator*(const Vector2D& point, const TransMatrix2D& tm);
  friend Vector2D transformAsPoint(const Vector2D& point, const TransMatrix2D& tm);
  friend Vector2D transformAsVector(const Vector2D& vec, const TransMatrix2D& tm);
  // Transformation of points and vectors. 

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Real m00, m01;
  Real m10, m11;
  Real m20, m21;

private:
  static const TransMatrix2D* ourIdentity;
};

declareInitStatics(TransMatrix2D);

//______________________________________________________________________ INLINES

inline const TransMatrix2D& TransMatrix2D::getIdentity()
{
  return *ourIdentity;
}

#endif // _TransMatrix2D_H

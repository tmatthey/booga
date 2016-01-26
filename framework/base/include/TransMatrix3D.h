/*
 * TransMatrix3D.h 
 *
 * General 4x3 transformation matrices.
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
 *  $Id: TransMatrix3D.h,v 1.8 1995/09/28 13:09:56 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _TransMatrix3D_H
# define _TransMatrix3D_H

#include "booga/base/StaticInit.h"
#include "booga/base/PrimitiveTypes.h"
#include "booga/base/mathutilities.h"
#include "booga/base/Vector3D.h"

#include <ostream>

/*________________________________________________________________ TransMatrix3D
 *
 *  [ m00 m01 m02 0 ]   
 *  [ m10 m11 m12 0 ]   representation of a 
 *  [ m20 m21 m22 0 ]   transformation matrix
 *  [ m30 m31 m32 1 ]
 */

class TransMatrix3D {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  TransMatrix3D();
  // TransMatrix3D(const TransMatrix3D&);  // Use default verions.
  TransMatrix3D(Real x00,   Real x01,   Real x02,
	       Real x10,   Real x11,   Real x12,
	       Real x20,   Real x21,   Real x22,
	       Real x30=0, Real x31=0, Real x32=0);
  TransMatrix3D(float mat[16]);
  TransMatrix3D(double mat[16]);
  TransMatrix3D(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3);
  TransMatrix3D(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3, 
	       const Vector3D& v4);

public:
  // TransMatrix3D& operator=(const TransMatrix3D&);  // Use default version.

public:
  // ~TransMatrix3D();  // Use default version.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class TransMatrix3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  static void initClass();

public:
  static const TransMatrix3D& getIdentity();  // Return the identity matrix.
  void identity();  // Set 'this' to the identity matrix.
  bool zero() const; // Check if all elements equals zero.

  Real operator()(int i, int j) const;
  // Extract an element.
  
  int operator==(const TransMatrix3D& tm) const;
  int operator!=(const TransMatrix3D& tm) const;
 
  TransMatrix3D& operator*=(const TransMatrix3D& tm);
  TransMatrix3D operator*(const TransMatrix3D& tm) const;  
  // Matrix multiplication.

  void cofactors();  // Compute the cofactor matrix of the given matrix.
  bool invert();      
  // Compute the inverse of the given matrix. 
  // Returns: false -> singular matrix
  //          true  -> success.

  void rotate(const Vector3D& axis, Real alpha);
  void rotate(const Vector3D& axis, Real sinAlpha, Real cosAlpha);
  // Add rotation around 'axis' by angle 'angle' to the transformation
  // matrix.

  void rotateX(Real alpha);
  void rotateX(Real sinAlpha, Real cosAlpha);
  void rotateY(Real alpha);
  void rotateY(Real sinAlpha, Real cosAlpha);
  void rotateZ(Real alpha);
  void rotateZ(Real sinAlpha, Real cosAlpha);
  // Add rotation around the X, Y or Z axis to the transformation 
  // matrix.

  void translate(Real tx, Real ty, Real tz);
  void translate(const Vector3D& trans);
  // Concat translation matrix to the current transformation.

  void scale(Real sx, Real sy, Real sz);
  void scale(const Vector3D& scaleFactor);
  // Concat scale matrix to the current transformation.
  
public:
  static TransMatrix3D makeRotate(const Vector3D& axis, Real alpha);
  static TransMatrix3D makeRotate(const Vector3D& axis, Real sinAlpha, Real cosAlpha);
  static TransMatrix3D makeRotateX(Real alpha);
  static TransMatrix3D makeRotateX(Real sinAlpha, Real cosAlpha);
  static TransMatrix3D makeRotateY(Real alpha);
  static TransMatrix3D makeRotateY(Real sinAlpha, Real cosAlpha);
  static TransMatrix3D makeRotateZ(Real alpha);
  static TransMatrix3D makeRotateZ(Real sinAlpha, Real cosAlpha);

  static TransMatrix3D makeTranslate(Real tx, Real ty, Real tz);
  static TransMatrix3D makeTranslate(const Vector3D& trans);

  static TransMatrix3D makeScale(Real sx, Real sy, Real sz);
  static TransMatrix3D makeScale(const Vector3D& scaleFactor);
  // Static members for the creation of various transformation 
  // matrices.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Friends of class TransMatrix3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  friend std::ostream& operator<<(std::ostream& os, const TransMatrix3D& tm);

  friend Vector3D operator*(const Vector3D& point, const TransMatrix3D& tm);
  friend Vector3D transformAsPoint(const Vector3D& point, const TransMatrix3D& tm);
  friend Vector3D transformAsVector(const Vector3D& vec, const TransMatrix3D& tm);
  friend Vector3D transformAsNormal(const Vector3D& normal, const TransMatrix3D& tm);
  // Transformation of points, vectors and normal vectors.
  
  friend void convert(const TransMatrix3D& from, float to[16]);
  friend void convert(const TransMatrix3D& from, double to[16]);
  // Conversion to built-in types.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Real m00, m01, m02;
  Real m10, m11, m12;
  Real m20, m21, m22;
  Real m30, m31, m32;

private:
  static const TransMatrix3D* ourIdentity;
};

declareInitStatics(TransMatrix3D);

//______________________________________________________________________ INLINES

inline const TransMatrix3D& TransMatrix3D::getIdentity()
{
  return *ourIdentity;
}

#endif // _TransMatrix3D_H

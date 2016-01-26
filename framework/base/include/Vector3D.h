/*
 * Vector3D.h 
 *
 * 3D Vector class.
 *
 * Copyright (C) 1994, Christoph Streit <streit@iam.unibe.ch>
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
 * ----------------------------------------------------------------------
 *  $Id: Vector3D.h,v 1.2 1995/04/21 12:37:12 amann Exp $
 * ----------------------------------------------------------------------
 */

#ifndef Vector3D_H
# define Vector3D_H

#include "booga/base/mathutilities.h"
#include "booga/base/Report.h"

class ostream;
class istream;

//_________________________________________________________________ Vector3D

class Vector3D {
public:
  Vector3D();
  Vector3D(Real x, Real y, Real z); 
  Vector3D(const Vector3D& vec);

  Real& operator[](int index);
  Real  operator[](int index) const;
  Real& x();
  Real  x() const;
  Real& y();
  Real  y() const;
  Real& z();
  Real  z() const;

  Vector3D& operator=(const Vector3D& vec);
  Vector3D& operator+=(const Vector3D& vec);
  Vector3D& operator-=(const Vector3D& vec); 
  Vector3D& operator*=(const Vector3D& vec); 
  Vector3D& operator*=(Real scale); 
  Vector3D& operator/=(Real scale); 

  int operator==(const Vector3D& vec) const;
  int operator!=(const Vector3D& vec) const;
  int equal(const Vector3D& vec, Real epsilon = EPSILON) const;

  Real sqr() const;                       // squared length of Vector3D
  Real length() const;                    // length of Vector3D
  int  zero() const;
  Real distance(const Vector3D& vec) const; // distance between two points
  Real   normalize();                     // normalize Vector3D
  Vector3D normalized() const;              // generate normalized Vector3D

  Vector3D operator-() const;                   // unary negation
  Vector3D operator+(const Vector3D& vec) const;  // Vector3D addition
  Vector3D operator-(const Vector3D& vec) const;  // Vector3D subtraction

  Vector3D cross(const Vector3D& vec) const;
  Vector3D operator*(const Vector3D& vec) const;  // Vector3D cross product

  Real dot(const Vector3D& vec) const; 
  Real operator^(const Vector3D& vec) const;    // Vector3D dot product

  Vector3D operator/(Real scale) const;         // scalar divison

  friend Vector3D operator*(Real scale, const Vector3D& vec); 
  friend Vector3D operator*(const Vector3D& vec, Real scale); 
  // scalar multiply

  friend ostream& operator<<(ostream& os, const Vector3D& vec);
  friend istream& operator>>(istream& is, Vector3D& vec);

private:
  Real myVec[3];
};

inline Real& Vector3D::operator[](int index)
{ 
  if (index<0 || index>2)
    Report::error("[Vector3D::operator[] ] index out of range");

  return myVec[index]; 
}

inline Real Vector3D::operator[](int index) const 
{ 
  if (index<0 || index>2)
    Report::error("[Vector3D::operator[] const] index out of range");

  return myVec[index]; 
}

inline Real& Vector3D::x()
{
  return myVec[0];
}

inline Real Vector3D::x() const
{
  return myVec[0];
}

inline Real& Vector3D::y()
{
  return myVec[1];
}

inline Real Vector3D::y() const
{
  return myVec[1];
}

inline Real& Vector3D::z()
{
  return myVec[2];
}

inline Real Vector3D::z() const
{
  return myVec[2];
}

#endif // Vector3D_H


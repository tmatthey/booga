/*
 * Vector2D.h
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
 *  $Id: Vector2D.h,v 1.4 1995/08/14 11:22:19 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Vector2D_H
#define _Vector2D_H

#include "booga/base/mathutilities.h"
#include "booga/base/Report.h"

#include <ostream>
#include <istream>

//_________________________________________________________________ Vector3D

class Vector2D {
public:
  Vector2D();
  Vector2D(Real x, Real y); 
  Vector2D(const Vector2D& vec);

  Real& operator[](int index);
  Real  operator[](int index) const;
  Real& x();
  Real  x() const;
  Real& y();
  Real  y() const;

  Vector2D& operator=(const Vector2D& vec);
  Vector2D& operator+=(const Vector2D& vec);
  Vector2D& operator-=(const Vector2D& vec); 
  Vector2D& operator*=(Real scale); 
  Vector2D& operator/=(Real scale); 

  int operator==(const Vector2D& vec) const;
  int operator!=(const Vector2D& vec) const;
  int equal(const Vector2D& vec, Real epsilon = EPSILON) const;

  Real sqr() const;                       // squared length of Vector2D
  Real length() const;                    // length of Vector2D
  int  zero() const;
  Real distance(const Vector2D& vec) const; // distance between two points
  Real   normalize();                     // normalize Vector2D
  Vector2D normalized() const;              // generate normalized Vector2D

  Vector2D operator-() const;                   // unary negation
  Vector2D operator+(const Vector2D& vec) const;  // Vector2D addition
  Vector2D operator-(const Vector2D& vec) const;  // Vector2D subtraction

  Real dot(const Vector2D& vec) const; 
  Real operator^(const Vector2D& vec) const;    // Vector2D dot product

  Vector2D operator/(Real scale) const;         // scalar divison

  friend Vector2D operator*(Real scale, const Vector2D& vec); 
  friend Vector2D operator*(const Vector2D& vec, Real scale); 
  // scalar multiply

  friend std::ostream& operator<<(std::ostream& os, const Vector2D& vec);
  friend std::istream& operator>>(std::istream& is, Vector2D& vec);

private:
  Real myVec[2];
};

inline Real& Vector2D::operator[](int index)
{ 
  if (index!=0 && index!=1)
    Report::error("[Vector2D::operator[] ] index out of range");

  return myVec[index]; 
}

inline Real Vector2D::operator[](int index) const 
{ 
  if (index!=0 && index!=1)
    Report::error("[Vector2D::operator[] const] index out of range");

  return myVec[index]; 
}

inline Real& Vector2D::x()
{
  return myVec[0];
}

inline Real Vector2D::x() const
{
  return myVec[0];
}

inline Real& Vector2D::y()
{
  return myVec[1];
}

inline Real Vector2D::y() const
{
  return myVec[1];
}

#endif // _Vector2D_H

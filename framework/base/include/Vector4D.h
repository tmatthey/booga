/*
 * Vector4D.h 
 *
 * 4D Vector class.
 *
 * Copyright (C) 1995, Richard Baechler <baechler@iam.unibe.ch>
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
 *  $Id: Vector4D.h,v 1.1 1995/09/28 15:03:08 streit Exp $
 * ----------------------------------------------------------------------
 */

#ifndef Vector4D_H
# define Vector4D_H

#include "booga/base/mathutilities.h"
#include "booga/base/Report.h"
#include "booga/base/Vector3D.h"

#include <ostream>
#include <istream>

//_________________________________________________________________ Vector4D

class Vector4D {
public:
  Vector4D();
  Vector4D(Real x, Real y, Real z, Real w); 
  Vector4D(const Vector3D& vec, Real w);
  Vector4D(const Vector4D& vec);

  Real& operator[](int index);
  Real  operator[](int index) const;
  Real& x();
  Real  x() const;
  Real& y();
  Real  y() const;
  Real& z();
  Real  z() const;
  Real& w();
  Real  w() const;

  Vector3D make3D();

  Vector4D& operator=(const Vector4D& vec);
  Vector4D& operator+=(const Vector4D& vec);
  Vector4D& operator-=(const Vector4D& vec);
  Vector4D& operator*=(Real scale);
  Vector4D& operator/=(Real scale);

  int operator==(const Vector4D& vec) const;
  int operator!=(const Vector4D& vec) const;
  int equal(const Vector4D& vec, Real epsilon = EPSILON) const;

  Real sqr() const;                       // squared length of Vector4D
  Real length() const;                    // length of Vector4D
  int  zero() const;
  Real distance(const Vector4D& vec) const; // distance between two points
  Real   normalize();                     // normalize Vector4D
  Vector4D normalized() const;              // generate normalized Vector4D

  Vector4D operator-() const;                   // unary negation
  Vector4D operator+(const Vector4D& vec) const;  // Vector4D addition
  Vector4D operator-(const Vector4D& vec) const;  // Vector4D subtraction

  Real dot(const Vector4D& vec) const;
  Real operator^(const Vector4D& vec) const;    // Vector4D dot product

  Vector4D operator/(Real scale) const;         // scalar divison

  friend Vector4D operator*(Real scale, const Vector4D& vec);
  friend Vector4D operator*(const Vector4D& vec, Real scale);
  // scalar multiply

  friend std::ostream& operator<<(std::ostream& os, const Vector4D& vec);
  friend std::istream& operator>>(std::istream& is, Vector4D& vec);

private:
  Real myVec[4];
};

inline Real& Vector4D::operator[](int index)
{
  if (index<0 || index>3)
    Report::error("[Vector4D::operator[] ] index out of range");

  return myVec[index];
}

inline Real Vector4D::operator[](int index) const
{
  if (index<0 || index>3)
    Report::error("[Vector4D::operator[] const] index out of range");

  return myVec[index];
}

inline Real& Vector4D::x()
{
  return myVec[0];
}

inline Real Vector4D::x() const
{
  return myVec[0];
}

inline Real& Vector4D::y()
{
  return myVec[1];
}

inline Real Vector4D::y() const
{
  return myVec[1];
}

inline Real& Vector4D::z()
{
  return myVec[2];
}

inline Real Vector4D::z() const
{
  return myVec[2];
}

inline Real& Vector4D::w()
{
  return myVec[3];
}

inline Real Vector4D::w() const
{
  return myVec[3];
}

inline Vector3D Vector4D::make3D ()
{
  if (w() != 0)
    return Vector3D (x()/w(), y()/w(), z()/w());
  else
    return Vector3D (x(), y(), z());
}

#endif // Vector4D_H


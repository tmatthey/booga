/*
 * Vector4D.C
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
 * ---------------------------------------------------------------------
 *  $Id: Vector4D.C,v 1.2 1997/09/19 07:15:13 buhlmann Exp $
 * ---------------------------------------------------------------------
 */
#ifdef WIN32
#include <iostream.h>
#elif SVR4
#include <stream.h>
#endif

#include <ctype.h>      // isspace(char)
#include "booga/base/Vector4D.h"

//_________________________________________________________________ Vector4D

Vector4D::Vector4D()
{
  myVec[0] = myVec[1] = myVec[2] = myVec[3] = 0.0;
}

Vector4D::Vector4D(Real x, Real y, Real z, Real w)
{
  myVec[0] = x; myVec[1] = y; myVec[2] = z; myVec[3] = w;
}

Vector4D::Vector4D (const Vector3D &vec, Real w)
{
  myVec[0] = w * vec.x();
  myVec[1] = w * vec.y();
  myVec[2] = w * vec.z();
  myVec[3] = w;
}

Vector4D::Vector4D(const Vector4D& vec)
{
  myVec[0] = vec.myVec[0];
  myVec[1] = vec.myVec[1];
  myVec[2] = vec.myVec[2];
  myVec[3] = vec.myVec[3];
}

Vector4D& Vector4D::operator=(const Vector4D& vec)
{
  myVec[0] = vec.myVec[0];
  myVec[1] = vec.myVec[1];
  myVec[2] = vec.myVec[2];
  myVec[3] = vec.myVec[3];

  return *this;
}

Vector4D& Vector4D::operator+=(const Vector4D& vec)
{
  myVec[0] += vec.myVec[0];
  myVec[1] += vec.myVec[1];
  myVec[2] += vec.myVec[2];
  myVec[3] += vec.myVec[3];

  return *this;
}

Vector4D& Vector4D::operator-=(const Vector4D& vec)
{
  myVec[0] -= vec.myVec[0];
  myVec[1] -= vec.myVec[1];
  myVec[2] -= vec.myVec[2];
  myVec[3] -= vec.myVec[3];

  return *this;
}

Vector4D& Vector4D::operator*=(Real scale)
{
  myVec[0] *= scale;
  myVec[1] *= scale;
  myVec[2] *= scale;
  myVec[3] *= scale;

  return *this;
}

Vector4D& Vector4D::operator/=(Real scale)
{
  if (::equal(scale, 0.0))
    Report::error("[Vector4D::operator/=] division by zero");

  Real d = 1/scale;
  myVec[0] *= d;
  myVec[1] *= d;
  myVec[2] *= d;
  myVec[3] *= d;

  return *this;
}

int Vector4D::operator==(const Vector4D& vec) const
{
  return (::equal(myVec[0], vec.myVec[0]) &&
	  ::equal(myVec[1], vec.myVec[1]) &&
	  ::equal(myVec[2], vec.myVec[2]) &&
	  ::equal(myVec[3], vec.myVec[3]));
}

int Vector4D::operator!=(const Vector4D& vec) const
{
  return (!::equal(myVec[0], vec.myVec[0]) ||
	  !::equal(myVec[1], vec.myVec[1]) ||
	  !::equal(myVec[2], vec.myVec[2]) ||
	  !::equal(myVec[3], vec.myVec[3]));
}

int Vector4D::equal(const Vector4D& vec, Real epsilon) const
{
  return (::equal(myVec[0], vec.myVec[0], epsilon) &&
	  ::equal(myVec[1], vec.myVec[1], epsilon) &&
	  ::equal(myVec[2], vec.myVec[2], epsilon) &&
	  ::equal(myVec[3], vec.myVec[3], epsilon));
}

Real Vector4D::sqr() const
{
  return myVec[0]*myVec[0] + myVec[1]*myVec[1] + myVec[2]*myVec[2] + myVec[3]*myVec[3];
}

Real Vector4D::length() const
{
  return sqrt(myVec[0]*myVec[0] + myVec[1]*myVec[1] + myVec[2]*myVec[2] + myVec[3]*myVec[3]);
}

int Vector4D::zero() const
{
  return (::equal(fabs(myVec[0]), 0.0) &&
	  ::equal(fabs(myVec[1]), 0.0) &&
	  ::equal(fabs(myVec[2]), 0.0) &&
	  ::equal(fabs(myVec[3]), 0.0));
}

Real Vector4D::distance(const Vector4D& vec) const
{
  return (*this - vec).length();
}

/*
 * Normalize the Vector4D and return the original length.
 */
Real Vector4D::normalize()
{
  Real len = length();

  if (::equal(len, 0.0))
    return 0.0;

  Real d = 1/len;
  myVec[0] *= d; myVec[1] *= d; myVec[2] *= d; myVec[3] *= d;
  return len;
}

/*
 * Return a normalized Vector4D, leave the original Vector4D unchanged.
 */
Vector4D Vector4D::normalized() const
{
  Real len = length();

  if (::equal(len, 0.0)) {
    Report::warning("[Vector4D::normalized] length is zero");
    return Vector4D();
  }

  return Vector4D(*this / len);
}

Vector4D Vector4D::operator-() const
{
  return Vector4D(-myVec[0], -myVec[1], -myVec[2], -myVec[3]);
}

Vector4D Vector4D::operator+(const Vector4D& vec) const
{
  return Vector4D(myVec[0] + vec.myVec[0],
		myVec[1] + vec.myVec[1],
		myVec[2] + vec.myVec[2],
		myVec[3] + vec.myVec[3]);
}

Vector4D Vector4D::operator-(const Vector4D& vec) const
{
  return Vector4D(myVec[0] - vec.myVec[0],
		myVec[1] - vec.myVec[1],
		myVec[2] - vec.myVec[2],
		myVec[3] - vec.myVec[3]);
}

Real Vector4D::operator^(const Vector4D& vec) const
{
  return (myVec[0]*vec.myVec[0] +
	  myVec[1]*vec.myVec[1] +
	  myVec[2]*vec.myVec[2] +
	  myVec[3]*vec.myVec[3]);
}

Real Vector4D::dot(const Vector4D& vec) const
{
  return (myVec[0]*vec.myVec[0] +
	  myVec[1]*vec.myVec[1] +
	  myVec[2]*vec.myVec[2] +
	  myVec[3]*vec.myVec[3]);
}

Vector4D Vector4D::operator/(Real scale) const
{
  if (::equal(scale, 0.0))
    Report::error("[Vector4D::operator/] division by zero");

  Real d = 1/scale;
  return Vector4D(myVec[0]*d, myVec[1]*d, myVec[2]*d, myVec[3]*d);
}

Vector4D operator*(Real scale, const Vector4D& vec)
{
  return Vector4D(scale*vec.myVec[0],
		scale*vec.myVec[1],
		scale*vec.myVec[2],
		scale*vec.myVec[3]);
}

Vector4D operator*(const Vector4D& vec, Real scale)
{
  return Vector4D(vec.myVec[0]*scale,
		vec.myVec[1]*scale,
		vec.myVec[2]*scale,
		vec.myVec[3]*scale);
}

ostream& operator<<(ostream& os, const Vector4D& vec)
{
  return os << "["
	    << vec.x() << ", " << vec.y() << ", " << vec.z() << ", " << vec.w()
	   << "]";
}

/*
 * From GGems IV, Jean-Francois Doue.
 */
istream& operator>>(istream& is, Vector4D& vec)
{
  Vector4D tmp;
  char c;

  // The vectors are formatted [ x , y , z , w ]
  while (is >> c && isspace(c)) ;  
  is >> tmp.myVec[0];
  while (is >> c && isspace(c)) ;  
  is >> tmp.myVec[1];
  while (is >> c && isspace(c)) ;  
  is >> tmp.myVec[2];
  while (is >> c && isspace(c)) ;
  is >> tmp.myVec[3];
  while (is >> c && isspace(c)) ;
  
  if (c != ']')
    is.clear(ios::badbit|is.rdstate());

  if (is)
    vec = tmp;
  else
    Report::warning("[operator>>(istream&, Vector4D&)] : illegal vector format");
    
  return is;
}


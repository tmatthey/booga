/*
 * Vector3D.C
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
 * ---------------------------------------------------------------------
 *  $Id: Vector3D.C,v 1.4 1997/09/19 07:15:12 buhlmann Exp $
 * ---------------------------------------------------------------------
 */

#include <iostream>
#include <ctype.h>      // isspace(char)
#include "booga/base/Vector3D.h"

//_________________________________________________________________ Vector3D

Vector3D::Vector3D()
{ 
  myVec[0] = myVec[1] = myVec[2] = 0.0; 
}

Vector3D::Vector3D(Real x, Real y, Real z) 
{ 
  myVec[0] = x; myVec[1] = y; myVec[2] = z; 
}

Vector3D::Vector3D(const Vector3D& vec)
{ 
  myVec[0] = vec.myVec[0]; 
  myVec[1] = vec.myVec[1]; 
  myVec[2] = vec.myVec[2]; 
}

Vector3D& Vector3D::operator=(const Vector3D& vec)
{
  myVec[0] = vec.myVec[0]; 
  myVec[1] = vec.myVec[1]; 
  myVec[2] = vec.myVec[2];

  return *this;
}

Vector3D& Vector3D::operator+=(const Vector3D& vec)
{
  myVec[0] += vec.myVec[0];  
  myVec[1] += vec.myVec[1];  
  myVec[2] += vec.myVec[2];

  return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& vec)
{
  myVec[0] -= vec.myVec[0];  
  myVec[1] -= vec.myVec[1];  
  myVec[2] -= vec.myVec[2];

  return *this;
}

Vector3D& Vector3D::operator*=(const Vector3D& vec)
{
  Real tmpX = myVec[0];
  Real tmpY = myVec[1];
  Real tmpZ = myVec[2];

  myVec[0] = tmpY*vec.myVec[2] - tmpZ*vec.myVec[1];
  myVec[1] = tmpX*vec.myVec[0] - tmpX*vec.myVec[2];
  myVec[2] = tmpX*vec.myVec[1] - tmpY*vec.myVec[0];

  return *this;
}

Vector3D& Vector3D::operator*=(Real scale)
{
  myVec[0] *= scale; 
  myVec[1] *= scale; 
  myVec[2] *= scale;

  return *this;
}

Vector3D& Vector3D::operator/=(Real scale)
{
  if (::equal(scale, 0.0))
    Report::error("[Vector3D::operator/=] division by zero");

  Real d = 1/scale;
  myVec[0] *= d; 
  myVec[1] *= d; 
  myVec[2] *= d;

  return *this;
}

int Vector3D::operator==(const Vector3D& vec) const
{
  return (::equal(myVec[0], vec.myVec[0]) && 
	  ::equal(myVec[1], vec.myVec[1]) && 
	  ::equal(myVec[2], vec.myVec[2]));
}

int Vector3D::operator!=(const Vector3D& vec) const
{
  return (!::equal(myVec[0], vec.myVec[0]) || 
	  !::equal(myVec[1], vec.myVec[1]) || 
	  !::equal(myVec[2], vec.myVec[2]));
}

int Vector3D::equal(const Vector3D& vec, Real epsilon) const
{
  return (::equal(myVec[0], vec.myVec[0], epsilon) && 
	  ::equal(myVec[1], vec.myVec[1], epsilon) && 
	  ::equal(myVec[2], vec.myVec[2], epsilon));
}

Real Vector3D::sqr() const
{
  return myVec[0]*myVec[0] + myVec[1]*myVec[1] + myVec[2]*myVec[2];
}

Real Vector3D::length() const
{
  return sqrt(myVec[0]*myVec[0] + myVec[1]*myVec[1] + myVec[2]*myVec[2]);
}

int Vector3D::zero() const
{
  return (::equal(fabs(myVec[0]), 0.0) &&
	  ::equal(fabs(myVec[1]), 0.0) &&
	  ::equal(fabs(myVec[2]), 0.0));
}

Real Vector3D::distance(const Vector3D& vec) const
{
  return (*this - vec).length();
}

/*
 * Normalize the Vector3D and return the original length.
 */
Real Vector3D::normalize()
{
  Real len = length();

  if (::equal(len, 0.0))
    return 0.0;

  Real d = 1/len;
  myVec[0] *= d; myVec[1] *= d; myVec[2] *= d;
  return len;
}

/*
 * Retur a normalized Vector3D, leave the original Vector3D unchanged.
 */
Vector3D Vector3D::normalized() const
{
  Real len = length();

  if (::equal(len, 0.0)) {
    Report::warning("[Vector3D::normalized] length is zero");
    return Vector3D();
  }

  return Vector3D(*this / len);
}

Vector3D Vector3D::operator-() const
{
  return Vector3D(-myVec[0], -myVec[1], -myVec[2]);
}

Vector3D Vector3D::operator+(const Vector3D& vec) const
{
  return Vector3D(myVec[0] + vec.myVec[0], 
		myVec[1] + vec.myVec[1], 
		myVec[2] + vec.myVec[2]);
}

Vector3D Vector3D::operator-(const Vector3D& vec) const
{
  return Vector3D(myVec[0] - vec.myVec[0], 
		myVec[1] - vec.myVec[1], 
		myVec[2] - vec.myVec[2]);
}

Vector3D Vector3D::operator*(const Vector3D& vec) const
{
  return Vector3D(myVec[1]*vec.myVec[2] - myVec[2]*vec.myVec[1],
		myVec[2]*vec.myVec[0] - myVec[0]*vec.myVec[2],
		myVec[0]*vec.myVec[1] - myVec[1]*vec.myVec[0]);
}

Vector3D Vector3D::cross(const Vector3D& vec) const
{
  return Vector3D(myVec[1]*vec.myVec[2] - myVec[2]*vec.myVec[1],
		myVec[2]*vec.myVec[0] - myVec[0]*vec.myVec[2],
		myVec[0]*vec.myVec[1] - myVec[1]*vec.myVec[0]);
}

Real Vector3D::operator^(const Vector3D& vec) const
{
  return (myVec[0]*vec.myVec[0] + 
	  myVec[1]*vec.myVec[1] + 
	  myVec[2]*vec.myVec[2]);
}

Real Vector3D::dot(const Vector3D& vec) const
{
  return (myVec[0]*vec.myVec[0] + 
	  myVec[1]*vec.myVec[1] + 
	  myVec[2]*vec.myVec[2]);
}

Vector3D Vector3D::operator/(Real scale) const
{
  if (::equal(scale, 0.0))
    Report::error("[Vector3D::operator/] division by zero");

  Real d = 1/scale;
  return Vector3D(myVec[0]*d, myVec[1]*d, myVec[2]*d);
}

Vector3D operator*(Real scale, const Vector3D& vec)
{
  return Vector3D(scale*vec.myVec[0], 
		scale*vec.myVec[1], 
		scale*vec.myVec[2]);
}

Vector3D operator*(const Vector3D& vec, Real scale) 
{
  return Vector3D(vec.myVec[0]*scale, 
		vec.myVec[1]*scale, 
		vec.myVec[2]*scale);
}

std::ostream& operator<<(std::ostream& os, const Vector3D& vec)
{
  return os << "[" 
            << vec.x() << ", " << vec.y() << ", " << vec.z()
	   << "]";
}

/*
 * From GGems IV, Jean-Francois Doue.
 */
std::istream& operator>>(std::istream& is, Vector3D& vec) 
{
  Vector3D tmp;
  char c;

  // The vectors are formatted [ x , y , z ]
  while (is >> c && isspace(c)) ;  
  is >> tmp.myVec[0];
  while (is >> c && isspace(c)) ;  
  is >> tmp.myVec[1];
  while (is >> c && isspace(c)) ;  
  is >> tmp.myVec[2];
  while (is >> c && isspace(c)) ;
  
  if (c != ']')
    is.clear(std::ios::badbit|is.rdstate());

  if (is)
    vec = tmp;
  else
    Report::warning("[operator>>(istream&, Vector3D&)] : illegal vector format");
    
  return is;
}

/*
 * Vector2D.C
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
 *  $Id: Vector2D.C,v 1.4 1997/09/19 07:15:10 buhlmann Exp $
 * ---------------------------------------------------------------------
 */

#include <iostream.h>
#include <ctype.h>      // isspace(char)
#include "booga/base/Vector2D.h"

//_________________________________________________________________ Vector2D

Vector2D::Vector2D()
{ 
  myVec[0] = myVec[1] = 0.0; 
}

Vector2D::Vector2D(Real x, Real y) 
{ 
  myVec[0] = x; myVec[1] = y; 
}

Vector2D::Vector2D(const Vector2D& vec)
{ 
  myVec[0] = vec.myVec[0]; 
  myVec[1] = vec.myVec[1]; 
}

Vector2D& Vector2D::operator=(const Vector2D& vec)
{
  myVec[0] = vec.myVec[0]; 
  myVec[1] = vec.myVec[1]; 

  return *this;
}

Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
  myVec[0] += vec.myVec[0];  
  myVec[1] += vec.myVec[1];  

  return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
  myVec[0] -= vec.myVec[0];  
  myVec[1] -= vec.myVec[1];  

  return *this;
}

Vector2D& Vector2D::operator*=(Real scale)
{
  myVec[0] *= scale; 
  myVec[1] *= scale; 

  return *this;
}

Vector2D& Vector2D::operator/=(Real scale)
{
  if (::equal(scale, 0.0))
    Report::error("[Vector2D::operator/=] division by zero");

  Real d = 1/scale;
  myVec[0] *= d; 
  myVec[1] *= d; 

  return *this;
}

int Vector2D::operator==(const Vector2D& vec) const
{
  return (::equal(myVec[0], vec.myVec[0]) && 
	  ::equal(myVec[1], vec.myVec[1]));
}

int Vector2D::operator!=(const Vector2D& vec) const
{
  return (!::equal(myVec[0], vec.myVec[0]) || 
	  !::equal(myVec[1], vec.myVec[1]));
}

int Vector2D::equal(const Vector2D& vec, Real epsilon) const
{
  return (::equal(myVec[0], vec.myVec[0], epsilon) && 
	  ::equal(myVec[1], vec.myVec[1], epsilon));
}

Real Vector2D::sqr() const
{
  return myVec[0]*myVec[0] + myVec[1]*myVec[1];
}

Real Vector2D::length() const
{
  return sqrt(myVec[0]*myVec[0] + myVec[1]*myVec[1]);
}

int Vector2D::zero() const
{
  return (::equal(fabs(myVec[0]), 0.0) &&
	  ::equal(fabs(myVec[1]), 0.0));
}

Real Vector2D::distance(const Vector2D& vec) const
{
  return (*this - vec).length();
}

/*
 * Normalize the Vector2D and return the original length.
 */
Real Vector2D::normalize()
{
  Real len = length();

  if (::equal(len, 0.0))
    return 0.0;

  Real d = 1/len;
  myVec[0] *= d; myVec[1] *= d; 
  return len;
}

/*
 * Return a normalized Vector2D, leave the original Vector2D unchanged.
 */
Vector2D Vector2D::normalized() const
{
  Real len = length();

  if (::equal(len, 0.0)) {
    Report::warning("[Vector2D::normalized] length is zero");
    return Vector2D();
  }

  return Vector2D(*this / len);
}

Vector2D Vector2D::operator-() const
{
  return Vector2D(-myVec[0], -myVec[1]);
}

Vector2D Vector2D::operator+(const Vector2D& vec) const
{
  return Vector2D(myVec[0] + vec.myVec[0], 
		  myVec[1] + vec.myVec[1]);
}

Vector2D Vector2D::operator-(const Vector2D& vec) const
{
  return Vector2D(myVec[0] - vec.myVec[0], 
		  myVec[1] - vec.myVec[1]);
}

Real Vector2D::operator^(const Vector2D& vec) const
{
  return (myVec[0]*vec.myVec[0] + 
	  myVec[1]*vec.myVec[1]);
}

Real Vector2D::dot(const Vector2D& vec) const
{
  return (myVec[0]*vec.myVec[0] + 
	  myVec[1]*vec.myVec[1]);
}

Vector2D Vector2D::operator/(Real scale) const
{
  if (::equal(scale, 0.0))
    Report::error("[Vector2D::operator/] division by zero");

  Real d = 1/scale;
  return Vector2D(myVec[0]*d, myVec[1]*d);
}

Vector2D operator*(Real scale, const Vector2D& vec)
{
  return Vector2D(scale*vec.myVec[0], 
		  scale*vec.myVec[1]);
}

Vector2D operator*(const Vector2D& vec, Real scale) 
{
  return Vector2D(vec.myVec[0]*scale, 
		  vec.myVec[1]*scale);
}

ostream& operator<<(ostream& os, const Vector2D& vec)
{
  return os << "[" 
            << vec.x() << ", " << vec.y() 
            << "]";
}

/*
 * From GGems IV, Jean-Francois Doue.
 */
istream& operator>>(istream& is, Vector2D& vec) 
{
  Vector2D tmp;
  char c;

  // The vectors are formatted [ x , y ]
  while (is >> c && isspace(c)) ;  
  is >> tmp.myVec[0];
  while (is >> c && isspace(c)) ;  
  is >> tmp.myVec[1];
  while (is >> c && isspace(c)) ;
  
  if (c != ']')
    is.clear(ios::badbit|is.rdstate());

  if (is)
    vec = tmp;
  else
    Report::warning("[operator>>(istream&, Vector2D&)] : illegal vector format");
    
  return is;
}

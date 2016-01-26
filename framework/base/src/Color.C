/*
 * Color.C
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
 *                        University of Berne, Switzerland
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
 *  $Id: Color.C,v 1.7 1997/09/19 07:14:00 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <ctype.h>      // isspace(char)
#include <math.h>

#include "booga/base/mathutilities.h"
#include "booga/base/Configuration.h"
#include "booga/base/ColorOption.h"
#include "booga/base/Color.h"

//________________________________________________________________________ Color

Color::Color()
{
  myRGB[0] = 0;
  myRGB[1] = 0;
  myRGB[2] = 0;
}

Color::Color(float red, float green, float blue)
{
  myRGB[0] = red;
  myRGB[1] = green;
  myRGB[2] = blue;
}

Color::Color(Vector3D& v)
{
  myRGB[0] = v.x();
  myRGB[1] = v.y();
  myRGB[2] = v.z();
}

Color::operator Vector3D() const
{
  return Vector3D(myRGB[0], myRGB[1], myRGB[2]);
}

Color& Color::operator+=(const Color& col)
{
  myRGB[0]+=col.myRGB[0];
  myRGB[1]+=col.myRGB[1];
  myRGB[2]+=col.myRGB[2];

  return *this;
}

Color& Color::operator-=(const Color& col)
{
  myRGB[0]-=col.myRGB[0];
  myRGB[1]-=col.myRGB[1];
  myRGB[2]-=col.myRGB[2];

  return *this;
}

Color& Color::operator*=(float factor)
{
  myRGB[0]*=factor;
  myRGB[1]*=factor;
  myRGB[2]*=factor;

  return *this;
}

float Color::brightness() const
{
  return 0.59*myRGB[0]+0.3*myRGB[1]+0.11*myRGB[2];
}

int Color::operator==(const Color& col) const
{
  return (equal(myRGB[0], col.myRGB[0]) && 
	 equal(myRGB[1], col.myRGB[1]) && 
	 equal(myRGB[2], col.myRGB[2]));
}

int Color::operator!=(const Color& col) const
{
  return !(equal(myRGB[0], col.myRGB[0]) && 
	  equal(myRGB[1], col.myRGB[1]) && 
	  equal(myRGB[2], col.myRGB[2]));
}

Color Color::operator+(const Color& col) const
{
  return Color(myRGB[0]+col.myRGB[0], 
	      myRGB[1]+col.myRGB[1], 
	      myRGB[2]+col.myRGB[2]);
}

Color Color::operator-(const Color& col) const
{
  return Color(myRGB[0]-col.myRGB[0], 
	      myRGB[1]-col.myRGB[1],
	      myRGB[2]-col.myRGB[2]);
}

Color Color::operator/(float denom) const
{
  if (equal(denom, 0))
    Report::error("[Color::operator/] division by zero");

  return Color(myRGB[0]/denom, myRGB[1]/denom, myRGB[2]/denom);
}

Color Color::operator*(float factor) const
{
  return Color(myRGB[0]*factor, myRGB[1]*factor, myRGB[2]*factor);
}

Color Color::operator*(const Color& col) const
{
  return Color(myRGB[0]*col.myRGB[0],
	      myRGB[1]*col.myRGB[1],
	      myRGB[2]*col.myRGB[2]);
}

Color Color::getDefault()
{
  getConfigurationOption(ColorOption, color, "Color.Default");
  if (color != NULL)
    return color->getColor();
  else
    return Color(1,0,0);  // Red is default
}

std::ostream& operator<<(std::ostream& os, const Color& col)
{
  return os << "[" << col.myRGB[0] << ", " << col.myRGB[1] 
	   << ", " << col.myRGB[2] << "]";
}

/*
 * From GGems IV, Jean-Francois Doue.
 */
std::istream& operator>>(std::istream& is, Color& col)
{
  Color tmp;
  char c;

  // The Colors are formatted [ x , y , z ]
  while (is >> c && isspace(c)) ;  
  is >> tmp.myRGB[0];
  while (is >> c && isspace(c)) ;  
  is >> tmp.myRGB[1];
  while (is >> c && isspace(c)) ;  
  is >> tmp.myRGB[2];
  while (is >> c && isspace(c)) ;
  
  if (c != ']')
    is.clear(std::ios::badbit|is.rdstate());

  if (is)
    col = tmp;
  else
    Report::warning("[operator>>(istream&, Color&)] : illegal color format");
    
  return is;
}


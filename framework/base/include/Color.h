/*
 * Color.h
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
 *  $Id: Color.h,v 1.6 1996/01/29 17:05:00 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Color_h
#define _Color_h

#include "booga/base/Report.h"
#include "booga/base/Vector3D.h"

class ostream;
class istream;

//________________________________________________________________________ Color

class Color {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Color();
  Color(float red, float green, float blue);
  Color(Vector3D& v);
  // Color(Const COlor&);            // Use default version.

public:
  // ~Color();                       // Use default version.

public:
  //Color& operator=(const Color&);  // Use default version.  

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class Color
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  operator Vector3D() const;

  int operator==(const Color& col) const;
  int operator!=(const Color& col) const;
  
  Color& operator+=(const Color& col);
  Color& operator-=(const Color& col);
  Color& operator*=(float factor);

  Color operator+(const Color& col) const;
  Color operator-(const Color& col) const;
  Color operator/(float denom) const;
  Color operator*(float factor) const;
  Color operator*(const Color& col) const;

  float getRed() const; 
  void  setRed(float red);
  float getGreen() const; 
  void  setGreen(float green);
  float getBlue() const; 
  void  setBlue(float blue);

  float  operator[](int index) const;
  float& operator[](int index);

  float brightness() const;

public:
  static Color getDefault();

public:
  friend ostream& operator<<(ostream& os, const Color& col);
  friend istream& operator>>(istream& is, Color& col);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  float myRGB[3];
};

//______________________________________________________________________ INLINES

inline float Color::getRed() const
{
  return myRGB[0];
}

inline void Color::setRed(float red)
{
  myRGB[0] = red;
}

inline float Color::getGreen() const
{
  return myRGB[1];
}

inline void Color::setGreen(float green)
{
  myRGB[1] = green;
}

inline float Color::getBlue() const
{
  return myRGB[2];
}

inline void Color::setBlue(float blue)
{
  myRGB[2] = blue;
}


inline float Color::operator[](int index) const
{
  if (index<0 || index>2)
    Report::error("[Color::operator[] const] index out of range");

  return myRGB[index]; 
}

inline float& Color::operator[](int index)
{
  if (index<0 || index>2)
    Report::error("[Color::operator[]] index out of range");

  return myRGB[index]; 
}

#endif



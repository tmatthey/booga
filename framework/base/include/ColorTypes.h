/*
 * $RCSfile: ColorTypes.h,v $
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: ColorTypes.h,v 1.4 1996/08/30 08:16:12 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ColorTypes_H
#define _ColorTypes_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/Color.h"

//__________________________________________________________________________ RGB

class RGB : public Color {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // RGB();                       // Use default version.
  // RGB(const RGB&);             // Use default version.
  
public:
  // ~RGB();                      // Use default version.

public:
  // RGB& operator=(const RGB&);  // Use default version.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class RGB
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setValue(float c1, float c2, float c3);
  void setValue(float value);
  void setValue(bool value);
  void getValue(float& c1, float& c2, float& c3) const;
  void getValue(float& value) const;
  void getValue(bool& value) const;
};

//_______________________________________________________________________ RGBChar

class RGBChar {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  RGBChar();
  // RGBChar(const RGBChar&);             // Use default version.

public:
  // ~RGBChar();                          // Use default version.

public:
  // RGBChar& operator=(const RGBChar&);  // Use default version.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class RGBChar
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setValue(float c1, float c2, float c3);
  void setValue(float value);
  void setValue(bool value);
  void getValue(float& c1, float& c2, float& c3) const;
  void getValue(float& value) const;
  void getValue(bool& value) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  unsigned char myRed, myGreen, myBlue;
};

inline RGBChar::RGBChar()
: myRed(0), myGreen(0), myBlue(0)
{}

//_________________________________________________________________________ Grey

class Grey {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Grey();
  // Grey(const Grey&);             // Use default version.

public:
  // ~Grey();                       // Use default version.

public:
  // Grey& operator=(const Grey&);  // Use default version.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class Grey
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setValue(float c1, float c2, float c3);
  void setValue(float value);
  void setValue(bool value);
  void getValue(float& c1, float& c2, float& c3) const;
  void getValue(float& value) const;
  void getValue(bool& value) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  float myValue;
};

inline Grey::Grey()
: myValue(0.0)
{}

//___________________________________________________________________________ BW

class BW {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  BW();
  // BW(const BW&);             // Use default version.

public:
  // ~BW();                     // Use default version.

public:
  // BW& operator=(const BW&);  // Use default version.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class BW
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setValue(float c1, float c2, float c3);
  void setValue(float value);
  void setValue(bool value);
  void getValue(float& c1, float& c2, float& c3) const;
  void getValue(float& value) const;
  void getValue(bool& value) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  bool myValue;
};

inline BW::BW()
: myValue(false)
{}

#endif // _ColorTypes_H

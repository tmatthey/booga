/*
 * Value.h 
 *
 * Polymorphic handling of Real, String, Vector and TransMatrix values.
 *
 * Copyright (C) 1994, Christoph Streit <streit@iam.unibe.ch>
 *                     Stephan Amann <amann@iam.unibe.ch>
 *                     University of Berne, Switzerland
 * Portions Copyright (C) 1990, Jonathan P. Leech
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
 *  $Id: Value.h,v 1.3 1995/10/06 14:07:24 amann Exp $
 * ----------------------------------------------------------------------
 */

#ifndef _Value_H
# define _Value_H

#include "booga/base/RCString.h"
#include "booga/base/Vector3D.h"
#include "booga/base/Vector2D.h"
#include "booga/base/TransMatrix3D.h"
#include "booga/base/TransMatrix2D.h"

//__________________________________________________________________ Value

class Value {
public:
  Value(Real val = 0.0);
  Value(const char* str);
  Value(const RCString& s);
  Value(Real x, Real y, Real z);
  Value(Real x, Real y);
  Value(const Vector3D& vec);
  Value(const Vector2D& vec);
  Value(const TransMatrix3D& tmat);
  Value(const TransMatrix2D& tmat);
  Value(const Value& v);

  ~Value();

  Value& operator=(const Value& v);
  Value& operator+=(const Value& v);
  Value& operator-=(const Value& v);
  Value& operator*=(const Value& v);
  Value& operator/=(const Value& v);
  Value& operator^=(const Value& v);
  Value& operator%=(const Value& v);

  operator int() const;
  // This conversion operator is usful, when using Value objects 
  // within conditional expression, e.g.
  //   if (Value("Hallo") < Value(4.3))  will lead to a valid result

  operator Real() const;
  operator RCString() const;
  operator Vector3D() const;
  operator Vector2D() const;
  operator TransMatrix3D() const;
  operator TransMatrix2D() const;

  int toReal(Real& x) const;
  int toRCString(RCString& s) const;
  int toVector3D(Vector3D& vec) const;
  int toVector2D(Vector2D& vec) const;
  int toTransMatrix3D(TransMatrix3D& tmat) const;
  int toTransMatrix2D(TransMatrix2D& tmat) const;

  Value operator-()               const;
  Value operator+(const Value& v) const;
  Value operator-(const Value& v) const;
  Value operator*(const Value& v) const;
  Value operator/(const Value& v) const;
  Value operator^(const Value& v) const;
  Value operator%(const Value& v) const;
  
  Value operator!()                const;
  Value operator&&(const Value& v) const;
  Value operator||(const Value& v) const;
  Value operator==(const Value& v) const;
  Value operator!=(const Value& v) const;
  Value operator< (const Value& v) const;
  Value operator<=(const Value& v) const;
  Value operator> (const Value& v) const;
  Value operator>=(const Value& v) const;

  Value operator[](const Value& v) const;

  friend ostream& operator<<(ostream& os, const Value& v);

protected:
  int myType;
  union {
    Real           realVal;
    RCString*      stringVal;
    Vector3D*      vector3DVal;
    Vector2D*      vector2DVal;
    TransMatrix3D* matrix3DVal;
    TransMatrix2D* matrix2DVal;
  }; 

protected: // Internals
  static void error(const RCString& op, 
		    const Value& arg1, const Value& arg2);
};

#endif // _Value_H 




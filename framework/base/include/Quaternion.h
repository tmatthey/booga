/*
 * $RCSfile: Quaternion.h,v $
 *
 * ADT Quaternion.
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
 *                        University of Berne, Switzerland
 *
 * ANSI C code from the article
 *    "Arcball Rotation Control"
 *       by Ken Shoemake, shoemake@graphics.cis.upenn.edu
 *       in "Graphics Gems IV", Academic Press, 1994
 * adapted to C++.
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
 *  $Id: Quaternion.h,v 1.2 1996/08/04 14:24:51 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Quaternion_H
#define _Quaternion_H

#include "booga/base/mathutilities.h"
#include "booga/base/TransMatrix3D.h"

#include <ostream>

//___________________________________________________________________ Quaternion

class Quaternion {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Quaternion(); 
  // Default ctor initializes to identity [0,0,0,1];
  Quaternion(Real x, Real y, Real z, Real w);
  // Quaternion(const Quaternion&);             // Use default version.

public:
  // ~Quaternion();                             // Use default version.

public:
  // Quaternion& operator=(const Quaternion&);  // Use default version.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class Quaternion
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public: // ------------ Accessors
  Real  x() const;
  Real& x();
  Real  y() const;
  Real& y();
  Real  z() const;
  Real& z();
  Real  w() const;
  Real& w();

  static const Quaternion& identity();

public: // ------------ Misc
  operator TransMatrix3D() const;
  // Construct rotation matrix from (possibly non-unit) quaternion.
  // Assumes matrix is used to multiply column vector on the left:
  // vnew = mat vold.  Works correctly for right-handed coordinate system
  // and right-handed rotations. 

  Quaternion conjugate() const;
  // Return conjugate of quaternion. 

public: // ------------ Friends
  friend Quaternion operator*(const Quaternion& qL, const Quaternion& qR);
  // Return quaternion product qL * qR.  Note: order is important!
  // To combine rotations, use the product qSecond * qFirst,
  // which gives the effect of rotating by qFirst then qSecond. 

  friend std::ostream& operator<<(std::ostream& os, const Quaternion& q);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Real myX, myY, myZ, myW;

private:
  static Quaternion ourQuatIdentity;
};

//______________________________________________________________________ INLINES

inline Real  Quaternion::x() const { return myX; }
inline Real& Quaternion::x()       { return myX; }

inline Real  Quaternion::y() const { return myY; }
inline Real& Quaternion::y()       { return myY; }

inline Real  Quaternion::z() const { return myZ; }
inline Real& Quaternion::z()       { return myZ; }

inline Real  Quaternion::w() const { return myW; }
inline Real& Quaternion::w()       { return myW; }

inline const Quaternion& Quaternion::identity()
{
  return ourQuatIdentity;
}

#endif // _Quaternion_H


/*
 * $RCSfile: Quaternion.C,v $
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
 *  $Id: Quaternion.C,v 1.2 1996/08/04 14:24:50 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <iostream.h>
#include "booga/base/Quaternion.h"

//___________________________________________________________________ Quaternion

Quaternion Quaternion::ourQuatIdentity(0, 0, 0, 1);

Quaternion::Quaternion()
: myX(0), myY(0), myZ(0), myW(1)
{}

Quaternion::Quaternion(Real x, Real y, Real z, Real w)
: myX(x), myY(y), myZ(z), myW(w)
{}

Quaternion::operator TransMatrix3D() const
{
  Real Nq = myX*myX + myY*myY + myZ*myZ + myW*myW;
  Real s = (Nq > 0.0) ? (2.0 / Nq) : 0.0;
  Real xs = myX*s,        ys = myY*s,         zs = myZ*s;
  Real wx = myW*xs,       wy = myW*ys,        wz = myW*zs;
  Real xx = myX*xs,       xy = myX*ys,        xz = myX*zs;
  Real yy = myY*ys,       yz = myY*zs,        zz = myZ*zs;

  return TransMatrix3D(1.0 - (yy + zz), xy - wz,xz + wy,
                       xy + wz,1.0 - (xx + zz),yz - wx,
                       xz - wy,yz + wx,                       
                                         1.0 - (xx + yy)
                      );
//  return TransMatrix3D(1.0 - (yy + zz), xy + wz,         xz - wy,
//                       xy - wz,         1.0 - (xx + zz), yz + wx,
//                       xz + wy,         yz - wx,         1.0 - (xx + yy));
}

Quaternion Quaternion::conjugate() const
{
  return Quaternion(-myX, -myY, -myZ, myW);
}

Quaternion operator*(const Quaternion& qL, const Quaternion& qR)
{
  return Quaternion(qL.myW*qR.myX + qL.myX*qR.myW + qL.myY*qR.myZ - qL.myZ*qR.myY,
                    qL.myW*qR.myY + qL.myY*qR.myW + qL.myZ*qR.myX - qL.myX*qR.myZ,
                    qL.myW*qR.myZ + qL.myZ*qR.myW + qL.myX*qR.myY - qL.myY*qR.myX,
                    qL.myW*qR.myW - qL.myX*qR.myX - qL.myY*qR.myY - qL.myZ*qR.myZ);
}

ostream& operator<<(ostream& os, const Quaternion& q)
{
  return os << '[' << q.myX << ' ' << q.myY << ' ' << q.myZ << ' ' << q.myW << ']';
}

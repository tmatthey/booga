/*
 * $RCSfile: BoundsUtilities.h,v $
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
 *  $Id: BoundsUtilities.h,v 1.4 1996/08/09 14:53:03 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _BoundsUtilities_H
#define _BoundsUtilities_H

class BoundingRect;
class BoundingBox;
class Ray2D;
class Ray3D;

#include "booga/base/PrimitiveTypes.h"

//_____________________________________________________________________ BoundsUtilities

class BoundsUtilities {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  BoundsUtilities();                                   // No instances.
  BoundsUtilities(const BoundsUtilities&);             // No copies.

private:
  ~BoundsUtilities();                                  // Use default version.

private:
  BoundsUtilities& operator=(const BoundsUtilities&);  // No assignments.


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class BoundsUtilities
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  static bool intersect(const BoundingRect& bound, const Ray2D& ray);
  static bool intersect(const BoundingBox& bound,  Ray3D& ray);

  static bool slabTest(Real dir, Real pos, 
                       Real boundsLow, Real boundsHigh, 
                       Real& tmin, Real& tmax);

  // Avoid warning about private ctor/dtor and no friends.
  friend class _dummy;
};

#endif // _BoundsUtilities_H


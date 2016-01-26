/*
 * $RCSfile: BoundsUtilities.C,v $
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
 *  $Id: BoundsUtilities.C,v 1.3 1996/07/26 13:49:25 streit Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "booga/base/BoundingRect.h"
#include "booga/base/BoundingBox.h"
#include "booga/object/Ray2D.h"
#include "booga/object/Ray3D.h"
#include "booga/object/BoundsUtilities.h"

//____________________________________________________________________ BoundsUtilities

bool BoundsUtilities::intersect(const BoundingRect& bound, const Ray2D& ray) 
{
  return bound.inside(ray.getOrigin());
}

bool BoundsUtilities::intersect(const BoundingBox& bound,  Ray3D& ray) 
{
  ray.setBoundsHitDistance(-1); // no hit
  
  if (bound.myIsEmpty)
    return false;

  //
  // Origin of ray inside bounding box ? There's for sure an intersection.
  //
  if (bound.inside(ray.getOrigin()))
    return true;                
  
  Real tmax = ray.getBestHitDistance();
  Real tmin = 0; // -MAXREAL;
 
  for (int i=0; i<3; i++)
    if (!slabTest(ray.getDirection()[i], ray.getOrigin()[i], 
                  bound.myBBMin[i], bound.myBBMax[i], 
                  tmin, tmax))
      return false;
 
  if (tmin > tmax)
    return false;
  if (tmax < 0)
    return false;
 
  if (tmin > ray.getBestHitDistance())
    return false;
 
  if (equal(tmin, -MAXREAL)) {
    if (tmax < ray.getBestHitDistance()) {
      ray.setBoundsHitDistance(tmax);
      return true;  // return tmax -> computed distance
    }
  }
  else if (tmin < ray.getBestHitDistance()) {
    ray.setBoundsHitDistance(tmin);
    return true;    // return tmin -> computed distance
  }

  return false;
}

bool BoundsUtilities::slabTest(Real dir, Real pos, 
                               Real boundsLow, Real boundsHigh, 
                               Real& tmin, Real& tmax) 
{
  // We don't have an intersection, if a ray is parallel to
  // a bounding box plane, and the rays origin is lower than
  // the lower bound or higher than the upper bound.
  if (equal(dir, 0)) 
    if (pos < boundsLow || pos > boundsHigh)
      return false;
    else
      return true;
      
  Real t1, t2, invDir = 1/dir;
  if (dir > 0) {
    t1 = (boundsHigh - pos) * invDir;
    t2 = (boundsLow - pos)  * invDir;
  } else {
    t1 = (boundsLow - pos)  * invDir;
    t2 = (boundsHigh - pos) * invDir;
  }    
 
  if (t1 < tmin)
    return false;
  if (t1 < tmax)
    tmax = t1;
  if (t2 > tmin) {
    if (t2 > tmax)
      return false;
    tmin = t2;
  }
 
  return true;
}


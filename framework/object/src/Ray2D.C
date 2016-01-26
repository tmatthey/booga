/*
 * Ray2D.C 
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
 *  $Id: Ray2D.C,v 1.9 1996/02/07 12:34:35 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Report.h"
#include "booga/object/Transform2D.h"
#include "booga/object/Object2D.h"
#include "booga/object/Primitive2D.h"
#include "booga/object/Path2D.h"
#include "booga/object/Ray2D.h"

//_______________________________________________________________________ Ray2D

Ray2D::Ray2D(const Vector2D& origin, const Vector2D& direction)
: myOrigin(origin), myDirection(direction)
{
  // myDirection.normalize()
  myPath = new Path2D;
  reset();
}

Ray2D::~Ray2D()
{
  delete myPath;
}

void Ray2D::reset()
{
  myLevel = 0;
  myPathIsVaild = false;
  myBestHitObject   = NULL;
  myBestHitDistance = MAXREAL;  // Far, far, far away.
  myTolerance       = EPSILON;  
}

Vector2D Ray2D::getHitPoint() const
{
  // return myOrigin + myBestHitDistance * myDirection;
  return myOrigin;
}

void Ray2D::addToPath(Object2D* object)
{
  if (myLevel < 0) {
    Report::error("[Ray2D::addToPath] illegal level");
    return;
  }
  
  myPathIsVaild = false;

  while (myTempPath.count()-1 < myLevel)
    myTempPath.append((Object2D*)NULL);
  
  myTempPath.item(myLevel) = object;
}

const Path2D* Ray2D::getPath() const
{
  if (myTempPath.count() <= 0)
    return NULL;
    
  //
  // This method alters the *internal* state of the object only ->
  // logical const-ness of 'this' is casted away.
  //
  Ray2D* This = (Ray2D*) this;

  if (!This->myPathIsVaild) {
    This->myPath->reset();
    Object2D* curObject;
    for (long i=0; i<This->myTempPath.count(); i++) {
      curObject = This->myTempPath.item(i);
      // 
      // Check for NULL objects in path.
      //
      if (curObject == NULL) {
        Report::warning("[Ray2D::getPath] NULL object in path");
        return NULL;
      }
      This->myPath->append(curObject);
      // 
      // Stop after first Primitive in path
      //
      if (curObject == myBestHitObject)
        break;
    }
    
    This->myPathIsVaild = true;
  }

  This->myPathIsVaild = true;

  return This->myPath;
}

Real Ray2D::transform(Transform2D& transform)
{
   myOrigin = transform.invTransformAsPoint(myOrigin);
   // myDirection = transform.invTransformAsVector(myDirection);
   
   // Real scaleFactor = myDirection.normalize();
   // myBestHitDistance *= scaleFactor;
   // myTolerance *= scaleFactor;

   // return scaleFactor;
   return 1.0;
}

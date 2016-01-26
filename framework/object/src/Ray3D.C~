/*
 * Ray3D.C 
 *
 * Copyright (C) 1995, Christoph Streit <streit@iam.unibe.ch>
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
 * -----------------------------------------------------------------------------
 *  $Id: Ray3D.C,v 1.13 1996/06/28 11:18:13 amann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Report.h"
#include "booga/object/Transform3D.h"
#include "booga/object/Object3D.h"
#include "booga/object/Primitive3D.h"
#include "booga/object/Path3D.h"
#include "booga/object/Ray3D.h"

//_______________________________________________________________________ Ray3D

Ray3D::Ray3D(const Vector3D& origin, const Vector3D& direction)
: myOrigin(origin), myDirection(direction)
{
  myDirection.normalize();
  myPath = new Path3D;

  reset();
}

Ray3D::~Ray3D()
{
  delete myPath;
}

void Ray3D::reset()
{
  myLevel = 0;
  myPathIsVaild = false;
  myBestHitObject   = NULL;
  myBestHitDistance = MAXREAL;  // Far, far, far away.
  myTolerance       = EPSILON;  
  
  myDepth        = 1;   // First Ray is always level 1.
  myContribution = 1.0; // First Ray has weight 1.
  
  myBoundsHitDistance = -1.0; // No Hit with Bounding Box
}

Vector3D Ray3D::getHitPoint() const
{
  return myOrigin + myBestHitDistance * myDirection;
}

void Ray3D::addToPath(Object3D* object)
{
  if (myLevel < 0) {
    Report::error("[Ray3D::addToPath] illegal level");
    return;
  }
  
  myPathIsVaild = false;

  while (myTempPath.count()-1 < myLevel)
    myTempPath.append((Object3D*)NULL);
  
  myTempPath.item(myLevel) = object;
}

const Path3D* Ray3D::getPath() const
{
  if (myTempPath.count() <= 0)
    return NULL;
    
  //
  // This method alters the *internal* state of the object only ->
  // logical const-ness of 'this' is casted away.
  //
  Ray3D* This = (Ray3D*) this;

  if (!This->myPathIsVaild) {
    This->myPath->reset();
    Object3D* curObject;
    for (long i=0; i<This->myTempPath.count(); i++) {
      curObject = This->myTempPath.item(i);
      // 
      // Check for NULL objects in path.
      //
      if (curObject == NULL) {
        Report::warning("[Ray3D::getPath] NULL object in path");
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

  return This->myPath;
}

Real Ray3D::transform(Transform3D& transform)
{
   myOrigin = transform.invTransformAsPoint(myOrigin);
   myDirection = transform.invTransformAsVector(myDirection);
   
   Real scaleFactor = myDirection.normalize();
   myBestHitDistance *= scaleFactor;
   myBoundsHitDistance *= scaleFactor;
   myTolerance *= scaleFactor;

   return scaleFactor;
}

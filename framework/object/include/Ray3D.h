/*
 * Ray3D.h
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
 *  $Id: Ray3D.h,v 1.8 1996/06/28 11:18:15 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Ray3D_H
# define _Ray3D_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/List.h"
#include "booga/base/Vector3D.h"

class Transform3D;
class Primitive3D;
class Object3D;
class Path3D;
class Ray3DFactory;

//_______________________________________________________________________ Ray3D

class Ray3D {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
friend class Ray3DFactory;
private:
  Ray3D(const Vector3D& origin, const Vector3D& direction); // for friends only.
  Ray3D(const Ray3D&);                                      // No copies.

public:
  ~Ray3D();  

private:
  Ray3D& operator=(const Ray3D&);                           // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class Ray3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void reset();
  
  void setOrigin(const Vector3D& origin);
  const Vector3D& getOrigin() const;
  
  void setDirection(const Vector3D& direction);
  const Vector3D& getDirection() const;

  Vector3D getHitPoint() const;

  void incLevel();
  void decLevel();
  void addToPath(Object3D* object);
  
  const Path3D* getPath() const;

  void setBestHitObject(Primitive3D* bestHitObject);
  Primitive3D* getBestHitObject() const;

  void setBestHitDistance(Real bestHitDistance);
  Real getBestHitDistance() const;

  void setBoundsHitDistance(Real distance);
  Real getBoundsHitDistance() const;

  void setTolerance(Real tolerance);
  Real getTolerance() const;

  Real transform(Transform3D& transform);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:                            // The ray itself
  Vector3D myOrigin;                
  Vector3D myDirection;

private:                            // Keep track of the intersection path
  int myLevel;                       // Current depth in path
  List<Object3D*> myTempPath;        
  bool myPathIsVaild;
  Path3D* myPath;

private:                            // Keep track of intersections
  Primitive3D* myBestHitObject;      // The best (nearest) object so far
  Real myBestHitDistance;            // ... and the distance from the origin
  Real myBoundsHitDistance;          // The distance from origin to current
                                     // bounding box intersection
  Real myTolerance;                  // Intersections nearer to origin are ignored
  
private:                           // Keep track of ray tree
  int myDepth;                      // Actual recursion depth
  Real myContribution;              // How much does this rays result contribute
                                    // to the final result?
};

//______________________________________________________________________ INLINES

inline void Ray3D::setOrigin(const Vector3D& origin)
{
  myOrigin = origin;
}

inline const Vector3D& Ray3D::getOrigin() const
{
  return myOrigin;
}
  
inline void Ray3D::setDirection(const Vector3D& direction)
{
  myDirection = direction;
  myDirection.normalize();
}

inline const Vector3D& Ray3D::getDirection() const
{
  return myDirection;
}

inline void Ray3D::incLevel()
{
  myLevel++;
}

inline void Ray3D::decLevel()
{
  myLevel--;
}
 
inline void Ray3D::setBestHitObject(Primitive3D* bestHitObject)
{
  myBestHitObject = bestHitObject;
}

inline Primitive3D* Ray3D::getBestHitObject() const
{
  return myBestHitObject;
}

inline void Ray3D::setBestHitDistance(Real bestHitDistance)
{
  myBestHitDistance = bestHitDistance;
}

inline Real Ray3D::getBestHitDistance() const
{
  return myBestHitDistance;
}

inline void Ray3D::setBoundsHitDistance(Real distance)
{
  myBoundsHitDistance = distance;
}

inline Real Ray3D::getBoundsHitDistance() const
{
  return myBoundsHitDistance;
}

inline void Ray3D::setTolerance(Real tolerance)
{
  myTolerance = tolerance; 
}

inline Real Ray3D::getTolerance() const
{
  return myTolerance;
}

#endif // _Ray3D_H


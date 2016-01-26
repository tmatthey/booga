/*
 * Ray2D.h
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
 *  $Id: Ray2D.h,v 1.6 1996/01/10 19:13:11 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Ray2D_H
#define _Ray2D_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/List.h"
#include "booga/base/Vector2D.h"

class Transform2D;
class Primitive2D;
class Object2D;
class Path2D;

//_______________________________________________________________________ Ray2D

class Ray2D {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Ray2D(const Vector2D& origin, const Vector2D& direction = Vector2D());
private:
  Ray2D(Ray2D&);  // No copies.

public:
  ~Ray2D();

public:
  Ray2D& operator=(const Ray2D&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class Ray2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void reset();
  
  void setOrigin(const Vector2D& origin);
  const Vector2D& getOrigin() const;
  
  void setDirection(const Vector2D& direction);
  const Vector2D& getDirection() const;

  Vector2D getHitPoint() const;

  void incLevel();
  void decLevel();
  void addToPath(Object2D* object);
  
  const Path2D* getPath() const;

  void setBestHitObject(Primitive2D* bestHitObject);
  Primitive2D* getBestHitObject() const;

  void setBestHitDistance(Real bestHitDistance);
  Real getBestHitDistance() const;

  void setBoundsHitDistance(Real distance);
  Real getBoundsHitDistance() const;

  void setTolerance(Real tolerance);
  Real getTolerance() const;

  Real transform(Transform2D& transform);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Vector2D myOrigin;
  Vector2D myDirection;

  int myLevel;
  List<Object2D*> myTempPath;
  bool myPathIsVaild;
  Path2D* myPath;

  Primitive2D* myBestHitObject;
  Real myBestHitDistance;
  Real myTolerance;
};

//______________________________________________________________________ INLINES

inline void Ray2D::setOrigin(const Vector2D& origin)
{
  myOrigin = origin;
}

inline const Vector2D& Ray2D::getOrigin() const
{
  return myOrigin;
}
  
inline void Ray2D::setDirection(const Vector2D& direction)
{
  myDirection = direction;
  myDirection.normalize();
}

inline const Vector2D& Ray2D::getDirection() const
{
  return myDirection;
}

inline void Ray2D::incLevel()
{
  myLevel++;
}

inline void Ray2D::decLevel()
{
  myLevel--;
}
 
inline void Ray2D::setBestHitObject(Primitive2D* bestHitObject)
{
  myBestHitObject = bestHitObject;
}

inline Primitive2D* Ray2D::getBestHitObject() const
{
  return myBestHitObject;
}

inline void Ray2D::setBestHitDistance(Real bestHitDistance)
{
  myBestHitDistance = bestHitDistance;
}

inline Real Ray2D::getBestHitDistance() const
{
  return myBestHitDistance;
}

inline void Ray2D::setTolerance(Real tolerance)
{
  myTolerance = tolerance; 
}

inline Real Ray2D::getTolerance() const
{
  return myTolerance;
}

inline void Ray2D::setBoundsHitDistance(Real){}

inline Real Ray2D::getBoundsHitDistance() const
{
  return 0.0;
}

#endif // _Ray2D_H


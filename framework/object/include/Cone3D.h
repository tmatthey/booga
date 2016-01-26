/*
 * $RCSfile: Cone3D.h,v $
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
 *  $Id: Cone3D.h,v 1.20 1996/10/04 09:46:20 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Cone3D_H
#define _Cone3D_H

#include "booga/object/Primitive3D.h"

/* ______________________________________________________________________ Cone3D
 *
 * A cone is stored and processed using the following canonical 
 * representation (makes life much easier...):
 *
 *                top radius = 1   (bottom radius = myDistance)
 *              |----|
 *          _________    _
 *          \       /    |
 *           \     /     |      height = 1
 *            \___/      |  _
 *                       |  |   myDistance
 *                       -  -
 *
 * The cone is aligned with the z-axis with start point at [0, myDistance] 
 * and end point at [0,1].
 */
 
class Cone3D : public Primitive3D {
declareRTTI(Cone3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Cone3D(Exemplar);
  Cone3D(Real radiusStart, const Vector3D& start, 
         Real radiusEnd,   const Vector3D& end);
  // Cone3D(const Cone3D&);                 // Use default version.

public:
  // virtual ~Cone3D();                     // Use default version.

private:  
  Cone3D& operator=(const Cone3D& sphere);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Cone3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  const Vector3D& getStart() const;
  void setStart(const Vector3D& start);

  const Vector3D& getEnd() const;
  void setEnd(const Vector3D& start);

  Real getStartRadius() const;
  Real getEndRadius() const;
  void setRadius(Real startRadius, Real endRadius);

  bool isClosed() const;
  void close();
  void open();

  const Transform3D& getCanonicalTransform() const;
  Real getDistance() const;
  
private:
  void computeCanonicalTransform();
  Vector3D unifiedNormal(const Vector3D& ucsPoint) const;
  // get normal in unified coordinate system

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Primitive3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object3D* createDecomposition() const;
  virtual Vector3D normal(const Vector3D& point) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object3D* copy() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool doIntersect(Ray3D& ray);
private:
  virtual void doComputeBounds();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual RCString getKeyword() const;
  virtual List<Value*>* createParameters();
  virtual void iterateAttributes(MakeableHandler* handler);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Real     myStartRadius;
  Vector3D myStart;
  Real     myEndRadius;
  Vector3D myEnd;
  bool     myIsClosed;

  Real myDistance;              // distance of apex to origin in normalized cone
  Transform3D myCanonicalTransform;  // General <--> conical transformation.
};

//______________________________________________________________________ INLINES

inline const Vector3D& Cone3D::getStart() const
{
  return myStart;
}

inline const Vector3D& Cone3D::getEnd() const
{
  return myEnd;
}

inline Real Cone3D::getStartRadius() const
{
  return myStartRadius;
}

inline Real Cone3D::getEndRadius() const
{
  return myEndRadius;
}

inline bool Cone3D::isClosed() const
{
  return myIsClosed;
}

inline void Cone3D::open()
{
  myIsClosed = false;
}

inline void Cone3D::close()
{
  myIsClosed = true;
}

inline const Transform3D& Cone3D::getCanonicalTransform() const
{
  return myCanonicalTransform;
}

inline Real Cone3D::getDistance() const
{
  return myDistance;
}

#endif // _Cone3D_H


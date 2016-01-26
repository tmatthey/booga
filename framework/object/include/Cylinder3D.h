/*
 * $RCSfile: Cylinder3D.h,v $
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
 *  $Id: Cylinder3D.h,v 1.16 1996/10/04 09:46:28 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Cylinder3D_H
#define _Cylinder3D_H

#include "booga/object/Primitive3D.h"

/*___________________________________________________________________ Cylinder3D
 *
 * A cylinder is processed using the following canonical 
 * representation (makes life much easier...):
 *
 *              top radius = 1   (bottom radius = 1)
 *             |--|
 *          ______    _
 *         |      |   |
 *         |      |   |   height = 1
 *         |______|  _| 
 *                      
 *
 * The cylinder is aligned with the z-axis with start point at [0, 0] 
 * and end point at [0,1].
 */

class Cylinder3D : public Primitive3D {
declareRTTI(Cylinder3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Cylinder3D(Exemplar);
  Cylinder3D(Real radius, const Vector3D& start, const Vector3D& end);
  // Cylinder3D(const Cylinder3D&);                 // Use default version.

public:
  // virtual ~Cylinder3D();                         // Use default version.

private:  
  Cylinder3D& operator=(const Cylinder3D& sphere);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Cylinder3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  const Vector3D& getStart() const;
  void setStart(const Vector3D& start);

  const Vector3D& getEnd() const;
  void setEnd(const Vector3D& start);

  Real getRadius() const;
  void setRadius(Real radius);

  bool isClosed() const;
  void close();
  void open();

  const Transform3D& getCanonicalTransform() const;

private:
  void computeCanonicalTransform();
  inline Vector3D unifiedNormal(const Vector3D& ucsPoint) const;
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
  virtual void doComputeBounds();
private:
  virtual bool doIntersect(Ray3D& ray);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual RCString getKeyword() const;
  virtual List<Value*>* createParameters();
  virtual void iterateAttributes(MakeableHandler *handler);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Real     myRadius;
  Vector3D myStart;
  Vector3D myEnd;
  bool     myIsClosed;

  Transform3D myCanonicalTransform;  // General <--> conical transformation.
};

//______________________________________________________________________ INLINES

inline const Vector3D& Cylinder3D::getStart() const
{
  return myStart;
}

inline const Vector3D& Cylinder3D::getEnd() const
{
  return myEnd;
}

inline Real Cylinder3D::getRadius() const
{
  return myRadius;
}

inline bool Cylinder3D::isClosed() const
{
  return myIsClosed;
}

inline void Cylinder3D::open()
{
  myIsClosed = false;
}

inline void Cylinder3D::close()
{
  myIsClosed = true;
}

inline const Transform3D& Cylinder3D::getCanonicalTransform() const
{
  return myCanonicalTransform;
}

#endif // _Cylinder3D_H

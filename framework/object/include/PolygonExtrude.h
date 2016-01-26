/*
 * PolygonExtrude.h
 *
 * Copyright (C) 1996, Thierry Matthey <matthey@iam.unibe.ch>
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
 *  $Id: PolygonExtrude.h,v 1.7 1996/12/19 16:14:51 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _PolygonExtrude_H
#define _PolygonExtrude_H

#include "booga/base/List.h"
#include "booga/object/Primitive3D.h"

// ____________________________________________________________________ PolygonExtrude

class PolygonExtrude : public Primitive3D {
declareRTTI(PolygonExtrude);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  PolygonExtrude(Exemplar);
  PolygonExtrude(Real height, const List<Vector3D>& vertices, 
                 const List<List<Vector3D> >& holes = List<List<Vector3D> >(0));
  PolygonExtrude(Real height, const List<Vector3D>& vertices, 
                 const List<Vector3D>& hole);
  PolygonExtrude(const PolygonExtrude& poly);

public:
  virtual ~PolygonExtrude();

private:  
  PolygonExtrude& operator=(const PolygonExtrude&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class PolygonExtrude
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void addVertex(const Vector3D& vertex);
  const List<Vector3D>& getVertices() const;
  void removeVertices();

  void addHole(const List<Vector3D>& hole);
  const List<List<Vector3D> >& getHoles() const;
  void removeHoles();
  
  Vector3D getNormal() const;

  void setHeight(Real height);
  Real getHeight() const;
  
private:

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
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);
  virtual RCString getKeyword() const;
  virtual List<Value*>* createParameters();
  virtual void iterateAttributes(MakeableHandler* handler);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  List<Vector3D> myVertices;
  List<List<Vector3D> > myHoles;
  Real myHeight;

  Object3D* myDecomposition; 
  // The decomposition ist cached for each polygon object.
};

//______________________________________________________________________ INLINES

inline const List<Vector3D>& PolygonExtrude::getVertices() const
{
  return myVertices;
}

inline const List<List<Vector3D> >& PolygonExtrude::getHoles() const
{
  return myHoles;
}

inline void PolygonExtrude::setHeight(Real height)
{
  myHeight = height;
}

inline Real PolygonExtrude::getHeight()const
{
  return myHeight;
}

inline void PolygonExtrude::removeVertices()
{
  myVertices.removeAll();
}

inline void PolygonExtrude::removeHoles()
{
  myHoles.removeAll();
}

#endif // _PolygonExtrude_H



/*
 * $RCSfile: Polygon3D.h,v $
 *
 * Copyright (C) 1994-96, Berhard Buehlmann <buhlmann@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: Polygon3D.h,v 1.15 1998/04/29 12:06:24 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Polygon3D_H
#define _Polygon3D_H

#include "booga/base/List.h"
#include "booga/object/Primitive3D.h"

// ____________________________________________________________________ Polygon3D

class Polygon3D : public Primitive3D {
declareRTTI(Polygon3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Polygon3D(Exemplar);
  Polygon3D(const List<Vector3D>& vertices, const List<Vector3D>& holes);
  Polygon3D(const List<Vector3D>& vectors, 
            const List<List<Vector3D> >& holes = List<List<Vector3D> >(0));
  Polygon3D(const Polygon3D& poly);

public:
  virtual ~Polygon3D();

private:  
  Polygon3D& operator=(const Polygon3D&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Polygon3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void addVertex(const Vector3D& vertex);
  void insertVertex(int i, const Vector3D& vertex);
  void setVertex(int i, const Vector3D& vertex);
  void removeVertex(int i);
  const List<Vector3D>& getVertices() const;
  void removeVertices();

  void addHole(const List<Vector3D>& hole);
  const List<List<Vector3D> >& getHoles() const;
  void removeHoles();
  
  Vector3D getNormal() const;
  
 
private:
  void computeNormal();

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
  Vector3D myNormal;

  Real myPlaneDist;        
  // Factor D of the plane equation Ax+By+Cz+D = 0 for the polygon.

  int myProjectionIndex1;	
  int myProjectionIndex2;
  // First and second projection axis.

  Object3D* myDecomposition; 
  // The decomposition ist cached for each polygon object.
};

//______________________________________________________________________ INLINES

inline const List<Vector3D>& Polygon3D::getVertices() const
{
  return myVertices;
}

inline const List<List<Vector3D> >& Polygon3D::getHoles() const
{
  return myHoles;
}

inline Vector3D Polygon3D::getNormal() const
{
  return myNormal;
}

inline void Polygon3D::removeVertices()
{
  myVertices.removeAll();
}

inline void Polygon3D::removeHoles()
{
  myHoles.removeAll();
}


#endif // _Polygon3D_H

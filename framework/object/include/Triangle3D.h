/*
 * $RCSfile: Triangle3D.h,v $
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
 *  $Id: Triangle3D.h,v 1.17 1996/10/04 09:48:58 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Triangle3D_H
#define _Triangle3D_H

#include "booga/object/Primitive3D.h"
#include "booga/base/Vector3D.h"

//___________________________________________________________________ Triangle3D

class Triangle3D : public Primitive3D {
declareRTTI(Triangle3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Triangle3D(Exemplar);
  Triangle3D(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3);
  Triangle3D(const Vector3D& v1, const Vector3D& n1,
	    const Vector3D& v2, const Vector3D& n2,
	    const Vector3D& v3, const Vector3D& n3);
  // Triangle3D(const Triangle3D&);          // Use default version.

public:
  // virtual ~Triangle3D();                  // Use default version.

private:
  Triangle3D& operator=(const Triangle3D&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Triangle3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  const Vector3D& getVertex(int index) const;
  void setVertex(int index, const Vector3D& newValue);

  const Vector3D& getNormal(int index) const;
  void setNormal(int index, const Vector3D& newValue);

private:
  void initTriangle();
  bool getBarycentricCoord(const Vector3D& point, Vector3D& bc) const;
   
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
  virtual RCString getKeyword() const;
  virtual List<Value*>* createParameters();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Vector3D myVertex1, myVertex2, myVertex3;  // Vertices
  Vector3D myNormal1, myNormal2, myNormal3;  // Normals
  
  Vector3D myPlaneNormal;          // Plane
  Real     myPlaneDist;
  
  Vector3D myEdge21, myEdge31;     // Edges of triangle
  char myDominant1, myDominant2;   // Dominant part normal
};

#endif // _Triangle3D_H

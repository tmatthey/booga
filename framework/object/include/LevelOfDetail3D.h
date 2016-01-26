/*
 * $RCSfile: LevelOfDetail3D.h,v $ 
 *
 * A simple LevelOfDetail of Object3D.
 *
 * Copyright (C) 1994-98, Bernhard Buehlmann <buhlmann@iam.unibe.ch>
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
 *  $Id: LevelOfDetail3D.h,v 1.1 1998/05/06 07:33:31 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _LevelOfDetail3D_H
#define _LevelOfDetail3D_H

#include "booga/object/Aggregate3D.h"

//_______________________________________________________________________ LevelOfDetail3D

class LevelOfDetail3D : public Aggregate3D {
declareRTTI(LevelOfDetail3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  LevelOfDetail3D();
  LevelOfDetail3D(Exemplar);
  // LevelOfDetail3D(const LevelOfDetail3D&);               // Use default version.

public:
  // virtual ~LevelOfDetail3D();                   // Use default version.

private:
  LevelOfDetail3D& operator=(const LevelOfDetail3D& LevelOfDetail);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Aggregate3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  virtual Aggregate3D* makeEmpty() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object3D* copy() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class LevelOfDetail3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void removeDistances();
  void addDistance(Real d);
  Real getDistance(long i);
  Real countDistances();
/** Sets the active object. This method should be called by the Renderer
which display the object. According to the List of distance values, the
corresponding object should be slected. The values specify the distance of the
center of the object's boundingbox in world coordinates to the eye point of 
the observing camera.
*/
  void setActiveObject (int i);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  virtual bool doIntersect(Ray3D& ray);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class MAggregate
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual long countSubobject() const;
  virtual Object3D* getSubobject(long index);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual RCString getKeyword() const;
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  List<Value*>* createParameters();
  virtual void iterateAttributes(MakeableHandler *handler);

private:
  List<Real> myDistanceList;
  int myActiveObject;
};

#endif // _LevelOfDetail3D_H

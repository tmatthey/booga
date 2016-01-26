/*
 * $RCSfile: SnatchRoof.h,v $
 *
 * Copyright (C) 1997, Thierry Matthey <matthey@iam.unibe.ch>
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
 *  $Id: SnatchRoof.h,v 1.2 1997/02/06 14:14:07 matthey Exp matthey $
 * -----------------------------------------------------------------------------
 */

#ifndef _SnatchRoof_H
#define _SnatchRoof_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/building/Snatch.h"

// ____________________________________________________________________ SnatchRoof

class SnatchRoof : public Snatch {
declareRTTI(SnatchRoof);
// enable RTTI support

public:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  SnatchRoof();
  SnatchRoof(Exemplar exemplar);
  SnatchRoof(const SnatchRoof& snatchroof);      
  SnatchRoof(const Vector2D& position);

public:
  virtual ~SnatchRoof();   
  
private:  
  SnatchRoof& operator=(const SnatchRoof& snatchroof);  // No assignments.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class SnatchRoof
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

public:
  const Vector2D& getPosition() const;
  void setPosition(const Vector2D& position);
  Object3D* getObject() const;
  Object3D* orphanObject();
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);
  virtual RCString getKeyword() const;
  virtual void iterateAttributes(MakeableHandler* handler);
  virtual List<Value*>* createParameters();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Snatch
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  virtual Object3D* getSnatchObjects(Building* building) const;
  virtual void getRaySegment(Vector3D &from, Vector3D &to) const;
  virtual TransMatrix3D getRotation(const Vector3D &hitpoint, const Vector3D &normal) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object3D* copy() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class BuildingObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual Object3D* doCreateSubject(Building* building) const;  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Vector2D  myPosition;
  Object3D* myObject;
};

//______________________________________________________________________ INLINES

inline Object3D* SnatchRoof::getObject() const 
{
  return myObject;
}

inline void SnatchRoof::setPosition(const Vector2D& position)
{
  myPosition = position;
}

inline const Vector2D& SnatchRoof::getPosition() const
{
  return myPosition;
}

#endif // _SnatchRoof_H

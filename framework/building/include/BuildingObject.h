/*
 * $RCSfile: BuildingObject.h,v $
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
 *  $Id: BuildingObject.h,v 1.1 1997/01/17 10:34:42 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _BuildingObject_H
#define _BuildingObject_H

#include "booga/object/Object3D.h"
#include "booga/object/NullObject3D.h"

class Building;
class Face;
class BoundingBox;
// ____________________________________________________________________ BuildingObject

class BuildingObject : public Object3D {
declareRTTI(BuildingObject);
// enable RTTI support

public:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  BuildingObject();
  BuildingObject(Exemplar exemplar);
  BuildingObject(const BuildingObject& buildingobject);

public:
  // virtual ~BuildingObject(); 
  
private:  
  BuildingObject& operator=(const BuildingObject&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class BuildingObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void turnOn();          
  void turnOff();        
  bool isOn() const;    
  void setParentBuilding(Building* building);  
  virtual void subjectChanged() const;

protected:
  // every BuildingObject does it's own decomposition
  virtual Object3D* doCreateSubject(Building* building) const=0;
  Object3D* getSubject() const;
public:
  virtual Building* getParentBuilding() const;  // should be private !!!!
 
private:
  virtual Object3D* createSubject(Building* building) const=0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Friends of class Face
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// friend Building* getParentBuilding();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object3D* makeUnique(Path3D* path = NULL, bool shared = false);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual long countSubobject() const;
  virtual Object3D* getSubobject(long index);

protected:  
  virtual void doComputeBounds();
  
private:
  virtual bool doIntersect(Ray3D& ray);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);
  virtual void iterateAttributes(MakeableHandler* handler);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Object3D* mySubject;
  bool      myIsOn;
  Building* myParentBuilding;
};

//______________________________________________________________________ INLINES

inline void  BuildingObject::turnOn()
{
  myIsOn = true;
}
 
inline void  BuildingObject::turnOff()
{
  myIsOn = false;
}
 
inline bool BuildingObject::isOn() const
{
  return myIsOn;
}

inline void BuildingObject::setParentBuilding(Building* building)
{
  myParentBuilding = building;
}

inline Building* BuildingObject::getParentBuilding() const
{
  return myParentBuilding;
}

#endif // _BuildingObject_H


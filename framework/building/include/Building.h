/*
 * $RCSfile: Building.h,v $
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
 *  $Id: Building.h,v 1.4 1997/02/20 09:39:54 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Building_H
#define _Building_H

#include "booga/base/List.h"
#include "booga/base/Vector2D.h"
#include "booga/object/Object3D.h"

class BuildingObject;
class Face;
class Front;
class Roof;

// ____________________________________________________________________ Building

class Building : public Object3D {
declareRTTI(Building);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Building(Exemplar);
  Building(Real height, const List<Vector3D>& vertices);
  Building(const Building& building);

public:
  virtual ~Building();

private:  
  Building& operator=(const Building&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Building
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // base of building
  void addVertex(const Vector3D& vertex);
  void setVertices(const List<Vector3D>& vertices);
  const List<Vector3D>& getVertices() const;
  void removeVertices();
  
  // holes/interior  of building
  void addHole(const List<Vector3D>& hole);
  const List<List<Vector3D> >& getHoles() const;
  void removeHoles();
  
  // height of the building
  void setHeight(Real height);
  Real getHeight() const;
  
  // 
  List<Vector3D> getPolygon(long index) const;
  List<Vector3D> getPolygonTop(long index) const;
  List<Vector3D> getPolygonBottom(long index) const;
  Vector3D getVertex(long frontindex, long polygonindex = 0) const;
  List<Vector3D> getFrontPolygon(long polygonindex,long frontindex) const;
  long countPolygon() const;
  long countFront(long polygonindex) const;

  // collecting all indirect faces from all fronts with specified index
  void getIndirectFaceObjects(long frontindex, long polygonindex, List<Face*>* facelist) const;
  // collecting all fronts with specified index
  List<Front*> getFrontObjects(long frontindex = -1, long polygonindex = -1) const;
  // collecting all roof objects
  List<Roof*> getRoofObjects() const;

  // operations
  void moveVertex(long frontindex, long polygonindex, const Vector2D& offset);
  void deleteVertex(long frontindex, long polygonindex);
  void insertVertex(long frontindex, long polygonindex, const Vector3D& vertex);  
  void changeIndex(long frontindex, long polygonindex, long newfrontindex, long newpolygonindex) const;
  bool testIndex(long frontindex, long polygonindex) const;
  
  // simple check of the parameters and the subobjects
  void checkBuilding() const;
  
  // design pattern: proxy
  void adoptObject(Object3D* object);    
  Object3D* orphanObject(long index);    
  void subjectChanged() const;
  void turnOn();          
  void turnOff();        
  bool isOn() const;    

private:
  // generates a building with fronts and roofs
  Object3D* dummyBuilding() const;
  // design pattern: proxy
  Object3D* createSubject() const;
  Object3D* getSubject() const;
    
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object3D* copy() const;
  virtual Object3D* makeUnique(Path3D* path = NULL, bool shared = false);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual long countSubobject() const;
  virtual Object3D* getSubobject(long index);

protected:  
  virtual void doComputeBounds();

public:
  virtual bool doIntersect(Ray3D& ray);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);
  virtual RCString getKeyword() const;
  void iterateAttributes(MakeableHandler *handler);
  List<Value*>* createParameters();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  // definition of the building
  List<Vector3D>        myVertices;
  List<List<Vector3D> > myHoles;
  Real                  myHeight;
  bool                  myIsOn;

  // objects to composit the building
  List<Object3D*> myObjectList;
  
  // decomposition
  Object3D*       mySubject;
};

//______________________________________________________________________ INLINES

inline const List<Vector3D>& Building::getVertices() const
{
  return myVertices;
}

inline void Building::setVertices(const List<Vector3D>& vertices)
{
  myVertices = vertices;
}

inline void Building::setHeight(Real height)
{
  myHeight = height;
}

inline Real Building::getHeight()const
{
  return myHeight;
}

inline const List<List<Vector3D> >& Building::getHoles() const
{
  return myHoles;
}

inline void Building::removeVertices()
{
  myVertices.removeAll();
}

inline void Building::removeHoles()
{
  myHoles.removeAll();
}

inline long Building::countPolygon() const
{
  return myHoles.count() + 1;
}

inline void  Building::turnOn()
{
  myIsOn = true;
}
 
inline void  Building::turnOff()
{
  myIsOn = false;
}
 
inline bool Building::isOn() const
{
  return myIsOn;
}

#endif // _Building_H



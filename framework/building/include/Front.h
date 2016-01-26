/*
 * $RCSfile: Front.h,v $
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
 *  $Id: Front.h,v 1.4 1997/04/10 12:42:07 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Front_H
#define _Front_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/building/BuildingObject.h"
#include "booga/building/Face.h"

class Building;
class FaceDummy;
class Face;

// ____________________________________________________________________ Front

class Front : public BuildingObject {
declareRTTI(Front);
// enable RTTI support

public:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Front();
  Front(Exemplar exemplar);
  Front(const Front& front);

public:
  virtual ~Front();
  
private:  
  Front& operator=(const Front&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);
  virtual void iterateAttributes(MakeableHandler* handler);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class BuildingObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void subjectChanged() const;
    
private:
  virtual Object3D* createSubject(Building* building) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual long countSubobject() const;
  virtual Object3D* getSubobject(long index);
protected:  
  virtual void doComputeBounds();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Front
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void adoptObject(Object3D* object);
  Object3D* orphanObject(long index); 
  Object3D* getObject(long index) const;    
  
  long getFrontIndex() const;
  void setFrontIndex(long frontindex);

  long getPolygonIndex() const;
  void setPolygonIndex(long polygonindex);

  virtual List<Vector2D> getPointsTop() const=0;
  virtual List<Vector2D> getPointsBottom() const=0;
  List<Vector2D> getFrontPolygon() const;
  virtual bool isFaceInFront(Face* face) const=0;

  void getIndirectFaceObjects(long frontindex, long polygonindex, List<Face*>* facelist) const;  

  long numberOfFaces() const;
  
  void wallOn();
  void wallOff();
  bool isWall() const;
    
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

private:                      // definition of front
  List<Object3D*> myObjectList;         
  long            myFrontIndex;
  long            myPolygonIndex;
  
  bool            myWallFlag;
};

//______________________________________________________________________ INLINES

inline long Front::getFrontIndex() const
{
  return myFrontIndex;
}

inline long Front::getPolygonIndex() const
{
  return myPolygonIndex;
}

inline void Front::wallOn()
{
  myWallFlag = true;
}

inline void Front::wallOff()
{
  myWallFlag = false;
}

inline bool Front::isWall() const
{
  return myWallFlag;
}

#endif // _Front_H


/*
 * $RCSfile: Face.h,v $
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
 *  $Id: Face.h,v 1.2 1997/01/29 18:45:53 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Face_H
#define _Face_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/Vector2D.h"
#include "booga/building/BuildingObject.h"

class Front;

// ____________________________________________________________________ Face

class Face : public BuildingObject {
declareRTTI(Face);
// enable RTTI support

public:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Face();
  Face(Exemplar exemplar);
  Face(const Face& face);

public:
  //virtual ~Face();
  
private:  
  Face& operator=(const Face&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);
  virtual void iterateAttributes(MakeableHandler* handler);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class BuildingObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  virtual Object3D* createSubject(Building* building) const;
public:
  virtual Building* getParentBuilding() const; // should be private:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Friends of class BuildingObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  friend Building* getParentBuilding();
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Face
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  const Vector2D& getFrom() const;
  Vector3D getFromReal(Real x, Real y) const;
  void setFrom(const Vector2D & from);
  
  const Vector2D& getTo() const;
  Vector3D getToReal(Real x, Real y) const;
  void setTo(const Vector2D & to);

  Vector3D getToFromReal(Real x, Real y) const;
  Vector3D getFromToReal(Real x, Real y) const;
  
  Vector3D getElementSize(Real x, Real y) const;
  
  long getColumn() const;
  void setColumn(long column);

  long getRow() const;
  void setRow(long row);

  Real getDepth() const;
  void setDepth(Real depth);

  long getFrontIndex() const;
  void setFrontIndex(long frontindex);

  long getPolygonIndex() const;
  void setPolygonIndex(long polygonindex);

  void setParentFront(Front* front);
  Real getWidth(Building* building) const;
  Vector3D getVertexStart(Building* building) const;
  Vector3D getVertexEnd(Building* building) const;

  // test if the face is filled
  virtual bool isFilled() const=0;
  // alternative holes for a face which is not inside the front
  virtual List<List<Vector3D> > getAlternativeHoles(Building* building) const;
  // appending all generated/indirect faces by other faces 
  virtual void getIndirectFaceObjects(long , long , List<Face*>* ) const {};  
  // test if the face is inside the front
  bool isFaceInFront(Front* front = NULL) const;
   
protected:
  // vertex in local coords
  Vector3D getVertexLocal(Building* building,long frontindex, long polygonindex) const;
  // transformation by the front
  Transform3D getFrontTransform() const;
                           
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Vector2D myFrom;          // definition of face
  Vector2D myTo;
  long     myColumn;     
  long     myRow;
  Real     myDepth;
  
private:                    // parameters from front
  long     myFrontIndex;
  long     myPolygonIndex;
  Front*   myParentFront;
};

//______________________________________________________________________ INLINES


inline void Face::setParentFront(Front* front)
{
  myParentFront = front;
}

inline const Vector2D& Face::getFrom() const
{
  return myFrom;
}

inline Vector3D Face::getFromReal(Real x, Real y) const
{
  return Vector3D(myFrom.x()*x,myFrom.y()*y,0);
}

inline void Face::setFrom(const Vector2D& from)
{
  myFrom = from;
}

inline const Vector2D& Face::getTo() const
{
  return myTo;
}

inline Vector3D Face::getToReal(Real x, Real y) const
{
  return Vector3D(myTo.x()*x,myTo.y()*y,0);
}

inline void Face::setTo(const Vector2D& to)
{
  myTo = to;
}

inline Vector3D Face::getToFromReal(Real x, Real y) const
{
  return Vector3D(myTo.x()*x,myFrom.y()*y,0);
}

inline Vector3D Face::getFromToReal(Real x, Real y) const
{
  return Vector3D(myFrom.x()*x,myTo.y()*y,0);
}

inline long Face::getColumn() const
{
  return myColumn;
}

inline void Face::setColumn(long column) 
{
  myColumn = column < 1 ? 1 : column;
}

inline long Face::getRow() const
{
  return myRow;
}

inline void Face::setRow(long row) 
{
  myRow = row < 1 ? 1 : row;
}

inline Real Face::getDepth() const
{
  return myDepth;
}

inline void Face::setDepth(Real depth)
{
  myDepth = depth;
}

inline Vector3D Face::getElementSize(Real x, Real y) const
{
  return Vector3D(x/(Real)myColumn * (myTo-myFrom).x(),y/(Real)myRow*(myTo-myFrom).y(),0);
}

inline long Face::getFrontIndex() const
{
  return myFrontIndex;
}

inline void Face::setFrontIndex(long frontindex)
{
  myFrontIndex = frontindex;
}

inline long Face::getPolygonIndex() const
{
  return myPolygonIndex;
}

inline void Face::setPolygonIndex(long polygonindex)
{
  myPolygonIndex = polygonindex;
}

#endif // _Face_H


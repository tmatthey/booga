/*
 * $RCSfile: FrontTriangle.h,v $
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
 *  $Id: FrontTriangle.h,v 1.3 1997/02/06 14:13:53 matthey Exp matthey $
 * -----------------------------------------------------------------------------
 */

#ifndef _FrontTriangle_H
#define _FrontTriangle_H

#include "booga/building/Front.h"

// ____________________________________________________________________ FrontTriangle

class FrontTriangle : public Front {
declareRTTI(FrontTriangle);
// enable RTTI support


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  FrontTriangle();
  FrontTriangle(Exemplar exemplar);
  // FrontTriangle(const FrontTriangle& front);     // Use default version.
  FrontTriangle(long frontindex, long polygonindex, const List<Vector2D>& vertices);

public:
  // virtual ~FrontTriangle();                // Use default version.
  
private:  
  FrontTriangle& operator=(const FrontTriangle&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class FrontTriangle
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void addVertex(const Vector2D& vertex);
  const List<Vector2D>& getVertices() const;
  void removeVertices();


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Front
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual List<Vector2D> getPointsTop() const;
  virtual List<Vector2D> getPointsBottom() const;
  virtual bool isFaceInFront(Face* face) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual RCString getKeyword() const;
  virtual List<Value*>* createParameters();
  virtual void iterateAttributes(MakeableHandler* handler);

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
  List<Vector2D>        myVertices;

};

//______________________________________________________________________ INLINES

inline const List<Vector2D>& FrontTriangle::getVertices() const
{
  return myVertices;
}

inline void FrontTriangle::removeVertices()
{
  myVertices.removeAll();
}

#endif // _FrontTriangle_H



